/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:40:07 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/20 13:41:21 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

static int	child_process(t_pipex *pipex)
{
	int	file;

	if (pipex->is_first)
	{
		file = open(pipex->filein, O_RDONLY);
		if (file == -1)
			file = open("/dev/null", O_RDONLY, 0644);
		if (file == -1)
			error();
		dup2(file, STDIN_FILENO);
		close(file);
	}
	else
		dup2(pipex->fd[0], STDIN_FILENO);
	if (!pipex->is_last)
		dup2(pipex->fd[1], STDOUT_FILENO);
	else
	{
		file = open(pipex->fileout, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (file == -1)
			error();
		dup2(file, STDOUT_FILENO);
		close(file);
	}
	return (close(pipex->fd[0]), close(pipex->fd[1]), execute(pipex), 0);
}

static void	fork_process(t_pipex *pipex, char **argv, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		if (i == 2)
		{
			pipex->is_first = 1;
			pipex->is_last = 0;
			pipex->argv = &argv[2];
		}
		else
		{
			pipex->is_first = 0;
			pipex->is_last = 1;
			pipex->argv = &argv[3];
		}
		child_process(pipex);
		exit(0);
	}
}

static void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	if (argc != 5)
		usage();
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->filein = argv[1];
	pipex->fileout = argv[argc - 1];
	if (pipe(pipex->fd) == -1)
		error();
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		status1;
	int		status2;

	init_pipex(&pipex, argc, argv, envp);
	fork_process(&pipex, argv, 2);
	fork_process(&pipex, argv, 3);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	wait(&status1);
	wait(&status2);
	if (WIFEXITED(status2) && WEXITSTATUS(status2) != 0)
		return (WEXITSTATUS(status2));
	if (WIFEXITED(status1) && WEXITSTATUS(status1) != 0)
		return (WEXITSTATUS(status1));
	return (0);
}
