/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:04:37 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/04 15:05:48 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <csignal>
#include <iostream>
#include <string>
#include "ManagerServer.hpp"

static void sigHandler(int sig)
{
	(void)sig;
}

int	main(int argc, char **argv)
{
	if (argc > 2)
	{
		std::cerr << "Usage: ./webserv [config_file]" << std::endl;
		return (1);
	}

	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, sigHandler);

	try
	{
		string configPath = (argc == 2)
			? argv[1] : string(PATH_CONF) + SERV_CONF;
		ManagerServer manager(configPath);
		manager.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
