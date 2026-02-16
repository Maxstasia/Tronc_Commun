/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:09:59 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/13 19:11:22 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "StringUtils.hpp"
#include "Validator.hpp"

/**
 * @brief Assure qu'une seule valeur suit une directive
 *
 * Vérifie qu'après la valeur actuelle, il n'y a pas d'autres valeurs consécutives.
 *
 * @param value_it Itérateur pointant sur la première valeur
 * @param tokens Liste complète des tokens
 * @param error_msg Message d'erreur à afficher s'il y a plusieurs valeurs
 * @throws std::runtime_error Si plusieurs valeurs sont détectées
 */
void Parser::ensureSingleValue(lst_iterator value_it,
	const list_pair_str_int &tokens, const string &error_msg) const
{
	lst_iterator next_it = value_it;
	++next_it;
	if (next_it != tokens.end() && next_it->second == VALUE)
		throw std::runtime_error(error_msg);
}

/**
 * @brief Supprime le point-virgule final d'une chaîne si présent
 *
 * @param raw La chaîne brute potentiellement terminée par un point-virgule
 * @return La chaîne sans point-virgule final, ou la chaîne originale si pas de point-virgule
 */
string Parser::stripTrailingSemicolon(const string &raw) const
{
	if (!raw.empty() && raw[raw.size() - 1] == ';')
		return (raw.substr(0, raw.size() - 1));
	return (raw);
}


/**
 * @brief Parse la directive 'listen' pour configurer le port d'écoute
 *
 * Lit la valeur du port, la valide et l'assigne au serveur.
 *
 * @param server Référence vers l'objet Server à configurer
 * @param it Itérateur sur les tokens (modifié par effet de bord)
 * @param tokens Liste complète des tokens
 * @throws std::runtime_error Si la valeur est manquante ou le port invalide
 */
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

/**
 * @brief Parse la directive 'host' pour configurer l'adresse d'écoute
 *
 * Lit l'adresse IP, la valide et l'assigne au serveur.
 *
 * @param server Référence vers l'objet Server à configurer
 * @param it Itérateur sur les tokens (modifié par effet de bord)
 * @param tokens Liste complète des tokens
 * @throws std::runtime_error Si l'adresse IP est manquante ou invalide
 */
void Parser::parseHost(Server &server, lst_iterator &it,const list_pair_str_int &tokens) const
{
	const string host_value = readSingleValue(it, tokens,"Parser: Expected value after 'host' directive","Parser: Unexpected value after value of host directive");
	Validator::validateIPAddress(host_value);
	server.setHost(host_value);
}

/**
 * @brief Parse la directive 'server_name' pour configurer les noms de serveur
 *
 * Lit tous les noms de serveur (peut être multiple) et les assigne au serveur
 * sous forme d'une chaîne séparée par des espaces.
 *
 * @param server Référence vers l'objet Server à configurer
 * @param it Itérateur sur les tokens (modifié par effet de bord)
 * @param tokens Liste complète des tokens
 * @throws std::runtime_error Si aucun nom de serveur n'est fourni
 */
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

/**
 * @brief Parse la directive 'error_page' pour configurer les pages d'erreur
 *
 * Lit les codes d'erreur HTTP et le chemin de la page d'erreur associée.
 * Plusieurs codes peuvent pointer vers la même page.
 *
 * @param server Référence vers l'objet Server à configurer
 * @param it Itérateur sur les tokens (modifié par effet de bord)
 * @param tokens Liste complète des tokens
 * @throws std::runtime_error Si moins de deux valeurs sont fournies (code + chemin)
 */
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

/**
 * @brief Parse la directive 'client_max_body_size' pour limiter la taille des requêtes
 *
 * Lit la taille maximale autorisée pour le corps d'une requête HTTP et vérifie
 * qu'elle est positive et n'excède pas 100 Mo.
 *
 * @param server Référence vers l'objet Server à configurer
 * @param it Itérateur sur les tokens (modifié par effet de bord)
 * @param tokens Liste complète des tokens
 * @throws std::runtime_error Si la taille est négative ou dépasse la limite
 */
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

/**
 * @brief Vérifie qu'une directive n'est pas dupliquée
 *
 * Contrôle si la directive fait partie de celles qui ne peuvent apparaître qu'une seule fois
 * et vérifie qu'elle n'a pas déjà été rencontrée.
 *
 * @param seen Ensemble des directives déjà rencontrées (modifié par effet de bord)
 * @param directive Nom de la directive à vérifier
 * @throws std::runtime_error Si la directive est dupliquée
 */
void Parser::checkDuplicateDirective(std::set<string> &seen, const string &directive) const
{
	const string arr[] = {DENINE_DOUBLON};
	const std::set<string> doublons(arr, arr + sizeof(arr) / sizeof(arr[0]));
	if (doublons.find(directive) != doublons.end() && seen.find(directive) != seen.end())
		throw std::runtime_error("Parser: Duplicate directive '" + directive + "'");
	seen.insert(directive);
}


/**
 * @brief Parse un bloc complet de configuration serveur
 *
 * Parcourt toutes les directives d'un bloc server et construit l'objet Server correspondant.
 * Gère les directives de niveau serveur et les blocs location imbriqués.
 *
 * @param it Itérateur sur les tokens (modifié par effet de bord)
 * @param tokens Liste complète des tokens
 * @return L'objet Server construit avec toutes ses configurations
 */
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

