/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:38:34 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/01 13:05:53 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int pwd(t_data *data)
{
    char *current_dir;

    current_dir = getcwd(NULL, 0);
    if (current_dir == NULL)
    {
        perror(RED"maxishell: pwd");
        data->exit_status = 1;
        return (1);
    }
    printf("%s\n", current_dir);
    free(data->pwd);
    data->pwd = current_dir;
    data->exit_status = 0;
    return (0);
}