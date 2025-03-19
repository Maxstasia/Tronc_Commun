/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:40:07 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/19 12:38:20 by mstasiak         ###   ########.fr       */
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
			file = open("/dev/null", O_RDONLY, 0777);
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
		file = open(pipex->fileout, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (file == -1)
			error();
		dup2(file, STDOUT_FILENO);
		close(file);
	}
	return (close(pipex->fd[0]), close(pipex->fd[1]), execute(pipex), 0);
}

static void	create_pipe(t_pipex *pipex)
{
	pid_t	pid;

	if (pipe(pipex->fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
		child_process(pipex);
	else
	{
		if (!pipex->is_first)
			close(pipex->fd[0]);
		close(pipex->fd[1]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		status;

	if (argc != 5)
		usage();
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.filein = argv[1];
	pipex.fileout = argv[argc - 1];
	pipex.is_first = 1;
	pipex.is_last = 0;
	pipex.argv = &argv[2];
	create_pipe(&pipex);
	pipex.is_first = 0;
	pipex.is_last = 1;
	pipex.argv = &argv[3];
	create_pipe(&pipex);
	while (wait(&status) > 0)
		;
	return (0);
}
