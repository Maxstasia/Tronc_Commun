/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ManagerServerAccessor.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:20:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/04 14:00:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ManagerServer.hpp"

// Getters
const vect_int& ManagerServer::getServersFd() const
{
	return _servers_fd;
}

vect_int& ManagerServer::getServersFd()
{
	return _servers_fd;
}

// Utility
bool ManagerServer::isServerSocket(int fd) const
{
	for (size_t i = 0; i < _servers_fd.size(); ++i)
	{
		if (_servers_fd[i] == fd)
			return true;
	}
	return false;
}
