/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:00:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/13 19:04:02 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventManager.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>

EventManager::EventManager() : _epoll_fd(-1)
{
}

EventManager::~EventManager()
{
	cleanup();
}

/**
 * @brief Initialise le gestionnaire d'evenements epoll.
 *
 * Cree un descripteur de fichier epoll avec epoll_create et configure
 * le flag FD_CLOEXEC. Leve une exception en cas d'echec.
 *
 * @return Aucune valeur de retour.
 * @throws std::runtime_error Si epoll_create echoue.
 */
void EventManager::initialize()
{
	_epoll_fd = epoll_create(EPOLL_MAX_EVENTS);
	if (_epoll_fd == -1)
		throw std::runtime_error("epoll_create failed");
	fcntl(_epoll_fd, F_SETFD, FD_CLOEXEC);
}

/**
 * @brief Ajoute un descripteur de fichier a epoll avec les evenements specifies.
 *
 * Utilise EPOLL_CTL_ADD pour ajouter le descripteur avec les drapeaux d'evenements.
 *
 * @param fd Le descripteur de fichier a ajouter.
 * @param events Les drapeaux d'evenements epoll (EPOLLIN, EPOLLOUT, etc.).
 * @return Aucune valeur de retour.
 * @throws std::runtime_error Si epoll_ctl echoue.
 */
void EventManager::addFd(int fd, uint32_t events)
{
	_ev.events = events;
	_ev.data.fd = fd;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, fd, &_ev) == -1)
		throw std::runtime_error("epoll_ctl ADD failed");
}

/**
 * @brief Modifie les evenements pour un descripteur de fichier existant dans epoll.
 *
 * Utilise EPOLL_CTL_MOD pour mettre a jour les drapeaux d'evenements.
 *
 * @param fd Le descripteur de fichier a modifier.
 * @param events Les nouveaux drapeaux d'evenements epoll.
 * @return Aucune valeur de retour.
 * @throws std::runtime_error Si epoll_ctl echoue.
 */
void EventManager::modifyFd(int fd, uint32_t events)
{
	_ev.events = events;
	_ev.data.fd = fd;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, fd, &_ev) == -1)
		throw std::runtime_error("epoll_ctl MOD failed");
}

/**
 * @brief Retire un descripteur de fichier d'epoll.
 *
 * Utilise EPOLL_CTL_DEL pour supprimer le descripteur.
 *
 * @param fd Le descripteur de fichier a retirer.
 * @return Aucune valeur de retour.
 * @throws std::runtime_error Si epoll_ctl echoue.
 */
void EventManager::removeFd(int fd)
{
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fd, NULL) == -1)
		throw std::runtime_error("epoll_ctl DEL failed");
}

/**
 * @brief Attend les evenements epoll avec un timeout.
 *
 * Appelle epoll_wait et retourne le nombre de descripteurs prets.
 *
 * @param events Tableau pour stocker les evenements.
 * @param max_events Nombre maximum d'evenements a retourner.
 * @param timeout Timeout en millisecondes.
 * @return Nombre de descripteurs prets, ou -1 en cas d'erreur.
 */
int EventManager::waitEvents(struct epoll_event* events, int max_events, int timeout)
{
	return epoll_wait(_epoll_fd, events, max_events, timeout);
}

/**
 * @brief Retourne le descripteur de fichier epoll.
 *
 * @return Le descripteur de fichier epoll.
 */
int EventManager::getEpollFd() const
{
	return _epoll_fd;
}

/**
 * @brief Nettoie les ressources epoll.
 *
 * Ferme le descripteur de fichier epoll s'il est valide et le remet a -1.
 *
 * @return Aucune valeur de retour.
 */
void EventManager::cleanup()
{
	if (_epoll_fd != -1)
	{
		close(_epoll_fd);
		_epoll_fd = -1;
	}
}
