/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ManagerServerEventLoop.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:08:12 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/04 09:42:02 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ManagerServer.hpp"
#include "../../Network/Server/Location/Location.hpp"


void ManagerServer::initServerSockets()
{
	_servers_fd.reserve(_servers.size());

	try
	{
		for (size_t i = 0; i < _servers.size(); ++i)
		{
			_servers_fd.push_back(_servers[i].setupServerSocket());
			_eventManager.addFd(_servers_fd.back(), EPOLLIN | EPOLLET | EPOLLRDHUP);
		}
	}
	catch (...)
	{
		for (size_t j = 0; j < _servers_fd.size(); ++j)
			close(_servers_fd[j]);
		throw;
	}
}

void ManagerServer::runEventLoop()
{
	struct epoll_event events[EPOLL_MAX_EVENTS];

	while (true)
	{
		int nfds = _eventManager.waitEvents(events, EPOLL_MAX_EVENTS, EPOLL_TIMEOUT_MS);

		if (nfds == -1)
		{
			if (errno == EINTR)
				break;
			throw std::runtime_error("epoll_wait failed");
		}

		_clientManager.checkTimeouts();

		if (nfds == 0)
			continue;

		for (int i = 0; i < nfds; i++)
		{
			int fd = events[i].data.fd;
			uint32_t event_flag = events[i].events;

			if (isServerSocket(fd))
				handleServerEvent(fd, event_flag);
			else
				handleClientEvent(fd, event_flag);
		}
	}
}

void ManagerServer::handleServerEvent(int fd, uint32_t event_flag)
{
	if (event_flag & EPOLLIN)
	{
		Server* server = selectServerForClient(fd);
		_clientManager.acceptNewClient(fd, server);
	}
}

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
		if (client && client->getRequest().isRequestComplete())
		{
			_requestProcessor.processRequest(*client);
			_clientManager.prepareClientForWriting(fd);
		}
	}

	if (event_flag & EPOLLOUT)
		_clientManager.handleClientWrite(fd);
}

// ====== FONCTIONS UTILITAIRES POUR runEventLoop ======

Server* ManagerServer::selectServerForClient(int server_fd)
{
	for (size_t i = 0; i < _servers_fd.size(); ++i)
	{
		if (_servers_fd[i] == server_fd)
			return &_servers[i];
	}
	return NULL;
}

