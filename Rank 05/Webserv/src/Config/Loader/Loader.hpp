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
#include "Tokenizer.hpp"
#include "DirectiveRegistry.hpp"
#include "MimeTypeRegistry.hpp"
#include <vector>

typedef std::vector<Server>  vect_serv;
class Loader
{
  private:
	string _configFile;
	DirectiveRegistry _directiveRegistry;
	Tokenizer _tokenizer;
	MimeTypeRegistry _mimeRegistry;

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
