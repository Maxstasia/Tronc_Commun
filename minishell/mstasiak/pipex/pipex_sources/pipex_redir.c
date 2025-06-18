/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:24:36 by jbias             #+#    #+#             */
/*   Updated: 2025/06/16 17:24:37 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_input_redirect(t_data *data, t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->file, O_RDONLY);
	if (fd < 0)
		error(data);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	handle_output_redirect(t_data *data, t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		error(data);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	handle_append_redirect(t_data *data, t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		error(data);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	handle_heredoc_redirect(t_data *data, t_redirect *redirect)
{
	handle_here_doc(data, redirect);
	if (redirect->is_heredoc_fd != -1)
	{
		dup2(redirect->is_heredoc_fd, STDIN_FILENO);
		close(redirect->is_heredoc_fd);
		redirect->is_heredoc_fd = -1;
	}
}

void	apply_redirects(t_data *data, t_cmd *cmd, t_redirect *redirect)
{
	int		i;
	int		heredoc_fd;

	heredoc_fd = -1;
	i = 0;
	while (i < cmd->redirect_count)
	{
		if (ft_strcmp(redirect->type, "<") == 0)
			handle_input_redirect(data, redirect);
		else if (ft_strcmp(redirect->type, ">") == 0)
			handle_output_redirect(data, redirect);
		else if (ft_strcmp(redirect->type, ">>") == 0)
			handle_append_redirect(data, redirect);
		else if (ft_strcmp(redirect->type, "<<") == 0)
			handle_heredoc_redirect(data, redirect);
		i++;
	}
	if (heredoc_fd != -1)
	{
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
	}
}
