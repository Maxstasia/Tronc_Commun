/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserLocation.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 17:05:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/01/21 10:24:04 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "Validator.hpp"

void Parser::parseAutoindex(Location &location, lst_iterator &it, const list_pair_str_int &tokens) const
{
	const string value = readSingleValue(it, tokens, "Parser: Expected value after autoindex directive", "Parser: Unexpected value after value of autoindex directive");
	location.setAutoindex(value == "on");
}

void Parser::parseAllowMethods(Location &location, lst_iterator &it, const list_pair_str_int &tokens) const
{
	const string valid_methods_array[] = {VALID_HTTP_METHODS};
	vector_string valid_methods(valid_methods_array, valid_methods_array + VALID_HTTP_METHODS_COUNT);

	lst_iterator value_it = expectValue(it, tokens, "Parser: Expected value after allow_methods directive");
	vector_string methods;
	lst_iterator walker = value_it;
	while (walker != tokens.end() && walker->second == VALUE)
	{
		string method = walker->first;
		if (!method.empty() && method[method.size() - 1] == ';')
			method = method.substr(0, method.size() - 1);

		Validator::validateHTTPMethod(method);
		methods.push_back(method);
		++walker;
	}
	if (methods.empty())
		throw std::runtime_error("Parser: Missing methods after allow_methods directive");
	lst_iterator last_value = walker;
	--last_value;
	location.setAllowMethods(methods);
	it = last_value;
}

void Parser::parseReturn(Location &location, lst_iterator &it, const list_pair_str_int &tokens) const
{
	location.setReturn(readSingleValue(it, tokens, "Parser: Expected value after return directive", "Parser: Unexpected value after value of return directive"));
}

void Parser::parseLocationDirective(Location &location, lst_iterator &it, const list_pair_str_int &tokens) const
{
	const string &directive = it->first;
	if (directive == "root")
	{
		const string root_path = readSingleValue(it, tokens, "Parser: Expected value after root directive", "Parser: Unexpected value after value of root directive");
		Validator::validatePath(root_path, "root");
		location.setRoot(root_path);
	}
	else if (directive == "index")
	{
		const string index_path = readSingleValue(it, tokens, "Parser: Expected value after index directive", "Parser: Unexpected value after value of index directive");
		Validator::validatePath(index_path, "index");
		location.setIndex(index_path);
	}
	else if (directive == "upload_path")
	{
		const string path = readSingleValue(it, tokens, "Parser: Expected value after upload_path directive", "Parser: Unexpected value after value of upload_path directive");
		Validator::validatePath(path, "upload_path");
		location.setUploadPath(path);
	}
	else if (directive == "autoindex")
		parseAutoindex(location, it, tokens);
	else if (directive == "allow_methods")
		parseAllowMethods(location, it, tokens);
	else if (directive == "return")
		parseReturn(location, it, tokens);
}

