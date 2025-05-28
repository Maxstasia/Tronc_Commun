/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/06 18:06:23 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_n_option(char *arg)
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

void	echo_builtin(t_token_list *token_list, t_data *data)
{
	int	i;
	int	newline;
	t_token_list	*tmp;

	tmp = token_list;
	i = 1;
	newline = 1;
	while (tmp->token && is_n_option(tmp->token))
	{
		newline = 0;
		i++;
	}
	while (token_list->token)
	{
		ft_putstr_fd(tmp->token, STDOUT_FILENO);
		i++;
		if (tmp->token)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (newline)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	data->exit_status = 0;
}
