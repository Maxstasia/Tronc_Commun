/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestAccessor.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/13 19:06:20 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "StringUtils.hpp"

/**
 * @brief Récupère la requête HTTP brute complète
 *
 * @return Référence vers la chaîne contenant la requête brute
 */
string &Request::getRequest(){
	return (_raw_request);
}

/**
 * @brief Récupère la méthode HTTP de la requête
 *
 * @return Méthode HTTP (GET, POST, DELETE, HEAD, etc.)
 */
string Request::getMethod() const {
	return _method;
}

/**
 * @brief Récupère l'URI de la requête (sans la query string)
 *
 * @return URI de la requête
 */
string Request::getUri() const {
	return _uri;
}

/**
 * @brief Récupère la chaîne de requête (query string)
 *
 * @return Paramètres de l'URL après le caractère '?'
 */
string Request::getQueryString() const {
	return _queryString;
}

/**
 * @brief Récupère la version du protocole HTTP
 *
 * @return Version HTTP (HTTP/1.0 ou HTTP/1.1)
 */
string Request::getHttpVersion() const {
	return _httpVersion;
}

/**
 * @brief Récupère le corps de la requête HTTP
 *
 * @return Contenu du corps de la requête
 */
string Request::getBody() const {
	return _body;
}

/**
 * @brief Récupère tous les en-têtes HTTP de la requête
 *
 * @return Map contenant les paires clé-valeur des en-têtes
 */
const map_str_str &Request::getHeaders() const {
	return _headers;
}

/**
 * @brief Vérifie si la requête a été analysée
 *
 * @return true si la requête a été parsée, false sinon
 */
bool Request::getIsParsed() const {
	return _isParsed;
}
/**
 * @brief Récupère le type de contenu de la requête
 *
 * @return Type MIME du contenu (Content-Type)
 */
string Request::getContentType() const
{
	return _contentType;
}

/**
 * @brief Récupère le code d'erreur de parsing
 *
 * @return Code d'erreur HTTP si une erreur s'est produite, 0 sinon
 */
int Request::getParseError() const
{
	return _parseError;
}

/**
 * @brief Récupère le message d'erreur de parsing
 *
 * @return Message d'erreur descriptif
 */
string Request::getParseErrorMessage() const
{
	return _parseErrorMessage;
}

/**
 * @brief Récupère la longueur du contenu de la requête
 *
 * @return Longueur du corps en octets, ou -1 si non définie
 */
long Request::getContentLength() const
{
	return _contentLength;
}

/**
 * @brief Récupère la valeur d'un cookie spécifique
 *
 * Analyse l'en-tête Cookie et extrait la valeur du cookie demandé.
 *
 * @param name Nom du cookie à rechercher
 * @return Valeur du cookie, ou chaîne vide si non trouvé
 */
string Request::getCookie(const string &name) const
{
	map_str_str::const_iterator it = _headers.find("cookie");
	if (it == _headers.end())
		return "";
	string cookies = it->second;
	size_t pos = 0;
	while (pos < cookies.length())
	{
		size_t eq = cookies.find('=', pos);
		if (eq == string::npos)
			break;
		size_t semi = cookies.find(';', eq);
		if (semi == string::npos)
			semi = cookies.length();
		string cookieName = StringUtils::trim(cookies.substr(pos, eq - pos));
		if (cookieName == name)
			return StringUtils::trim(cookies.substr(eq + 1, semi - eq - 1));
		pos = semi + 1;
	}
	return "";
}
