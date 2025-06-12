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

static pid_t fork_process(t_data *data, t_pipex *pipex, int i)
{
	pid_t pid;
	
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

void execute_pipeline(t_data *data, t_pipex *pipex)
{
	int i;
	int status;
	
	printf(YELLOW"DEBUG: Starting pipeline execution with %d commands\n"RESET, pipex->cmd_count);
	pipex->pids = (pid_t *)malloc(sizeof(pid_t) * pipex->cmd_count);
	if (!pipex->pids)
		error(data);
	pipex->prev_fd = -1;
	i = -1;
	while (++i < pipex->cmd_count)
	{
		printf(YELLOW"DEBUG: Executing command %d: %s\n"RESET, i, pipex->commands[i].args[0]);
		pipex->is_first = (i == 0);
		pipex->is_last = (i == pipex->cmd_count - 1);
		pipex->pids[i] = fork_process(data, pipex, i);
		printf(YELLOW"DEBUG: Forked process %d with PID %d\n"RESET, i, pipex->pids[i]);
	}
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	i = -1;
	while (++i < pipex->cmd_count)
	{
		printf(YELLOW"DEBUG: Waiting for process %d with PID %d\n"RESET, i, pipex->pids[i]);
		if (waitpid(pipex->pids[i], &status, 0) > 0 && WIFEXITED(status))
		{
			printf(YELLOW"DEBUG: Process %d exited with status %d\n"RESET, i, WEXITSTATUS(status));
			if (i == pipex->cmd_count - 1)
				data->exit_status = WEXITSTATUS(status);
		}
	}
	free(pipex->pids);
}
