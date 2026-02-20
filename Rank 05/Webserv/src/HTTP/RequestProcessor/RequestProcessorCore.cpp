#include "RequestProcessor.hpp"
#include "Location.hpp"
#include "StringUtils.hpp"


/**
 * @brief Traite une requête HTTP complète
 *
 * Point d'entrée principal pour le traitement d'une requête.
 * Valide, route et génère la réponse appropriée.
 *
 * @param client Référence vers le client dont la requête doit être traitée
 */
void RequestProcessor::processRequest(Client &client)
{
	if (!initRequestContext(client))
		return;
	const Server *server = client.getServer();
	string method = client.getRequest().getMethod();
	string uri = client.getRequest().getUri();
	if (!validateRequestBody(client, *server))
		return;
	const Location *loc = server->matchLocation(uri);
	client.setLocation(loc);
	if (handleMethodNotAllowed(client, loc, method))
		return;
	if (handleRedirect(client, loc))
		return;
	determineConnectionBehavior(client);
	dispatchRequest(client, *server, loc, method, uri);
}

/**
 * @brief Initialise le contexte de traitement de la requête
 *
 * Parse la requête, vérifie les erreurs et résout l'hôte virtuel.
 *
 * @param client Référence vers le client
 * @return true si l'initialisation réussit, false en cas d'erreur
 */
bool RequestProcessor::initRequestContext(Client &client)
{
	client.getRequest().parseRequest();
	string reqVersion = client.getRequest().getHttpVersion();
	if (reqVersion.empty())
		reqVersion = "HTTP/1.0";
	client.getResponse().setHttpVersion(reqVersion);
	if (client.getRequest().getParseError() != 0)
	{
		determineConnectionBehavior(client);
		sendErrorResponse(client, client.getRequest().getParseError(),
						  client.getRequest().getParseErrorMessage());
		return false;
	}
	if (!client.getServer())
	{
		determineConnectionBehavior(client);
		sendErrorResponse(client, HTTP_500);
		return false;
	}
	if (!resolveVirtualHost(client))
	{
		determineConnectionBehavior(client);
		sendErrorResponse(client, HTTP_400);
		return false;
	}
	return true;
}

/**
 * @brief Valide la taille du corps de la requête
 *
 * Vérifie que la taille du corps ne dépasse pas la limite configurée.
 *
 * @param client Référence vers le client
 * @param server Référence vers le serveur pour obtenir les limites
 * @return true si valide, false si le corps est trop grand
 */
bool RequestProcessor::validateRequestBody(Client &client, const Server &server)
{
	const Request &req = client.getRequest();
	if (req.getMethod() == "POST" && req.getContentLength() < 0
		&& req.getHeaders().find("transfer-encoding") == req.getHeaders().end())
	{
		determineConnectionBehavior(client);
		sendErrorResponse(client, HTTP_400);
		return false;
	}
	if (req.getContentLength() > 0)
	{
		unsigned long maxBody = server.getClientMaxBodySize();
		if (static_cast<unsigned long>(req.getContentLength()) > maxBody)
		{
			determineConnectionBehavior(client);
			sendErrorResponse(client, HTTP_413);
			return false;
		}
	}
	return true;
}

/**
 * @brief Vérifie la taille du corps avant le parsing complet
 *
 * Permet de rejeter rapidement les requêtes trop volumineuses.
 *
 * @param client Référence vers le client
 * @return true si la requête dépasse la limite, false sinon
 */
bool RequestProcessor::checkEarlyBodySize(Client &client)
{
	if (!client.getServer())
		return (false);
	long cl = client.getRequest().getRawContentLength();
	if (cl <= 0)
		return (false);
	unsigned long maxBody = client.getServer()->getClientMaxBodySize();
	if (static_cast<unsigned long>(cl) <= maxBody)
		return (false);
	client.getResponse().setHttpVersion("HTTP/1.1");
	determineConnectionBehavior(client);
	client.setShouldClose(true);
	client.getResponse().setHeader("Connection", "close");
	sendErrorResponse(client, HTTP_413);
	return (true);
}

bool RequestProcessor::checkEarlyReceivedSize(Client &client)
{
	Request &req = client.getRequest();
	if (!req.isHeaderFull())
	{
		if (req.getRequest().size() > MAX_HEADER_SIZE)
		{
			client.getResponse().setHttpVersion("HTTP/1.1");
			client.setShouldClose(true);
			client.getResponse().setHeader("Connection", "close");
			sendErrorResponse(client, HTTP_400);
			return (true);
		}
		return (false);
	}
	if (!client.getServer())
		return (false);
	unsigned long maxBody = client.getServer()->getClientMaxBodySize();
	size_t received = req.getBodyBytesReceived();
	if (received > maxBody)
	{
		client.getResponse().setHttpVersion("HTTP/1.1");
		determineConnectionBehavior(client);
		client.setShouldClose(true);
		client.getResponse().setHeader("Connection", "close");
		sendErrorResponse(client, HTTP_413);
		return (true);
	}
	return (false);
}

void RequestProcessor::handleIncompleteRequest(Client &client)
{
	client.getResponse().setHttpVersion("HTTP/1.1");
	client.setShouldClose(true);
	client.getResponse().setHeader("Connection", "close");
	sendErrorResponse(client, HTTP_400);
}

/**
 * @brief Résout l'hôte virtuel depuis l'en-tête Host
 *
 * Cherche le serveur virtuel correspondant au nom d'hôte de la requête.
 *
 * @param client Référence vers le client
 */
bool RequestProcessor::resolveVirtualHost(Client &client)
{
	if (!_servers || !client.getServer())
		return (true);
	map_str_str::const_iterator it = client.getRequest().getHeaders().find("host");
	if (it == client.getRequest().getHeaders().end())
		return (true);
	string host = it->second;
	size_t colon = host.find(':');
	if (colon != string::npos)
		host = host.substr(0, colon);
	int port = client.getServer()->getPort();
	for (size_t i = 0; i < _servers->size(); ++i)
	{
		if ((*_servers)[i].getPort() == port
			&& (*_servers)[i].getServerName() == host)
		{
			client.setServer(&(*_servers)[i]);
			return (true);
		}
	}
	return (true);
}

/**
 * @brief Vérifie si une méthode HTTP est autorisée pour une location
 *
 * @param method Méthode HTTP à vérifier
 * @param loc Pointeur vers la location (ou NULL pour autoriser)
 * @return true si la méthode est autorisée, false sinon
 */
bool RequestProcessor::isMethodAllowed(const string &method, const Location *loc) const
{
	if (!loc)
		return true;
	const vector_string &allowed = loc->getAllowMethods();
	if (allowed.empty())
		return true;
	string check = (method == "HEAD") ? "GET" : method;
	for (size_t i = 0; i < allowed.size(); ++i)
	{
		if (allowed[i] == check)
			return true;
	}
	return false;
}

/**
 * @brief Construit le chemin complet vers un fichier depuis l'URI
 *
 * Résout le chemin en combinant la racine, l'URI et le fichier d'index.
 *
 * @param uri URI de la requête
 * @param server Référence vers le serveur
 * @param loc Pointeur vers la location (ou NULL)
 * @return Chemin absolu vers le fichier, ou chaîne vide en cas d'erreur
 */
string RequestProcessor::buildFilePath(const string &uri, const Server &server,
	const Location *loc) const
{
	string root = loc ? loc->getEffectiveRoot(server.getRoot()) : server.getRoot();
	string index = loc ? loc->getEffectiveIndex(server.getIndex()) : server.getIndex();

	string path = FileUtils::ensureTrailingSlash(root);
	string cleanUri = StringUtils::urlDecode(uri);
	if (cleanUri.empty() && !uri.empty())
		return ("");
	if (!cleanUri.empty() && cleanUri[0] == '/')
		cleanUri = cleanUri.substr(1);
	path += cleanUri;

	if (FileUtils::isDirectory(path))
		path = FileUtils::ensureTrailingSlash(path) + index;

	return path;
}

/**
 * @brief Détermine si la connexion doit être maintenue ou fermée
 *
 * Analyse la version HTTP et l'en-tête Connection pour décider.
 *
 * @param client Référence vers le client
 */
void RequestProcessor::determineConnectionBehavior(Client &client)
{
	string version = client.getRequest().getHttpVersion();
	const map_str_str &headers = client.getRequest().getHeaders();
	map_str_str::const_iterator conn_it = headers.find("connection");
	string connVal;
	if (conn_it != headers.end())
		connVal = StringUtils::toLower(conn_it->second);

	bool shouldClose = false;

	if (version == "HTTP/1.0")
	{
		shouldClose = true;
		if (connVal == "keep-alive")
			shouldClose = false;
	}
	else
	{
		shouldClose = false;
		if (connVal == "close")
			shouldClose = true;
	}

	client.setShouldClose(shouldClose);

	if (shouldClose)
		client.getResponse().setHeader("Connection", "close");
	else
		client.getResponse().setHeader("Connection", "keep-alive");
}

/**
 * @brief Gestion d'une méthode HTTP non autorisée
 *
 * Envoie une erreur 405 Method Not Allowed avec l'en-tête Allow.
 *
 * @param client Référence vers le client
 * @param loc Pointeur vers la location
 * @param method Méthode HTTP demandée
 * @return true si la méthode est interdite, false si autorisée
 */
bool RequestProcessor::handleMethodNotAllowed(Client &client, const Location *loc,
	const string &method)
{
	if (isMethodAllowed(method, loc))
		return false;
	determineConnectionBehavior(client);
	const vector_string &allowed = loc->getAllowMethods();
	string allowHeader;
	for (size_t i = 0; i < allowed.size(); ++i)
	{
		if (i > 0)
			allowHeader += ", ";
		allowHeader += allowed[i];
	}
	client.getResponse().setHeader("Allow", allowHeader);
	sendErrorResponse(client, HTTP_405);
	return true;
}

/**
 * @brief Gestion des redirections HTTP
 *
 * Si la location définit une redirection, envoie une réponse 301.
 *
 * @param client Référence vers le client
 * @param loc Pointeur vers la location
 * @return true si une redirection est effectuée, false sinon
 */
bool RequestProcessor::handleRedirect(Client &client, const Location *loc)
{
	if (!loc || loc->getReturn().empty())
		return false;
	determineConnectionBehavior(client);
	Response &response = client.getResponse();
	response.setStatus(HTTP_301);
	response.setHeader("Location", loc->getReturn());
	response.setBody("");
	response.buildResponse();
	return true;
}

/**
 * @brief Dispatche la requête vers le gestionnaire approprié
 *
 * Redirige vers CGI, fichier statique, ou gestionnaire de méthode spécifique.
 *
 * @param client Référence vers le client
 * @param server Référence vers le serveur
 * @param loc Pointeur vers la location
 * @param method Méthode HTTP
 * @param uri URI de la requête
 */
void RequestProcessor::dispatchRequest(Client &client, const Server &server,
	const Location *loc, const string &method, const string &uri)
{
	if (handleCookieRoutes(client, method, uri))
		return;
	if (_cgiHandler.isCgiRequest(uri, loc))
	{
		if (!_cgiHandler.executeCgi(client, server, loc))
			return;
		return;
	}
	if (method == "GET" || method == "HEAD")
	{
		string filePath = buildFilePath(uri, server, loc);
		if (filePath.empty())
		{
			sendErrorResponse(client, HTTP_400);
			return;
		}
		if (!FileUtils::fileExists(filePath))
		{
			handleMissingFile(client, server, loc, uri, method);
			return;
		}
		if (!FileUtils::isPathSafe(filePath, server.getRoot()))
		{
			sendErrorResponse(client, HTTP_403);
			return;
		}
		serveStaticFile(client, filePath);
		if (method == "HEAD")
			client.getResponse().stripBodyFromFinalResponse();
	}
	else if (method == "POST")
		handlePost(client, server, loc);
	else if (method == "DELETE")
		handleDelete(client, server, loc);
	else
		sendErrorResponse(client, HTTP_501);
}
