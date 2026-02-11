/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestProcessor.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:15:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/04 16:15:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestProcessor.hpp"
#include "Location.hpp"
#include "StringUtils.hpp"
#include <fstream>
#include <sstream>
#include <cstdio>
#include <dirent.h>

RequestProcessor::RequestProcessor() : _loader(NULL), _servers(NULL)
{
}

RequestProcessor::~RequestProcessor()
{
}

void RequestProcessor::setLoader(const Loader *loader)
{
	_loader = loader;
}

void RequestProcessor::setServers(std::vector<Server> *servers)
{
	_servers = servers;
}

void RequestProcessor::resolveVirtualHost(Client &client)
{
	if (!_servers || !client.getServer())
		return;
	map_str_str::const_iterator it = client.getRequest().getHeaders().find("host");
	if (it == client.getRequest().getHeaders().end())
		return;
	string host = it->second;
	size_t colon = host.find(':');
	if (colon != string::npos)
		host = host.substr(0, colon);
	int port = client.getServer()->getPort();
	for (size_t i = 0; i < _servers->size(); ++i)
	{
		if ((*_servers)[i].getPort() == port
			&& (*_servers)[i].getServerName().find(host) != string::npos)
		{
			client.setServer(&(*_servers)[i]);
			return;
		}
	}
}

// ============================================================================
// Méthodes utilitaires
// ============================================================================

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

string RequestProcessor::buildFilePath(const string &uri, const Server &server, const Location *loc) const
{
	string root = loc ? loc->getEffectiveRoot(server.getRoot()) : server.getRoot();
	string index = loc ? loc->getEffectiveIndex(server.getIndex()) : server.getIndex();

	string path = FileUtils::ensureTrailingSlash(root);
	string cleanUri = StringUtils::urlDecode(uri);
	if (!cleanUri.empty() && cleanUri[0] == '/')
		cleanUri = cleanUri.substr(1);
	path += cleanUri;

	if (FileUtils::isDirectory(path))
		path = FileUtils::ensureTrailingSlash(path) + index;

	return path;
}

// ============================================================================
// Gestion de connexion (RFC 1945)
// ============================================================================

void RequestProcessor::determineConnectionBehavior(Client &client)
{
	string version = client.getRequest().getHttpVersion();
	const map_str_str &headers = client.getRequest().getHeaders();
	map_str_str::const_iterator conn_it = headers.find("connection");

	bool shouldClose = false;

	if (version == "HTTP/1.0")
	{
		shouldClose = true;
		if (conn_it != headers.end() && conn_it->second == "keep-alive")
			shouldClose = false;
	}
	else
	{
		shouldClose = false;
		if (conn_it != headers.end() && conn_it->second == "close")
			shouldClose = true;
	}

	client.setShouldClose(shouldClose);

	if (shouldClose)
		client.getResponse().setHeader("Connection", "close");
	else
		client.getResponse().setHeader("Connection", "keep-alive");
}

// ============================================================================
// Réponses HTTP
// ============================================================================

void RequestProcessor::sendErrorResponse(Client &client, int code, const string &message)
{
	Response &response = client.getResponse();
	response.setStatus(code, message);
	response.setHeader("Content-Type", "text/html");

	const Server *server = client.getServer();
	if (server)
	{
		map_int_string errors = server->getError();
		map_int_string::iterator it = errors.find(code);
		if (it != errors.end())
		{
			string path = server->getRoot() + "/" + it->second;
			if (FileUtils::fileExists(path))
			{
				ifstream file(path.c_str(), std::ios::binary);
				if (file.is_open())
				{
					stringstream content;
					content << file.rdbuf();
					file.close();
					response.setBody(content.str());
					response.buildResponse();
					return;
				}
			}
		}
	}

	stringstream body;
	body << "<html><head><title>" << code << " " << message << "</title></head>";
	body << "<body><h1>" << code << " " << message << "</h1></body></html>";

	response.setBody(body.str());
	response.buildResponse();
}

void RequestProcessor::serveStaticFile(Client &client, const string &filePath)
{
	ifstream file(filePath.c_str(), std::ios::binary);
	if (!file.is_open())
	{
		sendErrorResponse(client, 404, "Not Found");
		return;
	}

	stringstream content;
	content << file.rdbuf();
	file.close();

	string mimeType = "application/octet-stream";
	size_t dotPos = filePath.rfind('.');
	if (dotPos != string::npos && _loader)
		mimeType = _loader->getMimeType(filePath.substr(dotPos + 1));

	Response &response = client.getResponse();
	response.setStatus(200, "OK");
	response.setHeader("Content-Type", mimeType);
	response.setBody(content.str());
	response.buildResponse();
}

// ============================================================================
// Traitement principal - Sous-fonctions
// ============================================================================

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
		sendErrorResponse(client, 500, "Internal Server Error");
		return false;
	}
	resolveVirtualHost(client);
	return true;
}

bool RequestProcessor::validateRequestBody(Client &client, const Server &server)
{
	const Request &req = client.getRequest();
	if (req.getMethod() == "POST" && req.getContentLength() < 0)
	{
		determineConnectionBehavior(client);
		sendErrorResponse(client, 400, "Bad Request");
		return false;
	}
	if (req.getContentLength() > 0)
	{
		unsigned long maxBody = server.getClientMaxBodySize();
		if (static_cast<unsigned long>(req.getContentLength()) > maxBody)
		{
			determineConnectionBehavior(client);
			sendErrorResponse(client, 413, "Request Entity Too Large");
			return false;
		}
	}
	return true;
}

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
	sendErrorResponse(client, 405, "Method Not Allowed");
	return true;
}

bool RequestProcessor::handleRedirect(Client &client, const Location *loc)
{
	if (!loc || loc->getReturn().empty())
		return false;
	determineConnectionBehavior(client);
	Response &response = client.getResponse();
	response.setStatus(301, "Moved Permanently");
	response.setHeader("Location", loc->getReturn());
	response.setBody("");
	response.buildResponse();
	return true;
}

void RequestProcessor::dispatchRequest(Client &client, const Server &server,
									   const Location *loc, const string &method,
									   const string &uri)
{
	// Routes spéciales pour les cookies
	if (uri == "/setcookie" && method == "GET")
	{
		Response &response = client.getResponse();
		response.setStatus(200, "OK");
		response.setHeader("Content-Type", "text/html; charset=utf-8");
		response.setHeader("Set-Cookie", "session=webserv_test_123; Path=/; Max-Age=3600");
		response.setBody("<html><body><h1>Cookie défini !</h1><p>session=webserv_test_123</p></body></html>");
		response.buildResponse();
		return;
	}
	if (uri == "/deletecookie" && method == "GET")
	{
		Response &response = client.getResponse();
		response.setStatus(200, "OK");
		response.setHeader("Content-Type", "text/html; charset=utf-8");
		response.setHeader("Set-Cookie", "session=; Path=/; Max-Age=0");
		response.setBody("<html><body><h1>Cookie supprimé !</h1></body></html>");
		response.buildResponse();
		return;
	}
	if (uri == "/showcookies" && method == "GET")
	{
		string sessionCookie = client.getRequest().getCookie("session");
		Response &response = client.getResponse();
		response.setStatus(200, "OK");
		response.setHeader("Content-Type", "text/html; charset=utf-8");
		string body = "<html><body><h1>Cookies reçus</h1>";
		if (!sessionCookie.empty())
			body += "<p>session = " + sessionCookie + "</p>";
		else
			body += "<p>Aucun cookie 'session' trouvé</p>";
		body += "</body></html>";
		response.setBody(body);
		response.buildResponse();
		return;
	}
	
	if (method == "GET" || method == "HEAD")
	{
		string filePath = buildFilePath(uri, server, loc);
		if (filePath.find("..") != string::npos)
		{
			sendErrorResponse(client, 403, "Forbidden");
			return;
		}
		if (!FileUtils::fileExists(filePath))
		{
			handleMissingFile(client, server, loc, uri, method);
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
		sendErrorResponse(client, 501, "Not Implemented");
}

// ============================================================================
// Traitement principal
// ============================================================================

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

// ============================================================================
// Méthodes POST - Utilitaires
// ============================================================================

string RequestProcessor::getUploadPath(const Server &server, const Location *loc) const
{
	return loc ? loc->getEffectiveUploadPath(server.getRoot()) : server.getRoot();
}

string RequestProcessor::extractBoundary(const string &contentType) const
{
	size_t pos = contentType.find("boundary=");
	if (pos == string::npos)
		return "";
	return contentType.substr(pos + 9);
}

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

bool RequestProcessor::saveUploadedFile(const string &uploadPath, const string &filename, const string &content)
{
	string fullPath = FileUtils::ensureTrailingSlash(uploadPath) + filename;

	ofstream file(fullPath.c_str(), std::ios::binary);
	if (!file.is_open())
		return false;
	file.write(content.c_str(), content.size());
	file.close();
	return true;
}

void RequestProcessor::sendSuccessResponse(Client &client, int code, const string &message, const string &body)
{
	Response &response = client.getResponse();
	response.setStatus(code, message);
	response.setHeader("Content-Type", "text/html");
	response.setBody(body);
	response.buildResponse();
}

// ============================================================================
// Méthodes POST - Handlers
// ============================================================================

bool RequestProcessor::handleMultipartUpload(Client &client, const string &uploadPath)
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
		pos += delimiter.size();
		if (body.substr(pos, 2) == "--")
			break;

		size_t headerEnd = body.find("\r\n\r\n", pos);
		if (headerEnd == string::npos)
			break;

		size_t nextBoundary = body.find(delimiter, headerEnd);
		if (nextBoundary == string::npos)
			break;

		string partHeaders = body.substr(pos, headerEnd - pos);
		string partContent = body.substr(headerEnd + 4, nextBoundary - headerEnd - 6);
		string filename = extractFilename(partHeaders);

		if (!filename.empty())
		{
			if (!saveUploadedFile(uploadPath, filename, partContent))
				return false;
		}
	}
	return true;
}

void RequestProcessor::handleDelete(Client &client, const Server &server, const Location *loc)
{
	string uri = client.getRequest().getUri();
	string filePath = buildFilePath(uri, server, loc);

	if (filePath.find("..") != string::npos)
	{
		sendErrorResponse(client, 403, "Forbidden");
		return;
	}
	if (!FileUtils::fileExists(filePath))
	{
		sendErrorResponse(client, 404, "Not Found");
		return;
	}
	if (FileUtils::isDirectory(filePath))
	{
		sendErrorResponse(client, 403, "Forbidden");
		return;
	}
	if (std::remove(filePath.c_str()) == 0)
	{
		Response &response = client.getResponse();
		response.setStatus(204, "No Content");
		response.setBody("");
		response.buildResponse();
	}
	else
		sendErrorResponse(client, 500, "Internal Server Error");
}

void RequestProcessor::handleMissingFile(Client &client, const Server &server,
										 const Location *loc, const string &uri,
										 const string &method)
{
	string root = loc ? loc->getEffectiveRoot(server.getRoot()) : server.getRoot();
	string dirPath = FileUtils::ensureTrailingSlash(root);
	string cleanUri = uri;
	if (!cleanUri.empty() && cleanUri[0] == '/')
		cleanUri = cleanUri.substr(1);
	dirPath += cleanUri;
	if (loc && loc->getAutoindex() && FileUtils::isDirectory(dirPath))
		handleAutoindex(client, dirPath, uri);
	else
		sendErrorResponse(client, 404, "Not Found");
	if (method == "HEAD")
		client.getResponse().stripBodyFromFinalResponse();
}

void RequestProcessor::handleAutoindex(Client &client, const string &dirPath, const string &uri)
{
	DIR *dir = opendir(dirPath.c_str());
	if (!dir)
	{
		sendErrorResponse(client, 500, "Internal Server Error");
		return;
	}

	string baseUri = FileUtils::ensureTrailingSlash(uri);
	string safeUri = StringUtils::escapeHtml(baseUri);
	string body = "<html><head><title>Index of " + safeUri + "</title></head><body>";
	body += "<h1>Index of " + safeUri + "</h1><hr><pre>";

	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL)
	{
		string name = entry->d_name;
		if (name == ".")
			continue;
		string safeName = StringUtils::escapeHtml(name);
		string encodedName = StringUtils::urlEncode(name);
		string link = "<a href=\"" + baseUri + encodedName + "\">" + safeName + "</a>\n";
		body += link;
	}
	closedir(dir);
	body += "</pre><hr></body></html>";
	sendSuccessResponse(client, 200, "OK", body);
}

void RequestProcessor::handlePost(Client &client, const Server &server, const Location *loc)
{
	const string &contentType = client.getRequest().getContentType();
	string uploadPath = getUploadPath(server, loc);

	if (contentType.find("multipart/form-data") != string::npos)
	{
		if (!handleMultipartUpload(client, uploadPath))
		{
			sendErrorResponse(client, 400, "Bad Request");
			return;
		}
		sendSuccessResponse(client, 201, "Created", "<html><body><h1>File uploaded successfully</h1></body></html>");
	}
	else
	{
		sendSuccessResponse(client, 200, "OK", "<html><body><h1>POST received</h1></body></html>");
	}
}
