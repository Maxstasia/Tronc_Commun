/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:24:29 by jbias             #+#    #+#             */
/*   Updated: 2025/07/03 16:57:34 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signal_exit_status = 0;

void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		if (g_signal_exit_status == 999)
			return ;
		g_signal_exit_status = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_heredoc_signals(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_exit_status = 130;
		write(STDOUT_FILENO, "\n", 1);
		close(STDIN_FILENO);
	}
}

void	restore_default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_heredoc_sigquit(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\b\b  \b\b", 6);
}
