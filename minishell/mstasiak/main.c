/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:47:05 by jbias             #+#    #+#             */
/*   Updated: 2025/06/27 15:11:22 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static t_token_list	*reinit_token_list(t_token_list *token_list, t_data *data)
{
	if (token_list)
		free_token_list(&token_list);
	token_list = malloc(sizeof(t_token_list));
	if (!token_list)
	{
		ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
		free_data(data);
		exit(1);
	}
	init_token_list(token_list);
	return (token_list);
}

static int	init_minishell(int ac, t_token_list **token_list,
		t_data *data, char **envp)
{
	if (ac != 1)
	{
		ft_putstr_fd(RED"Error: ./maxishell takes no arguments\n"RESET, 2);
		return (1);
	}
	*token_list = malloc(sizeof(t_token_list));
	if (!*token_list)
	{
		ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
		return (1);
	}
	init_token_list(*token_list);
	init_signals();
	init_data(data, envp);
	return (0);
}

static void	main_loop(t_data *data, t_token_list **token_list)
{
	char	*line;

	while (1)
	{
		line = readline("\001"CYAN"\002maxishell$ \001"RESET"\002");
		if (!line)
		{
			ft_putstr_fd(PINK"exit\n"RESET, STDOUT_FILENO);
			clear_history();
			free_token_list(token_list);
			free_data(data);
			exit(data->exit_status);
		}
		if (*line)
		{
			add_history(line);
			process_input_line(data, line, *token_list);
			*token_list = reinit_token_list(*token_list, data);
			if (ft_strstr(line, "<<"))
				rl_on_new_line();
		}
	}
	exit(data->exit_status);
}

int	main(int ac, char **av, char **envp)
{
	t_data			data;
	t_token_list	*token_list;

	(void)av;
	if (init_minishell(ac, &token_list, &data, envp) != 0)
		return (1);
	using_history();
	main_loop(&data, &token_list);
	return (data.exit_status);
}
