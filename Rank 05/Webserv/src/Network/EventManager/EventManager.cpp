/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:00:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/04 16:00:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventManager.hpp"
#include <unistd.h>
#include <stdexcept>

EventManager::EventManager() : _epoll_fd(-1)
{
}

EventManager::~EventManager()
{
	cleanup();
}

void EventManager::initialize()
{
	_epoll_fd = epoll_create(EPOLL_MAX_EVENTS);
	if (_epoll_fd == -1)
		throw std::runtime_error("epoll_create failed");
}

void EventManager::addFd(int fd, uint32_t events)
{
	_ev.events = events;
	_ev.data.fd = fd;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, fd, &_ev) == -1)
		throw std::runtime_error("epoll_ctl ADD failed");
}

void EventManager::modifyFd(int fd, uint32_t events)
{
	_ev.events = events;
	_ev.data.fd = fd;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, fd, &_ev) == -1)
		throw std::runtime_error("epoll_ctl MOD failed");
}

void EventManager::removeFd(int fd)
{
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fd, NULL) == -1)
		throw std::runtime_error("epoll_ctl DEL failed");
}

int EventManager::waitEvents(struct epoll_event* events, int max_events, int timeout)
{
	return epoll_wait(_epoll_fd, events, max_events, timeout);
}

int EventManager::getEpollFd() const
{
	return _epoll_fd;
}

void EventManager::cleanup()
{
	if (_epoll_fd != -1)
	{
		close(_epoll_fd);
		_epoll_fd = -1;
	}
}
