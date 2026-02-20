#include "ManagerServer.hpp"

// Getters
/**
 * @brief Retourne une reference constante vers le vecteur des descripteurs de fichiers des serveurs.
 *
 * @return Referenc constante vers _servers_fd.
 */
const vect_int& ManagerServer::getServersFd() const
{
	return _servers_fd;
}

/**
 * @brief Retourne une reference mutable vers le vecteur des descripteurs de fichiers des serveurs.
 *
 * @return Reference mutable vers _servers_fd.
 */
vect_int& ManagerServer::getServersFd()
{
	return _servers_fd;
}

// Utility
/**
 * @brief Verifie si un descripteur de fichier correspond a un socket serveur.
 *
 * Parcourt le vecteur _servers_fd pour determiner si le fd donne appartient
 * a l'un des sockets d'ecoute des serveurs.
 *
 * @param fd Le descripteur de fichier a verifier.
 * @return true si fd est un socket serveur, false sinon.
 */
bool ManagerServer::isServerSocket(int fd) const
{
	return _fd_to_server.find(fd) != _fd_to_server.end();
}
