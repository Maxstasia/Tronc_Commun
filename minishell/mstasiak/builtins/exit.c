/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:37:09 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/28 13:48:00 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

long    ft_atol(const char *str)
{
    long    result;
    int     sign;

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

static int  isnum(char *str)
{
    int i;

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

void    exit_builtin(t_data *data, char *cmd)
{
    ft_putstr_fd(PINK"exit\n"RESET, 2);
    if (!cmd)
    {
        free_data(data);
        exit(data->exit_status);
    }
    if (!isnum(cmd))
    {
        ft_putstr_fd(RED"maxishell: exit: '"YELLOW, 2);
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(RED"' : numeric argument required\n"RESET, 2);
        free_data(data);
        exit(255);
    }
    if (cmd)
    {
        ft_putstr_fd(RED"maxishell: exit: too many arguments\n"RESET, 2);
        data->exit_status = 1;
        return ;
    }
    data->exit_status = ft_atol(cmd);
    data->exit_status = data->exit_status % 256;
    exit(data->exit_status);
}