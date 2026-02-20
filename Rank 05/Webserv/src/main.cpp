#include "ManagerServer.hpp"
#include <csignal>
#include <iostream>
#include <string>

volatile sig_atomic_t	g_shutdown = 0;

static void	sigHandler(int sig)
{
	(void)sig;
	g_shutdown = 1;
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	string				configPath;

	if (argc > 2)
	{
		std::cerr << "Usage: ./webserv [config_file]" << std::endl;
		return (1);
	}
	signal(SIGPIPE, SIG_IGN);
	sa.sa_handler = sigHandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	try
	{
		configPath = (argc == 2) ? argv[1] : string(PATH_CONF) + SERV_CONF;
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
