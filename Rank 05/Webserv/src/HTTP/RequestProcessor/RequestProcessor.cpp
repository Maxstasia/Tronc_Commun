/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestProcessor.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:15:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/12 21:30:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestProcessor.hpp"

RequestProcessor::RequestProcessor() : _loader(NULL), _servers(NULL)
{
}

RequestProcessor::~RequestProcessor()
{
}

/**
 * @brief Définit le chargeur de configuration
 *
 * @param loader Pointeur vers le chargeur de configuration à utiliser
 */
void RequestProcessor::setLoader(const Loader *loader)
{
	_loader = loader;
}

/**
 * @brief Définit la liste des serveurs virtuels
 *
 * @param servers Pointeur vers le vecteur de serveurs à utiliser
 */
void RequestProcessor::setServers(std::vector<Server> *servers)
{
	_servers = servers;
}
