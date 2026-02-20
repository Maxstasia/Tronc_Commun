#include "CgiHandler.hpp"

/**
 * @brief Vérifie si une requête doit être traitée par CGI
 *
 * Détermine si l'URI correspond à un script CGI selon l'extension configurée.
 *
 * @param uri URI de la requête
 * @param loc Pointeur vers la location contenant la config CGI
 * @return true si la requête est un CGI, false sinon
 */
bool CgiHandler::isCgiRequest(const string &uri, const Location *loc) const
{
	if (!loc || loc->getCgiExtension().empty() || loc->getCgiPath().empty())
		return false;
	const string &ext = loc->getCgiExtension();
	string cleanUri = uri;
	size_t queryPos = cleanUri.find('?');
	if (queryPos != string::npos)
		cleanUri = cleanUri.substr(0, queryPos);
	if (cleanUri.size() >= ext.size()
		&& cleanUri.compare(cleanUri.size() - ext.size(), ext.size(), ext) == 0)
		return true;
	if (cleanUri.find(ext + "/") != string::npos)
		return true;
	return false;
}
