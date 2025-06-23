/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:37:09 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/28 20:09:57 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

static int	isnum(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_builtin(t_data *data, t_cmd *cmd)
{
	ft_putstr_fd(PINK"exit\n"RESET, 2);
	if (!cmd->args[1])
	{
		free_data_fields(data);
		exit(data->exit_status);
	}
	if (!isnum(cmd->args[1]))
	{
		ft_putstr_fd(RED"maxishell: exit: '"YELLOW, 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(RED"' : numeric argument required\n"RESET, 2);
		free_data_fields(data);
		exit(255);
	}
	if (cmd->args[2])
	{
		ft_putstr_fd(RED"maxishell: exit: too many arguments\n"RESET, 2);
		data->exit_status = 1;
		return ;
	}
	data->exit_status = ft_atol(cmd->args[1]);
	data->exit_status = data->exit_status % 256;
	free_data_fields(data);
	exit(data->exit_status);
}
