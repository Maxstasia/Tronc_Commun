/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerAccessor.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:36:38 by mstasiak          #+#    #+#             */
/*   Updated: 2026/02/13 19:04:02 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Location.hpp"

int Server::getPort() const{return _port;}
string Server::getHost() const{return _host;}
string Server::getRoot() const{return _root;}
string Server::getIndex() const{return _index;}
unsigned long Server::getClientMaxBodySize() const{return _client_max_body_size;}
string Server::getServerName() const{return _server_name;}
map_int_string Server::getError() const{return _error;}
const std::vector<Location> &Server::getLocations() const{return _locations;}

Server &Server::setPort(int port)
{
	_port = port;
	return *this;
}

Server &Server::setHost(const string &host)
{
	_host = host;
	return *this;
}

Server & Server::setRoot(const string &root)
{
	_root = root;
	return *this;
}

Server & Server::setIndex(const string &index)
{
	_index = index;
	return *this;
}

Server & Server::setClientMaxBodySize(unsigned long size)
{
	_client_max_body_size = size;
	return *this;
}

Server & Server::setServerName(const string &server_name)
{
	_server_name = server_name;
	return *this;
}

Server & Server::setError(const map_int_string &error)
{
	_error = error;
	return *this;
}

Location &Server::addLocation()
{
	_locations.push_back(Location());
	return _locations.back();
}

/**
 * @brief Trouve la location correspondant le mieux a un URI.
 *
 * Utilise un algorithme de correspondance par prefixe le plus long.
 * Parcourt toutes les locations et retourne celle avec le plus long prefixe correspondant.
 *
 * @param uri L'URI de la requete.
 * @return Pointeur vers la Location correspondante, ou NULL si aucune correspondance.
 */
const Location* Server::matchLocation(const string &uri) const
{
	const Location* best_match = NULL;
	size_t longest_match = 0;

	for (size_t i = 0; i < _locations.size(); ++i)
	{
		const string &path = _locations[i].getPath();
		if (uri.find(path) == 0 && path.size() > longest_match)
		{
			longest_match = path.size();
			best_match = &_locations[i];
		}
	}
	return best_match;
}
