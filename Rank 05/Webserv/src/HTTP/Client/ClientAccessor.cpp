#include "Client.hpp"
#include "Server.hpp"
#include "Location.hpp"

/**
 * @brief Récupère le descripteur de fichier du socket client
 *
 * @return Le descripteur de fichier du client
 */
int Client::getClientFd() const {
	return _client_fd;
}

/**
 * @brief Récupère l'adresse socket du client
 *
 * @return La structure sockaddr_in contenant l'adresse et le port du client
 */
struct sockaddr_in Client::getClientAddr() const {
	return _client_addr;
}

/**
 * @brief Récupère une référence modifiable vers la requête HTTP
 *
 * @return Référence vers l'objet Request du client
 */
Request &Client::getRequest(){
	return (_request);
}

/**
 * @brief Récupère une référence modifiable vers la réponse HTTP
 *
 * @return Référence vers l'objet Response du client
 */
Response &Client::getResponse() {
	return (_response);
}

/**
 * @brief Récupère le nombre d'octets déjà envoyés au client
 *
 * @return Référence vers le compteur d'octets envoyés
 */
size_t &Client::getBytes() {
	return (_bytes);
}

/**
 * @brief Récupère le pointeur vers le serveur virtuel associé
 *
 * @return Pointeur vers l'objet Server, ou NULL si non défini
 */
Server* Client::getServer() const {
	return _server;
}

/**
 * @brief Récupère le pointeur vers la location correspondant à l'URI
 *
 * @return Pointeur constant vers l'objet Location, ou NULL si non défini
 */
const Location* Client::getLocation() const {
	return _location;
}

/**
 * @brief Définit le serveur virtuel associé à ce client
 *
 * @param server Pointeur vers le serveur virtuel à associer
 */
void Client::setServer(Server* server) {
	_server = server;
}

/**
 * @brief Définit la location correspondant à l'URI de la requête
 *
 * @param location Pointeur constant vers la location à associer
 */
void Client::setLocation(const Location* location) {
	_location = location;
}

/**
 * @brief Vérifie si la connexion doit être fermée après la réponse
 *
 * @return true si la connexion doit être fermée, false pour keep-alive
 */
bool Client::shouldClose() const {
	return _shouldClose;
}

/**
 * @brief Définit si la connexion doit être fermée
 *
 * @param close true pour fermer la connexion, false pour la maintenir
 */
void Client::setShouldClose(bool close) {
	_shouldClose = close;
}

/**
 * @brief Met à jour l'horodatage de la dernière activité du client
 *
 * Utilisé pour détecter les connexions inactives et appliquer un timeout.
 */
void Client::updateActivity() {
	_lastActivity = time(NULL);
}

/**
 * @brief Récupère l'horodatage de la dernière activité
 *
 * @return Timestamp de la dernière activité enregistrée
 */
time_t Client::getLastActivity() const {
	return _lastActivity;
}

/**
 * @brief Récupère l'identifiant du processus CGI
 *
 * @return PID du processus CGI en cours, ou -1 si aucun
 */
pid_t Client::getCgiPid() const { return _cgiPid; }
/**
 * @brief Récupère le descripteur du pipe de sortie CGI
 *
 * @return Descripteur de fichier du pipe de lecture CGI, ou -1 si aucun
 */
int Client::getCgiPipeFd() const { return _cgiPipeFd; }
int Client::getCgiWritePipeFd() const { return _cgiWritePipeFd; }
size_t &Client::getCgiBodySent() { return _cgiBodySent; }

void Client::setCgiWritePipeFd(int fd) { _cgiWritePipeFd = fd; }
/**
 * @brief Récupère le buffer de sortie du CGI
 *
 * @return Référence vers la chaîne contenant la sortie accumulée du CGI
 */
string &Client::getCgiOutput() { return _cgiOutput; }
/**
 * @brief Récupère l'horodatage de démarrage du CGI
 *
 * @return Timestamp du démarrage du processus CGI
 */
time_t Client::getCgiStartTime() const { return _cgiStartTime; }
/**
 * @brief Vérifie si un processus CGI est actuellement en cours d'exécution
 *
 * @return true si un CGI est en cours, false sinon
 */
bool Client::isCgiRunning() const { return _cgiRunning; }

/**
 * @brief Démarre l'exécution d'un CGI et initialise ses paramètres
 *
 * @param pid Identifiant du processus CGI forké
 * @param pipeFd Descripteur du pipe pour lire la sortie du CGI
 */
void Client::startCgi(pid_t pid, int pipeFd)
{
	_cgiPid = pid;
	_cgiPipeFd = pipeFd;
	_cgiStartTime = time(NULL);
	_cgiRunning = true;
	_cgiOutput.clear();
}

/**
 * @brief Ajoute des données au buffer de sortie du CGI
 *
 * @param data Pointeur vers les données à ajouter
 * @param len Longueur des données en octets
 */
void Client::appendCgiOutput(const char *data, size_t len)
{
	_cgiOutput.append(data, len);
}

/**
 * @brief Réinitialise tous les paramètres liés au CGI
 *
 * Nettoie l'état du CGI après la fin de son exécution.
 */
void Client::clearCgi()
{
	_cgiPid = -1;
	_cgiPipeFd = -1;
	_cgiWritePipeFd = -1;
	_cgiBodySent = 0;
	_cgiOutput.clear();
	_cgiStartTime = 0;
	_cgiRunning = false;
}
