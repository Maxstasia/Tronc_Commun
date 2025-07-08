/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_executor2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:20:30 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/08 15:10:18 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static pid_t	fork_process(t_data *data, t_pipex *pipex, int i)
{
	pid_t	pid;

	if (!pipex->is_last)
	{
		if (pipe(pipex->fd) < 0)
		{
			if (pipex->pids)
				free(pipex->pids);
			error(data);
		}
	}
	pid = fork();
	if (pid < 0)
	{
		if (pipex->pids)
			free(pipex->pids);
		error(data);
	}
	if (pid == 0)
		return (child_process(data, pipex, i), exit(0), pid);
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	if (!pipex->is_last)
		return (close(pipex->fd[1]), pipex->prev_fd = pipex->fd[0], pid);
	return (pid);
}

static void	close_parent_heredoc_fds(t_pipex *pipex)
{
	int		i;
	int		j;
	t_cmd	*cmd;

	i = -1;
	while (++i < pipex->cmd_count)
	{
		cmd = &pipex->commands[i];
		j = -1;
		while (++j < cmd->redirect_count)
		{
			if (ft_strcmp(cmd->redirects[j].type, "<<") == 0
				&& cmd->redirects[j].is_heredoc_fd > 0)
			{
				close(cmd->redirects[j].is_heredoc_fd);
				cmd->redirects[j].is_heredoc_fd = -1;
			}
		}
	}
}

void	fork_all_processes(t_data *data, t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->cmd_count)
	{
		pipex->is_first = (i == 0);
		pipex->is_last = (i == pipex->cmd_count - 1);
		pipex->pids[i] = fork_process(data, pipex, i);
	}
	close_parent_heredoc_fds(pipex);
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
}
