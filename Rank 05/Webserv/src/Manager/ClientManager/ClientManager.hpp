/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:10:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/04 16:10:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	EventManager& _eventManager;
	CgiHandler _cgiHandler;

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

	void registerCgiPipe(int pipeFd, int clientFd);
	bool isCgiPipe(int fd) const;
	void handleCgiPipeRead(int fd);
	void handleCgiPipeError(int fd);

	void cleanupCgi(Client &client);
	void handleCgiTimeout(int clientFd);
	Client* getClient(int fd);
	bool hasClient(int fd) const;
	std::map<int, Client>& getClients();
	CgiHandler &getCgiHandler();
};
