#include "Request.hpp"
#include "StringUtils.hpp"
#include <cctype>
#include <sstream>

static bool	isChunkedRaw(const string &raw, size_t header_end)
{
	string	lower;
	size_t	pos;
	size_t	line_end;
	string	value;

	lower = StringUtils::toLower(raw.substr(0, header_end));
	pos = lower.find("\r\ntransfer-encoding:");
	if (pos == string::npos)
		return (false);
	pos += 2;
	line_end = lower.find("\r\n", pos);
	value = lower.substr(pos + 18, line_end - pos - 18);
	return (StringUtils::trim(value) == "chunked");
}

static long	extractContentLengthRaw(const string &raw, size_t header_end)
{
	string	headers_str;
	string	lower;
	size_t	cl_pos;
	size_t	value_start;
	size_t	line_end;
	string	cl_value;
	long	content_length;

	headers_str = raw.substr(0, header_end);
	lower = StringUtils::toLower(headers_str);
	cl_pos = lower.find("\r\ncontent-length:");
	if (cl_pos == string::npos)
		return (-1);
	cl_pos += 2;
	value_start = cl_pos + 15;
	line_end = headers_str.find("\r\n", value_start);
	if (line_end == string::npos)
		line_end = headers_str.size();
	cl_value = StringUtils::trim(headers_str.substr(value_start, line_end
				- value_start));
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
	size_t header_end = _raw_request.find("\r\n\r\n");
	if (header_end == string::npos)
		return (false);

	if (isChunkedRaw(_raw_request, header_end))
		return (_raw_request.find("0\r\n\r\n", header_end + 4) != string::npos);

	long cl = extractContentLengthRaw(_raw_request, header_end);
	if (cl < 0)
		return (true);

	size_t body_start = header_end + 4;
	size_t body_received = (_raw_request.size() > body_start) ? _raw_request.size()
		- body_start : 0;
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
	size_t	qpos;

	if (!std::getline(stream, line))
		return (setError(HTTP_400), false);
	line = StringUtils::trim(line);
	istringstream line_stream(line);
	string method, uri, version;
	line_stream >> method >> uri >> version;
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
	if (method != "GET" && method != "HEAD" && method != "POST"
		&& method != "DELETE")
		return (setError(HTTP_501), false);
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
 * @brief Analyse tous les en-têtes HTTP de la requête
 *
 * Extrait les paires clé-valeur des en-têtes et les stocke dans la map.
 *
 * @param stream Flux d'entrée contenant les en-têtes
 */
void Request::parseHeaders(istringstream &stream)
{
	string	line;
	size_t	colon;
	string	key;
	string	value;

	while (std::getline(stream, line))
	{
		line = StringUtils::trim(line);
		if (line.empty())
			continue ;
		colon = line.find(':');
		if (colon != string::npos)
		{
			key = StringUtils::toLower(StringUtils::trim(line.substr(0,
							colon)));
			value = StringUtils::trim(line.substr(colon + 1));
			_headers[key] = value;
			if (key == "host")
				_hostCount++;
			if (key == "content-type")
				_contentType = value;
		}
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
	if (!validateHost())
		return ;
	map_str_str::iterator te = _headers.find("transfer-encoding");
	if (te != _headers.end() && te->second == "chunked")
	{
		if (!decodeChunkedBody())
			return (setError(HTTP_400));
	}
	else if (!validateContentLength())
		return ;
	if (_method == "GET" || _method == "HEAD" || _method == "DELETE")
		_body.clear();
	_isParsed = true;
}
