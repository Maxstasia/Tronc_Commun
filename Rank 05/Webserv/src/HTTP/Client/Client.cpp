#include "Client.hpp"

Client::Client() : _client_fd(-1), _bytes(0), _server(NULL), _location(NULL), _shouldClose(false), _lastActivity(time(NULL)), _cgiPid(-1), _cgiPipeFd(-1), _cgiWritePipeFd(-1), _cgiBodySent(0), _cgiStartTime(0), _cgiRunning(false) {}

Client::Client(int client_fd, struct sockaddr_in client_addr)
	: _client_fd(client_fd), _client_addr(client_addr), _bytes(0), _server(NULL), _location(NULL), _shouldClose(false), _lastActivity(time(NULL)), _cgiPid(-1), _cgiPipeFd(-1), _cgiWritePipeFd(-1), _cgiBodySent(0), _cgiStartTime(0), _cgiRunning(false) {}

Client::~Client() {}

/**
 * @brief Ajoute des données au buffer de la requête HTTP
 *
 * Permet d'accumuler les données reçues du client pour constituer
 * progressivement la requête HTTP complète.
 *
 * @param buffer Pointeur vers les données à ajouter
 * @param size Taille des données en octets
 */
void Client::appendRequest(const char* buffer, size_t size) {
	_request.appendRequest(buffer, size);
}

/**
 * @brief Réinitialise l'état du client pour une nouvelle requête
 *
 * Remet à zéro tous les attributs du client (requête, réponse, CGI, etc.)
 * pour permettre le traitement d'une nouvelle requête sur la même connexion
 * (keep-alive).
 */
void Client::reset() {
	_request = Request();
	_response = Response();
	_bytes = 0;
	_location = NULL;
	_shouldClose = false;
	_lastActivity = time(NULL);
	_cgiPid = -1;
	_cgiPipeFd = -1;
	_cgiWritePipeFd = -1;
	_cgiBodySent = 0;
	_cgiOutput.clear();
	_cgiStartTime = 0;
	_cgiRunning = false;
}

/**
 * @brief Vérifie si la réponse HTTP a été entièrement envoyée au client
 *
 * @return true si toute la réponse a été transmise, false sinon
 */
bool Client::isFullySent() const {
	return (_response.getFinalResponse().empty() == false && _bytes >= _response.getFinalResponse().size());
}
