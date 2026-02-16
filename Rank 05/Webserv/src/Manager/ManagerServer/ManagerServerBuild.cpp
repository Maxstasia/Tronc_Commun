/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ManagerServerBuild.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:36:43 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/13 19:02:20 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ManagerServer.hpp"
#include "Loader.hpp"
#include "Parser.hpp"

/**
 * @brief Construit les objets Server a partir des tokens de configuration.
 *
 * Analyse les tokens de configuration du loader via Parser::parseServers
 * et retourne un vecteur d'objets Server. Encapsule les exceptions pour
 * fournir un message d'erreur descriptif.
 *
 * @return Vecteur d'objets Server crees a partir de la configuration.
 * @throws std::runtime_error En cas d'echec de l'analyse.
 */
vect_serv ManagerServer::buildServers() const
{
	try {
		return Parser::parseServers(_loader.getListLexer());
	} catch (const std::exception &e) {
		throw std::runtime_error(std::string("Loader: Failed to build servers: ") + e.what());
	}
}
