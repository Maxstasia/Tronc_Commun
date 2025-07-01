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

static void	update_exit_status(t_data *data, t_pipex *pipex, int status, int i)
{
	if (pipex->cmd_count == 1 || i == pipex->cmd_count - 1)
	{
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit_status = 128 + WTERMSIG(status);
	}
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

void	execute_pipeline(t_data *data, t_pipex *pipex)
{
	int	i;
	int	status;

	if (!pipex || pipex->cmd_count <= 0)
		return ;
	if (preprocess_all_heredocs(data, pipex) == -1)
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
	close_parent_heredoc_fds(pipex);
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	i = -1;
	while (++i < pipex->cmd_count)
		if (waitpid(pipex->pids[i], &status, 0) > 0)
			update_exit_status(data, pipex, status, i);
}
