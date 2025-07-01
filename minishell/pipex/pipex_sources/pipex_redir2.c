/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:24:36 by jbias             #+#    #+#             */
/*   Updated: 2025/06/16 17:24:37 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	apply_redir_norm2(t_data *data, t_cmd *cmd,
	t_redirect *redirect, int *last_heredoc_fd)
{
	(void)data;
	(void)cmd;
	(void)redirect;
	(void)last_heredoc_fd;
	return (0);
}

int	apply_redir_norm2_no_heredoc(t_data *data, t_cmd *cmd,
	t_redirect *redirect, int *last_heredoc_fd)
{
	(void)data;
	(void)cmd;
	(void)redirect;
	(void)last_heredoc_fd;
	return (0);
}

int	apply_redir_norm2_child(t_data *data, t_cmd *cmd,
	t_redirect *redirect, int *last_heredoc_fd)
{
	int		i;
	int		dup_fd;

	(void)data;
	i = -1;
	while (++i < cmd->redirect_count)
	{
		if (ft_strcmp(redirect[i].type, "<<") == 0)
		{
			if (redirect[i].is_heredoc_fd == -1)
			{
				if (*last_heredoc_fd != -1)
					close(*last_heredoc_fd);
				return (-1);
			}
			dup_fd = dup(redirect[i].is_heredoc_fd);
			if (dup_fd == -1)
			{
				if (*last_heredoc_fd != -1)
					close(*last_heredoc_fd);
				return (-1);
			}
			if (*last_heredoc_fd != -1)
				close(*last_heredoc_fd);
			*last_heredoc_fd = dup_fd;
			redirect[i].is_heredoc_fd = dup_fd;
		}
	}
	return (0);
}
