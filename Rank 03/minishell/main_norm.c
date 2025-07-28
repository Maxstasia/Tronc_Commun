/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:00:48 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/03 17:49:02 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	norm_loop_2(t_data *data, t_token_list **token_list, char *line)
{
	add_history(line);
	process_input_line(data, line, *token_list);
	*token_list = reinit_token_list(*token_list, data);
	if (!*token_list)
	{
		ft_putstr_fd(RED"minishell: Critical error, exiting\n"RESET, 2);
		free(line);
		rl_clear_history();
		free_data(data);
		exit(1);
	}
	if (ft_strstr(line, "<<"))
		rl_on_new_line();
	if (data->should_exit)
	{
		free(line);
		if (token_list && *token_list)
			free_token_list(token_list);
		rl_clear_history();
		free_data(data);
		exit(data->exit_status);
	}
}
