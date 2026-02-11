#include "Request.hpp"

Request::Request() : _isParsed(false), _parseError(0), _contentLength(-1),
	_hostCount(0) {}

Request::~Request() {}

void Request::appendRequest(const char* buffer, size_t size)
{
	_raw_request.append(buffer, size);
}
