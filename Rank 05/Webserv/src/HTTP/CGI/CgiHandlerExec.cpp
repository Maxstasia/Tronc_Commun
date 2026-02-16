/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandlerExec.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CgiHandler.hpp"
#include <cstdlib>
#include <errno.h>
#include <climits>

/**
 * @brief Construit le chemin absolu vers le script CGI
 *
 * Résout le chemin du script en combinant la racine et l'URI,
 * et en tronquant à l'extension CGI.
 *
 * @param uri URI de la requête
 * @param server Référence vers le serveur
 * @param loc Pointeur vers la location
 * @return Chemin absolu du script CGI
 */
string CgiHandler::buildScriptPath(const string &uri, const Server &server,
	const Location *loc)
{
	string	root;
	string	cleanUri;
	size_t	queryPos;
	string	path;
	size_t	extPos;

	root = loc ? loc->getEffectiveRoot(server.getRoot()) : server.getRoot();
	cleanUri = uri;
	queryPos = cleanUri.find('?');
	if (queryPos != string::npos)
		cleanUri = cleanUri.substr(0, queryPos);
	path = FileUtils::ensureTrailingSlash(root);
	if (!cleanUri.empty() && cleanUri[0] == '/')
		cleanUri = cleanUri.substr(1);
	const string &ext = loc->getCgiExtension();
	extPos = cleanUri.find(ext);
	if (extPos != string::npos)
		cleanUri = cleanUri.substr(0, extPos + ext.size());
	path += cleanUri;
	char resolved[PATH_MAX];
	if (realpath(path.c_str(), resolved))
		return (string(resolved));
	return (path);
}

/**
 * @brief Définit une erreur CGI dans la réponse
 *
 * Construit une page d'erreur HTML pour les erreurs liées au CGI.
 *
 * @param response Référence vers la réponse à remplir
 * @param code Code d'erreur HTTP
 * @param msg Message d'erreur
 */
void CgiHandler::setCgiError(Response &response, int code, const string &msg)
{
	stringstream	ss;

	response.setStatus(code, msg);
	response.setHeader("Content-Type", "text/html");
	ss << "<html><body><h1>" << code << " " << msg << "</h1></body></html>";
	response.setBody(ss.str());
	response.buildResponse();
}

/**
 * @brief Code exécuté par le processus enfant pour lancer le CGI
 *
 * Configure les redirections stdin/stdout et exécute le script CGI.
 *
 * @param pipe_in Pipe pour l'entrée standard du CGI
 * @param pipe_out Pipe pour la sortie standard du CGI
 * @param cgiPath Chemin de l'interpréteur CGI
 * @param scriptPath Chemin du script à exécuter
 * @param envp Environnement CGI
 */
void CgiHandler::executeCgiChild(int pipe_in[2], int pipe_out[2],
	const string &cgiPath, const string &scriptPath, char **envp)
{
	char	*argv[3];
	string	scriptDir;
	size_t	lastSlash;

	close(pipe_in[1]);
	close(pipe_out[0]);
	dup2(pipe_in[0], STDIN_FILENO);
	dup2(pipe_out[1], STDOUT_FILENO);
	close(pipe_in[0]);
	close(pipe_out[1]);
	lastSlash = scriptPath.rfind('/');
	if (lastSlash != string::npos)
	{
		scriptDir = scriptPath.substr(0, lastSlash);
		chdir(scriptDir.c_str());
	}
	argv[0] = const_cast<char *>(cgiPath.c_str());
	argv[1] = const_cast<char *>(scriptPath.c_str());
	argv[2] = NULL;
	execve(cgiPath.c_str(), argv, envp);
	_exit(1);
}

/**
 * @brief Code exécuté par le processus parent après le fork
 *
 * Envoie le corps de la requête au CGI et initialise la lecture asynchrone.
 *
 * @param client Référence vers le client
 * @param pid PID du processus CGI
 * @param pipeWriteEnd Descripteur d'écriture vers le CGI
 * @param pipeReadEnd Descripteur de lecture depuis le CGI
 * @param envp Environnement à libérer
 */
void CgiHandler::executeCgiParent(Client &client, pid_t pid,
	int pipeWriteEnd, int pipeReadEnd, char **envp)
{
	freeEnvp(envp);
	const string &body = client.getRequest().getBody();
	if (!body.empty())
	{
		size_t total = body.size();
		size_t sent = 0;
		while (sent < total)
		{
			ssize_t w = write(pipeWriteEnd, body.c_str() + sent, total - sent);
			if (w <= 0)
				break ;
			sent += w;
		}
	}
	close(pipeWriteEnd);
	fcntl(pipeReadEnd, F_SETFL, O_NONBLOCK);
	client.startCgi(pid, pipeReadEnd);
}

/**
 * @brief Lance l'exécution d'un script CGI
 *
 * Crée les pipes, fork un processus et démarre l'exécution du CGI.
 *
 * @param client Référence vers le client
 * @param server Référence vers le serveur
 * @param loc Pointeur vers la location contenant la config CGI
 * @return true si le CGI démarre avec succès, false en cas d'erreur
 */
bool CgiHandler::executeCgi(Client &client, const Server &server,
	const Location *loc)
{
	string	uri;
	string	scriptPath;
	string	pathInfo;
	size_t	extPos;
	char	**envp;
	int		pipe_in[2];
	int		pipe_out[2];
	pid_t	pid;

	uri = client.getRequest().getUri();
	scriptPath = buildScriptPath(uri, server, loc);
	if (!FileUtils::fileExists(scriptPath))
	{
		setCgiError(client.getResponse(), HTTP_404);
		return (false);
	}
	const string &ext = loc->getCgiExtension();
	extPos = uri.find(ext);
	if (extPos != string::npos && extPos + ext.size() < uri.size())
		pathInfo = uri.substr(extPos + ext.size());
	envp = buildEnvp(client.getRequest(), server, scriptPath, pathInfo);
	if (pipe(pipe_in) == -1 || pipe(pipe_out) == -1)
	{
		freeEnvp(envp);
		setCgiError(client.getResponse(), HTTP_500);
		return (false);
	}
	pid = fork();
	if (pid == -1)
	{
		close(pipe_in[0]); close(pipe_in[1]);
		close(pipe_out[0]); close(pipe_out[1]);
		freeEnvp(envp);
		setCgiError(client.getResponse(), HTTP_500);
		return (false);
	}
	if (pid == 0)
		executeCgiChild(pipe_in, pipe_out, loc->getCgiPath(), scriptPath, envp);
	close(pipe_in[0]);
	close(pipe_out[1]);
	executeCgiParent(client, pid, pipe_in[1], pipe_out[0], envp);
	return (true);
}
