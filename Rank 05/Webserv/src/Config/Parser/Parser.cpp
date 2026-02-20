#include "Parser.hpp"
#include "Location.hpp"
#include "Validator.hpp"

Parser::Parser()
{}

Parser::Parser(const Parser &other)
{
	(void)other;
}

Parser &Parser::operator=(const Parser &other)
{
	if (this != &other)
	{
		(void)other;
	}
	return (*this);
}

Parser::~Parser()
{}


/**
 * @brief Parse les tokens pour extraire les blocs de configuration des serveurs
 *
 * Parcourt la liste de tokens et identifie chaque bloc "server", puis construit
 * un objet Server pour chacun d'eux.
 *
 * @param tokens Liste des tokens à analyser
 * @return Vecteur contenant tous les serveurs parsés
 * @throws std::runtime_error Si aucun token n'est fourni ou si un bloc serveur est vide
 */
std::vector<Server> Parser::parseServers(const list_pair_str_int &tokens)
{
	std::vector<Server> servers;
	if (tokens.empty())
		throw std::runtime_error("Parser: No tokens to parse");
	lst_iterator it = tokens.begin();
	while (it != tokens.end())
	{
		if (it->first == "server")
		{
			++it;
			if (it == tokens.end())
				throw std::runtime_error("Parser: Empty server block");
			servers.push_back(Parser().parseServerBlock(it, tokens));
			continue ;
		}
		++it;
	}
	return (servers);
}

/**
 * @brief Vérifie qu'une valeur suit une directive
 *
 * Incrémente l'itérateur et vérifie que le token suivant est bien de type VALUE.
 *
 * @param directive_it Itérateur pointant sur la directive
 * @param tokens Liste complète des tokens
 * @param error_msg Message d'erreur à afficher si la valeur est manquante
 * @return Itérateur pointant sur la valeur
 * @throws std::runtime_error Si aucune valeur ne suit la directive
 */
lst_iterator Parser::expectValue(lst_iterator directive_it, const list_pair_str_int &tokens, const string &error_msg) const
{
	lst_iterator value_it = directive_it;
	++value_it;
	if (value_it == tokens.end() || value_it->second != VALUE)
		throw std::runtime_error(error_msg);
	return value_it;
}

/**
 * @brief Parse la directive 'root' d'un serveur
 *
 * Lit la valeur de la directive root, valide le chemin et l'assigne au serveur.
 *
 * @param server Référence vers l'objet Server à configurer
 * @param it Itérateur sur les tokens (modifié par effet de bord)
 * @param tokens Liste complète des tokens
 * @throws std::runtime_error Si la valeur est manquante ou invalide
 */
void Parser::parseRoot(Server &server, lst_iterator &it, const list_pair_str_int &tokens) const
{
	const string root_path = readSingleValue(it, tokens, "Parser: Expected value after root directive", "Parser: Unexpected value after value of root directive");
	Validator::validatePath(root_path, "root");
	server.setRoot(root_path);
}

/**
 * @brief Lit une valeur unique après une directive
 *
 * Vérifie qu'une seule valeur suit la directive, retire le point-virgule final
 * et retourne la valeur nettoyée.
 *
 * @param it Itérateur sur les tokens (modifié par effet de bord)
 * @param tokens Liste complète des tokens
 * @param missing_msg Message d'erreur si la valeur est manquante
 * @param extra_msg Message d'erreur s'il y a des valeurs supplémentaires
 * @return La valeur nettoyée (sans point-virgule final)
 * @throws std::runtime_error Si la valeur est manquante ou multiple
 */
string Parser::readSingleValue(lst_iterator &it, const list_pair_str_int &tokens, const string &missing_msg, const string &extra_msg) const
{
	lst_iterator value_it = expectValue(it, tokens, missing_msg);
	ensureSingleValue(value_it, tokens, extra_msg);
	it = value_it;
	return stripTrailingSemicolon(value_it->first);
}

/**
 * @brief Parse un bloc de configuration location
 *
 * Extrait le chemin de la location, crée un nouvel objet Location et parse
 * toutes les directives contenues dans le bloc.
 *
 * @param server Référence vers le serveur auquel ajouter la location
 * @param it Itérateur sur les tokens (modifié par effet de bord)
 * @param tokens Liste complète des tokens
 * @throws std::runtime_error Si le format du bloc location est invalide ou incomplet
 */
void Parser::parseLocationBlock(Server &server, lst_iterator &it, const list_pair_str_int &tokens) const
{
	if (it == tokens.end())
		throw std::runtime_error("Parser: Malformed location directive (missing path)");
	++it;
	if (it == tokens.end() || it->second != URL)
		throw std::runtime_error("Parser: Expected location path after 'location'");
	Location &location = server.addLocation();
	location.setPath(it->first);
	++it;
	if (it == tokens.end() || it->second != CURLY_BRACKET_OPEN)
		throw std::runtime_error("Parser: Expected '{' after location path");

	std::set<string> seen_directives;
	int depth = 0;
	for (++it; it != tokens.end(); ++it)
	{
		if (it->second == CURLY_BRACKET_OPEN)
		{
			++depth;
			continue;
		}
		if (it->second == CURLY_BRACKET_CLOSED)
		{
			if (depth == 0)
				break;
			--depth;
			continue;
		}
		if (it->second == DIRECTIVE)
		{
			const string &directive = it->first;
			if (directive != "allow_methods")
				checkDuplicateDirective(seen_directives, directive);
			parseLocationDirective(location, it, tokens);
		}
	}
	if (it == tokens.end())
		throw std::runtime_error("Parser: Unterminated location block");
}


/**
 * @brief Parse la directive 'index' d'un serveur
 *
 * Lit la valeur de la directive index, valide le chemin et l'assigne au serveur.
 *
 * @param server Référence vers l'objet Server à configurer
 * @param it Itérateur sur les tokens (modifié par effet de bord)
 * @param tokens Liste complète des tokens
 * @throws std::runtime_error Si la valeur est manquante ou invalide
 */
void Parser::parseIndex(Server &server, lst_iterator &it, const list_pair_str_int &tokens) const
{
	const string index_path = readSingleValue(it, tokens, "Parser: Expected value after index directive", "Parser: Unexpected value after value of index directive");
	Validator::validatePath(index_path, "index");
	server.setIndex(index_path);
}

