/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:43:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/10 14:58:46 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	norm_exec_pipeline(t_data *data, t_pipex *pipex, int i)
{
	if (i == pipex->cmd_count - 1)
		data->exit_status = WEXITSTATUS(pipex->pids[i]);
}

static pid_t	fork_process(t_data *data, t_pipex *pipex, int i)
{
	pid_t	pid;

	if (!pipex->is_last)
	{
		if (pipe(pipex->fd) < 0)
			error(data);
	}
	pid = fork();
	if (pid < 0)
		error(data);
	if (pid == 0)
	{
		child_process(data, pipex, i);
		exit(0);
	}
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	if (!pipex->is_last)
	{
		close(pipex->fd[1]);
		pipex->prev_fd = pipex->fd[0];
	}
	return (pid);
}

void	execute_pipeline(t_data *data, t_pipex *pipex)
{
	int	i;
	int	status;

	if (!pipex || pipex->cmd_count <= 0)
		return ;
	pipex->pids = (pid_t *)malloc(sizeof(pid_t) * pipex->cmd_count);
	if (!pipex->pids)
		error(data);
	pipex->prev_fd = -1;
	i = -1;
	while (++i < pipex->cmd_count)
	{
		pipex->is_first = (i == 0);
		pipex->is_last = (i == pipex->cmd_count - 1);
		pipex->pids[i] = fork_process(data, pipex, i);
	}
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	i = -1;
	while (++i < pipex->cmd_count)
	{
		if (waitpid(pipex->pids[i], &status, 0) > 0 && WIFEXITED(status))
			norm_exec_pipeline(data, pipex, i);
	}
}
