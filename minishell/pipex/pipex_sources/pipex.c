/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:42:28 by jbias             #+#    #+#             */
/*   Updated: 2025/07/03 16:57:19 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_process(t_data *data, t_pipex *pipex, int cmd_index)
{
	t_cmd	*cmd;
	int		redir_error;

	cmd = &pipex->commands[cmd_index];
	if (!pipex->is_last)
		close(pipex->fd[0]);
	if (!pipex->is_first)
	{
		dup2(pipex->prev_fd, STDIN_FILENO);
		close(pipex->prev_fd);
	}
	if (!pipex->is_last)
	{
		dup2(pipex->fd[1], STDOUT_FILENO);
		close(pipex->fd[1]);
	}
	redir_error = 0;
	if (cmd->redirect_count > 0)
	{
		redir_error = apply_redirects_child(data, cmd, cmd->redirects);
		if (redir_error != 0)
			exit(redir_error);
	}
	execute(data, cmd);
}
