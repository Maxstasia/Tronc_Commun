/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Loader.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 15:02:03 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/01/13 11:48:05 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Loader.hpp"
#include "Tokenizer.hpp"
#include "Validator.hpp"
#include "MimeTypeRegistry.hpp"
#include "DirectiveRegistry.hpp"

Loader::~Loader(){}

void Loader::Print_MIME()
{
	for (size_t i = 0; i < mime_type.size(); i++)
	{
		std::cout << mime_type[i].first << "-> " << mime_type[i].second << std::endl;
	}
}
Loader::Loader(const string &configFile)
{
	try
	{
		_configFile = configFile;

		// Load directive types
		DirectiveRegistry directiveRegistry;
		directiveRegistry.load();
		directive_type = directiveRegistry.getDirectiveTypes();

		// Tokenize config file
		Tokenizer tokenizer(configFile);
		listLexer = tokenizer.tokenize();
		nb_brace = 0; // Reset after tokenization

		// Validate tokens
		try
		{
			Validator validator(directive_type, listLexer, nb_brace);
			validator.validate();
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
			exit(1);
		}

		// Load MIME types
		MimeTypeRegistry mimeRegistry;
		mimeRegistry.load();
		mime_type = mimeRegistry.getMimeTypes();
	}
	catch (const std::exception &e)
	{
		std::cerr << "Loader: " << e.what() << std::endl;
		throw;
	}
}

Loader::Loader(const Loader &other)
{
	*this = other;
}
// tode a evoir
Loader &Loader::operator=(const Loader &other)
{
	if (this != &other)
	{
		_configFile = other._configFile;
	}
	return (*this);
}
