#include "ClientManager.hpp"
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <iostream>

/**
 * @brief Accepte les nouvelles connexions clientes sur un socket serveur.
 *
 * Boucle pour accepter toutes les connexions en attente, configure chaque
 * socket client en mode non-bloquant et close-on-exec, cree un objet Client,
 * et l'enregistre dans epoll en mode EPOLLIN pour detecter les lectures.
 *
 * @param server_fd Le descripteur de fichier du socket serveur.
 * @param server Pointeur vers l'objet Server auquel associer le client.
 * @return Aucune valeur de retour.
 */
void ClientManager::acceptNewClient(int server_fd, Server* server)
{
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);

	int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);

	if (client_fd == -1)
		return;
	fcntl(client_fd, F_SETFL, O_NONBLOCK);
	fcntl(client_fd, F_SETFD, FD_CLOEXEC);

	Client new_client(client_fd, client_addr);
	new_client.setServer(server);
	_clients.insert(std::make_pair(client_fd, new_client));

	try
	{
		_eventManager.addFd(client_fd, EPOLLIN | EPOLLRDHUP);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Failed to add client to epoll: " << e.what() << std::endl;
		_clients.erase(client_fd);
		close(client_fd);
	}
}

/**
 * @brief Gere la deconnexion d'un client.
 *
 * Nettoie le CGI si actif, retire le descripteur d'epoll, supprime le client
 * de la map _clients, et ferme le socket.
 *
 * @param fd Le descripteur de fichier du client a deconnecter.
 * @return Aucune valeur de retour.
 */
void ClientManager::handleClientDisconnect(int fd)
{
	std::map<int, Client>::iterator it = _clients.find(fd);
	if (it == _clients.end())
		return ;
	if (it->second.isCgiRunning())
		cleanupCgi(it->second);
	_eventManager.removeFd(fd);
	_clients.erase(fd);
	close(fd);
}

/**
 * @brief Lit les donnees depuis le socket client.
 *
 * Lit les donnees dans un buffer, les ajoute a la requete du client, gere
 * les deconnexions en cas d'erreur, et met a jour le timestamp d'activite.
 *
 * @param fd Le descripteur de fichier du client.
 * @return Aucune valeur de retour.
 */
void ClientManager::handleClientRead(int fd)
{
	char buffer[SOCKET_BUFFER_SIZE];
	ssize_t count = read(fd, buffer, sizeof(buffer));

	if (count <= 0)
	{
		handleClientDisconnect(fd);
		return;
	}
	std::map<int, Client>::iterator it = _clients.find(fd);
	if (it == _clients.end())
		return;
	Client &client = it->second;
	client.updateActivity();
	client.appendRequest(buffer, count);
}

/**
 * @brief Finalise l'operation d'ecriture d'un client.
 *
 * Si le flag shouldClose est active, deconnecte le client. Sinon, reinitialise
 * l'etat du client pour reutilisation et repasse epoll en mode EPOLLIN.
 *
 * @param fd Le descripteur de fichier du client.
 * @param client Reference vers l'objet Client.
 * @return Aucune valeur de retour.
 */
void ClientManager::finishClientWrite(int fd, Client &client)
{
	if (client.shouldClose())
	{
		handleClientDisconnect(fd);
		return;
	}
	client.reset();
	_eventManager.modifyFd(fd, EPOLLIN | EPOLLRDHUP);
}

/**
 * @brief Envoie les donnees de reponse au client.
 *
 * Envoie la reponse HTTP par le socket, suit le nombre d'octets envoyes,
 * et appelle finishClientWrite quand la reponse complete est envoyee.
 *
 * @param fd Le descripteur de fichier du client.
 * @return Aucune valeur de retour.
 */
void ClientManager::handleClientWrite(int fd)
{
	std::map<int, Client>::iterator it = _clients.find(fd);
	if (it == _clients.end())
		return;
	Client &client = it->second;
	const std::string &responseStr = client.getResponse().getFinalResponse();
	if (responseStr.empty())
		return;
	size_t total = responseStr.size();
	size_t &sent = client.getBytes();
	ssize_t bytes = send(fd, responseStr.c_str() + sent, total - sent, 0);
	if (bytes <= 0)
	{
		handleClientDisconnect(fd);
		return;
	}
	sent += bytes;
	if (sent >= total)
		finishClientWrite(fd, client);
	else
		_eventManager.modifyFd(fd, EPOLLIN | EPOLLRDHUP | EPOLLOUT);
}

/**
 * @brief Prepare le client pour l'ecriture en ajoutant EPOLLOUT.
 *
 * Modifie les evenements epoll du client pour inclure EPOLLOUT afin
 * d'activer la detection de la disponibilite d'ecriture.
 *
 * @param fd Le descripteur de fichier du client.
 * @return Aucune valeur de retour.
 */
void ClientManager::prepareClientForWriting(int fd)
{
	try
	{
		_eventManager.modifyFd(fd, EPOLLIN | EPOLLRDHUP | EPOLLOUT);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Failed to add EPOLLOUT for fd " << fd << ": " << e.what() << std::endl;
	}
}
