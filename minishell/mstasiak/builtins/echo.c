/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/01 18:03:01 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int is_n_option(char *arg)
{
	int	i;
	
	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void echo_builtin(t_data *data)
{
	int	i;
	int	newline;
	
	i = 1;
	newline = 1;
	while (data->cmd[i] && is_n_option(data->cmd[i]))
	{
		newline = 0;
		i++;
	}
	while (data->cmd[i])
	{
		ft_putstr_fd(data->cmd[i], STDOUT_FILENO);
		if (data->cmd[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	data->exit_status = 0;
}
