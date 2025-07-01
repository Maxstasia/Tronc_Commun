/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:37:40 by jbias             #+#    #+#             */
/*   Updated: 2025/06/30 20:37:41 by jbias            ###   ########.fr       */
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
