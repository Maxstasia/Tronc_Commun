/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:36:03 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/17 17:38:18 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_env_error(t_data *data, char * arg)
{
    ft_putstr_fd("minishell: env: ", 2);
    ft_putstr_fd(arg, 2);
    ft_putstr_fd(": No such file or directory\n", 2);
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

int env(t_data *data)
{
    if (data->cmd[1])
    {
        print_env_error(data, data->cmd[1]);
        return (1);
    }
    display_env(data);
    return (0);
}
