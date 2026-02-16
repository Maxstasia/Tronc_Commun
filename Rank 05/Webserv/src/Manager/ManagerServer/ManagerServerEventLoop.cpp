/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ManagerServerEventLoop.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:08:12 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/15 15:52:02 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ManagerServer.hpp"
#include "../../Network/Server/Location/Location.hpp"


/**
 * @brief Initialise les sockets d'ecoute pour chaque serveur configure.
 *
 * Pour chaque objet Server, cree un socket TCP (bind + listen) puis
 * l'enregistre dans epoll en mode EPOLLIN pour detecter les nouvelles
 * connexions entrantes. En cas d'erreur, ferme tous les sockets deja
 * ouverts avant de propager l'exception.
 *
 * @return Aucune valeur de retour. Les fd sont stockes dans _servers_fd
 * 	et enregistres dans _eventManager.
 */
void ManagerServer::initServerSockets()
{
	_servers_fd.reserve(_servers.size());

	try
	{
		for (size_t i = 0; i < _servers.size(); ++i)
		{
			_servers_fd.push_back(_servers[i].setupServerSocket());
			_eventManager.addFd(_servers_fd.back(), EPOLLIN | EPOLLRDHUP);
		}
	}
	catch (...)
	{
		for (size_t j = 0; j < _servers_fd.size(); ++j)
			close(_servers_fd[j]);
		throw;
	}
}

/**
 * @brief Gere les evenements lies aux pipes CGI.
 *
 * Traite les evenements EPOLLERR (via handleCgiPipeError) et
 * EPOLLIN/EPOLLHUP (via handleCgiPipeRead) pour les pipes de
 * communication avec les processus CGI.
 *
 * @param fd Le descripteur de fichier du pipe CGI.
 * @param event_flag Les drapeaux d'evenements epoll.
 * @return Aucune valeur de retour.
 */
void ManagerServer::handleCgiEvent(int fd, uint32_t event_flag)
{
	if (event_flag & EPOLLERR)
		_clientManager.handleCgiPipeError(fd);
	else if (event_flag & (EPOLLIN | EPOLLHUP))
		_clientManager.handleCgiPipeRead(fd);
}

/**
 * @brief Dispatche les evenements vers le gestionnaire approprie.
 *
 * Determine le type de descripteur (socket serveur, pipe CGI, ou socket client)
 * et route l'evenement vers la fonction de traitement correspondante.
 *
 * @param fd Le descripteur de fichier ayant declenche l'evenement.
 * @param event_flag Les drapeaux d'evenements epoll.
 * @return Aucune valeur de retour.
 */
void ManagerServer::dispatchEvent(int fd, uint32_t event_flag)
{
	if (isServerSocket(fd))
		handleServerEvent(fd, event_flag);
	else if (_clientManager.isCgiPipe(fd))
		handleCgiEvent(fd, event_flag);
	else
		handleClientEvent(fd, event_flag);
}

/**
 * @brief Boucle principale de traitement des evenements epoll.
 *
 * Utilise epoll_wait pour attendre les evenements avec un timeout,
 * verifie les timeouts des clients, puis traite chaque evenement recu
 * jusqu'a reception d'une interruption (EINTR).
 *
 * @return Aucune valeur de retour.
 * @throws std::runtime_error Si epoll_wait echoue pour une autre raison que EINTR.
 */
void ManagerServer::runEventLoop()
{
	struct epoll_event events[EPOLL_MAX_EVENTS];

	while (!g_shutdown)
	{
		int nfds = _eventManager.waitEvents(events, EPOLL_MAX_EVENTS,
			EPOLL_TIMEOUT_MS);
		if (nfds == -1)
		{
			if (errno == EINTR)
				continue;
			throw std::runtime_error("epoll_wait failed");
		}
		_clientManager.checkTimeouts();
		if (nfds == 0)
			continue;
		for (int i = 0; i < nfds; i++)
			dispatchEvent(events[i].data.fd, events[i].events);
	}
}

/**
 * @brief Gere les evenements sur les sockets d'ecoute des serveurs.
 *
 * Traite les evenements EPOLLIN (nouvelle connexion entrante) en selectionnant
 * le serveur correspondant et en deleguant l'acceptation au ClientManager.
 *
 * @param fd Le descripteur de fichier du socket serveur.
 * @param event_flag Les drapeaux d'evenements epoll.
 * @return Aucune valeur de retour.
 */
void ManagerServer::handleServerEvent(int fd, uint32_t event_flag)
{
	if (event_flag & EPOLLIN)
	{
		Server* server = selectServerForClient(fd);
		if (!server)
			return;
		_clientManager.acceptNewClient(fd, server);
	}
}

/**
 * @brief Gere les evenements sur les sockets clients.
 *
 * Traite les deconnexions (EPOLLERR/EPOLLHUP/EPOLLRDHUP), les lectures (EPOLLIN)
 * avec verification precoce de la taille du corps, le traitement des requetes
 * completes (incluant CGI), et les ecritures (EPOLLOUT).
 *
 * @param fd Le descripteur de fichier du socket client.
 * @param event_flag Les drapeaux d'evenements epoll.
 * @return Aucune valeur de retour.
 */
void ManagerServer::handleClientEvent(int fd, uint32_t event_flag)
{
	if (event_flag & (EPOLLERR | EPOLLHUP | EPOLLRDHUP))
	{
		_clientManager.handleClientDisconnect(fd);
		return;
	}

	if (event_flag & EPOLLIN)
	{
		_clientManager.handleClientRead(fd);
		Client* client = _clientManager.getClient(fd);
		if (!client)
			return;
		if (client->getRequest().isHeaderFull()
			&& !client->getRequest().isRequestComplete()
			&& _requestProcessor.checkEarlyBodySize(*client))
		{
			_clientManager.prepareClientForWriting(fd);
			return;
		}
		if (client->getRequest().isRequestComplete())
		{
			_requestProcessor.processRequest(*client);
			if (client->isCgiRunning())
				_clientManager.registerCgiPipe(client->getCgiPipeFd(), fd);
			else
				_clientManager.prepareClientForWriting(fd);
		}
	}

	if (event_flag & EPOLLOUT)
	{
		_clientManager.handleClientWrite(fd);
	}
}

/**
 * @brief Selectionne l'objet Server correspondant a un descripteur de socket serveur.
 *
 * Parcourt les vecteurs _servers_fd et _servers pour trouver et retourner
 * un pointeur vers le serveur correspondant au server_fd donne.
 *
 * @param server_fd Le descripteur de fichier du socket serveur.
 * @return Pointeur vers l'objet Server correspondant, ou NULL si non trouve.
 */
Server* ManagerServer::selectServerForClient(int server_fd)
{
	for (size_t i = 0; i < _servers_fd.size(); ++i)
	{
		if (_servers_fd[i] == server_fd)
			return &_servers[i];
	}
	return NULL;
}

