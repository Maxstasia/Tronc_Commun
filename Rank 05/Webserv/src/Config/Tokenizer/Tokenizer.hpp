/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:00:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/04 15:00:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "FileUtils.hpp"

class Tokenizer
{
  private:
	string _configFile;
	int _braceCount;
	list_pair_str_int _tokens;

	vector_string trimLine(const string &line);
	bool parseLocation(const vector_string &tokens);
	bool parseSection(const vector_string &tokens);
	bool parseCloseBrace(const vector_string &tokens);
	bool parseOpenBrace(const vector_string &tokens, int index);
	bool parseComment(const vector_string &tokens);
	void parseDirective(const vector_string &tokens);

  public:
	Tokenizer();
	Tokenizer(const string &configFile);
	~Tokenizer();
	Tokenizer(const Tokenizer &other);
	Tokenizer &operator=(const Tokenizer &other);

	list_pair_str_int tokenize();
	const list_pair_str_int &getTokens() const;
};
