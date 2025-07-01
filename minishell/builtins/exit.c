/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:37:09 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/27 16:01:05 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <limits.h>

static int	check_overflow(long long result, int digit, int sign)
{
	if (sign == 1)
	{
		if (result > (LLONG_MAX - digit) / 10)
		{
			ft_putstr_fd(RED"minishell: exit: out of range\n"RESET, 2);
			return (1);
		}
	}
	else
	{
		if (result < (LLONG_MIN + digit) / 10)
		{
			ft_putstr_fd(RED"minishell: exit: out of range\n"RESET, 2);
			return (1);
		}
	}
	return (0);
}

static long	long	ft_atol(const char *str)
{
	long long	result;
	int			sign;
	int			digit;

	if (!str)
		return (0);
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
		digit = *str - '0';
		if (check_overflow(result, digit, sign))
			exit(2);
		result = result * 10 + digit;
		str++;
	}
	return (result * sign);
}

static int	isnum(char *str)
{
	int	i;

	if (!str)
		return (0);
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
		free_data(data);
		exit(data->exit_status);
	}
	if (!isnum(cmd->args[1]))
	{
		ft_putstr_fd(RED"minishell: exit: '"YELLOW, 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(RED"' : numeric argument required\n"RESET, 2);
		free_data(data);
		exit(2);
	}
	if (cmd->args[2])
	{
		ft_putstr_fd(RED"minishell: exit: too many arguments\n"RESET, 2);
		data->exit_status = 1;
		return ;
	}
	data->exit_status = ft_atol(cmd->args[1]);
	data->exit_status = data->exit_status % 256;
	free_data(data);
	exit(data->exit_status);
}
