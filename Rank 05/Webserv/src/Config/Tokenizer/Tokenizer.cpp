#include "Tokenizer.hpp"
#include "StringUtils.hpp"

Tokenizer::Tokenizer() : _braceCount(0)
{
}

Tokenizer::Tokenizer(const string &configFile) : _configFile(configFile), _braceCount(0)
{
	tokenize();
}

Tokenizer::~Tokenizer()
{
}

Tokenizer::Tokenizer(const Tokenizer &other) : _configFile(other._configFile), _braceCount(other._braceCount), _tokens(other._tokens)
{
}

Tokenizer &Tokenizer::operator=(const Tokenizer &other)
{
	if (this != &other)
	{
		_configFile = other._configFile;
		_braceCount = other._braceCount;
		_tokens = other._tokens;
	}
	return (*this);
}

/**
 * @brief Tokenise le fichier de configuration
 *
 * Lit le fichier de configuration ligne par ligne et convertit chaque élément
 * en tokens typés (sections, directives, valeurs, accolades, commentaires).
 *
 * @return Liste de paires <string, int> représentant les tokens et leurs types
 * @throws std::runtime_error Si le fichier ne peut pas être ouvert
 */
list_pair_str_int Tokenizer::tokenize()
{
	string			line;
	ifstream		in;
	vector_string	tokens;

	_braceCount = 0;
	_tokens.clear();
	FileUtils::openFileOrThrow(in, _configFile);
	while (std::getline(in, line))
	{
		tokens = trimLine(line);
		if (tokens.empty())
			continue ;
		if (parseLocation(tokens))
			continue ;
		if (parseSection(tokens))
			continue ;
		if (parseOpenBrace(tokens, 0))
			continue ;
		if (parseCloseBrace(tokens))
			continue ;
		if (parseComment(tokens))
			continue ;
		parseDirective(tokens);
	}
	return (_tokens);
}

/**
 * @brief Retourne la liste des tokens générés
 *
 * @return Référence constante vers la liste des tokens
 */
const list_pair_str_int &Tokenizer::getTokens() const
{
	return (_tokens);
}

/**
 * @brief Parse une section (comme "server {") de la configuration
 *
 * Vérifie si la ligne contient une section suivie immédiatement d'une accolade ouvrante.
 *
 * @param tokens Vecteur de tokens de la ligne courante
 * @return true si une section a été parsée, false sinon
 */
bool Tokenizer::parseSection(const vector_string &tokens)
{
	pair_str_int	tmp;

	if (tokens.size() < 2 || tokens[1] != "{")
		return (false);
	tmp.first = tokens[0];
	tmp.second = SECTION;
	_tokens.push_back(tmp);
	parseOpenBrace(tokens, 1);
	return (true);
}

/**
 * @brief Parse une accolade fermante
 *
 * Détecte les accolades fermantes et décrémente le compteur d'imbrication.
 *
 * @param tokens Vecteur de tokens de la ligne courante
 * @return true si une accolade fermante a été parsée, false sinon
 */
bool Tokenizer::parseCloseBrace(const vector_string &tokens)
{
	pair_str_int	tmp;

	if (tokens[0] != "}")
		return (false);
	tmp.first = tokens[0];
	tmp.second = CURLY_BRACKET_CLOSED;
	_tokens.push_back(tmp);
	_braceCount--;
	return (true);
}

/**
 * @brief Parse une accolade ouvrante à un index donné
 *
 * Détecte les accolades ouvrantes et incrémente le compteur d'imbrication.
 *
 * @param tokens Vecteur de tokens de la ligne courante
 * @param index Position dans le vecteur où chercher l'accolade
 * @return true si une accolade ouvrante a été parsée, false sinon
 */
bool Tokenizer::parseOpenBrace(const vector_string &tokens, int index)
{
	pair_str_int	tmp;

	if (tokens[index] != "{")
		return (false);
	tmp.first = tokens[index];
	tmp.second = CURLY_BRACKET_OPEN;
	_tokens.push_back(tmp);
	_braceCount++;
	return (true);
}

/**
 * @brief Parse une ligne de commentaire
 *
 * Détecte les lignes commençant par '#' qui représentent des commentaires.
 *
 * @param tokens Vecteur de tokens de la ligne courante
 * @return true si un commentaire a été parsé, false sinon
 */
bool Tokenizer::parseComment(const vector_string &tokens)
{
	pair_str_int	tmp;

	if (tokens[0].empty() || tokens[0][0] != '#')
		return (false);
	tmp.first = tokens[0];
	tmp.second = COMMENT;
	_tokens.push_back(tmp);
	return (true);
}

/**
 * @brief Parse une directive et ses valeurs
 *
 * Identifie le premier token comme directive et tous les suivants comme valeurs.
 *
 * @param tokens Vecteur de tokens de la ligne courante
 */
void Tokenizer::parseDirective(const vector_string &tokens)
{
	pair_str_int	tmp;

	tmp.first = tokens[0];
	tmp.second = DIRECTIVE;
	_tokens.push_back(tmp);
	for (size_t i = 1; i < tokens.size(); ++i)
	{
		tmp.first = tokens[i];
		tmp.second = VALUE;
		_tokens.push_back(tmp);
	}
}

/**
 * @brief Nettoie et découpe une ligne en tokens
 *
 * Sépare la ligne selon les espaces et retire les espaces superflus de chaque token.
 *
 * @param line La ligne brute à traiter
 * @return Vecteur de tokens nettoyés
 */
vector_string Tokenizer::trimLine(const string &line)
{
	vector_string	raw;
	vector_string	tokens;

	raw = StringUtils::split(line, ' ');
	for (vector_string::const_iterator it = raw.begin(); it != raw.end(); ++it)
	{
		string cleaned = StringUtils::trim(*it);
		if (!cleaned.empty())
			tokens.push_back(cleaned);
	}
	return (tokens);
}

/**
 * @brief Parse un bloc location avec son chemin
 *
 * Détecte les lignes "location [path] {" et crée les tokens appropriés
 * pour la section, l'URL et l'accolade ouvrante.
 *
 * @param tokens Vecteur de tokens de la ligne courante
 * @return true si un bloc location a été parsé, false sinon
 */
bool Tokenizer::parseLocation(const vector_string &tokens)
{
	pair_str_int	tmp;

	if (tokens[0] != "location" || tokens.size() < 3)//#todo a verifier si different 3
		return (false);
	tmp.first = tokens[0];
	tmp.second = SECTION;
	_tokens.push_back(tmp);
	tmp.first = tokens[1];
	tmp.second = URL;
	_tokens.push_back(tmp);
	parseOpenBrace(tokens, 2);
	return (true);
}
