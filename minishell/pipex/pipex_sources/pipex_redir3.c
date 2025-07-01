/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_redir3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:05:26 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/01 17:14:36 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	apply_redirects_no_heredoc(t_data *data, t_cmd *cmd, t_redirect *redirect)
{
	int		i;
	int		last_heredoc_fd;
	int		error_code;

	last_heredoc_fd = -1;
	if (apply_redir_norm2(data, cmd, redirect,
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
