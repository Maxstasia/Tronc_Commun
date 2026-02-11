/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestAccessor.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/11 11:37:58 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

string &Request::getRequest(){
	return (_raw_request);
}

string Request::getMethod() const {
	return _method;
}

string Request::getUri() const {
	return _uri;
}

string Request::getQueryString() const {
	return _queryString;
}

string Request::getHttpVersion() const {
	return _httpVersion;
}

string Request::getBody() const {
	return _body;
}

const map_str_str &Request::getHeaders() const {
	return _headers;
}

bool Request::getIsParsed() const {
	return _isParsed;
}
string Request::getContentType() const
{
	return _contentType;
}

int Request::getParseError() const
{
	return _parseError;
}

string Request::getParseErrorMessage() const
{
	return _parseErrorMessage;
}

long Request::getContentLength() const
{
	return _contentLength;
}

string Request::getCookie(const string &name) const
{
	map_str_str::const_iterator it = _headers.find("cookie");
	if (it == _headers.end())
		return "";
	
	string cookies = it->second;
	size_t pos = 0;
	
	while (pos < cookies.length())
	{
		size_t eq = cookies.find('=', pos);
		if (eq == string::npos)
			break;
		
		size_t semi = cookies.find(';', eq);
		if (semi == string::npos)
			semi = cookies.length();
		
		string cookieName = cookies.substr(pos, eq - pos);
		// Trim spaces
		size_t start = cookieName.find_first_not_of(" \t");
		size_t end = cookieName.find_last_not_of(" \t");
		if (start != string::npos)
			cookieName = cookieName.substr(start, end - start + 1);
		
		if (cookieName == name)
		{
			string value = cookies.substr(eq + 1, semi - eq - 1);
			// Trim spaces
			start = value.find_first_not_of(" \t");
			end = value.find_last_not_of(" \t");
			if (start != string::npos)
				return value.substr(start, end - start + 1);
			return value;
		}
		
		pos = semi + 1;
	}
	
	return "";
}
