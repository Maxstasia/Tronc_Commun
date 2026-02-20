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
	try
	{
		for (size_t i = 0; i < _servers.size(); ++i)
		{
			const std::vector<int> &ports = _servers[i].getPorts();
			for (size_t p = 0; p < ports.size(); ++p)
			{
				int fd = _servers[i].setupServerSocket(ports[p]);
				_servers_fd.push_back(fd);
				_fd_to_server[fd] = &_servers[i];
				_eventManager.addFd(fd, EPOLLIN | EPOLLRDHUP);
			}
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
	else if (event_flag & EPOLLOUT)
		_clientManager.handleCgiPipeWrite(fd);
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
		std::vector<int> &incomplete = _clientManager.getTimedOutIncomplete();
		for (size_t j = 0; j < incomplete.size(); ++j)
		{
			Client *c = _clientManager.getClient(incomplete[j]);
			if (c)
			{
				_requestProcessor.handleIncompleteRequest(*c);
				_clientManager.prepareClientForWriting(incomplete[j]);
			}
		}
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
void ManagerServer::handleClientRdhup(int fd)
{
	Client* client = _clientManager.getClient(fd);
	if (client && client->getRequest().isHeaderFull()
		&& !client->getRequest().isRequestComplete())
	{
		_requestProcessor.handleIncompleteRequest(*client);
		_clientManager.prepareClientForWriting(fd);
		return;
	}
	_clientManager.handleClientDisconnect(fd);
}

void ManagerServer::processCompleteRequest(int fd, Client &client)
{
	_requestProcessor.processRequest(client);
	if (client.isCgiRunning())
	{
		_clientManager.registerCgiPipe(client.getCgiPipeFd(), fd);
		if (client.getCgiWritePipeFd() != -1)
			_clientManager.registerCgiWritePipe(client.getCgiWritePipeFd(), fd);
	}
	else
		_clientManager.prepareClientForWriting(fd);
}

void ManagerServer::handleClientReadEvent(int fd)
{
	_clientManager.handleClientRead(fd);
	Client* client = _clientManager.getClient(fd);
	if (!client)
		return;
	if (_requestProcessor.checkEarlyReceivedSize(*client))
		return _clientManager.prepareClientForWriting(fd);
	if (client->getRequest().isHeaderFull()
		&& !client->getRequest().isRequestComplete()
		&& _requestProcessor.checkEarlyBodySize(*client))
		return _clientManager.prepareClientForWriting(fd);
	if (client->getRequest().isRequestComplete())
		processCompleteRequest(fd, *client);
}

void ManagerServer::handleClientEvent(int fd, uint32_t event_flag)
{
	if (!_clientManager.hasClient(fd))
		return;
	if (event_flag & (EPOLLERR | EPOLLHUP))
		return _clientManager.handleClientDisconnect(fd);
	if (event_flag & EPOLLRDHUP)
		return handleClientRdhup(fd);
	if (event_flag & EPOLLIN)
		handleClientReadEvent(fd);
	else if (event_flag & EPOLLOUT)
		_clientManager.handleClientWrite(fd);
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
	std::map<int, Server*>::iterator it = _fd_to_server.find(server_fd);
	if (it != _fd_to_server.end())
		return it->second;
	return NULL;
}

