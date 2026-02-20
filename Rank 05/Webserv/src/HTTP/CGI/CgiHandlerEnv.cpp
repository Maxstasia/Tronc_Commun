#include "CgiHandler.hpp"
#include <cstdlib>

/**
 * @brief Ajoute une variable d'environnement au vecteur
 *
 * @param env Vecteur de chaînes d'environnement
 * @param key Nom de la variable
 * @param value Valeur de la variable
 */
void CgiHandler::addEnvVar(std::vector<string> &env, const string &key,
	const string &value)
{
	env.push_back(key + "=" + value);
}

/**
 * @brief Convertit les en-têtes HTTP en variables d'environnement CGI
 *
 * Transforme les en-têtes HTTP en format HTTP_* conforme à CGI/1.1.
 *
 * @param env Vecteur de variables d'environnement à compléter
 * @param req Référence vers la requête contenant les en-têtes
 */
void CgiHandler::addCgiHttpHeaders(std::vector<string> &env, const Request &req)
{
	string	key;

	const map_str_str &headers = req.getHeaders();
	map_str_str::const_iterator it;
	for (it = headers.begin(); it != headers.end(); ++it)
	{
		key = it->first;
		for (size_t i = 0; i < key.size(); ++i)
		{
			if (key[i] == '-')
				key[i] = '_';
			else if (key[i] >= 'a' && key[i] <= 'z')
				key[i] = key[i] - 'a' + 'A';
		}
		if (key == "CONTENT_TYPE" || key == "CONTENT_LENGTH")
			continue ;
		addEnvVar(env, "HTTP_" + key, it->second);
	}
}

/**
 * @brief Convertit un vecteur de chaînes en tableau envp de style C
 *
 * Alloue dynamiquement un tableau de char* terminé par NULL.
 *
 * @param env Vecteur de chaînes d'environnement
 * @return Tableau alloué de char* (doit être libéré avec freeEnvp)
 */
char **CgiHandler::vecToEnvp(const std::vector<string> &env)
{
	char	**envp;

	envp = new char *[env.size() + 1];
	for (size_t i = 0; i < env.size(); ++i)
	{
		envp[i] = new char[env[i].size() + 1];
		std::strcpy(envp[i], env[i].c_str());
	}
	envp[env.size()] = NULL;
	return (envp);
}

/**
 * @brief Construit l'environnement complet pour l'exécution du CGI
 *
 * Crée toutes les variables CGI standard (GATEWAY_INTERFACE, REQUEST_METHOD, etc.)
 * ainsi que les en-têtes HTTP transformés.
 *
 * @param req Référence vers la requête HTTP
 * @param server Référence vers le serveur
 * @param scriptPath Chemin absolu vers le script CGI
 * @param pathInfo Information de chemin supplémentaire
 * @return Tableau envp alloué (doit être libéré avec freeEnvp)
 */
char **CgiHandler::buildEnvp(const Request &req, const Server &server,
	const string &scriptPath, const string &pathInfo)
{
	std::vector<string>	env;
	stringstream		ss;
	stringstream		cl;

	addEnvVar(env, "GATEWAY_INTERFACE", "CGI/1.1");
	addEnvVar(env, "SERVER_PROTOCOL", req.getHttpVersion());
	addEnvVar(env, "SERVER_SOFTWARE", "Webserv");
	addEnvVar(env, "REQUEST_METHOD", req.getMethod());
	addEnvVar(env, "QUERY_STRING", req.getQueryString());
	addEnvVar(env, "SCRIPT_NAME", req.getUri());
	addEnvVar(env, "SCRIPT_FILENAME", scriptPath);
	addEnvVar(env, "PATH_INFO", pathInfo.empty() ? "/" : pathInfo);
	addEnvVar(env, "PATH_TRANSLATED", scriptPath);
	addEnvVar(env, "REDIRECT_STATUS", "200");
	ss << server.getPort();
	addEnvVar(env, "SERVER_PORT", ss.str());
	addEnvVar(env, "SERVER_NAME", server.getServerName());
	if (!req.getContentType().empty())
		addEnvVar(env, "CONTENT_TYPE", req.getContentType());
	if (req.getContentLength() >= 0)
	{
		cl << req.getContentLength();
		addEnvVar(env, "CONTENT_LENGTH", cl.str());
	}
	addCgiHttpHeaders(env, req);
	return (vecToEnvp(env));
}

/**
 * @brief Libère la mémoire d'un tableau envp
 *
 * @param envp Tableau alloué à libérer (peut être NULL)
 */
void CgiHandler::freeEnvp(char **envp)
{
	if (!envp)
		return ;
	for (int i = 0; envp[i]; ++i)
		delete[] envp[i];
	delete[] envp;
}
