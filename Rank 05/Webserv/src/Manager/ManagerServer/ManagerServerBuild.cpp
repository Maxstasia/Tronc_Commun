/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ManagerServerBuild.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:36:43 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/01/25 10:19:46 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ManagerServer.hpp"
#include "Loader.hpp"
#include "Parser.hpp"

vect_serv ManagerServer::buildServers() const
{
	try {
		return Parser::parseServers(_loader.getListLexer());
	} catch (const std::exception &e) {
		throw std::runtime_error(std::string("Loader: Failed to build servers: ") + e.what());
	}
}
