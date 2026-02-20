#include "ClientManager.hpp"
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

ClientManager::ClientManager(EventManager& eventManager)
	: _eventManager(eventManager)
{
}

ClientManager::~ClientManager()
{
	std::map<int, Client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->second.isCgiRunning())
		{
			pid_t pid = it->second.getCgiPid();
			if (pid > 0)
			{
				kill(pid, SIGKILL);
				waitpid(pid, NULL, 0);
			}
		}
		close(it->first);
	}
	std::map<int, int>::iterator pipeIt;
	for (pipeIt = _cgiPipeToClient.begin(); pipeIt != _cgiPipeToClient.end(); ++pipeIt)
		close(pipeIt->first);
	_cgiPipeToClient.clear();
	_clients.clear();
}
