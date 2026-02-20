#include "Validator.hpp"
#include "StringUtils.hpp"

// ===== Static Semantic Validation Methods =====

/**
 * @brief Valide le format d'une adresse IP
 *
 * Vérifie que l'adresse est composée de 4 octets numériques séparés par des points,
 * chaque octet devant être entre 0 et 255.
 *
 * @param host L'adresse IP à valider
 * @throws std::runtime_error Si le format de l'adresse IP est invalide
 */
void Validator::validateIPAddress(const string &host)
{
	vector_string octets = StringUtils::split(host, '.');
	if (octets.size() != 4)
		return ;
	for (size_t i = 0; i < octets.size(); ++i)
	{
		if (octets[i].empty() || octets[i].size() > 3)
			throw std::runtime_error("Parser: Invalid IP address format");

		for (size_t j = 0; j < octets[i].size(); ++j)
		{
			if (!std::isdigit(static_cast<unsigned char>(octets[i][j])))
				return ;
		}

		long octet_value = std::atol(octets[i].c_str());
		if (octet_value < 0 || octet_value > 255)
			throw std::runtime_error("Parser: IP address octet must be between 0 and 255");
	}
}

/**
 * @brief Valide un chemin de fichier ou de répertoire
 *
 * Vérifie que le chemin n'est pas vide, ne contient pas de traversal (..),
 * et ne contient pas de caractères invalides.
 *
 * @param path Le chemin à valider
 * @param directive_name Nom de la directive utilisant ce chemin (pour les messages d'erreur)
 * @throws std::runtime_error Si le chemin est invalide
 */
void Validator::validatePath(const string &path, const string &directive_name)
{
	if (path.empty())
		throw std::runtime_error("Parser: Empty path for " + directive_name);

	if (path.find("..") != string::npos)
		throw std::runtime_error("Parser: Path traversal not allowed in " + directive_name);

	for (size_t i = 0; i < path.size(); ++i)
	{
		char c = path[i];
		if (c == '\0' || c == '\n' || c == '\r')
			throw std::runtime_error("Parser: Invalid character in path for " + directive_name);
	}
}

/**
 * @brief Valide un numéro de port
 *
 * Vérifie que le port est dans la plage valide 1-65535.
 *
 * @param port Le numéro de port à valider
 * @throws std::runtime_error Si le port est hors de la plage valide
 */
void Validator::validatePort(int port)
{
	if (port < 1 || port > 65535)
		throw std::runtime_error("Parser: Port must be between 1 and 65535");
}

/**
 * @brief Valide une méthode HTTP
 *
 * Vérifie que la méthode fait partie des méthodes HTTP valides supportées
 * (GET, POST, DELETE, HEAD, PUT).
 *
 * @param method Le nom de la méthode HTTP à valider
 * @throws std::runtime_error Si la méthode n'est pas valide
 */
void Validator::validateHTTPMethod(const string &method)
{
	const string valid_methods[] = {"GET", "POST", "DELETE", "HEAD", "PUT"};
	const size_t num_methods = 5;

	for (size_t i = 0; i < num_methods; ++i)
	{
		if (method == valid_methods[i])
			return;
	}
	throw std::runtime_error("Parser: Invalid HTTP method '" + method + "' (valid: GET, POST, DELETE, HEAD, PUT)");
}
