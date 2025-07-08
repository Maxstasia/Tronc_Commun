/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:47:05 by jbias             #+#    #+#             */
/*   Updated: 2025/07/03 19:35:07 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_token_list	*reinit_token_list(t_token_list *token_list, t_data *data)
{
	(void)data;
	if (token_list)
		free_token_list(&token_list);
	token_list = malloc(sizeof(t_token_list));
	if (!token_list)
	{
		ft_putstr_fd(RED"minishell: malloc failed\n"RESET, 2);
		return (NULL);
	}
	init_token_list(token_list);
	return (token_list);
}

static int	init_minishell(int ac, t_token_list **token_list,
		t_data *data, char **envp)
{
	if (ac != 1)
	{
		ft_putstr_fd(RED"Error: ./minishell takes no arguments\n"RESET, 2);
		return (1);
	}
	*token_list = malloc(sizeof(t_token_list));
	if (!*token_list)
	{
		ft_putstr_fd(RED"minishell: malloc failed\n"RESET, 2);
		return (1);
	}
	init_token_list(*token_list);
	init_signals();
	init_data(data, envp);
	return (0);
}

static void	norm_loop(t_data *data, t_token_list **token_list, char *line)
{
	if (!line)
	{
		ft_putstr_fd(PINK"exit\n"RESET, STDOUT_FILENO);
		rl_clear_history();
		if (token_list && *token_list)
			free_token_list(token_list);
		free_data(data);
		exit(data->exit_status);
	}
	if (*line)
		norm_loop_2(data, token_list, line);
	free(line);
}

static void	main_loop(t_data *data, t_token_list **token_list)
{
	char	*line;

	while (1)
	{
		line = readline("\001"CYAN"\002minishell$ \001"RESET"\002");
		if (g_signal_exit_status != 0 && g_signal_exit_status != 999)
		{
			data->exit_status = g_signal_exit_status;
			g_signal_exit_status = 0;
		}
		norm_loop(data, token_list, line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data			data;
	t_token_list	*token_list;

	(void)av;
	if (init_minishell(ac, &token_list, &data, envp) != 0)
		return (1);
	main_loop(&data, &token_list);
	rl_clear_history();
	if (token_list)
		free_token_list(&token_list);
	free_data_temp(&data);
	free_data(&data);
	exit(data.exit_status);
}
