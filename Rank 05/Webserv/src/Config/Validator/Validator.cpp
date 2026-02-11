/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Validator.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:10:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/04 15:10:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Validator.hpp"
#include "StringUtils.hpp"

Validator::Validator(const vector_string &directiveTypes, const list_pair_str_int &tokens, int braceCount)
	: _directiveTypes(directiveTypes), _tokens(tokens), _braceCount(braceCount)
{
}

Validator::~Validator()
{
}

void Validator::checkBraceBalance() const
{
	if (_braceCount > 0)
		throw std::runtime_error("Too many opening braces");
	if (_braceCount < 0)
		throw std::runtime_error("Too many closing braces");
}

void Validator::validate()
{
	int			depth;
	lst_iterator	it;
	lst_iterator	next;

	checkBraceBalance();
	validateStartToken(_tokens);
	depth = 0;
	it = _tokens.begin();
	while (it != _tokens.end())
	{
		next = it;
		++next;
		validateSection(it, next);
		validateUrl(it, next);
		validateDirective(it, next);
		validateEmptyBlock(it, next, _tokens.end());
		if (it->second == CURLY_BRACKET_OPEN)
			depth++;
		if (it->second == CURLY_BRACKET_CLOSED)
		{
			depth--;
			if (depth < 0)
				throw std::runtime_error("Unexpected closing brace");
		}
		++it;
	}
	if (depth != 0)
		throw std::runtime_error("Unbalanced braces in config file");
}

void Validator::validateSection(lst_iterator it, lst_iterator next) const
{
	if (it->second != SECTION)
		return ;
	if (!isDirectiveAllowed(it->first))
		throw std::runtime_error("Unknown section '" + it->first + "'");
	if (next == _tokens.end())
		throw std::runtime_error("Section '" + it->first + "' without content");
	if (it->first == "location")
	{
		if (next->second != URL)
			throw std::runtime_error("'location' must be followed by a path");
	}
	else if (next->second != CURLY_BRACKET_OPEN)
		throw std::runtime_error("Section '" + it->first + "' must be followed by '{'");
}

void Validator::validateUrl(lst_iterator it, lst_iterator next) const
{
	if (it->second != URL)
		return ;
	if (next == _tokens.end() || next->second != CURLY_BRACKET_OPEN)
		throw std::runtime_error("URL '" + it->first + "' must be followed by '{'");
}

void Validator::validateDirective(lst_iterator it, lst_iterator next) const
{
	if (it->second != DIRECTIVE)
		return ;
	if (!isDirectiveAllowed(it->first))
		throw std::runtime_error("Unknown directive '" + it->first + "'");
	if (next == _tokens.end() || next->second != VALUE)
		throw std::runtime_error("Directive '" + it->first + "' must have a value");
}

void Validator::validateEmptyBlock(lst_iterator it, lst_iterator next,
	lst_iterator end) const
{
	if (it->second != CURLY_BRACKET_OPEN)
		return ;
	if (next != end && next->second == CURLY_BRACKET_CLOSED)
		throw std::runtime_error("Empty block detected");
}

void Validator::validateStartToken(const list_pair_str_int &lst) const
{
	if (lst.empty())
		return ;
	int firstType = lst.begin()->second;
	if (firstType != SECTION && firstType != COMMENT)
		throw std::runtime_error("Config must start with a section (like 'server')");
}

bool Validator::isDirectiveAllowed(const string &key) const
{
	return (std::find(_directiveTypes.begin(), _directiveTypes.end(),key) != _directiveTypes.end());
}
