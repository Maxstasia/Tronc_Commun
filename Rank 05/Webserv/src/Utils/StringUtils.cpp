/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:30:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/04 14:39:53 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StringUtils.hpp"
#include <sstream>

string StringUtils::trim(const string &s)
{
	string::size_type first = s.find_first_not_of(" \t\r\n");
	if (first == string::npos)
		return ("");
	string::size_type last = s.find_last_not_of(" \t\r\n");
	return (s.substr(first, last - first + 1));
}

string StringUtils::toLower(const string &s)
{
	string result = s;
	for (size_t i = 0; i < result.size(); ++i)
		result[i] = std::tolower(result[i]);
	return result;
}

vector_string StringUtils::split(const string &s, char delim)
{
	vector_string tokens;
	istringstream iss(s);
	string token;
	while (std::getline(iss, token, delim))
		tokens.push_back(token);
	return tokens;
}

string StringUtils::escapeHtml(const string &s)
{
	string result;
	for (size_t i = 0; i < s.size(); ++i)
	{
		if (s[i] == '<')
			result += "&lt;";
		else if (s[i] == '>')
			result += "&gt;";
		else if (s[i] == '&')
			result += "&amp;";
		else if (s[i] == '"')
			result += "&quot;";
		else
			result += s[i];
	}
	return result;
}

string StringUtils::urlEncode(const string &s)
{
	string result;
	const char *hex = "0123456789ABCDEF";
	for (size_t i = 0; i < s.size(); ++i)
	{
		unsigned char c = s[i];
		if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~' || c == '/')
			result += c;
		else
		{
			result += '%';
			result += hex[(c >> 4) & 0x0F];
			result += hex[c & 0x0F];
		}
	}
	return result;
}

string StringUtils::urlDecode(const string &s)
{
	string result;
	for (size_t i = 0; i < s.size(); ++i)
	{
		if (s[i] == '%' && i + 2 < s.size())
		{
			string hex = s.substr(i + 1, 2);
			char c = static_cast<char>(std::strtol(hex.c_str(), NULL, 16));
			result += c;
			i += 2;
		}
		else if (s[i] == '+')
			result += ' ';
		else
			result += s[i];
	}
	return result;
}

StringUtils::StringUtils() {}
StringUtils::StringUtils(const StringUtils &other) { (void)other; }
StringUtils &StringUtils::operator=(const StringUtils &other)
{
	(void)other;
	return *this;
}
StringUtils::~StringUtils() {}
