#include "Request.hpp"
#include "StringUtils.hpp"
#include <sstream>
#include <cctype>

static bool isChunkedRaw(const string &raw, size_t header_end)
{
	string lower = StringUtils::toLower(raw.substr(0, header_end));
	size_t pos = lower.find("transfer-encoding:");
	if (pos == string::npos)
		return false;
	size_t line_end = lower.find("\r\n", pos);
	string value = lower.substr(pos + 18, line_end - pos - 18);
	return StringUtils::trim(value) == "chunked";
}

static long extractContentLengthRaw(const string &raw, size_t header_end)
{
	string headers_str = raw.substr(0, header_end);

	string lower = StringUtils::toLower(headers_str);
	size_t cl_pos = lower.find("content-length:");
	if (cl_pos == string::npos)
		return -1;

	size_t value_start = cl_pos + 15;
	size_t line_end = headers_str.find("\r\n", value_start);
	if (line_end == string::npos)
		line_end = headers_str.size();

	string cl_value = StringUtils::trim(
		headers_str.substr(value_start, line_end - value_start));
	if (cl_value.empty())
		return -1;

	istringstream iss(cl_value);
	long content_length = 0;
	iss >> content_length;
	if (iss.fail() || content_length < 0)
		return -1;
	return content_length;
}

bool Request::isHeaderFull() const
{
	return _raw_request.find("\r\n\r\n") != string::npos;
}

bool Request::isRequestComplete() const
{
	size_t header_end = _raw_request.find("\r\n\r\n");
	if (header_end == string::npos)
		return false;

	if (isChunkedRaw(_raw_request, header_end))
		return _raw_request.find("0\r\n\r\n", header_end + 4) != string::npos;

	long cl = extractContentLengthRaw(_raw_request, header_end);
	if (cl < 0)
		return true;

	size_t body_start = header_end + 4;
	size_t body_received = (_raw_request.size() > body_start)
		? _raw_request.size() - body_start : 0;
	return (static_cast<long>(body_received) >= cl);
}

void Request::setError(int code, const string &message)
{
	_parseError = code;
	_parseErrorMessage = message;
	_isParsed = true;
}

bool Request::parseRequestLine(istringstream &stream)
{
	string line;
	if (!std::getline(stream, line))
		return (setError(400, "Bad Request"), false);

	line = StringUtils::trim(line);
	istringstream line_stream(line);
	string method, uri, version;
	line_stream >> method >> uri >> version;

	if (method.empty() || uri.empty())
		return (setError(400, "Bad Request"), false);
	if (version.empty())
	{
		if (method != "GET")
			return (setError(400, "Bad Request"), false);
		version = "HTTP/1.0";
	}
	else
	{
		if (version.size() < 8
			|| version.substr(0, 5) != "HTTP/"
			|| !std::isdigit(version[5])
			|| version[6] != '.'
			|| !std::isdigit(version[7]))
			return (setError(400, "Bad Request"), false);
		if (version != "HTTP/1.0" && version != "HTTP/1.1")
			return (setError(505, "HTTP Version Not Supported"), false);
	}
	if (method != "GET" && method != "HEAD"
		&& method != "POST" && method != "DELETE")
		return (setError(501, "Not Implemented"), false);

	string extra;
	if (line_stream >> extra)
		return (setError(400, "Bad Request"), false);

	_method = method;
	size_t qpos = uri.find('?');
	if (qpos != string::npos)
	{
		_uri = uri.substr(0, qpos);
		_queryString = uri.substr(qpos + 1);
	}
	else
		_uri = uri;
	_httpVersion = version;
	return true;
}

void Request::parseHeaders(istringstream &stream)
{
	string line;
	while (std::getline(stream, line))
	{
		line = StringUtils::trim(line);
		if (line.empty())
			continue;
		size_t colon = line.find(':');
		if (colon != string::npos)
		{
			string key = StringUtils::toLower(
				StringUtils::trim(line.substr(0, colon)));
			string value = StringUtils::trim(line.substr(colon + 1));
			_headers[key] = value;
			if (key == "host")
				_hostCount++;
			if (key == "content-type")
				_contentType = value;
		}
	}
}

bool Request::validateHost()
{
	if (_hostCount > 1)
		return (setError(400, "Bad Request"), false);
	if (_httpVersion == "HTTP/1.1" && _hostCount == 0)
		return (setError(400, "Bad Request"), false);
	return true;
}

void Request::printHeaders() const
{
	std::cout << "=== Request Headers ===" << std::endl;
	std::cout << _method << " " << _uri << " " << _httpVersion << std::endl;
	map_str_str::const_iterator it = _headers.begin();
	for (; it != _headers.end(); ++it)
		std::cout << it->first << ": " << it->second << std::endl;
	if (!_body.empty())
		std::cout << "Body: " << _body << std::endl;
	std::cout << "=======================" << std::endl;
}

bool Request::validateContentLength()
{
	map_str_str::iterator it = _headers.find("content-length");
	if (it == _headers.end())
		return true;

	istringstream cl_ss(it->second);
	cl_ss >> _contentLength;
	if (cl_ss.fail() || _contentLength < 0)
		return (setError(400, "Bad Request"), false);

	if (_body.size() > static_cast<size_t>(_contentLength))
		_body = _body.substr(0, _contentLength);
	return true;
}

bool Request::decodeChunkedBody()
{
	string decoded;
	size_t pos = 0;

	while (pos < _body.size())
	{
		size_t crlf = _body.find("\r\n", pos);
		if (crlf == string::npos)
			return false;
		string hex_str = _body.substr(pos, crlf - pos);
		unsigned long chunk_size = 0;
		istringstream iss(hex_str);
		iss >> std::hex >> chunk_size;
		if (iss.fail())
			return false;
		if (chunk_size == 0)
			break;
		size_t data_start = crlf + 2;
		if (data_start + chunk_size > _body.size())
			return false;
		decoded.append(_body, data_start, chunk_size);
		pos = data_start + chunk_size + 2;
	}
	_body = decoded;
	return true;
}

void Request::parseRequest()
{
	if (_isParsed)
		return;

	size_t header_end = _raw_request.find("\r\n\r\n");
	if (header_end == string::npos)
		return;

	string headers = _raw_request.substr(0, header_end);
	if (_raw_request.size() > header_end + 4)
		_body = _raw_request.substr(header_end + 4);

	istringstream stream(headers);

	if (!parseRequestLine(stream))
		return;
	parseHeaders(stream);
	if (!validateHost())
		return;
	map_str_str::iterator te = _headers.find("transfer-encoding");
	if (te != _headers.end() && te->second == "chunked")
	{
		if (!decodeChunkedBody())
			return (setError(400, "Bad Request"));
	}
	else if (!validateContentLength())
		return;
	if (_method == "GET" || _method == "HEAD" || _method == "DELETE")
		_body.clear();
	_isParsed = true;
}
