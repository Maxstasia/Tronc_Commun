/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:42:28 by jbias             #+#    #+#             */
/*   Updated: 2025/06/16 15:42:31 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
void	apply_redirects(t_data *data, t_cmd *cmd)
{
	int		i;
	int		fd;
	int		heredoc_fd;

	heredoc_fd = -1;
	i = -1;
	while (++i, i < cmd->redirect_count)
	{
		if (ft_strcmp(cmd->redirects[i].type, "<") == 0)
		{
			fd = open(cmd->redirects[i].file, O_RDONLY);
			if (fd < 0)
				error(data);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (ft_strcmp(cmd->redirects[i].type, ">") == 0)
		{
			fd = open(cmd->redirects[i].file, O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				error(data);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (ft_strcmp(cmd->redirects[i].type, ">>") == 0)
		{
			fd = open(cmd->redirects[i].file, O_WRONLY
					| O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				error(data);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (ft_strcmp(cmd->redirects[i].type, "<<") == 0)
		{
			handle_here_doc(data, &cmd->redirects[i]);
			if (cmd->redirects[i].is_heredoc_fd != -1)
			{
				dup2(cmd->redirects[i].is_heredoc_fd, STDIN_FILENO);
				close(cmd->redirects[i].is_heredoc_fd);
				cmd->redirects[i].is_heredoc_fd = -1;
			}
		}
	}
	if (heredoc_fd != -1)
	{
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
	}
}*/

void	child_process(t_data *data, t_pipex *pipex, int cmd_index)
{
	t_cmd	*cmd;

	cmd = &pipex->commands[cmd_index];
	if (!pipex->is_last)
		close(pipex->fd[0]);
	if (cmd->redirect_count > 0)
		apply_redirects(data, cmd, cmd->redirects);
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
	execute(data, cmd);
}
