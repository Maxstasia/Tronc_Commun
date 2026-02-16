/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ManagerServer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:25:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/01/28 14:59:53 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../../Config/Loader/Loader.hpp"
#include "Client.hpp"
#include "EventManager.hpp"
#include "ClientManager.hpp"
#include "RequestProcessor.hpp"

class ManagerServer
{
	private:
			 Loader _loader;
			 std::vector<Server> _servers;
			 EventManager _eventManager;
			 ClientManager _clientManager;
			 RequestProcessor _requestProcessor;
			 vect_int _servers_fd;

	//ManagerPrint
	void printServers(const std::vector<Server> &servers) const;
	void printServer(const Server &server, size_t index) const;
	void printLocation(const Location &location) const;

	//ManagerServerEventLoop
	void initServerSockets();
	void runEventLoop();
	void handleServerEvent(int fd, uint32_t event_flag);
	void handleClientEvent(int fd, uint32_t event_flag);
	void handleCgiEvent(int fd, uint32_t event_flag);
	void dispatchEvent(int fd, uint32_t event_flag);
	Server* selectServerForClient(int server_fd);

	//ManagerServerAccessor
	vect_int& getServersFd();
	const vect_int& getServersFd() const;
	bool isServerSocket(int fd) const;


	//ManagerServerBuild
	vect_serv buildServers() const;

  public:
	ManagerServer(const string &configPath);
	ManagerServer(const ManagerServer &other);
	ManagerServer &operator=(const ManagerServer &other);
	~ManagerServer();

	void run();
	const std::vector<Server> &getServers() const;
	std::vector<Server> &servers();

};
