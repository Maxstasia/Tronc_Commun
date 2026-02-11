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
#include <map>

class ClientManager
{
  private:
	std::map<int, Client> _clients;
	EventManager& _eventManager;

  public:
	ClientManager(EventManager& eventManager);
	~ClientManager();

	void acceptNewClient(int server_fd, Server* server);
	void handleClientRead(int fd);
	void handleClientWrite(int fd);
	void handleClientDisconnect(int fd);
	void prepareClientForWriting(int fd);
	void checkTimeouts();

	Client* getClient(int fd);
	bool hasClient(int fd) const;
	std::map<int, Client>& getClients();
};
