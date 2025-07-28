/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:43:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/03 17:22:41 by mstasiak         ###   ########.fr       */
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

static int	init_pipeline_execution(t_data *data, t_pipex *pipex)
{
	if (!pipex || pipex->cmd_count <= 0)
		return (-1);
	if (preprocess_all_heredocs(data, pipex) == -1)
		return (-1);
	pipex->pids = (pid_t *)malloc(sizeof(pid_t) * pipex->cmd_count);
	if (!pipex->pids)
		error(data);
	pipex->prev_fd = -1;
	g_signal_exit_status = 999;
	return (0);
}

void	execute_pipeline(t_data *data, t_pipex *pipex, t_token_list *tok)
{
	int	i;
	int	status;

	if (init_pipeline_execution(data, pipex) == -1)
		return ;
	fork_all_processes(data, pipex, tok);
	i = -1;
	while (++i < pipex->cmd_count)
	{
		if (waitpid(pipex->pids[i], &status, 0) > 0)
		{
			update_exit_status(data, pipex, status, i);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				write(STDOUT_FILENO, "\n", 1);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
				write(STDOUT_FILENO, "Quitter (core dumped)\n", 22);
		}
	}
	g_signal_exit_status = 0;
	if (pipex->pids)
	{
		free(pipex->pids);
		pipex->pids = NULL;
	}
}
