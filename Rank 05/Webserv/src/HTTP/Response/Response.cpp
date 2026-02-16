#include "Response.hpp"
#include <sstream>
#include <ctime>

Response::Response() : _status(200), _statusMessage("OK"), _httpVersion("HTTP/1.1") {}

Response::~Response() {}

/**
 * @brief Définit le corps de la réponse HTTP
 *
 * @param body Contenu du corps de la réponse
 */
void Response::setBody(const string &body) {
	_body = body;
}

/**
 * @brief Définit le code et le message de statut HTTP
 *
 * @param status Code de statut HTTP (200, 404, 500, etc.)
 * @param statusMessage Message descriptif du statut
 */
void Response::setStatus(int status, const string &statusMessage) {
	_status = status;
	_statusMessage = statusMessage;
}

/**
 * @brief Définit ou modifie un en-tête HTTP de la réponse
 *
 * @param key Nom de l'en-tête
 * @param value Valeur de l'en-tête
 */
void Response::setHeader(const string &key, const string &value) {
	_headers[key] = value;
}

/**
 * @brief Définit la version du protocole HTTP de la réponse
 *
 * @param version Version HTTP (HTTP/1.0 ou HTTP/1.1)
 */
void Response::setHttpVersion(const string &version) {
	_httpVersion = version;
}

/**
 * @brief Supprime le corps de la réponse finale (pour méthode HEAD)
 *
 * Conserve uniquement les en-têtes de la réponse en supprimant le corps.
 */
void Response::stripBodyFromFinalResponse() {
	size_t separator = _finalResponse.find("\r\n\r\n");
	if (separator != string::npos)
		_finalResponse = _finalResponse.substr(0, separator + 4);
}

/**
 * @brief Construit la réponse HTTP finale complète
 *
 * Assemble la ligne de statut, les en-têtes et le corps pour former
 * la réponse HTTP prête à être envoyée.
 */
void Response::buildResponse() {
	stringstream result;

	{
		stringstream result_len;
		result_len << _body.size();
		_headers["Content-Length"] = result_len.str();
	}

	if (_headers.find("Date") == _headers.end())
	{
		time_t now = time(NULL);
		struct tm gmt;
		gmtime_r(&now, &gmt);
		char buf[64];
		strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S GMT", &gmt);
		_headers["Date"] = buf;
	}

	if (_headers.find("Server") == _headers.end())
		_headers["Server"] = "Webserv/1.0";

	if (!_body.empty() && _headers.find("Content-Type") == _headers.end())
		_headers["Content-Type"] = "text/html";

	result << _httpVersion << " " << _status << " " << _statusMessage << "\r\n";
	map_str_str_iterator it;
	for (it = _headers.begin(); it != _headers.end(); ++it)
	{
		result << it->first << ": " << it->second << "\r\n";
	}
	result << "\r\n" << _body;
	_finalResponse = result.str();
}
