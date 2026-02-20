#include "RequestProcessor.hpp"
#include "Location.hpp"
#include <fstream>
#include <sstream>
#include <ctime>

/**
 * @brief Récupère le chemin de répertoire pour les uploads
 *
 * @param server Référence vers le serveur
 * @param loc Pointeur vers la location
 * @return Chemin du répertoire d'upload
 */
string RequestProcessor::getUploadPath(const Server &server, const Location *loc) const
{
	return loc ? loc->getEffectiveUploadPath(server.getRoot()) : server.getRoot();
}

/**
 * @brief Génère un nom de fichier unique pour un upload POST
 *
 * Utilise le timestamp actuel et détermine l'extension depuis le Content-Type.
 *
 * @param contentType Type MIME du contenu
 * @return Nom de fichier généré
 */
string RequestProcessor::generatePostFilename(const string &contentType) const
{
	stringstream ss;
	ss << "post_" << time(NULL);
	if (contentType.find("text/plain") != string::npos)
		ss << ".txt";
	else if (contentType.find("application/json") != string::npos)
		ss << ".json";
	else if (contentType.find("application/xml") != string::npos)
		ss << ".xml";
	else if (contentType.find("text/html") != string::npos)
		ss << ".html";
	else
		ss << ".bin";
	return ss.str();
}

/**
 * @brief Extrait la chaîne boundary depuis le Content-Type
 *
 * @param contentType En-tête Content-Type contenant le boundary
 * @return Chaîne boundary, ou vide si non trouvée
 */
string RequestProcessor::extractBoundary(const string &contentType) const
{
	size_t pos = contentType.find("boundary=");
	if (pos == string::npos)
		return "";
	return contentType.substr(pos + 9);
}

/**
 * @brief Extrait le nom de fichier depuis les en-têtes multipart
 *
 * Valide et nettoie le nom de fichier pour éviter les vulnérabilités.
 *
 * @param headers En-têtes de la partie multipart
 * @return Nom de fichier validé, ou vide si invalide
 */
string RequestProcessor::extractFilename(const string &headers) const
{
	size_t pos = headers.find("filename=\"");
	if (pos == string::npos)
		return "";
	size_t start = pos + 10;
	size_t end = headers.find("\"", start);
	if (end == string::npos)
		return "";
	string filename = headers.substr(start, end - start);
	size_t lastSlash = filename.find_last_of("/\\");
	if (lastSlash != string::npos)
		filename = filename.substr(lastSlash + 1);
	if (filename.empty() || filename == "." || filename == ".."
		|| filename.find("..") != string::npos)
		return "";
	return filename;
}

/**
 * @brief Résout un nom de fichier unique dans un répertoire
 *
 * Si le fichier existe déjà, ajoute un suffixe (1), (2), etc.
 * avant l'extension jusqu'à trouver un nom disponible.
 *
 * @param dir Répertoire cible (avec slash final)
 * @param filename Nom de fichier original
 * @return Nom de fichier unique disponible
 */
static string resolveUniqueFilename(const string &dir, const string &filename)
{
	string		base = filename;
	string		ext;
	size_t		dot = filename.find_last_of('.');
	struct stat	st;

	if (dot != string::npos && dot != 0)
	{
		base = filename.substr(0, dot);
		ext = filename.substr(dot);
	}
	if (stat((dir + filename).c_str(), &st) != 0)
		return (filename);
	for (int i = 1; i <= 999; ++i)
	{
		stringstream ss;
		ss << base << "(" << i << ")" << ext;
		if (stat((dir + ss.str()).c_str(), &st) != 0)
			return (ss.str());
	}
	return (filename);
}

/**
 * @brief Sauvegarde un fichier uploadé sur le disque
 *
 * Résout un nom unique si le fichier existe déjà,
 * puis vérifie la sécurité du chemin avant d'écrire.
 *
 * @param uploadPath Répertoire d'upload
 * @param filename Nom du fichier à créer
 * @param content Contenu du fichier
 * @return true si l'écriture réussit, false sinon
 */
bool RequestProcessor::saveUploadedFile(const string &uploadPath,
	const string &filename, const string &content)
{
	string dir = FileUtils::ensureTrailingSlash(uploadPath);
	string unique = resolveUniqueFilename(dir, filename);
	string fullPath = dir + unique;
	if (!FileUtils::isPathSafe(fullPath, uploadPath))
		return false;
	ofstream file(fullPath.c_str(), std::ios::binary);
	if (!file.is_open())
		return false;
	file.write(content.c_str(), content.size());
	file.close();
	return true;
}

/**
 * @brief Traite une partie d'un corps multipart/form-data
 *
 * Extrait et sauvegarde le fichier contenu dans cette partie.
 *
 * @param body Corps complet de la requête
 * @param delimiter Délimiteur boundary
 * @param pos Position actuelle dans le corps (modifiée)
 * @param uploadPath Répertoire d'upload
 * @return true si le traitement réussit, false pour fin de traitement
 */
bool RequestProcessor::processMultipartPart(const string &body,
	const string &delimiter, size_t &pos, const string &uploadPath)
{
	pos += delimiter.size();
	if (body.substr(pos, 2) == "--")
		return false;
	size_t headerEnd = body.find("\r\n\r\n", pos);
	if (headerEnd == string::npos)
		return false;
	size_t nextBoundary = body.find(delimiter, headerEnd);
	if (nextBoundary == string::npos)
		return false;
	string partHeaders = body.substr(pos, headerEnd - pos);
	string partContent = body.substr(headerEnd + 4, nextBoundary - headerEnd - 6);
	string filename = extractFilename(partHeaders);
	if (!filename.empty())
		return saveUploadedFile(uploadPath, filename, partContent);
	return true;
}

/**
 * @brief Gestion d'un upload multipart/form-data complet
 *
 * Parse et traite toutes les parties d'un corps multipart.
 *
 * @param client Référence vers le client
 * @param uploadPath Répertoire d'upload
 * @return true si le traitement réussit, false en cas d'erreur
 */
bool RequestProcessor::handleMultipartUpload(Client &client,
	const string &uploadPath)
{
	const string &contentType = client.getRequest().getContentType();
	const string &body = client.getRequest().getBody();
	string boundary = extractBoundary(contentType);
	if (boundary.empty())
		return false;
	string delimiter = "--" + boundary;
	size_t pos = body.find(delimiter);
	if (pos == string::npos)
		return false;
	while ((pos = body.find(delimiter, pos)) != string::npos)
	{
		if (!processMultipartPart(body, delimiter, pos, uploadPath))
			break;
	}
	return true;
}

/**
 * @brief Traite une requête HTTP POST
 *
 * Gère les uploads multipart ou simples selon le Content-Type.
 *
 * @param client Référence vers le client
 * @param server Référence vers le serveur
 * @param loc Pointeur vers la location
 */
void RequestProcessor::handlePost(Client &client, const Server &server, const Location *loc)
{
	const string &contentType = client.getRequest().getContentType();
	string uploadPath = getUploadPath(server, loc);

	if (contentType.find("multipart/form-data") != string::npos)
	{
		if (!handleMultipartUpload(client, uploadPath))
		{
			sendErrorResponse(client, HTTP_400);
			return;
		}

		sendSuccessResponse(client, HTTP_201,
			"<html><body><h1>File uploaded successfully</h1></body></html>");
	}
	else
	{
		string filename = generatePostFilename(contentType);
		if (!saveUploadedFile(uploadPath, filename, client.getRequest().getBody()))
		{
			sendErrorResponse(client, HTTP_500);
			return;
		}
		sendSuccessResponse(client, HTTP_201,
			"<html><body><h1>File created: " + filename + "</h1></body></html>");
	}
}
