/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ManagerServerPrint.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 17:45:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/13 19:02:20 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ManagerServer.hpp"
#include "Location.hpp"


/**
 * @brief Affiche les details de configuration d'une location.
 *
 * Imprime le chemin, root, index, autoindex, methodes autorisees et
 * directive return de la location donnee.
 *
 * @param location La location a afficher.
 * @return Aucune valeur de retour.
 */
void ManagerServer::printLocation(const Location &location) const
{
	std::cout << "    - location " << location.getPath() << "\n";
	if (!location.getRoot().empty())
		std::cout << "      root: " << location.getRoot() << "\n";
	if (!location.getIndex().empty())
		std::cout << "      index: " << location.getIndex() << "\n";
	std::cout << "      autoindex: " << (location.getAutoindex() ? "on" : "off") << "\n";
	const vector_string &methods = location.getAllowMethods();
	if (!methods.empty())
	{
		std::cout << "      allow_methods:";
		for (vector_string::const_iterator it = methods.begin(); it != methods.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << "\n";
	}
	if (!location.getReturn().empty())
		std::cout << "      return: " << location.getReturn() << "\n";
}

/**
 * @brief Affiche la configuration complete d'un serveur.
 *
 * Imprime le numero de serveur, host:port, server_name, root, index,
 * client_max_body_size et toutes les locations associees.
 *
 * @param server Le serveur a afficher.
 * @param index Le numero d'index du serveur.
 * @return Aucune valeur de retour.
 */
void ManagerServer::printServer(const Server &server, std::size_t index) const
{
	std::cout << "====================\n";
	std::cout << "server #" << index << "\n";
	std::cout << "  listen: " << server.getHost() << ':' << server.getPort() << "\n";
	if (!server.getServerName().empty())
		std::cout << "  server_name: " << server.getServerName() << "\n";
	if (!server.getRoot().empty())
		std::cout << "  root: " << server.getRoot() << "\n";
	if (!server.getIndex().empty())
		std::cout << "  index: " << server.getIndex() << "\n";
	std::cout << "  client_max_body_size: " << server.getClientMaxBodySize() << "\n";
	const std::vector<Location> &locations = server.getLocations();
	if (!locations.empty())
		std::cout << "  locations:\n";
	for (std::vector<Location>::const_iterator it = locations.begin(); it != locations.end(); ++it)
	{
		printLocation(*it);
	}
}

/**
 * @brief Affiche la banniere de demarrage avec les URLs de tous les serveurs.
 *
 * Imprime un message de demarrage suivi des URLs de chaque serveur,
 * en convertissant 0.0.0.0 en localhost pour l'affichage.
 *
 * @param servers Le vecteur de serveurs a afficher.
 * @return Aucune valeur de retour.
 */
void ManagerServer::printServers(const std::vector<Server> &servers) const
{
	std::cout << "\nWebserv started:\n";
	for (std::vector<Server>::const_iterator it = servers.begin(); it != servers.end(); ++it)
	{
		std::string host = it->getHost();
		if (host == "0.0.0.0")
			host = "localhost";
		std::cout << "  http://" << host << ":" << it->getPort() << "/\n";
	}
	std::cout << "\n";
}
