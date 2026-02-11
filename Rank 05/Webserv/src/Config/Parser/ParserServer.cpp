/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:09:59 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/09 17:34:10 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "StringUtils.hpp"
#include "Validator.hpp"

void Parser::ensureSingleValue(lst_iterator value_it,
	const list_pair_str_int &tokens, const string &error_msg) const
{
	lst_iterator next_it = value_it;
	++next_it;
	if (next_it != tokens.end() && next_it->second == VALUE)
		throw std::runtime_error(error_msg);
}

string Parser::stripTrailingSemicolon(const string &raw) const
{
	if (!raw.empty() && raw[raw.size() - 1] == ';')
		return (raw.substr(0, raw.size() - 1));
	return (raw);
}


void Parser::parseListen(Server &server, lst_iterator &it,
	const list_pair_str_int &tokens) const
{
	const string value = readSingleValue(it, tokens,
			"Parser: Expected value after 'listen' directive",
			"Parser: Unexpected value after value of port directive");

	int port = std::atoi(value.c_str());
	Validator::validatePort(port);
	server.setPort(port);
}

void Parser::parseHost(Server &server, lst_iterator &it,const list_pair_str_int &tokens) const
{
	const string host_value = readSingleValue(it, tokens,"Parser: Expected value after 'host' directive","Parser: Unexpected value after value of host directive");
	Validator::validateIPAddress(host_value);
	server.setHost(host_value);
}

void Parser::parseServerName(Server &server, lst_iterator &it,
	const list_pair_str_int &tokens) const
{
	lst_iterator value_it = expectValue(it, tokens,
			"Parser: Expected value after server_name directive");
	string names;
	lst_iterator walker = value_it;
	while (walker != tokens.end() && walker->second == VALUE)
	{
		names += stripTrailingSemicolon(walker->first) + " ";
		++walker;
	}
	if (!names.empty())
		server.setServerName(names.substr(0, names.size() - 1));
	if (walker != value_it)
	{
		lst_iterator last_value = walker;
		--last_value;
		it = last_value;
	}
	else
		it = value_it;
}

void Parser::parseErrorPage(Server &server, lst_iterator &it,
	const list_pair_str_int &tokens) const
{
	lst_iterator value_it = expectValue(it, tokens,"Parser: Expected value after error_page directive");
	vector_string values;
	lst_iterator walker = value_it;
	while (walker != tokens.end() && walker->second == VALUE)
	{
		values.push_back(stripTrailingSemicolon(walker->first));
		++walker;
	}
	if (values.size() < 2)
		throw std::runtime_error("Parser: error_page needs code and path");
	map_int_string errors = server.getError();
	string path = values.back();
	for (size_t i = 0; i + 1 < values.size(); ++i)
		errors[std::atoi(values[i].c_str())] = path;
	server.setError(errors);
	lst_iterator last = walker;
	--last;
	it = last;
}

void Parser::parseClientMaxBodySize(Server &server, lst_iterator &it,
	const list_pair_str_int &tokens) const
{
	const string value = readSingleValue(it, tokens,
			"Parser: Expected value after client_max_body_size directive",
			"Parser: Unexpected value after value of client_max_body_size directive");

	long size = std::atol(value.c_str());
	const long MAX_BODY_SIZE = 100 * 1024 * 1024;

	if (size < 0)
		throw std::runtime_error("Parser: client_max_body_size must be positive");
	if (size > MAX_BODY_SIZE)
		throw std::runtime_error("Parser: client_max_body_size exceeds maximum limit (100MB)");

	server.setClientMaxBodySize(static_cast<unsigned long>(size));
}

void Parser::checkDuplicateDirective(std::set<string> &seen, const string &directive) const
{
	const string arr[] = {DENINE_DOUBLON};
	const std::set<string> doublons(arr, arr + sizeof(arr) / sizeof(arr[0]));
	if (doublons.find(directive) != doublons.end() && seen.find(directive) != seen.end())
		throw std::runtime_error("Parser: Duplicate directive '" + directive + "'");
	seen.insert(directive);
}


Server Parser::parseServerBlock(lst_iterator &it,
	const list_pair_str_int &tokens) const
{
	Server server;
	std::set<string> seen_directives;

	while (it != tokens.end() && it->first != "server")
	{
		const string &directive = it->first;
		if (directive == "listen")
		{
			checkDuplicateDirective(seen_directives, "listen");
			parseListen(server, it, tokens);
		}
		else if (directive == "host")
		{
			checkDuplicateDirective(seen_directives, "host");
			parseHost(server, it, tokens);
		}
		else if (directive == "server_name")
		{
			checkDuplicateDirective(seen_directives, "server_name");
			parseServerName(server, it, tokens);
		}
		else if (directive == "root")
		{
			checkDuplicateDirective(seen_directives, "root");
			parseRoot(server, it, tokens);
		}
		else if (directive == "index")
		{
			checkDuplicateDirective(seen_directives, "index");
			parseIndex(server, it, tokens);
		}
		else if (directive == "error_page")
		{
			checkDuplicateDirective(seen_directives, "error_page");
			parseErrorPage(server, it, tokens);
		}
		else if (directive == "client_max_body_size")
		{
			checkDuplicateDirective(seen_directives, "client_max_body_size");
			parseClientMaxBodySize(server, it, tokens);
		}
		else if (directive == "location")
			parseLocationBlock(server, it, tokens);
		++it;
	}
	return (server);
}

