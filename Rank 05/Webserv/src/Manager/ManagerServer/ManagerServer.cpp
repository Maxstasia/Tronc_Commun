#include "ManagerServer.hpp"

ManagerServer::ManagerServer(const std::string &configPath)
	: _loader(configPath), _servers(buildServers()), _clientManager(_eventManager)
{
}

/**
 * @brief Lance le serveur web et demarre la boucle evenementielle.
 *
 * Initialise le gestionnaire d'evenements, configure le processeur de requetes,
 * initialise les sockets d'ecoute, affiche la configuration des serveurs et
 * demarre la boucle principale de traitement des evenements.
 *
 * @return Aucune valeur de retour.
 */
void ManagerServer::run()
{
	_eventManager.initialize();
	_requestProcessor.setLoader(&_loader);
	_requestProcessor.setServers(&_servers);
	initServerSockets();
	printServers(_servers);
	runEventLoop();
}

ManagerServer::ManagerServer(const ManagerServer &other)
	: _loader(other._loader), _servers(other._servers), _clientManager(_eventManager)
{
}

ManagerServer &ManagerServer::operator=(const ManagerServer &other)
{
	if (this != &other)
	{
		_loader = other._loader;
		_servers = other._servers;
	}
	return (*this);
}

ManagerServer::~ManagerServer()
{
	for (size_t i = 0; i < _servers_fd.size(); ++i)
		close(_servers_fd[i]);
}

const std::vector<Server> &ManagerServer::getServers() const
{
	return (_servers);
}

std::vector<Server> &ManagerServer::servers()
{
	return (_servers);
}
