#include "FileUtils.hpp"
#include <cstdlib>


FileUtils::FileUtils(void){}
FileUtils::FileUtils(const FileUtils&other){*this = other;}
FileUtils::~FileUtils(void){}
FileUtils&FileUtils::operator=(const FileUtils&other)
{
	if (this != &other){}
	return (*this);
}

/**
 * @brief Ouvre un fichier ou leve une exception en cas d'echec.
 *
 * Ferme et reinitialise le flux avant d'essayer de l'ouvrir.
 * Si le chemin est vide ou si l'ouverture echoue, une exception est levee.
 *
 * @param stream Le flux ifstream a utiliser pour ouvrir le fichier.
 * @param path Le chemin du fichier a ouvrir.
 * @return Aucune valeur de retour. Le flux est modifie directement.
 */
void FileUtils::openFileOrThrow(ifstream &stream, const string &path)
{
	if (path.empty())
		throw std::invalid_argument("Empty path");
	stream.close();
	stream.clear();
	stream.open(path.c_str());
	if (!stream.is_open())
		throw std::runtime_error("Impossible to open " + path);
}

/**
 * @brief Verifie si un fichier existe.
 *
 * @param path Le chemin du fichier a verifier.
 * @return true si le fichier existe, false sinon.
 */
bool FileUtils::fileExists(const string &path)
{
	struct stat buffer;
	return (stat(path.c_str(), &buffer) == 0);
}

/**
 * @brief Verifie si le chemin correspond a un repertoire.
 *
 * @param path Le chemin a verifier.
 * @return true si le chemin est un repertoire, false sinon.
 */
bool FileUtils::isDirectory(const string &path)
{
	struct stat buffer;
	if (stat(path.c_str(), &buffer) != 0)
		return false;
	return S_ISDIR(buffer.st_mode);
}

/**
 * @brief Assure qu'un chemin se termine par un slash.
 *
 * Si le chemin est vide ou se termine deja par '/', il est retourne tel quel.
 * Sinon, un '/' est ajoute a la fin.
 *
 * @param path Le chemin a modifier.
 * @return Le chemin avec un slash terminal.
 */
string FileUtils::ensureTrailingSlash(const string &path)
{
	if (path.empty() || path[path.size() - 1] == '/')
		return path;
	return path + "/";
}

/**
 * @brief Verifie si un chemin est un sous-chemin d'un repertoire racine.
 *
 * @param path Le chemin a verifier.
 * @param root Le repertoire racine.
 * @return true si path est un sous-chemin de root, false sinon.
 */
static bool isSubPath(const string &path, const string &root)
{
	if (path.size() < root.size())
		return false;
	if (path.compare(0, root.size(), root) != 0)
		return false;
	return (path.size() == root.size() || path[root.size()] == '/');
}

/**
 * @brief Verifie si un chemin de fichier est securise par rapport a un repertoire racine.
 *
 * Resout les chemins absolus et verifie que le fichier cible se trouve bien
 * dans l'arborescence du repertoire racine specifie. Evite les attaques de type
 * directory traversal.
 *
 * @param filePath Le chemin du fichier a verifier.
 * @param root Le repertoire racine autorise.
 * @return true si le chemin est securise, false sinon.
 */
bool FileUtils::isPathSafe(const string &filePath, const string &root)
{
	char *resolvedRoot = realpath(root.c_str(), NULL);
	if (!resolvedRoot)
		return false;
	string rootStr(resolvedRoot);
	free(resolvedRoot);

	char *resolvedFile = realpath(filePath.c_str(), NULL);
	if (resolvedFile)
	{
		string fileStr(resolvedFile);
		free(resolvedFile);
		return isSubPath(fileStr, rootStr);
	}
	string parent = filePath;
	size_t pos = parent.find_last_of('/');
	if (pos == string::npos)
		return false;
	parent = parent.substr(0, pos);
	char *resolvedParent = realpath(parent.c_str(), NULL);
	if (!resolvedParent)
		return false;
	string parentStr(resolvedParent);
	free(resolvedParent);
	return isSubPath(parentStr, rootStr);
}
