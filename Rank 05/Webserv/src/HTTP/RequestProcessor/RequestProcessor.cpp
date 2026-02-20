#include "RequestProcessor.hpp"

RequestProcessor::RequestProcessor() : _loader(NULL), _servers(NULL)
{
}

RequestProcessor::~RequestProcessor()
{
}

/**
 * @brief Définit le chargeur de configuration
 *
 * @param loader Pointeur vers le chargeur de configuration à utiliser
 */
void RequestProcessor::setLoader(const Loader *loader)
{
	_loader = loader;
}

/**
 * @brief Définit la liste des serveurs virtuels
 *
 * @param servers Pointeur vers le vecteur de serveurs à utiliser
 */
void RequestProcessor::setServers(std::vector<Server> *servers)
{
	_servers = servers;
}
