#include "Request.hpp"
#include "StringUtils.hpp"
#include <cctype>
#include <sstream>

static const char	*g_no_duplicate_headers[] = {
	NO_DUPLICATE_HEADERS, NULL
};

static const char	*g_bodyless_methods[] = {
	BODYLESS_METHODS, NULL
};

static bool	isBodylessMethod(const string &method)
{
	for (int i = 0; g_bodyless_methods[i]; ++i)
	{
		if (method == g_bodyless_methods[i])
			return (true);
	}
	return (false);
}

static bool	isDuplicateForbidden(const string &key)
{
	for (int i = 0; g_no_duplicate_headers[i]; ++i)
	{
		if (key == g_no_duplicate_headers[i])
			return (true);
	}
	return (false);
}

/**
 * @brief Vérifie si un nom de header est valide selon la RFC 7230
 *
 * Rejette les caractères de contrôle, séparateurs et délimiteurs.
 *
 * @param name Nom du header à valider
 * @return true si valide, false sinon
 */
static bool	isValidHeaderName(const string &name)
{
	for (size_t i = 0; i < name.size(); ++i)
	{
		unsigned char c = name[i];
		if (c <= 32 || c == 127 || c == '(' || c == ')' || c == '<'
			|| c == '>' || c == '@' || c == ',' || c == ';'
			|| c == '\\' || c == '"' || c == '/' || c == '['
			|| c == ']' || c == '?' || c == '=' || c == '{'
			|| c == '}')
			return (false);
	}
	return (!name.empty());
}

/**
 * @brief Vérifie si une valeur de header est valide selon la RFC 7230
 *
 * Rejette les caractères de contrôle sauf la tabulation horizontale.
 *
 * @param value Valeur du header à valider
 * @return true si valide, false sinon
 */
static bool	isValidHeaderValue(const string &value)
{
	for (size_t i = 0; i < value.size(); ++i)
	{
		unsigned char c = value[i];
		if (c < 32 && c != '\t')
			return (false);
		if (c == 127)
			return (false);
	}
	return (true);
}

/**
 * @brief Recherche la valeur d'un header dans la requête brute
 *
 * Effectue une recherche case-insensitive dans les en-têtes bruts
 * avant le parsing complet de la requête.
 *
 * @param raw Requête brute complète
 * @param header_end Position de la fin des en-têtes
 * @param name Nom du header recherché (en minuscules)
 * @return Valeur trimmée du header, ou chaîne vide si absent
 */
static string	findRawHeaderValue(const string &raw, size_t header_end,
	const string &name)
{
	string	lower;
	size_t	pos;
	size_t	line_end;

	lower = StringUtils::toLower(raw.substr(0, header_end));
	pos = lower.find("\r\n" + name + ":");
	if (pos == string::npos)
		return ("");
	pos += name.size() + 3;
	line_end = lower.find("\r\n", pos);
	if (line_end == string::npos)
		line_end = lower.size();
	return (StringUtils::trim(lower.substr(pos, line_end - pos)));
}

/**
 * @brief Détecte le Transfer-Encoding chunked avant le parsing complet
 *
 * @param raw Requête brute complète
 * @param header_end Position de la fin des en-têtes
 * @return true si chunked, false sinon
 */
static bool	isChunkedRaw(const string &raw, size_t header_end)
{
	return (findRawHeaderValue(raw, header_end, "transfer-encoding")
		== "chunked");
}

/**
 * @brief Détecte les Content-Length dupliqués dans la requête brute
 *
 * Vérifie la présence de plusieurs en-têtes Content-Length,
 * ce qui constitue une erreur selon la RFC 7230 §3.3.2.
 *
 * @param raw Requête brute complète
 * @param header_end Position de la fin des en-têtes
 * @return true si dupliqué, false sinon
 */
static bool	hasDuplicateContentLength(const string &raw, size_t header_end)
{
	string	lower;
	size_t	first;

	lower = StringUtils::toLower(raw.substr(0, header_end));
	first = lower.find("\r\ncontent-length:");
	if (first == string::npos)
		return (false);
	return (lower.find("\r\ncontent-length:", first + 1) != string::npos);
}

/**
 * @brief Extrait la méthode HTTP depuis la requête brute
 *
 * Récupère le premier mot avant l'espace dans la Request-Line.
 *
 * @param raw Requête brute complète
 * @return Méthode HTTP, ou chaîne vide si invalide
 */
static string	extractMethodRaw(const string &raw)
{
	size_t	sp;

	sp = raw.find(' ');
	if (sp == string::npos || sp == 0)
		return ("");
	return (raw.substr(0, sp));
}

/**
 * @brief Extrait la valeur de Content-Length depuis la requête brute
 *
 * Recherche et parse l'en-tête Content-Length avant le parsing complet
 * pour déterminer la taille attendue du corps.
 *
 * @param raw Requête brute complète
 * @param header_end Position de la fin des en-têtes
 * @return Longueur du contenu en octets, ou -1 si absent ou invalide
 */
static long	extractContentLengthRaw(const string &raw, size_t header_end)
{
	string	cl_value;
	long	content_length;

	cl_value = findRawHeaderValue(raw, header_end, "content-length");
	if (cl_value.empty())
		return (-1);
	istringstream iss(cl_value);
	content_length = 0;
	iss >> content_length;
	if (iss.fail() || content_length < 0)
		return (-1);
	return (content_length);
}

/**
 * @brief Vérifie si les en-têtes HTTP ont été complètement reçus
 *
 * @return true si la séquence "\r\n\r\n" est présente, false sinon
 */
bool Request::isHeaderFull() const
{
	return (_raw_request.find("\r\n\r\n") != string::npos);
}

/**
 * @brief Extrait la longueur du contenu depuis la requête brute
 *
 * @return Longueur du contenu en octets, ou -1 si non définie
 */
long Request::getRawContentLength() const
{
	size_t header_end = _raw_request.find("\r\n\r\n");
	if (header_end == string::npos)
		return (-1);
	return (extractContentLengthRaw(_raw_request, header_end));
}

/**
 * @brief Vérifie si la requête HTTP est complète
 *
 * Contrôle que les en-têtes et le corps (selon Content-Length ou chunked)
 * ont été entièrement reçus.
 *
 * @return true si la requête est complète, false sinon
 */
bool Request::isRequestComplete() const
{
	size_t	header_end;
	string	method;

	header_end = _raw_request.find("\r\n\r\n");
	if (header_end == string::npos)
		return (false);
	if (hasDuplicateContentLength(_raw_request, header_end))
		return (true);
	method = extractMethodRaw(_raw_request);
	if (isBodylessMethod(method))
		return (true);
	if (isChunkedRaw(_raw_request, header_end))
		return (_raw_request.find("0\r\n\r\n", header_end + 4)
			!= string::npos);

	long cl = extractContentLengthRaw(_raw_request, header_end);
	if (cl < 0)
		return (true);
	size_t body_start = header_end + 4;
	size_t body_received = (_raw_request.size() > body_start)
		? _raw_request.size() - body_start : 0;
	return (static_cast<long>(body_received) >= cl);
}

/**
 * @brief Définit une erreur de parsing
 *
 * @param code Code d'erreur HTTP
 * @param message Message d'erreur descriptif
 */
void Request::setError(int code, const string &message)
{
	_parseError = code;
	_parseErrorMessage = message;
	_isParsed = true;
}

/**
 * @brief Valide la version du protocole HTTP
 *
 * Vérifie le format et la compatibilité de la version HTTP.
 *
 * @param version Chaîne de version à valider
 * @return true si valide, false sinon
 */
bool Request::validateVersion(const string &version)
{
	if (version.size() < 8 || version.substr(0, 5) != "HTTP/"
		|| !std::isdigit(version[5]) || version[6] != '.'
		|| !std::isdigit(version[7]))
		return (setError(HTTP_400), false);
	if (version != "HTTP/1.0" && version != "HTTP/1.1")
		return (setError(HTTP_505), false);
	return (true);
}

/**
 * @brief Valide les composants de la Request-Line
 *
 * Vérifie la version HTTP, la taille de l'URI et la méthode supportée.
 *
 * @param method Méthode HTTP extraite
 * @param uri URI extraite
 * @param version Version HTTP (modifiée si simple request)
 * @return true si valide, false en cas d'erreur
 */
bool Request::validateRequestLine(const string &method, const string &uri,
	string &version)
{
	if (method.empty() || uri.empty())
		return (setError(HTTP_400), false);
	if (version.empty())
	{
		if (method != "GET")
			return (setError(HTTP_400), false);
		version = "HTTP/1.0";
	}
	else if (!validateVersion(version))
		return (false);
	if (uri.size() > MAX_URI_SIZE)
		return (setError(HTTP_414), false);
	_httpVersion = version;
	if (method != "GET" && method != "HEAD" && method != "POST"
		&& method != "DELETE")
		return (setError(HTTP_501), false);
	return (true);
}

/**
 * @brief Analyse la ligne de requête HTTP
 *
 * Extrait la méthode, l'URI et la version depuis la première ligne.
 *
 * @param stream Flux d'entrée contenant la requête
 * @return true si le parsing réussit, false en cas d'erreur
 */
bool Request::parseRequestLine(istringstream &stream)
{
	string	line;
	string	extra;
	string	method;
	string	uri;
	string	version;
	size_t	qpos;

	if (!std::getline(stream, line))
		return (setError(HTTP_400), false);
	line = StringUtils::trim(line);
	istringstream line_stream(line);
	line_stream >> method >> uri >> version;
	if (!validateRequestLine(method, uri, version))
		return (false);
	if (line_stream >> extra)
		return (setError(HTTP_400), false);
	_method = method;
	qpos = uri.find('?');
	if (qpos != string::npos)
	{
		_uri = uri.substr(0, qpos);
		_queryString = uri.substr(qpos + 1);
	}
	else
		_uri = uri;
	_httpVersion = version;
	return (true);
}

/**
 * @brief Parse et stocke une ligne de header individuelle
 *
 * Valide le format, les caractères et les doublons interdits,
 * puis stocke la paire clé-valeur dans la map des headers.
 *
 * @param line Ligne de header trimmée
 * @return true si valide, false en cas d'erreur
 */
bool Request::parseHeaderLine(const string &line)
{
	size_t	colon;
	string	key;
	string	value;

	if (line.size() > MAX_HEADER_FIELD_SIZE)
		return (setError(HTTP_431), false);
	colon = line.find(':');
	if (colon == string::npos || colon == 0)
		return (setError(HTTP_400), false);
	if (line[colon - 1] == ' ' || line[colon - 1] == '\t')
		return (setError(HTTP_400), false);
	key = line.substr(0, colon);
	if (!isValidHeaderName(key))
		return (setError(HTTP_400), false);
	value = StringUtils::trim(line.substr(colon + 1));
	if (!isValidHeaderValue(value))
		return (setError(HTTP_400), false);
	key = StringUtils::toLower(key);
	if (_headers.count(key) && isDuplicateForbidden(key))
		return (setError(HTTP_400), false);
	_headers[key] = value;
	if (key == "host")
		_hostCount++;
	if (key == "content-type")
		_contentType = value;
	return (true);
}

/**
 * @brief Analyse tous les en-têtes HTTP de la requête
 *
 * Itère sur chaque ligne du flux et délègue le parsing
 * de chaque header individuel à parseHeaderLine().
 *
 * @param stream Flux d'entrée contenant les en-têtes
 */
void Request::parseHeaders(istringstream &stream)
{
	string	line;
	int		count;

	count = 0;
	while (std::getline(stream, line))
	{
		if (++count > MAX_HEADER_COUNT)
			return (setError(HTTP_431));
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);
		if (line.find('\r') != string::npos)
			return (setError(HTTP_400));
		line = StringUtils::trim(line);
		if (line.empty())
			continue ;
		if (!parseHeaderLine(line))
			return ;
	}
}

/**
 * @brief Valide l'en-tête Host de la requête
 *
 * Vérifie qu'il n'y a qu'un seul en-tête Host et qu'il est présent en HTTP/1.1.
 *
 * @return true si valide, false sinon
 */
bool Request::validateHost()
{
	if (_hostCount > 1)
		return (setError(HTTP_400), false);
	if (_httpVersion == "HTTP/1.1" && _hostCount == 0)
		return (setError(HTTP_400), false);
	return (true);
}

/**
 * @brief Valide et extrait la longueur du contenu
 *
 * Vérifie le format de Content-Length et tronque le corps si nécessaire.
 *
 * @return true si valide, false sinon
 */
bool Request::validateContentLength()
{
	map_str_str::iterator it = _headers.find("content-length");
	if (it == _headers.end())
		return (true);
	istringstream cl_ss(it->second);
	cl_ss >> _contentLength;
	if (cl_ss.fail() || _contentLength < 0)
		return (setError(HTTP_400), false);
	if (_body.size() > static_cast<size_t>(_contentLength))
		_body = _body.substr(0, _contentLength);
	return (true);
}

/**
 * @brief Décode un corps de requête encodé en chunked
 *
 * Traite l'encodage de transfert chunked et reconstruit le corps complet.
 *
 * @return true si le décodage réussit, false sinon
 */
bool Request::decodeChunkedBody()
{
	string			decoded;
	size_t			pos;
	size_t			crlf;
	string			hex_str;
	unsigned long	chunk_size;
	size_t			data_start;

	pos = 0;
	while (pos < _body.size())
	{
		crlf = _body.find("\r\n", pos);
		if (crlf == string::npos)
			return (false);
		hex_str = _body.substr(pos, crlf - pos);
		chunk_size = 0;
		istringstream iss(hex_str);
		iss >> std::hex >> chunk_size;
		if (iss.fail())
			return (false);
		if (chunk_size == 0)
			break ;
		data_start = crlf + 2;
		if (data_start + chunk_size + 2 > _body.size())
			return false;
		decoded.append(_body, data_start, chunk_size);
		pos = data_start + chunk_size + 2;
	}
	_body = decoded;
	return true;
}

/**
 * @brief Valide le Transfer-Encoding ou le Content-Length du corps
 *
 * Vérifie la cohérence entre Transfer-Encoding et Content-Length
 * selon la RFC 7230 §3.3, et décode le corps chunked si nécessaire.
 *
 * @return true si valide, false en cas d'erreur
 */
bool Request::validateTransferEncoding()
{
	map_str_str::iterator te;

	te = _headers.find("transfer-encoding");
	if (te == _headers.end())
		return (validateContentLength());
	if (_headers.find("content-length") != _headers.end())
		return (setError(HTTP_400), false);
	if (StringUtils::toLower(te->second) != "chunked")
		return (setError(HTTP_400), false);
	if (!decodeChunkedBody())
		return (setError(HTTP_400), false);
	_contentLength = static_cast<long>(_body.size());
	return (true);
}

/**
 * @brief Analyse complètement la requête HTTP
 *
 * Effectue le parsing complet de la requête incluant la ligne de requête,
 * les en-têtes, et le corps (avec support du chunked encoding).
 */
void Request::parseRequest()
{
	size_t	header_end;
	string	headers;

	if (_isParsed)
		return ;
	header_end = _raw_request.find("\r\n\r\n");
	if (header_end == string::npos)
		return ;
	headers = _raw_request.substr(0, header_end);
	if (_raw_request.size() > header_end + 4)
		_body = _raw_request.substr(header_end + 4);
	istringstream stream(headers);
	if (!parseRequestLine(stream))
		return ;
	parseHeaders(stream);
	if (_parseError != 0)
		return ;
	if (!validateHost() || !validateTransferEncoding())
		return ;
	if (isBodylessMethod(_method))
		_body.clear();
	_isParsed = true;
}
