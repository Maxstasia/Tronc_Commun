#pragma once

#include <string>
#include <map>
#include <iostream>
#include "FileUtils.hpp"

class Response {
	private:
		map_str_str _headers;
		string _body;

		int _status;
		string _statusMessage;
		string _httpVersion;
		string _finalResponse;
	
	public:
		Response();
		~Response();
		void setHeader(const string &key, const string &value);
		void setBody(const string &body);
		void setStatus(int code, const string &statusMessage);
		void buildResponse();
		void setHttpVersion(const string &version);
		void stripBodyFromFinalResponse();
		const string &getFinalResponse() const;
		const map_str_str &getHeaders() const;
		string getBody() const;
		int getStatus() const;
		string getStatusMessage() const;
		string getHttpVersion() const;
};
