#include "CgiHandler.hpp"
#include <sys/wait.h>

/**
 * @brief Analyse les en-têtes retournés par le script CGI
 *
 * Parse les en-têtes CGI et extrait le statut s'il est présent.
 *
 * @param response Référence vers la réponse à remplir
 * @param headerPart Chaîne contenant les en-têtes CGI
 * @param statusCode Code de statut extrait (modifié)
 * @param statusMsg Message de statut extrait (modifié)
 */
void CgiHandler::parseCgiHeaders(Response &response, const string &headerPart,
	int &statusCode, string &statusMsg)
{
	string	line;
	size_t	colonPos;
	string	key;
	string	value;
	size_t	spacePos;

	istringstream headerStream(headerPart);
	while (std::getline(headerStream, line))
	{
		if (!line.empty() && line[line.size() - 1] == '\r')
			line = line.substr(0, line.size() - 1);
		colonPos = line.find(':');
		if (colonPos == string::npos)
			continue ;
		key = line.substr(0, colonPos);
		value = line.substr(colonPos + 1);
		while (!value.empty() && value[0] == ' ')
			value = value.substr(1);
		if (key == "Status")
		{
			istringstream statusStream(value);
			statusStream >> statusCode;
			spacePos = value.find(' ');
			if (spacePos != string::npos)
				statusMsg = value.substr(spacePos + 1);
		}
		else
			response.setHeader(key, value);
	}
}

/**
 * @brief Finalise l'exécution du CGI et construit la réponse
 *
 * Attend la fin du processus CGI, parse sa sortie et construit
 * la réponse HTTP finale.
 *
 * @param client Référence vers le client
 */
void CgiHandler::finishCgi(Client &client)
{
	int		status;
	pid_t	pid;
	size_t	headerEnd;
	size_t	bodyStart;
	int		statusCode;
	string	statusMsg;

	status = 0;
	pid = client.getCgiPid();
	waitpid(pid, &status, 0);
	const string &raw = client.getCgiOutput();
	if (raw.empty())
	{
		setCgiError(client.getResponse(), HTTP_502);
		client.clearCgi();
		return ;
	}
	headerEnd = raw.find("\r\n\r\n");
	if (headerEnd == string::npos)
		headerEnd = raw.find("\n\n");
	if (headerEnd == string::npos)
	{
		Response &response = client.getResponse();
		response.setStatus(200, "OK");
		response.setHeader("Content-Type", "text/html");
		response.setBody(raw);
		response.buildResponse();
		client.clearCgi();
		return ;
	}
	string headerPart = raw.substr(0, headerEnd);
	bodyStart = headerEnd + (raw[headerEnd] == '\n' ? 2 : 4);
	string body = raw.substr(bodyStart);
	Response &response = client.getResponse();
	statusCode = 200;
	statusMsg = "OK";
	parseCgiHeaders(response, headerPart, statusCode, statusMsg);
	response.setStatus(statusCode, statusMsg);
	response.setBody(body);
	response.buildResponse();
	client.clearCgi();
}
