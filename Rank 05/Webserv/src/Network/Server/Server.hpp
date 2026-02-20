#pragma once

#include "FileUtils.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


class Location;

class Server
{
  private:
	std::vector<int> _ports;
	string _host;
	string _root;
	string _index;
	unsigned long _client_max_body_size;
	string _server_name;
	map_int_string _error;
	std::vector<Location> _locations;

	void clearLocations();

  public:
	Server();
	Server &operator=(const Server &other);
	Server(const Server &other);
	~Server();

	int getPort() const;
	const std::vector<int> &getPorts() const;
	string getHost() const;
	string getRoot() const;
	string getIndex() const;
	unsigned long getClientMaxBodySize() const;
	string getServerName() const;
	map_int_string getError() const;
	const std::vector<Location> &getLocations() const;
	const Location* matchLocation(const string &uri) const;

	//ServerSocket
	int createSocket() const;
	sockaddr_in buildAddress(int port) const;
	void bindAndListen(int fd, const sockaddr_in &addr) const;
	int setupServerSocket(int port) const;

	Server &addPort(int port);
	Server &setHost(const string &host);
	Server &setRoot(const string &root);
	Server &setIndex(const string &index);
	Server &setClientMaxBodySize(unsigned long size);
	Server &setServerName(const string &server_name);
	Server &setError(const map_int_string &error);
	Location &addLocation();
};
