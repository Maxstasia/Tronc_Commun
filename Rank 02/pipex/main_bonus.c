/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/04 16:33:32 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex_bonus.h"

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
		if (pipex->here_doc)
			pipex->argv = &pipex->argv[i + 3];
		else
			pipex->argv = &pipex->argv[i + 2];
		return (child_process(pipex), exit(0), 0);
	}
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	pipex->prev_fd = pipex->fd[0];
	return (close(pipex->fd[1]), pid);
}

static void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	if (argc < 5 || (ft_strcmp(argv[1], "here_doc") == 0 && argc < 6))
		usage();
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->here_doc = (ft_strcmp(argv[1], "here_doc") == 0);
	pipex->filein = argv[1];
	pipex->fileout = argv[argc - 1];
	pipex->prev_fd = -1;
}

static void	launch_processes(t_pipex *pipex, t_temp *tmp)
{
	int		i;

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
	if (pipex->pids)
		free(pipex->pids);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	t_temp	tmp;

	tmp.last_status = 0;
	tmp.status = 0;
	init_pipex(&pipex, argc, argv, envp);
	if (pipex.here_doc)
	{
		handle_here_doc(&pipex);
		tmp.cmd_count = argc - 4;
	}
	else
		tmp.cmd_count = argc - 3;
	pipex.pids = (pid_t *)malloc(sizeof(pid_t) * tmp.cmd_count);
	launch_processes(&pipex, &tmp);
	return (tmp.last_status);
}
