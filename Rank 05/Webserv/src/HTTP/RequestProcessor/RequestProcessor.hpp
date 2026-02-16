/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestProcessor.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:15:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/04 16:15:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "FileUtils.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Loader.hpp"
#include "CgiHandler.hpp"

class Location;

class RequestProcessor
{
  private:
	const Loader *_loader;
	std::vector<Server> *_servers;
	CgiHandler _cgiHandler;

	void resolveVirtualHost(Client &client);
	string buildFilePath(const string &uri, const Server &server, const Location *loc) const;
	bool isMethodAllowed(const string &method, const Location *loc) const;
	bool initRequestContext(Client &client);
	bool validateRequestBody(Client &client, const Server &server);
	bool handleMethodNotAllowed(Client &client, const Location *loc, const string &method);
	bool handleRedirect(Client &client, const Location *loc);
	bool handleCookieRoutes(Client &client, const string &method, const string &uri);
	void sendCookieResponse(Client &client, const string &setCookie, const string &body);
	void dispatchRequest(Client &client, const Server &server, const Location *loc,
						 const string &method, const string &uri);

	void serveStaticFile(Client &client, const string &filePath);
	void sendErrorResponse(Client &client, int code, const string &message);
	void determineConnectionBehavior(Client &client);
	void handlePost(Client &client, const Server &server, const Location *loc);
	void handleDelete(Client &client, const Server &server, const Location *loc);
	void handleAutoindex(Client &client, const string &dirPath, const string &uri);
	void handleMissingFile(Client &client, const Server &server, const Location *loc,
						   const string &uri, const string &method);
	bool handleMultipartUpload(Client &client, const string &uploadPath);
	void sendSuccessResponse(Client &client, int code, const string &message, const string &body);

	string getUploadPath(const Server &server, const Location *loc) const;
	string generatePostFilename(const string &contentType) const;
	string extractBoundary(const string &contentType) const;
	string extractFilename(const string &headers) const;
	bool saveUploadedFile(const string &uploadPath, const string &filename, const string &content);
	bool processMultipartPart(const string &body, const string &delimiter,
							  size_t &pos, const string &uploadPath);

  public:
	RequestProcessor();
	~RequestProcessor();

	void setLoader(const Loader *loader);
	void setServers(std::vector<Server> *servers);
	void processRequest(Client &client);
	bool checkEarlyBodySize(Client &client);
};
