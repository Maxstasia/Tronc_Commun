#include "Parser.hpp"
#include "Validator.hpp"

/**
 * @brief Parse la directive 'autoindex' pour activer/désactiver le listing de répertoire
 *
 * Lit la valeur "on" ou autre et configure l'autoindex de la location.
 *
 * @param location Référence vers l'objet Location à configurer
 * @param it Itérateur sur les tokens (modifié par effet de bord)
 * @param tokens Liste complète des tokens
 * @throws std::runtime_error Si la valeur est manquante ou invalide
 */
void Parser::parseAutoindex(Location &location, lst_iterator &it, const list_pair_str_int &tokens) const
{
	const string value = readSingleValue(it, tokens, "Parser: Expected value after autoindex directive", "Parser: Unexpected value after value of autoindex directive");
	if(!(value == "on") && !(value  == "off"))
		throw std::runtime_error("Autoindinx not valide");
	location.setAutoindex(value == "on");
}

/**
 * @brief Parse la directive 'allow_methods' pour définir les méthodes HTTP autorisées
 *
 * Lit une liste de méthodes HTTP (GET, POST, DELETE, etc.) et valide chacune d'elles.
 * Configure la liste des méthodes autorisées pour la location.
 *
 * @param location Référence vers l'objet Location à configurer
 * @param it Itérateur sur les tokens (modifié par effet de bord)
 * @param tokens Liste complète des tokens
 * @throws std::runtime_error Si aucune méthode n'est spécifiée ou si une méthode est invalide
 */
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

/**
 * @brief Parse la directive 'return' pour configurer une redirection
 *
 * Lit la valeur de la directive return (code de statut ou URL) et l'assigne à la location.
 *
 * @param location Référence vers l'objet Location à configurer
 * @param it Itérateur sur les tokens (modifié par effet de bord)
 * @param tokens Liste complète des tokens
 * @throws std::runtime_error Si la valeur est manquante ou invalide
 */
void Parser::parseReturn(Location &location, lst_iterator &it, const list_pair_str_int &tokens) const
{
	location.setReturn(readSingleValue(it, tokens, "Parser: Expected value after return directive", "Parser: Unexpected value after value of return directive"));
}

/**
 * @brief Parse et traite une directive spécifique à un bloc location
 *
 * Identifie le type de directive (root, index, upload_path, autoindex, allow_methods,
 * return, cgi_extension, cgi_path) et délègue son traitement à la fonction appropriée.
 *
 * @param location Référence vers l'objet Location à configurer
 * @param it Itérateur sur les tokens (modifié par effet de bord)
 * @param tokens Liste complète des tokens
 * @throws std::runtime_error Si la directive ou sa valeur est invalide
 */
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
	else if (directive == "cgi_extension")
	{
		const string ext = readSingleValue(it, tokens, "Parser: Expected value after cgi_extension directive", "Parser: Unexpected value after value of cgi_extension directive");
		location.setCgiExtension(ext);
	}
	else if (directive == "cgi_path")
	{
		const string path = readSingleValue(it, tokens, "Parser: Expected value after cgi_path directive", "Parser: Unexpected value after value of cgi_path directive");
		location.setCgiPath(path);
	}
}

