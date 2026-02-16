#pragma once

#include <string>
#include <map>
#include <iostream>
#include "FileUtils.hpp"

class Request{
	private:
		string _raw_request;

		string _method; // GET ...etc etc
		string _uri; // chemin sans query string
		string _queryString;
		string _httpVersion;
		string _contentType;
		map_str_str _headers;
		string _body;

		bool _isParsed;
		int _parseError;
		string _parseErrorMessage;
		long _contentLength;
		int _hostCount;

		void setError(int code, const string &message);
		bool parseRequestLine(istringstream &stream);
		bool validateVersion(const string &version);
		void parseHeaders(istringstream &stream);
		bool validateContentLength();
		bool validateHost();
		bool decodeChunkedBody();

	public:
		Request();
		~Request();
		string &getRequest();
		void appendRequest(const char* buffer, size_t size);
		bool isHeaderFull() const;
		bool isRequestComplete() const;
		long getRawContentLength() const;
		void parseRequest();
		string getMethod() const;
		string getUri() const;
		string getQueryString() const;
		string getHttpVersion() const;
		string getBody() const;
		const map_str_str &getHeaders() const;
		bool getIsParsed() const;
		string getContentType() const;
		int getParseError() const;
		string getParseErrorMessage() const;
		long getContentLength() const;
	string getCookie(const string &name) const;
};
