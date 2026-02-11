#include "Client.hpp"

Client::Client() : _client_fd(-1), _bytes(0), _server(NULL), _location(NULL), _shouldClose(false), _lastActivity(time(NULL)) {}

Client::Client(int client_fd, struct sockaddr_in client_addr)
	: _client_fd(client_fd), _client_addr(client_addr), _bytes(0), _server(NULL), _location(NULL), _shouldClose(false), _lastActivity(time(NULL)) {}

Client::~Client() {}

void Client::appendRequest(const char* buffer, size_t size) {
	_request.appendRequest(buffer, size);
}

void Client::reset() {
	_request = Request();
	_response = Response();
	_bytes = 0;
	_location = NULL;
	_shouldClose = false;
	_lastActivity = time(NULL);
}

bool Client::isFullySent() const {
	return (_response.getFinalResponse().empty() == false && _bytes >= _response.getFinalResponse().size());
}
