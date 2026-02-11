/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:00:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/04 15:00:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tokenizer.hpp"
#include "StringUtils.hpp"

Tokenizer::Tokenizer(const string &configFile) : _configFile(configFile), _braceCount(0)
{
}

Tokenizer::~Tokenizer()
{
}

Tokenizer::Tokenizer(const Tokenizer &other) : _configFile(other._configFile), _braceCount(other._braceCount), _tokens(other._tokens)
{
}

Tokenizer &Tokenizer::operator=(const Tokenizer &other)
{
	if (this != &other)
	{
		_configFile = other._configFile;
		_braceCount = other._braceCount;
		_tokens = other._tokens;
	}
	return (*this);
}

list_pair_str_int Tokenizer::tokenize()
{
	string			line;
	ifstream		in;
	vector_string	tokens;

	_braceCount = 0;
	_tokens.clear();
	FileUtils::openFileOrThrow(in, _configFile);
	while (std::getline(in, line))
	{
		tokens = trimLine(line);
		if (tokens.empty())
			continue ;
		if (parseLocation(tokens))
			continue ;
		if (parseSection(tokens))
			continue ;
		if (parseOpenBrace(tokens, 0))
			continue ;
		if (parseCloseBrace(tokens))
			continue ;
		if (parseComment(tokens))
			continue ;
		parseDirective(tokens);
	}
	return (_tokens);
}

const list_pair_str_int &Tokenizer::getTokens() const
{
	return (_tokens);
}

bool Tokenizer::parseSection(const vector_string &tokens)
{
	pair_str_int	tmp;

	if (tokens.size() < 2 || tokens[1] != "{")
		return (false);
	tmp.first = tokens[0];
	tmp.second = SECTION;
	_tokens.push_back(tmp);
	parseOpenBrace(tokens, 1);
	return (true);
}

bool Tokenizer::parseCloseBrace(const vector_string &tokens)
{
	pair_str_int	tmp;

	if (tokens[0] != "}")
		return (false);
	tmp.first = tokens[0];
	tmp.second = CURLY_BRACKET_CLOSED;
	_tokens.push_back(tmp);
	_braceCount--;
	return (true);
}

bool Tokenizer::parseOpenBrace(const vector_string &tokens, int index)
{
	pair_str_int	tmp;

	if (tokens[index] != "{")
		return (false);
	tmp.first = tokens[index];
	tmp.second = CURLY_BRACKET_OPEN;
	_tokens.push_back(tmp);
	_braceCount++;
	return (true);
}

bool Tokenizer::parseComment(const vector_string &tokens)
{
	pair_str_int	tmp;

	if (tokens[0].empty() || tokens[0][0] != '#')
		return (false);
	tmp.first = tokens[0];
	tmp.second = COMMENT;
	_tokens.push_back(tmp);
	return (true);
}

void Tokenizer::parseDirective(const vector_string &tokens)
{
	pair_str_int	tmp;

	tmp.first = tokens[0];
	tmp.second = DIRECTIVE;
	_tokens.push_back(tmp);
	for (size_t i = 1; i < tokens.size(); ++i)
	{
		tmp.first = tokens[i];
		tmp.second = VALUE;
		_tokens.push_back(tmp);
	}
}

vector_string Tokenizer::trimLine(const string &line)
{
	vector_string	raw;
	vector_string	tokens;

	raw = StringUtils::split(line, ' ');
	for (vector_string::const_iterator it = raw.begin(); it != raw.end(); ++it)
	{
		string cleaned = StringUtils::trim(*it);
		if (!cleaned.empty())
			tokens.push_back(cleaned);
	}
	return (tokens);
}

bool Tokenizer::parseLocation(const vector_string &tokens)
{
	pair_str_int	tmp;

	if (tokens[0] != "location" || tokens.size() < 3)
		return (false);
	tmp.first = tokens[0];
	tmp.second = SECTION;
	_tokens.push_back(tmp);
	tmp.first = tokens[1];
	tmp.second = URL;
	_tokens.push_back(tmp);
	parseOpenBrace(tokens, 2);
	return (true);
}
