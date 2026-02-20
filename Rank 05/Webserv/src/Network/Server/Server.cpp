#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include "Server.hpp"
#include "Location/Location.hpp"

Server::Server() : _host("127.0.0.1"), _root(""), _index("index.html"), _client_max_body_size(1048576){}

Server::Server(const Server &other)
{
	_ports = other._ports;
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
		_ports = other._ports;
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
