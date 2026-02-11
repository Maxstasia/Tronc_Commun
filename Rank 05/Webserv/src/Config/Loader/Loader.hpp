/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Loader.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 14:54:37 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/01/13 13:38:43 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "FileUtils.hpp"
#include "Server.hpp"
#include <vector>

typedef std::vector<Server>  vect_serv;
class Loader
{
  private:
	string _configFile;
	int nb_brace;
	list_pair_str_int listLexer;
	vector_pair_string mime_type;
	vector_string directive_type;


	// valide config
	void valideConfig(list_pair_str_int &lst);
	void checkBraceBalance() const;
	void validateSection(lst_iterator it, lst_iterator next) const;
	void validateUrl(lst_iterator it, lst_iterator next) const;
	void validateDirective(lst_iterator it, lst_iterator next) const;
	void validateEmptyBlock(lst_iterator it, lst_iterator next,lst_iterator end) const;
	void validateStartToken(const list_pair_str_int &lst) const;

	// tokenisation
	void tokenizeLine(const string &configFile);
	void loadMimeTypes();
	void Print_MIME();
	void printLexer() const;
	vector_string trimLine(const string &line);
	bool parseLocation(const vector_string &tokens);
	bool parseSection(const vector_string &tokens);
	bool parseCloseBrace(const vector_string &tokens);
	bool parseOpenBrace(const vector_string &tokens, int index);
	bool parseComment(const vector_string &tokens);
	void parseDirective(const vector_string &tokens);

	// load_files
	void loadDirectivesTypes();
	void loadTypesFile(const string &fileName,
		void (Loader::*lineHandler)(const string &));
	void handleMimeLine(const string &line);
	void handleDirectiveLine(const string &line);
	bool isDirectiveAllowed(const string &key) const;

	// pars_server
	void creatServe();

public:
	const list_pair_str_int &getListLexer() const;
	string getMimeType(const string &extension) const;

public:
	Loader();
	 Loader(const string &configFile);
	 Loader &operator=(const Loader &other);
	 Loader(const Loader &other);
	 virtual ~Loader();


};
