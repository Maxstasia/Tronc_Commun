#pragma once

#include "FileUtils.hpp"
#include "Client.hpp"
#include "EventManager.hpp"
#include "CgiHandler.hpp"
#include <map>

class ClientManager
{
  private:
	std::map<int, Client> _clients;
	std::map<int, int> _cgiPipeToClient;
	std::map<int, int> _cgiWritePipeToClient;
	EventManager& _eventManager;
	CgiHandler _cgiHandler;
	std::vector<int> _timedOutIncomplete;

  public:
	ClientManager(EventManager& eventManager);
	~ClientManager();

	void acceptNewClient(int server_fd, Server* server);
	void handleClientRead(int fd);
	void handleClientWrite(int fd);
	void finishClientWrite(int fd, Client &client);
	void handleClientDisconnect(int fd);
	void prepareClientForWriting(int fd);
	void checkTimeouts();
	std::vector<int> &getTimedOutIncomplete();

	void registerCgiPipe(int pipeFd, int clientFd);
	void registerCgiWritePipe(int pipeFd, int clientFd);
	bool isCgiPipe(int fd) const;
	void handleCgiPipeRead(int fd);
	void handleCgiPipeWrite(int fd);
	void handleCgiPipeError(int fd);

	void cleanupCgi(Client &client);
	void handleCgiTimeout(int clientFd);
	Client* getClient(int fd);
	bool hasClient(int fd) const;
	std::map<int, Client>& getClients();
	CgiHandler &getCgiHandler();
};
