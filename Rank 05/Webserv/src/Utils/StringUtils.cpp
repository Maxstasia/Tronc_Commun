#include "StringUtils.hpp"
#include <sstream>

/**
 * @brief Supprime les espaces blancs au debut et a la fin d'une chaine.
 *
 * @param s La chaine a traiter.
 * @return La chaine sans espaces blancs aux extremites.
 */
string StringUtils::trim(const string &s)
{
	string::size_type first = s.find_first_not_of(" \t\r\n");
	if (first == string::npos)
		return ("");
	string::size_type last = s.find_last_not_of(" \t\r\n");
	return (s.substr(first, last - first + 1));
}

/**
 * @brief Convertit une chaine en minuscules.
 *
 * @param s La chaine a convertir.
 * @return La chaine en minuscules.
 */
string StringUtils::toLower(const string &s)
{
	string result = s;
	for (size_t i = 0; i < result.size(); ++i)
		result[i] = std::tolower(result[i]);
	return result;
}

/**
 * @brief Divise une chaine en tokens selon un delimiteur.
 *
 * @param s La chaine a diviser.
 * @param delim Le caractere delimiteur.
 * @return Un vecteur contenant les tokens.
 */
vector_string StringUtils::split(const string &s, char delim)
{
	vector_string tokens;
	istringstream iss(s);
	string token;
	while (std::getline(iss, token, delim))
		tokens.push_back(token);
	return tokens;
	return tokens;
}

/**
 * @brief Echappe les caracteres speciaux HTML dans une chaine.
 *
 * Remplace les caracteres <, >, &, et " par leurs entities HTML correspondents.
 *
 * @param s La chaine a echapper.
 * @return La chaine avec les caracteres HTML echappes.
 */
string StringUtils::escapeHtml(const string &s)
{
	string result;
	for (size_t i = 0; i < s.size(); ++i)
	{
		if (s[i] == '<')
			result += "&lt;";
		else if (s[i] == '>')
			result += "&gt;";
		else if (s[i] == '&')
			result += "&amp;";
		else if (s[i] == '"')
			result += "&quot;";
		else
			result += s[i];
	}
	return result;
}

/**
 * @brief Encode une chaine au format URL.
 *
 * Les caracteres alphanumeriques et certains symboles (-, _, ., ~, /) sont
 * preserves, les autres sont encodes en pourcentage hexadecimal.
 *
 * @param s La chaine a encoder.
 * @return La chaine encodee pour une URL.
 */
string StringUtils::urlEncode(const string &s)
{
	string result;
	const char *hex = "0123456789ABCDEF";
	for (size_t i = 0; i < s.size(); ++i)
	{
		unsigned char c = s[i];
		if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~' || c == '/')
			result += c;
		else
		{
			result += '%';
			result += hex[(c >> 4) & 0x0F];
			result += hex[c & 0x0F];
		}
	}
	return result;
}

/**
 * @brief Decode une chaine au format URL.
 *
 * Remplace les sequences %XX par le caractere correspondant et les '+' par des espaces.
 *
 * @param s La chaine encodee a decoder.
 * @return La chaine decodee, ou une chaine vide en cas d'erreur de format.
 */
string StringUtils::urlDecode(const string &s)
{
	string result;
	for (size_t i = 0; i < s.size(); ++i)
	{
		if (s[i] == '%')
		{
			if (i + 2 >= s.size()
				|| !std::isxdigit(s[i + 1]) || !std::isxdigit(s[i + 2]))
				return ("");
			string hex = s.substr(i + 1, 2);
			result += static_cast<char>(std::strtol(hex.c_str(), NULL, 16));
			i += 2;
		}
		else if (s[i] == '+')
			result += ' ';
		else
			result += s[i];
	}
	return result;
}

/**
 * @brief Constructeur par defaut de StringUtils.
 *
 * @return Aucune valeur de retour.
 */
StringUtils::StringUtils() {}

/**
 * @brief Constructeur de copie de StringUtils.
 *
 * @param other L'objet StringUtils a copier.
 * @return Aucune valeur de retour.
 */
StringUtils::StringUtils(const StringUtils &other) { (void)other; }

/**
 * @brief Operateur d'assignation de StringUtils.
 *
 * @param other L'objet StringUtils a assigner.
 * @return Une reference vers l'objet courant.
 */
StringUtils &StringUtils::operator=(const StringUtils &other)
{
	(void)other;
	return *this;
}

/**
 * @brief Destructeur de StringUtils.
 *
 * @return Aucune valeur de retour.
 */
StringUtils::~StringUtils() {}
