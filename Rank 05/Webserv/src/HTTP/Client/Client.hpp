#pragma once

#include "Request.hpp"
#include "Response.hpp"
#include "FileUtils.hpp"
#include <netinet/in.h>
#include <ctime>

class Server;
class Location;

class Client {
	private:
		int _client_fd;
		struct sockaddr_in _client_addr;
		Request _request; // EPOLLIN
		Response _response; // EPOLLOUT
		size_t _bytes;

		// Reference au serveur virtuel qui gere ce client
		Server* _server;
		// Reference a la location matchee pour cette requete
		const Location* _location;
		bool _shouldClose;
		time_t _lastActivity;

	public:
		Client();
		~Client();
		Client(int client_fd, struct sockaddr_in client_addr);

		int getClientFd() const;
		struct sockaddr_in getClientAddr() const;

		Request &getRequest();
		Response &getResponse();
		size_t &getBytes();
		Server* getServer() const;
		const Location* getLocation() const;
		bool shouldClose() const;

		void setServer(Server* server);
		void setLocation(const Location* location);
		void setShouldClose(bool close);
		void updateActivity();
		time_t getLastActivity() const;

		void appendRequest(const char* buffer, size_t size);

		void reset();
		bool isFullySent() const;
};
