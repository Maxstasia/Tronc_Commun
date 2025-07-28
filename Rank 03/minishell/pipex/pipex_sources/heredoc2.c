/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:37:40 by jbias             #+#    #+#             */
/*   Updated: 2025/07/01 16:59:30 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc_loop_norm(t_data *data, char *expanded_delim)
{
	if (g_signal_exit_status == 130)
	{
		data->exit_status = 130;
		return (1);
	}
	ft_putstr_fd("\nbash: warning: heredoc delim by EOF (wanted `", 2);
	ft_putstr_fd(expanded_delim, 2);
	ft_putstr_fd("')\n", 2);
	return (0);
}

int	reset_signal_exit(int sig_exit)
{
	if (sig_exit == 130)
		return (0);
	return (sig_exit);
}

void	handle_here_doc_delayed(t_data *data, t_redirect *redirect)
{
	if (redirect->is_heredoc_fd > 0)
		return ;
	handle_here_doc(data, redirect);
}

int	preprocess_all_heredocs(t_data *data, t_pipex *pipex)
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
			if (ft_strcmp(cmd->redirects[j].type, "<<") == 0)
			{
				handle_here_doc(data, &cmd->redirects[j]);
				if (cmd->redirects[j].is_heredoc_fd == -1)
					return (-1);
			}
		}
	}
	return (0);
}
