/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:19:15 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/01/28 14:59:45 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

 int Server::createSocket() const
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		throw std::runtime_error("Server: socket creation failed");

	int opt = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		close(fd);
		throw std::runtime_error("Server: setsockopt failed");
	}
	return fd;
}

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

int Server::setupServerSocket() const
{
	int fd = createSocket();
	try
	{
		sockaddr_in addr = buildAddress(*this);
		bindAndListen(fd, addr);

		// Mettre le socket en mode non-bloquant pour epoll Edge-Triggered
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
