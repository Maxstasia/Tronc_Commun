/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:40:07 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/03 17:07:19 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

static pid_t	fork_process(t_pipex *pipex, int i, t_temp *tmp)
{
	pid_t	pid;

	if (pipe(pipex->fd) < 0)
		return (error(pipex), 1);
	pid = fork();
	if (pid < 0)
		return (error(pipex), 1);
	if (pid == 0)
	{
		pipex->is_first = (i == 0);
		pipex->is_last = (i == tmp->cmd_count - 1);
		pipex->argv = &pipex->argv[i + 2];
		if (pipex->pids)
			free(pipex->pids);
		return (child_process(pipex), exit(0), 0);
	}
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	pipex->prev_fd = pipex->fd[0];
	return (close(pipex->fd[1]), pid);
}

static void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	if (argc != 5)
		usage();
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->filein = argv[1];
	pipex->fileout = argv[argc - 1];
	pipex->prev_fd = -1;
}

static void	launch_processes(t_pipex *pipex, t_temp *tmp)
{
	int		i;

	pipex->pids = (pid_t *)malloc(sizeof(pid_t) * tmp->cmd_count);
	if (!pipex->pids)
	{
		if (pipex->prev_fd != -1)
			close(pipex->prev_fd);
		error(pipex);
	}
	i = -1;
	while (++i < tmp->cmd_count)
		pipex->pids[i] = fork_process(pipex, i, tmp);
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	i = -1;
	while (++i < tmp->cmd_count)
	{
		if (waitpid(pipex->pids[i], &tmp->status, 0) > 0
			&& WIFEXITED(tmp->status))
		{
			if (i == tmp->cmd_count - 1)
				tmp->last_status = WEXITSTATUS(tmp->status);
		}
	}
	free(pipex->pids);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	t_temp	tmp;

	tmp.last_status = 0;
	tmp.status = 0;
	init_pipex(&pipex, argc, argv, envp);
	tmp.cmd_count = argc - 3;
	launch_processes(&pipex, &tmp);
	return (tmp.last_status);
}
