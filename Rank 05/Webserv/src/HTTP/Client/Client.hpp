#pragma once

#include "Request.hpp"
#include "Response.hpp"
#include "FileUtils.hpp"
#include <netinet/in.h>
#include <ctime>
#include <sys/types.h>

class Server;
class Location;

class Client {
	private:
		int _client_fd;
		struct sockaddr_in _client_addr;
		Request _request; // EPOLLIN
		Response _response; // EPOLLOUT
		size_t _bytes;

		Server* _server;
		const Location* _location;
		bool _shouldClose;
		time_t _lastActivity;

		// CGI state
		pid_t _cgiPid;
		int _cgiPipeFd;
		int _cgiWritePipeFd;
		size_t _cgiBodySent;
		string _cgiOutput;
		time_t _cgiStartTime;
		bool _cgiRunning;

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

		// CGI accessors
		pid_t getCgiPid() const;
		int getCgiPipeFd() const;
		int getCgiWritePipeFd() const;
		size_t &getCgiBodySent();
		string &getCgiOutput();
		time_t getCgiStartTime() const;
		bool isCgiRunning() const;
		void startCgi(pid_t pid, int pipeFd);
		void setCgiWritePipeFd(int fd);
		void appendCgiOutput(const char *data, size_t len);
		void clearCgi();
};
