/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:36:03 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/01 13:05:53 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_env_error(t_data *data, char * arg)
{
    ft_putstr_fd(RED"maxishell: env: '"YELLOW, 2);
    ft_putstr_fd(arg, 2);
    ft_putstr_fd(RED"' : No such file or directory\n"RESET, 2);
    data->exit_status = 127;
}

static void	display_env(t_data *data)
{
    int i;

    i = 0;
    while (data->envp[i])
    {
        ft_putstr_fd(data->envp[i], 1);
        ft_putchar_fd('\n', 1);
        i++;
    }
    data->exit_status = 0;
}

int env(t_data *data, char *cmd)
{
    if (cmd)
    {
        print_env_error(data, cmd);
        return (1);
    }
    display_env(data);
    return (0);
}
