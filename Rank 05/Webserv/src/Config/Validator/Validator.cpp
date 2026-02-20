#include "Validator.hpp"
#include "StringUtils.hpp"

Validator::Validator(const vector_string &directiveTypes, const list_pair_str_int &tokens, int braceCount)
	: _directiveTypes(directiveTypes), _tokens(tokens), _braceCount(braceCount)
{
	validate();
}

Validator::~Validator()
{
}

/**
 * @brief Vérifie l'équilibre des accolades
 *
 * Contrôle que le compteur d'accolades est à zéro, signifiant que toutes les
 * accolades ouvertes ont été correctement fermées.
 *
 * @throws std::runtime_error Si le nombre d'accolades est déséquilibré
 */
void Validator::checkBraceBalance() const
{
	if (_braceCount > 0)
		throw std::runtime_error("Too many opening braces");
	if (_braceCount < 0)
		throw std::runtime_error("Too many closing braces");
}

/**
 * @brief Valide la structure syntaxique de la configuration
 *
 * Parcourt tous les tokens pour vérifier la cohérence syntaxique : sections,
 * directives, valeurs, accolades, et l'équilibre des blocs.
 *
 * @throws std::runtime_error Si une erreur de syntaxe est détectée
 */
void Validator::validate()
{
	int			depth;
	lst_iterator	it;
	lst_iterator	next;

	checkBraceBalance();
	validateStartToken(_tokens);
	depth = 0;
	it = _tokens.begin();
	while (it != _tokens.end())
	{
		next = it;
		++next;
		validateSection(it, next);
		validateUrl(it, next);
		validateDirective(it, next);
		validateEmptyBlock(it, next, _tokens.end());
		if (it->second == CURLY_BRACKET_OPEN)
			depth++;
		if (it->second == CURLY_BRACKET_CLOSED)
		{
			depth--;
			if (depth < 0)
				throw std::runtime_error("Unexpected closing brace");
		}
		++it;
	}
	if (depth != 0)
		throw std::runtime_error("Unbalanced braces in config file");
}

/**
 * @brief Valide une section de configuration
 *
 * Vérifie qu'une section est reconnue, qu'elle a un contenu et que la syntaxe
 * est correcte (notamment pour les sections location qui nécessitent un chemin).
 *
 * @param it Itérateur pointant sur le token de section
 * @param next Itérateur pointant sur le token suivant
 * @throws std::runtime_error Si la section est inconnue ou mal formée
 */
void Validator::validateSection(lst_iterator it, lst_iterator next) const
{
	if (it->second != SECTION)
		return ;
	if (!isDirectiveAllowed(it->first))
		throw std::runtime_error("Unknown section '" + it->first + "'");
	if (next == _tokens.end())
		throw std::runtime_error("Section '" + it->first + "' without content");
	if (it->first == "location")
	{
		if (next->second != URL)
			throw std::runtime_error("'location' must be followed by a path");
	}
	else if (next->second != CURLY_BRACKET_OPEN)
		throw std::runtime_error("Section '" + it->first + "' must be followed by '{'");
}

/**
 * @brief Valide un token de type URL
 *
 * Vérifie qu'une URL est suivie d'une accolade ouvrante.
 *
 * @param it Itérateur pointant sur le token URL
 * @param next Itérateur pointant sur le token suivant
 * @throws std::runtime_error Si l'URL n'est pas suivie de '{'
 */
void Validator::validateUrl(lst_iterator it, lst_iterator next) const
{
	if (it->second != URL)
		return ;
	if (next == _tokens.end() || next->second != CURLY_BRACKET_OPEN)
		throw std::runtime_error("URL '" + it->first + "' must be followed by '{'");
}

/**
 * @brief Valide une directive de configuration
 *
 * Vérifie qu'une directive est reconnue et qu'elle est suivie d'au moins une valeur.
 *
 * @param it Itérateur pointant sur le token de directive
 * @param next Itérateur pointant sur le token suivant
 * @throws std::runtime_error Si la directive est inconnue ou sans valeur
 */
void Validator::validateDirective(lst_iterator it, lst_iterator next) const
{
	if (it->second != DIRECTIVE)
		return ;
	if (!isDirectiveAllowed(it->first))
		throw std::runtime_error("Unknown directive '" + it->first + "'");
	if (next == _tokens.end() || next->second != VALUE)
		throw std::runtime_error("Directive '" + it->first + "' must have a value");
}

/**
 * @brief Vérifie qu'un bloc n'est pas vide
 *
 * Détecte les blocs qui s'ouvrent et se ferment immédiatement sans contenu.
 *
 * @param it Itérateur pointant sur l'accolade ouvrante
 * @param next Itérateur pointant sur le token suivant
 * @param end Itérateur de fin de la liste
 * @throws std::runtime_error Si un bloc vide est détecté
 */
void Validator::validateEmptyBlock(lst_iterator it, lst_iterator next,
	lst_iterator end) const
{
	if (it->second != CURLY_BRACKET_OPEN)
		return ;
	if (next != end && next->second == CURLY_BRACKET_CLOSED)
		throw std::runtime_error("Empty block detected");
}

/**
 * @brief Valide le premiestringr token du fichier de configuration
 *
 * Vérifie que le fichier commence par une section (comme "server") ou un commentaire.
 *
 * @param lst Liste complète des tokens
 * @throws std::runtime_error Si le premier token n'est pas une section ou un commentaire
 */
void Validator::validateStartToken(const list_pair_str_int &lst) const
{
	if (lst.empty())
		return ;
	int firstType = lst.begin()->second;
	if (firstType != SECTION && firstType != COMMENT)
		throw std::runtime_error("Config must start with a section (like 'server')");
}

/**
 * @brief Vérifie si une directive est autorisée
 *
 * Recherche la clé (directive ou section) dans la liste des types de directives autorisés.
 *
 * @param key Le nom de la directive ou section à vérifier
 * @return true si la directive est autorisée, false sinon
 */
bool Validator::isDirectiveAllowed(const string &key) const
{
	return (std::find(_directiveTypes.begin(), _directiveTypes.end(),key) != _directiveTypes.end());
}
