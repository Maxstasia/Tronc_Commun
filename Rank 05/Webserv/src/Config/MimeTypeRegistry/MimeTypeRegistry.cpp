#include "MimeTypeRegistry.hpp"
#include "StringUtils.hpp"

MimeTypeRegistry::MimeTypeRegistry()
{
	load();
}

MimeTypeRegistry::~MimeTypeRegistry()
{
}

/**
 * @brief Charge les types MIME depuis le fichier de configuration
 *
 * Lit le fichier mime.types et remplit la liste des associations extension-MIME.
 *
 * @throws std::runtime_error Si aucun type MIME n'est défini dans le fichier
 */
void MimeTypeRegistry::load()
{
	_mimeTypes.clear();
	loadTypesFile("mime.types");
	if (_mimeTypes.empty())
		throw std::runtime_error("mime.types: MIME not defined in " + string(PATH_CONF) + "mime.types");
}

/**
 * @brief Retourne la liste des types MIME chargés
 *
 * @return Référence constante vers le vecteur de paires <extension, type MIME>
 */
const vector_pair_string &MimeTypeRegistry::getMimeTypes() const
{
	return (_mimeTypes);
}

/**
 * @brief Charge un fichier de types MIME
 *
 * Ouvre et parse le fichier spécifié pour extraire les associations extension-MIME
 * définies dans un bloc "types { }".
 *
 * @param fileName Nom du fichier à charger (relatif au répertoire de configuration)
 * @throws std::runtime_error Si le fichier ne peut pas être ouvert
 */
void MimeTypeRegistry::loadTypesFile(const string &fileName)
{
	ifstream	typeFile;
	string		line;
	string		trimmed;
	bool		inBlock = false;

	FileUtils::openFileOrThrow(typeFile, string(PATH_CONF) + fileName);
	while (std::getline(typeFile, line))
	{
		trimmed = StringUtils::trim(line);
		if (trimmed.empty() || trimmed[0] == '#')
			continue;
		if (!inBlock)
		{
			if (trimmed.find("types") != string::npos && trimmed.find('{') != string::npos)
				inBlock = true;
			continue;
		}
		if (trimmed[0] == '}')
			break;
		handleMimeLine(trimmed);
	}
}

/**
 * @brief Traite une ligne de définition de type MIME
 *
 * Parse une ligne au format "type/mime extension1 extension2;" et crée les associations.
 *
 * @param line La ligne contenant le type MIME et ses extensions
 */
void MimeTypeRegistry::handleMimeLine(const string &line)
{
	std::istringstream iss(line);
	string mimeType;
	iss >> mimeType;
	if (mimeType.empty())
		return;
	for (string ext; iss >> ext;)
	{
		if (!ext.empty() && ext[ext.size() - 1] == ';')
			ext.erase(ext.size() - 1);
		if (!ext.empty())
			_mimeTypes.push_back(pair_string(ext, mimeType));
	}
}
