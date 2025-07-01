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

static int	handle_input_redirect(t_data *data, t_redirect *redirect)
{
	int	fd;
	int	error_code;

	fd = open(redirect->file, O_RDONLY);
	if (fd < 0)
	{
		error_code = error_codes(data, redirect);
		return (error_code);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	handle_output_redirect(t_data *data, t_redirect *redirect)
{
	int	fd;
	int	error_code;

	fd = open(redirect->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		error_code = error_codes(data, redirect);
		return (error_code);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_append_redirect(t_data *data, t_redirect *redirect)
{
	int	fd;
	int	error_code;

	fd = open(redirect->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		error_code = error_codes(data, redirect);
		return (error_code);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_redir_norm(t_data *data, t_redirect *redirect)
{
	int	error_code;

	if (ft_strcmp(redirect->type, "<") == 0)
	{
		error_code = handle_input_redirect(data, redirect);
		if (error_code != 0)
			return (error_code);
	}
	else if (ft_strcmp(redirect->type, ">") == 0)
	{
		error_code = handle_output_redirect(data, redirect);
		if (error_code != 0)
			return (error_code);
	}
	else if (ft_strcmp(redirect->type, ">>") == 0)
	{
		error_code = handle_append_redirect(data, redirect);
		if (error_code != 0)
			return (error_code);
	}
	return (0);
}

int	apply_redirects(t_data *data, t_cmd *cmd, t_redirect *redirect)
{
	int		i;
	int		last_heredoc_fd;
	int		error_code;

	last_heredoc_fd = -1;
	if (apply_redir_norm2(data, cmd, redirect, &last_heredoc_fd) != 0)
		return (data->exit_status);
	i = -1;
	while (++i < cmd->redirect_count)
	{
		if (ft_strcmp(redirect[i].type, "<<") != 0)
		{
			error_code = apply_redir_norm(data, &redirect[i]);
			if (error_code != 0)
				return (check_hdoc_fd(&last_heredoc_fd), error_code);
		}
	}
	return (check_hdoc_fd(&last_heredoc_fd), 0);
}

int	apply_redirects_no_heredoc(t_data *data, t_cmd *cmd, t_redirect *redirect)
{
	int		i;
	int		last_heredoc_fd;
	int		error_code;

	last_heredoc_fd = -1;
	if (apply_redir_norm2_no_heredoc(data, cmd, redirect,
			&last_heredoc_fd) != 0)
		return (data->exit_status);
	i = -1;
	while (++i < cmd->redirect_count)
	{
		if (ft_strcmp(redirect[i].type, "<<") != 0)
		{
			error_code = apply_redir_norm(data, &redirect[i]);
			if (error_code != 0)
				return (check_hdoc_fd(&last_heredoc_fd), error_code);
		}
	}
	return (check_hdoc_fd(&last_heredoc_fd), 0);
}

int	apply_redirects_child(t_data *data, t_cmd *cmd, t_redirect *redirect)
{
	int		i;
	int		last_heredoc_fd;
	int		error_code;

	last_heredoc_fd = -1;
	if (apply_redir_norm2_child(data, cmd, redirect, &last_heredoc_fd) != 0)
		return (data->exit_status);
	i = -1;
	while (++i < cmd->redirect_count)
	{
		if (ft_strcmp(redirect[i].type, "<<") != 0)
		{
			error_code = apply_redir_norm(data, &redirect[i]);
			if (error_code != 0)
				return (check_hdoc_fd(&last_heredoc_fd), error_code);
		}
	}
	return (check_hdoc_fd(&last_heredoc_fd), 0);
}
