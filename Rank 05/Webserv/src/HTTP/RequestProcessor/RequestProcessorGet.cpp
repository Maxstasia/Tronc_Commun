/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestProcessorGet.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 21:30:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/13 19:07:48 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestProcessor.hpp"
#include "Location.hpp"
#include "StringUtils.hpp"
#include <cstdio>
#include <dirent.h>

/**
 * @brief Traite une requête HTTP DELETE
 *
 * Supprime le fichier spécifié par l'URI si autorisé.
 *
 * @param client Référence vers le client
 * @param server Référence vers le serveur
 * @param loc Pointeur vers la location
 */
void RequestProcessor::handleDelete(Client &client, const Server &server, const Location *loc)
{
	string uri = client.getRequest().getUri();
	string filePath = buildFilePath(uri, server, loc);

	if (filePath.empty())
	{
		sendErrorResponse(client, HTTP_400);
		return;
	}
	if (!FileUtils::isPathSafe(filePath, server.getRoot()))
	{
		sendErrorResponse(client, HTTP_403);
		return;
	}
	if (!FileUtils::fileExists(filePath))
	{
		sendErrorResponse(client, HTTP_404);
		return;
	}
	if (FileUtils::isDirectory(filePath))
	{
		sendErrorResponse(client, HTTP_403);
		return;
	}
	if (std::remove(filePath.c_str()) == 0)
	{
		Response &response = client.getResponse();
		response.setStatus(HTTP_204);
		response.setBody("");
		response.buildResponse();
	}
	else
		sendErrorResponse(client, HTTP_500);
}

/**
 * @brief Gestion d'un fichier manquant
 *
 * Tente d'afficher un listing de répertoire si autoindex est activé,
 * sinon envoie une erreur 404.
 *
 * @param client Référence vers le client
 * @param server Référence vers le serveur
 * @param loc Pointeur vers la location
 * @param uri URI de la requête
 * @param method Méthode HTTP (pour gestion HEAD)
 */
void RequestProcessor::handleMissingFile(Client &client, const Server &server,
	const Location *loc, const string &uri, const string &method)
{
	string root = loc ? loc->getEffectiveRoot(server.getRoot()) : server.getRoot();
	string dirPath = FileUtils::ensureTrailingSlash(root);
	string cleanUri = uri;
	if (!cleanUri.empty() && cleanUri[0] == '/')
		cleanUri = cleanUri.substr(1);
	dirPath += cleanUri;
	if (loc && loc->getAutoindex() && FileUtils::isDirectory(dirPath))
		handleAutoindex(client, dirPath, uri);
	else
		sendErrorResponse(client, HTTP_404);
	if (method == "HEAD")
		client.getResponse().stripBodyFromFinalResponse();
}

/**
 * @brief Génère un listing HTML du contenu d'un répertoire
 *
 * Crée une page HTML listant tous les fichiers du répertoire.
 *
 * @param client Référence vers le client
 * @param dirPath Chemin du répertoire à lister
 * @param uri URI du répertoire
 */
void RequestProcessor::handleAutoindex(Client &client, const string &dirPath,
	const string &uri)
{
	DIR *dir = opendir(dirPath.c_str());
	if (!dir)
	{
		sendErrorResponse(client, HTTP_500);
		return;
	}

	string baseUri = FileUtils::ensureTrailingSlash(uri);
	string safeUri = StringUtils::escapeHtml(baseUri);
	string body = "<html><head><title>Index of " + safeUri + "</title></head><body>";
	body += "<h1>Index of " + safeUri + "</h1><hr><pre>";

	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL)
	{
		string name = entry->d_name;
		if (name == ".")
			continue;
		string safeName = StringUtils::escapeHtml(name);
		string encodedName = StringUtils::urlEncode(name);
		string link = "<a href=\"" + baseUri + encodedName + "\">" + safeName + "</a>\n";
		body += link;
	}
	closedir(dir);
	body += "</pre><hr></body></html>";
	sendSuccessResponse(client, HTTP_200, body);
}
