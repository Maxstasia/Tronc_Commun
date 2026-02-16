/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:00:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "FileUtils.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Location.hpp"

#define CGI_TIMEOUT_SEC 5

class CgiHandler
{
  private:
	char **buildEnvp(const Request &req, const Server &server,
					 const string &scriptPath, const string &pathInfo);
	void freeEnvp(char **envp);
	void addEnvVar(std::vector<string> &env, const string &key, const string &value);
	void addCgiHttpHeaders(std::vector<string> &env, const Request &req);
	char **vecToEnvp(const std::vector<string> &env);
	string buildScriptPath(const string &uri, const Server &server, const Location *loc);
	void setCgiError(Response &response, int code, const string &msg);
	void executeCgiChild(int pipe_in[2], int pipe_out[2],
						 const string &cgiPath, const string &scriptPath, char **envp);
	void executeCgiParent(Client &client, pid_t pid,
						  int pipeWriteEnd, int pipeReadEnd, char **envp);
	void parseCgiHeaders(Response &response, const string &headerPart,
						 int &statusCode, string &statusMsg);

  public:
	CgiHandler();
	CgiHandler(const CgiHandler &other);
	CgiHandler &operator=(const CgiHandler &other);
	~CgiHandler();

	bool isCgiRequest(const string &uri, const Location *loc) const;
	bool executeCgi(Client &client, const Server &server, const Location *loc);
	void finishCgi(Client &client);
};
