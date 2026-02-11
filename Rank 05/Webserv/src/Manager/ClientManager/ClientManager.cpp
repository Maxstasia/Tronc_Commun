/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:10:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/04 16:10:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientManager.hpp"
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <ctime>
#include <iostream>

ClientManager::ClientManager(EventManager& eventManager)
	: _eventManager(eventManager)
{
}

ClientManager::~ClientManager()
{
	std::map<int, Client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
	{
		close(it->first);
	}
	_clients.clear();
}

void ClientManager::acceptNewClient(int server_fd, Server* server)
{
	while (true)
	{
		struct sockaddr_in client_addr;
		socklen_t client_len = sizeof(client_addr);

		int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);

		if (client_fd == -1)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break;
			std::cerr << "Error: " << strerror(errno) << std::endl;
			break;
		}
		std::cout << "New client connected with fd: " << client_fd << std::endl;

		fcntl(client_fd, F_SETFL, O_NONBLOCK);

		Client new_client(client_fd, client_addr);
		new_client.setServer(server);
		_clients.insert(std::make_pair(client_fd, new_client));

		try
		{
			_eventManager.addFd(client_fd, EPOLLIN | EPOLLET | EPOLLRDHUP);
		}
		catch (const std::exception& e)
		{
			std::cerr << "Failed to add client to epoll: " << e.what() << std::endl;
			_clients.erase(client_fd);
			close(client_fd);
		}
	}
}

void ClientManager::handleClientDisconnect(int fd)
{
	std::cerr << "Client disconnected or error on fd: " << fd << std::endl;
	try
	{
		_eventManager.removeFd(fd);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Failed to remove fd from epoll: " << e.what() << std::endl;
	}
	_clients.erase(fd);
	close(fd);
}

void ClientManager::handleClientRead(int fd)
{
	char buffer[SOCKET_BUFFER_SIZE];
	while (true)
	{
		ssize_t count = read(fd, buffer, sizeof(buffer));

		if (count == -1)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break;
			std::cerr << "Read error on fd " << fd << ": " << strerror(errno) << std::endl;
			handleClientDisconnect(fd);
			break;
		}
		else if (count == 0)
		{
			std::cout << "Client disconnected on fd: " << fd << std::endl;
			handleClientDisconnect(fd);
			break;
		}
		else
		{
			std::map<int, Client>::iterator it = _clients.find(fd);
			if (it != _clients.end())
			{
				Client &client = it->second;
				client.updateActivity();
				client.appendRequest(buffer, count);
				std::cout << "Received " << count << " bytes from fd " << fd << std::endl;
			}
		}
	}
}

void ClientManager::handleClientWrite(int fd)
{
	std::map<int, Client>::iterator it = _clients.find(fd);
	if (it != _clients.end())
	{
		Client &client = it->second;
		const std::string &responseStr = client.getResponse().getFinalResponse();

		if (responseStr.empty())
			return;

		size_t total = responseStr.size();
		size_t &sent = client.getBytes();

		ssize_t bytes = send(fd, responseStr.c_str() + sent, total - sent, 0);
		if (bytes == -1)
		{
			if (errno != EAGAIN && errno != EWOULDBLOCK)
			{
				std::cerr << "Send error on fd " << fd << std::endl;
				handleClientDisconnect(fd);
			}
		}
		else
		{
			sent += bytes;
			if (sent >= total)
			{
				std::cout << "Response fully sent to fd " << fd << std::endl;

				if (client.shouldClose())
				{
					handleClientDisconnect(fd);
					return;
				}

				client.reset();

				try
				{
					_eventManager.modifyFd(fd, EPOLLIN | EPOLLET | EPOLLRDHUP);
				}
				catch (const std::exception& e)
				{
					std::cerr << "Failed to modify epoll after send: " << e.what() << std::endl;
				}
			}
		}
	}
}

void ClientManager::prepareClientForWriting(int fd)
{
	try
	{
		_eventManager.modifyFd(fd, EPOLLIN | EPOLLET | EPOLLRDHUP | EPOLLOUT);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Failed to add EPOLLOUT for fd " << fd << ": " << e.what() << std::endl;
	}
}

Client* ClientManager::getClient(int fd)
{
	std::map<int, Client>::iterator it = _clients.find(fd);
	if (it != _clients.end())
		return &(it->second);
	return NULL;
}

bool ClientManager::hasClient(int fd) const
{
	return _clients.find(fd) != _clients.end();
}

std::map<int, Client>& ClientManager::getClients()
{
	return _clients;
}

void ClientManager::checkTimeouts()
{
	time_t now = time(NULL);
	std::vector<int> toDisconnect;

	std::map<int, Client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (now - it->second.getLastActivity() > CLIENT_TIMEOUT_SEC)
			toDisconnect.push_back(it->first);
	}
	for (size_t i = 0; i < toDisconnect.size(); ++i)
	{
		std::cout << "Timeout on fd: " << toDisconnect[i] << std::endl;
		handleClientDisconnect(toDisconnect[i]);
	}
}
