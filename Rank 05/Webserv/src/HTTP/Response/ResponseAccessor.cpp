#include "Response.hpp"

/**
 * @brief Récupère la réponse HTTP finale complète
 *
 * @return Référence constante vers la chaîne de réponse prête à envoyer
 */
const string &Response::getFinalResponse() const {
	return _finalResponse;
}

/**
 * @brief Récupère tous les en-têtes de la réponse
 *
 * @return Map constante contenant les paires clé-valeur des en-têtes
 */
const map_str_str &Response::getHeaders() const {
	return _headers;
}

/**
 * @brief Récupère le corps de la réponse
 *
 * @return Contenu du corps de la réponse
 */
string Response::getBody() const {
	return _body;
}

/**
 * @brief Récupère le code de statut HTTP
 *
 * @return Code de statut (200, 404, 500, etc.)
 */
int Response::getStatus() const {
	return _status;
}

/**
 * @brief Récupère le message de statut HTTP
 *
 * @return Message descriptif du statut (OK, Not Found, etc.)
 */
string Response::getStatusMessage() const {
	return _statusMessage;
}

/**
 * @brief Récupère la version du protocole HTTP de la réponse
 *
 * @return Version HTTP (HTTP/1.0 ou HTTP/1.1)
 */
string Response::getHttpVersion() const {
	return _httpVersion;
}
