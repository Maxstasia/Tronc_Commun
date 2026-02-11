/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientAccessor.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include "Location.hpp"

int Client::getClientFd() const {
	return _client_fd;
}

struct sockaddr_in Client::getClientAddr() const {
	return _client_addr;
}

Request &Client::getRequest(){
	return (_request);
}

Response &Client::getResponse() {
	return (_response);
}

size_t &Client::getBytes() {
	return (_bytes);
}

Server* Client::getServer() const {
	return _server;
}

const Location* Client::getLocation() const {
	return _location;
}

void Client::setServer(Server* server) {
	_server = server;
}

void Client::setLocation(const Location* location) {
	_location = location;
}

bool Client::shouldClose() const {
	return _shouldClose;
}

void Client::setShouldClose(bool close) {
	_shouldClose = close;
}

void Client::updateActivity() {
	_lastActivity = time(NULL);
}

time_t Client::getLastActivity() const {
	return _lastActivity;
}
