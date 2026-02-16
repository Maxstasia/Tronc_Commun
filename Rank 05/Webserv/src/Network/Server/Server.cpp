#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 12:53:28 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/01/21 09:54:43 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Location/Location.hpp"

Server::Server() : _port(8080), _host("127.0.0.1"), _root(""), _index("index.html"), _client_max_body_size(1048576){}

Server::Server(const Server &other)
{
	_port = other._port;
	_host = other._host;
	_root = other._root;
	_index = other._index;
	_client_max_body_size = other._client_max_body_size;
	_server_name = other._server_name;
	_error = other._error;
	_locations = other._locations;
}

Server &Server::operator=(const Server &other)
{
	if (this != &other)
	{
		clearLocations();
		_port = other._port;
		_host = other._host;
		_root = other._root;
		_index = other._index;
		_client_max_body_size = other._client_max_body_size;
		_server_name = other._server_name;
		_error = other._error;
		_locations = other._locations;
	}
	return (*this);
}

Server::~Server()
{
	clearLocations();
}

/**
 * @brief Efface toutes les locations du serveur.
 *
 * Vide le vecteur _locations.
 *
 * @return Aucune valeur de retour.
 */
void Server::clearLocations()
{
	_locations.clear();
}
