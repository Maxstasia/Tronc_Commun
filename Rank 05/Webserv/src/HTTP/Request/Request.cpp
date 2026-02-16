#include "Request.hpp"

Request::Request() : _isParsed(false), _parseError(0), _contentLength(-1),
	_hostCount(0)
{
}

Request::~Request()
{
}

/**
 * @brief Ajoute des données brutes au buffer de la requête HTTP
 *
 * Permet d'accumuler progressivement les données reçues pour constituer
 * la requête HTTP complète avant son parsing.
 *
 * @param buffer Pointeur vers les données à ajouter
 * @param size Taille des données en octets
 */
void Request::appendRequest(const char *buffer, size_t size)
{
	_raw_request.append(buffer, size);
}
