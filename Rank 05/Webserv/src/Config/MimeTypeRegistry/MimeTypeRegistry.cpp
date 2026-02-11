/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MimeTypeRegistry.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:20:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/04 15:20:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MimeTypeRegistry.hpp"
#include "StringUtils.hpp"

MimeTypeRegistry::MimeTypeRegistry()
{
}

MimeTypeRegistry::~MimeTypeRegistry()
{
}

void MimeTypeRegistry::load()
{
	_mimeTypes.clear();
	loadTypesFile("mime.types");
	if (_mimeTypes.empty())
		throw std::runtime_error("mime.types: MIME not defined in " + string(PATH_CONF) + "mime.types");
}

const vector_pair_string &MimeTypeRegistry::getMimeTypes() const
{
	return (_mimeTypes);
}

void MimeTypeRegistry::loadTypesFile(const string &fileName)
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
		handleMimeLine(trimmed);
	}
}

void MimeTypeRegistry::handleMimeLine(const string &line)
{
	std::istringstream iss(line);
	string mimeType;
	iss >> mimeType;
	if (mimeType.empty())
		return;
	for (string ext; iss >> ext;)
	{
		if (!ext.empty() && ext[ext.size() - 1] == ';')
			ext.erase(ext.size() - 1);
		if (!ext.empty())
			_mimeTypes.push_back(pair_string(ext, mimeType));
	}
}
