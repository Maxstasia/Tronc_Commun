/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectiveRegistry.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:25:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/04 15:25:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DirectiveRegistry.hpp"
#include "StringUtils.hpp"

DirectiveRegistry::DirectiveRegistry()
{
}

DirectiveRegistry::~DirectiveRegistry()
{
}

void DirectiveRegistry::load()
{
	_directiveTypes.clear();
	loadTypesFile("directives.types");
	if (_directiveTypes.empty())
		throw std::runtime_error("directives.types: No directives defined in " + string(PATH_CONF) + "directives.types");
}

const vector_string &DirectiveRegistry::getDirectiveTypes() const
{
	return (_directiveTypes);
}

void DirectiveRegistry::loadTypesFile(const string &fileName)
{
	ifstream	typeFile;
	string		line;
	string		trimmed;
	bool		inBlock = false;

	FileUtils::openFileOrThrow(typeFile, string(PATH_CONF) + fileName);
	while (std::getline(typeFile, line))
	{
		trimmed = StringUtils::trim(line);
		if (trimmed.empty() || trimmed[0] == '#')
			continue;
		if (!inBlock)
		{
			if (trimmed.find("types") != string::npos && trimmed.find('{') != string::npos)
				inBlock = true;
			continue;
		}
		if (trimmed[0] == '}')
			break;
		handleDirectiveLine(trimmed);
	}
}

void DirectiveRegistry::handleDirectiveLine(const string &line)
{
	string directive = line;
	if (!directive.empty() && directive[directive.size() - 1] == ';')
		directive.erase(directive.size() - 1);
	if (!directive.empty())
		_directiveTypes.push_back(directive);
}
