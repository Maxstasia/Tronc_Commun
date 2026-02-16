/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:19:15 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/13 19:04:02 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/**
 * @brief Cree un socket TCP et configure les options de base.
 *
 * Cree un socket TCP, definit FD_CLOEXEC et SO_REUSEADDR. Leve une
 * exception en cas d'echec.
 *
 * @return Le descripteur de fichier du socket cree.
 * @throws std::runtime_error Si la creation du socket ou setsockopt echoue.
 */
 int Server::createSocket() const
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		throw std::runtime_error("Server: socket creation failed");
	fcntl(fd, F_SETFD, FD_CLOEXEC);

	int opt = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		close(fd);
		throw std::runtime_error("Server: setsockopt failed");
	}
	return fd;
}

/**
 * @brief Construit une structure sockaddr_in a partir de la configuration du serveur.
 *
 * Gere les cas speciaux : empty/"*" -> INADDR_ANY, "localhost" -> 127.0.0.1.
 * Valide l'adresse IP avec inet_pton.
 *
 * @param server L'objet Server contenant la configuration.
 * @return La structure sockaddr_in construite.
 * @throws std::runtime_error Si l'adresse IP est invalide.
 */
sockaddr_in Server::buildAddress(const Server &server) const
{
	struct sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(server.getPort());

	// Gérer les cas spéciaux
	if (server.getHost().empty() || server.getHost() == "*")
		addr.sin_addr.s_addr = INADDR_ANY;
	else if (server.getHost() == "localhost")
		addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // 127.0.0.1
	else if (inet_pton(AF_INET, server.getHost().c_str(), &addr.sin_addr) != 1)
		throw std::runtime_error("Server: invalid listen host " + server.getHost());

	return addr;
}

/**
 * @brief Lie le socket a l'adresse et demarre l'ecoute.
 *
 * Appelle bind() avec l'adresse fournie et listen() avec SOMAXCONN.
 * Ferme le socket et leve une exception en cas d'echec.
 *
 * @param fd Le descripteur de fichier du socket.
 * @param addr La structure sockaddr_in d'adresse.
 * @return Aucune valeur de retour.
 * @throws std::runtime_error Si bind ou listen echoue.
 */
void Server::bindAndListen(int fd, const sockaddr_in &addr) const
{
	if (bind(fd, reinterpret_cast<const struct sockaddr*>(&addr), sizeof(addr)) == -1)
	{
		close(fd);
		throw std::runtime_error("Server: bind failed");
	}
	if (listen(fd, SOMAXCONN) == -1)
	{
		close(fd);
		throw std::runtime_error("Server: listen failed");
	}
}

/**
 * @brief Configuration complete du socket serveur.
 *
 * Cree le socket, le lie, demarre l'ecoute, et le met en mode non-bloquant.
 * Assure le nettoyage en cas d'exception.
 *
 * @return Le descripteur de fichier du socket pret.
 * @throws std::runtime_error En cas d'echec a n'importe quelle etape.
 */
int Server::setupServerSocket() const
{
	int fd = createSocket();
	try
	{
		sockaddr_in addr = buildAddress(*this);
		bindAndListen(fd, addr);

		if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
		{
			close(fd);
			throw std::runtime_error("Server: fcntl O_NONBLOCK failed");
		}
	}
	catch (...)
	{
		close(fd);
		throw;
	}
	return fd;
}
