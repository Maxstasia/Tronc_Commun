#include "Response.hpp"
#include <sstream>
#include <ctime>

Response::Response() : _status(200), _statusMessage("OK"), _httpVersion("HTTP/1.1") {}

Response::~Response() {}

void Response::setBody(const string &body) {
	_body = body;
}

void Response::setStatus(int status, const string &statusMessage) {
	_status = status;
	_statusMessage = statusMessage;
}

void Response::setHeader(const string &key, const string &value) {
	_headers[key] = value;
}

void Response::setHttpVersion(const string &version) {
	_httpVersion = version;
}

void Response::stripBodyFromFinalResponse() {
	size_t separator = _finalResponse.find("\r\n\r\n");
	if (separator != string::npos)
		_finalResponse = _finalResponse.substr(0, separator + 4);
}

void Response::buildResponse() {
	stringstream result;

	{
		stringstream result_len;
		result_len << _body.size();
		_headers["Content-Length"] = result_len.str();
	}

	if (_headers.find("Date") == _headers.end())
	{
		time_t now = time(NULL);
		struct tm *gmt = gmtime(&now);
		char buf[64];
		strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S GMT", gmt);
		_headers["Date"] = buf;
	}

	if (_headers.find("Server") == _headers.end())
		_headers["Server"] = "Webserv/1.0";

	if (!_body.empty() && _headers.find("Content-Type") == _headers.end())
		_headers["Content-Type"] = "text/html";

	result << _httpVersion << " " << _status << " " << _statusMessage << "\r\n";
	map_str_str_iterator it;
	for (it = _headers.begin(); it != _headers.end(); ++it)
	{
		result << it->first << ": " << it->second << "\r\n";
	}
	result << "\r\n" << _body;
	_finalResponse = result.str();
}
