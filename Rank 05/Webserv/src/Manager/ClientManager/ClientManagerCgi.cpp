#include "ClientManager.hpp"
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>

/**
 * @brief Nettoie les ressources d'un processus CGI.
 *
 * Tue le processus CGI avec SIGKILL, attend sa terminaison, retire le pipe
 * d'epoll, ferme le pipe, et efface les mappings associes.
 *
 * @param client Reference vers le client dont le CGI doit etre nettoye.
 * @return Aucune valeur de retour.
 */
void ClientManager::cleanupCgi(Client &client)
{
	int writePipeFd = client.getCgiWritePipeFd();
	if (writePipeFd != -1)
	{
		_eventManager.removeFd(writePipeFd);
		close(writePipeFd);
		_cgiWritePipeToClient.erase(writePipeFd);
	}
	int pipeFd = client.getCgiPipeFd();
	pid_t pid = client.getCgiPid();
	if (pid > 0)
	{
		kill(pid, SIGKILL);
		waitpid(pid, NULL, 0);
	}
	_eventManager.removeFd(pipeFd);
	close(pipeFd);
	_cgiPipeToClient.erase(pipeFd);
	client.clearCgi();
}

/**
 * @brief Enregistre un pipe CGI et l'associe a un client.
 *
 * Mappe le pipe CGI au descripteur client, enregistre le pipe avec epoll
 * pour la lecture, et gere les erreurs d'enregistrement.
 *
 * @param pipeFd Le descripteur de fichier du pipe CGI.
 * @param clientFd Le descripteur de fichier du client.
 * @return Aucune valeur de retour.
 */
void ClientManager::registerCgiPipe(int pipeFd, int clientFd)
{
	_cgiPipeToClient[pipeFd] = clientFd;
	try
	{
		_eventManager.addFd(pipeFd, EPOLLIN);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Failed to add CGI pipe to epoll: " << e.what() << std::endl;
		_cgiPipeToClient.erase(pipeFd);
		close(pipeFd);
	}
}

/**
 * @brief Verifie si un descripteur correspond a un pipe CGI.
 *
 * @param fd Le descripteur de fichier a verifier.
 * @return true si fd est un pipe CGI dans _cgiPipeToClient, false sinon.
 */
bool ClientManager::isCgiPipe(int fd) const
{
	return _cgiPipeToClient.find(fd) != _cgiPipeToClient.end()
		|| _cgiWritePipeToClient.find(fd) != _cgiWritePipeToClient.end();
}

void ClientManager::registerCgiWritePipe(int pipeFd, int clientFd)
{
	_cgiWritePipeToClient[pipeFd] = clientFd;
	try
	{
		_eventManager.addFd(pipeFd, EPOLLOUT);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Failed to add CGI write pipe to epoll: " << e.what() << std::endl;
		_cgiWritePipeToClient.erase(pipeFd);
		close(pipeFd);
	}
}

void ClientManager::handleCgiPipeWrite(int fd)
{
	std::map<int, int>::iterator pipeIt = _cgiWritePipeToClient.find(fd);
	if (pipeIt == _cgiWritePipeToClient.end())
		return;

	int clientFd = pipeIt->second;
	std::map<int, Client>::iterator clientIt = _clients.find(clientFd);
	if (clientIt == _clients.end())
	{
		_eventManager.removeFd(fd);
		close(fd);
		_cgiWritePipeToClient.erase(fd);
		return;
	}

	Client &client = clientIt->second;
	const string &body = client.getRequest().getBody();
	size_t &sent = client.getCgiBodySent();
	size_t total = body.size();

	ssize_t w = write(fd, body.c_str() + sent, total - sent);
	if (w < 0)
	{
		_eventManager.removeFd(fd);
		close(fd);
		_cgiWritePipeToClient.erase(fd);
		client.setCgiWritePipeFd(-1);
		return;
	}
	sent += static_cast<size_t>(w);
	if (sent >= total)
	{
		_eventManager.removeFd(fd);
		close(fd);
		_cgiWritePipeToClient.erase(fd);
		client.setCgiWritePipeFd(-1);
	}
}

/**
 * @brief Lit la sortie d'un pipe CGI.
 *
 * Lit les donnees du pipe, les ajoute au buffer de sortie CGI du client, gere
 * la fin du flux (EOF) en finalisant le CGI et en preparant la reponse (supprime
 * le corps pour HEAD).
 *
 * @param fd Le descripteur de fichier du pipe CGI.
 * @return Aucune valeur de retour.
 */
void ClientManager::handleCgiPipeRead(int fd)
{
	std::map<int, int>::iterator pipeIt = _cgiPipeToClient.find(fd);
	if (pipeIt == _cgiPipeToClient.end())
		return;

	int clientFd = pipeIt->second;
	std::map<int, Client>::iterator clientIt = _clients.find(clientFd);
	if (clientIt == _clients.end())
	{
		handleCgiPipeError(fd);
		return;
	}

	Client &client = clientIt->second;
	char buffer[SOCKET_BUFFER_SIZE];
	ssize_t count = read(fd, buffer, sizeof(buffer));

	if (count < 0)
	{
		handleCgiPipeError(fd);
		return;
	}
	if (count == 0)
	{
		_eventManager.removeFd(fd);
		close(fd);
		_cgiPipeToClient.erase(fd);
		_cgiHandler.finishCgi(client);
		if (client.getRequest().getMethod() == "HEAD")
			client.getResponse().stripBodyFromFinalResponse();
		prepareClientForWriting(clientFd);
		return;
	}
	client.appendCgiOutput(buffer, count);
}

/**
 * @brief Gere les erreurs sur un pipe CGI.
 *
 * Tue le processus CGI, ferme le pipe, envoie une reponse 502 Bad Gateway
 * au client, et prepare le client pour l'ecriture.
 *
 * @param fd Le descripteur de fichier du pipe CGI en erreur.
 * @return Aucune valeur de retour.
 */
void ClientManager::handleCgiPipeError(int fd)
{
	std::map<int, int>::iterator writeIt = _cgiWritePipeToClient.find(fd);
	if (writeIt != _cgiWritePipeToClient.end())
	{
		_eventManager.removeFd(fd);
		close(fd);
		_cgiWritePipeToClient.erase(fd);
		std::map<int, Client>::iterator cIt = _clients.find(writeIt->second);
		if (cIt != _clients.end())
			cIt->second.setCgiWritePipeFd(-1);
		return;
	}
	std::map<int, int>::iterator pipeIt = _cgiPipeToClient.find(fd);
	if (pipeIt == _cgiPipeToClient.end())
		return;

	int clientFd = pipeIt->second;

	_eventManager.removeFd(fd);
	close(fd);
	_cgiPipeToClient.erase(fd);

	std::map<int, Client>::iterator clientIt = _clients.find(clientFd);
	if (clientIt != _clients.end())
	{
		Client &client = clientIt->second;
		if (client.isCgiRunning())
		{
			pid_t pid = client.getCgiPid();
			if (pid > 0)
			{
				kill(pid, SIGKILL);
				waitpid(pid, NULL, 0);
			}
			client.clearCgi();
		}
		Response &response = client.getResponse();
		response.setStatus(HTTP_502);
		response.setHeader("Content-Type", "text/html");
		response.setBody("<html><body><h1>502 Bad Gateway</h1></body></html>");
		response.buildResponse();
		prepareClientForWriting(clientFd);
	}
}
