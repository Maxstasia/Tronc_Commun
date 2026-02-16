/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectiveRegistry.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:25:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/13 19:12:17 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DirectiveRegistry.hpp"
#include "StringUtils.hpp"

DirectiveRegistry::DirectiveRegistry()
{
	load();
}

DirectiveRegistry::~DirectiveRegistry()
{
}

/**
 * @brief Charge les types de directives depuis le fichier de configuration
 *
 * Lit le fichier directives.types et remplit la liste des directives autorisées.
 *
 * @throws std::runtime_error Si aucune directive n'est définie dans le fichier
 */
void DirectiveRegistry::load()
{
	_directiveTypes.clear();
	loadTypesFile("directives.types");
	if (_directiveTypes.empty())
		throw std::runtime_error("directives.types: No directives defined in " + string(PATH_CONF) + "directives.types");
}

/**
 * @brief Retourne la liste des types de directives autorisés
 *
 * @return Référence constante vers le vecteur des types de directives
 */
const vector_string &DirectiveRegistry::getDirectiveTypes() const
{
	return (_directiveTypes);
}

/**
 * @brief Charge un fichier de types de directives
 *
 * Ouvre et parse le fichier spécifié pour extraire les directives définies
 * dans un bloc "types { }".
 *
 * @param fileName Nom du fichier à charger (relatif au répertoire de configuration)
 * @throws std::runtime_error Si le fichier ne peut pas être ouvert
 */
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

/**
 * @brief Traite une ligne de directive du fichier types
 *
 * Retire le point-virgule final si présent et ajoute la directive à la liste.
 *
 * @param line La ligne contenant le nom de la directive
 */
void DirectiveRegistry::handleDirectiveLine(const string &line)
{
	string directive = line;
	if (!directive.empty() && directive[directive.size() - 1] == ';')
		directive.erase(directive.size() - 1);
	if (!directive.empty())
		_directiveTypes.push_back(directive);
}
