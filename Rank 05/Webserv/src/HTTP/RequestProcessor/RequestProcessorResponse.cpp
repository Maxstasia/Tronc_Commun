/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestProcessorResponse.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 21:30:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/13 19:08:25 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestProcessor.hpp"
#include "Location.hpp"
#include <fstream>
#include <sstream>

/**
 * @brief Envoie une réponse d'erreur HTTP au client
 *
 * Tente de charger une page d'erreur personnalisée, sinon génère une page par défaut.
 *
 * @param client Référence vers le client
 * @param code Code d'erreur HTTP
 * @param message Message d'erreur (optionnel)
 */
void RequestProcessor::sendErrorResponse(Client &client, int code, const string &message)
{
	Response &response = client.getResponse();
	response.setStatus(code, message);
	response.setHeader("Content-Type", "text/html");

	const Server *server = client.getServer();
	if (server)
	{
		map_int_string errors = server->getError();
		map_int_string::iterator it = errors.find(code);
		if (it != errors.end())
		{
			string path = server->getRoot() + "/" + it->second;
			if (FileUtils::fileExists(path))
			{
				ifstream file(path.c_str(), std::ios::binary);
				if (file.is_open())
				{
					stringstream content;
					content << file.rdbuf();
					file.close();
					response.setBody(content.str());
					response.buildResponse();
					return;
				}
			}
		}
	}

	stringstream body;
	body << "<html><head><title>" << code << " " << message << "</title></head>";
	body << "<body><h1>" << code << " " << message << "</h1></body></html>";

	response.setBody(body.str());
	response.buildResponse();
	if (client.getRequest().getMethod() == "HEAD")
		response.stripBodyFromFinalResponse();
}

/**
 * @brief Sert un fichier statique au client
 *
 * Lit le fichier, détermine son type MIME et construit la réponse.
 *
 * @param client Référence vers le client
 * @param filePath Chemin absolu du fichier à servir
 */
void RequestProcessor::serveStaticFile(Client &client, const string &filePath)
{
	ifstream file(filePath.c_str(), std::ios::binary);
	if (!file.is_open())
	{
		sendErrorResponse(client, HTTP_404);
		return;
	}

	stringstream content;
	content << file.rdbuf();
	file.close();

	string mimeType = "application/octet-stream";
	size_t dotPos = filePath.rfind('.');
	if (dotPos != string::npos && _loader)
		mimeType = _loader->getMimeType(filePath.substr(dotPos + 1));

	Response &response = client.getResponse();
	response.setStatus(HTTP_200);
	response.setHeader("Content-Type", mimeType);
	response.setBody(content.str());
	response.buildResponse();
}

/**
 * @brief Envoie une réponse de succès avec un corps HTML
 *
 * @param client Référence vers le client
 * @param code Code de statut HTTP
 * @param message Message de statut
 * @param body Contenu HTML de la réponse
 */
void RequestProcessor::sendSuccessResponse(Client &client, int code,
	const string &message, const string &body)
{
	Response &response = client.getResponse();
	response.setStatus(code, message);
	response.setHeader("Content-Type", "text/html");
	response.setBody(body);
	response.buildResponse();
}

/**
 * @brief Envoie une réponse avec définition de cookie
 *
 * @param client Référence vers le client
 * @param setCookie Valeur de l'en-tête Set-Cookie
 * @param body Contenu HTML de la réponse
 */
void RequestProcessor::sendCookieResponse(Client &client, const string &setCookie,
	const string &body)
{
	Response &response = client.getResponse();
	response.setStatus(HTTP_200);
	response.setHeader("Content-Type", "text/html; charset=utf-8");
	if (!setCookie.empty())
		response.setHeader("Set-Cookie", setCookie);
	response.setBody(body);
	response.buildResponse();
}

/**
 * @brief Gestion des routes spéciales de démonstration des cookies
 *
 * Traite les routes /setcookie, /deletecookie et /showcookies.
 *
 * @param client Référence vers le client
 * @param method Méthode HTTP
 * @param uri URI de la requête
 * @return true si une route cookie est traitée, false sinon
 */
bool RequestProcessor::handleCookieRoutes(Client &client, const string &method,
	const string &uri)
{
	if (method != "GET")
		return false;
	if (uri == "/setcookie")
	{
		sendCookieResponse(client, "session=webserv_test_123; Path=/; Max-Age=3600",
			"<html><body><h1>Cookie défini !</h1><p>session=webserv_test_123</p></body></html>");
		return true;
	}
	if (uri == "/deletecookie")
	{
		sendCookieResponse(client, "session=; Path=/; Max-Age=0",
			"<html><body><h1>Cookie supprimé !</h1></body></html>");
		return true;
	}
	if (uri == "/showcookies")
	{
		string session = client.getRequest().getCookie("session");
		string body = "<html><body><h1>Cookies reçus</h1>";
		if (!session.empty())
			body += "<p>session = " + session + "</p>";
		else
			body += "<p>Aucun cookie 'session' trouvé</p>";
		body += "</body></html>";
		sendCookieResponse(client, "", body);
		return true;
	}
	return false;
}
