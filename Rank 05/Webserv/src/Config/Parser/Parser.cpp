/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:03:14 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/01/26 10:44:55 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "Location.hpp"
#include "Validator.hpp"

Parser::Parser()
{}

Parser::Parser(const Parser &other)
{
	(void)other;
}

Parser &Parser::operator=(const Parser &other)
{
	if (this != &other)
	{
		(void)other;
	}
	return (*this);
}

Parser::~Parser()
{}


std::vector<Server> Parser::parseServers(const list_pair_str_int &tokens)
{
	std::vector<Server> servers;
	if (tokens.empty())
		throw std::runtime_error("Parser: No tokens to parse");
	lst_iterator it = tokens.begin();
	while (it != tokens.end())
	{
		if (it->first == "server")
		{
			++it;
			if (it == tokens.end())
				throw std::runtime_error("Parser: Empty server block");
			servers.push_back(Parser().parseServerBlock(it, tokens));
			continue ;
		}
		++it;
	}
	return (servers);
}

lst_iterator Parser::expectValue(lst_iterator directive_it, const list_pair_str_int &tokens, const string &error_msg) const
{
	lst_iterator value_it = directive_it;
	++value_it;
	if (value_it == tokens.end() || value_it->second != VALUE)
		throw std::runtime_error(error_msg);
	return value_it;
}

void Parser::parseRoot(Server &server, lst_iterator &it, const list_pair_str_int &tokens) const
{
	const string root_path = readSingleValue(it, tokens, "Parser: Expected value after root directive", "Parser: Unexpected value after value of root directive");
	Validator::validatePath(root_path, "root");
	server.setRoot(root_path);
}

string Parser::readSingleValue(lst_iterator &it, const list_pair_str_int &tokens, const string &missing_msg, const string &extra_msg) const
{
	lst_iterator value_it = expectValue(it, tokens, missing_msg);
	ensureSingleValue(value_it, tokens, extra_msg);
	it = value_it;
	return stripTrailingSemicolon(value_it->first);
}

void Parser::parseLocationBlock(Server &server, lst_iterator &it, const list_pair_str_int &tokens) const
{
	if (it == tokens.end())
		throw std::runtime_error("Parser: Malformed location directive (missing path)");
	++it;
	if (it == tokens.end() || it->second != URL)
		throw std::runtime_error("Parser: Expected location path after 'location'");
	Location &location = server.addLocation();
	location.setPath(it->first);
	++it;
	if (it == tokens.end() || it->second != CURLY_BRACKET_OPEN)
		throw std::runtime_error("Parser: Expected '{' after location path");

	std::set<string> seen_directives;
	int depth = 0;
	for (++it; it != tokens.end(); ++it)
	{
		if (it->second == CURLY_BRACKET_OPEN)
		{
			++depth;
			continue;
		}
		if (it->second == CURLY_BRACKET_CLOSED)
		{
			if (depth == 0)
				break;
			--depth;
			continue;
		}
		if (it->second == DIRECTIVE)
		{
			const string &directive = it->first;
			if (directive != "allow_methods")
				checkDuplicateDirective(seen_directives, directive);
			parseLocationDirective(location, it, tokens);
		}
	}
	if (it == tokens.end())
		throw std::runtime_error("Parser: Unterminated location block");
}


void Parser::parseIndex(Server &server, lst_iterator &it, const list_pair_str_int &tokens) const
{
	const string index_path = readSingleValue(it, tokens, "Parser: Expected value after index directive", "Parser: Unexpected value after value of index directive");
	Validator::validatePath(index_path, "index");
	server.setIndex(index_path);
}

