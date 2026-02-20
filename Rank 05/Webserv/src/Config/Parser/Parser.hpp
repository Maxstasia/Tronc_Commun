#pragma once

#include "FileUtils.hpp"
#include "Server.hpp"
#include "Location.hpp"

class Parser
{
  private:
	//ParseServer
	Server parseServerBlock(lst_iterator &it, const list_pair_str_int &tokens) const;
	void ensureSingleValue(lst_iterator value_it, const list_pair_str_int &tokens, const string &error_msg) const;
	string stripTrailingSemicolon(const string &raw) const;
	void parseListen(Server &server, lst_iterator &it, const list_pair_str_int &tokens) const;
	void parseHost(Server &server, lst_iterator &it, const list_pair_str_int &tokens) const;
	void parseServerName(Server &server, lst_iterator &it, const list_pair_str_int &tokens) const;
	void parseErrorPage(Server &server, lst_iterator &it, const list_pair_str_int &tokens) const;
	void parseClientMaxBodySize(Server &server, lst_iterator &it, const list_pair_str_int &tokens) const;
	void checkDuplicateDirective(std::set<string> &seen, const string &directive) const;

	//ParseLocation
	void parseLocationDirective(Location &location, lst_iterator &it, const list_pair_str_int &tokens) const;
	void parseAutoindex(Location &location, lst_iterator &it, const list_pair_str_int &tokens) const;
	void parseAllowMethods(Location &location, lst_iterator &it, const list_pair_str_int &tokens) const;
	void parseReturn(Location &location, lst_iterator &it, const list_pair_str_int &tokens) const;

	//Parse
	lst_iterator expectValue(lst_iterator directive_it, const list_pair_str_int &tokens, const string &error_msg) const;
	void parseRoot(Server &server, lst_iterator &it, const list_pair_str_int &tokens) const;
	string readSingleValue(lst_iterator &it, const list_pair_str_int &tokens, const string &missing_msg, const string &extra_msg) const;
	void parseLocationBlock(Server &server, lst_iterator &it, const list_pair_str_int &tokens) const;
	void parseIndex(Server &server, lst_iterator &it, const list_pair_str_int &tokens) const;

  public:
	Parser();
	Parser(const Parser &other);
	Parser &operator=(const Parser &other);
	~Parser();

	static std::vector<Server> parseServers(const list_pair_str_int &tokens);
};
