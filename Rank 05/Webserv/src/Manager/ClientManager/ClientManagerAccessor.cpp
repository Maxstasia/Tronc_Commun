/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManagerAccessor.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 21:30:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/13 19:03:14 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientManager.hpp"
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <ctime>
#include <iostream>

/**
 * @brief Retourne un pointeur vers l'objet Client pour un descripteur donne.
 *
 * Recherche le client dans la map _clients et retourne un pointeur vers
 * l'objet Client, ou NULL s'il n'existe pas.
 *
 * @param fd Le descripteur de fichier du client.
 * @return Pointeur vers Client, ou NULL si non trouve.
 */
Client* ClientManager::getClient(int fd)
{
	std::map<int, Client>::iterator it = _clients.find(fd);
	if (it != _clients.end())
		return &(it->second);
	return NULL;
}

/**
 * @brief Verifie si un client existe pour un descripteur donne.
 *
 * @param fd Le descripteur de fichier a verifier.
 * @return true si le client existe dans _clients, false sinon.
 */
bool ClientManager::hasClient(int fd) const
{
	return _clients.find(fd) != _clients.end();
}

/**
 * @brief Retourne une reference vers la map de clients.
 *
 * @return Reference vers _clients.
 */
std::map<int, Client>& ClientManager::getClients()
{
	return _clients;
}

/**
 * @brief Retourne une reference vers le gestionnaire CGI.
 *
 * @return Reference vers _cgiHandler.
 */
CgiHandler &ClientManager::getCgiHandler()
{
	return _cgiHandler;
}

/**
 * @brief Gere le timeout d'un processus CGI.
 *
 * Nettoie le processus CGI, envoie une reponse 504 Gateway Timeout au client,
 * et prepare le client pour l'ecriture.
 *
 * @param clientFd Le descripteur de fichier du client.
 * @return Aucune valeur de retour.
 */
void ClientManager::handleCgiTimeout(int clientFd)
{
	std::map<int, Client>::iterator cIt = _clients.find(clientFd);
	if (cIt == _clients.end())
		return;
	Client &client = cIt->second;
	cleanupCgi(client);
	Response &response = client.getResponse();
	response.setStatus(HTTP_504);
	response.setHeader("Content-Type", "text/html");
	response.setBody("<html><body><h1>504 Gateway Timeout</h1></body></html>");
	response.buildResponse();
	prepareClientForWriting(clientFd);
}

/**
 * @brief Verifie et gere les timeouts CGI et clients inactifs.
 *
 * Parcourt tous les clients, identifie ceux avec un timeout CGI (>= CGI_TIMEOUT_SEC)
 * ou un timeout d'inactivite (> CLIENT_TIMEOUT_SEC), et les traite en consequence.
 *
 * @return Aucune valeur de retour.
 */
void ClientManager::checkTimeouts()
{
	time_t now = time(NULL);
	std::vector<int> toDisconnect;
	std::vector<int> cgiTimedOut;

	std::map<int, Client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->second.isCgiRunning()
			&& now - it->second.getCgiStartTime() >= CGI_TIMEOUT_SEC)
		{
			cgiTimedOut.push_back(it->first);
			continue;
		}
		if (now - it->second.getLastActivity() > CLIENT_TIMEOUT_SEC)
			toDisconnect.push_back(it->first);
	}
	for (size_t i = 0; i < cgiTimedOut.size(); ++i)
		handleCgiTimeout(cgiTimedOut[i]);
	for (size_t i = 0; i < toDisconnect.size(); ++i)
		handleClientDisconnect(toDisconnect[i]);
}
