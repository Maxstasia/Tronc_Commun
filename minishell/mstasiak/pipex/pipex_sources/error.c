/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:39:14 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/23 15:06:56 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	malloc_failed(t_data *data)
{
	ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
	if (data)
		data->exit_status = EXIT_FAILURE;
	exit(EXIT_FAILURE);
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	free(tab);
}

void	free_cmd(t_cmd *cmd)
{
    int	i;
    
    if (!cmd)
        return ;
    i = 0;
    if (cmd->args)
    {
        free_tab(cmd->args);
        cmd->args = NULL;
    }
    if (cmd->redirects)
    {
        while (i < cmd->redirect_count)
        {
            if (cmd->redirects[i].type)
            {
                free(cmd->redirects[i].type);
                cmd->redirects[i].type = NULL;
            }
            if (cmd->redirects[i].file)
            {
                free(cmd->redirects[i].file);
                cmd->redirects[i].file = NULL;
            }
            i++;
        }
        free(cmd->redirects);
        cmd->redirects = NULL;
    }
    cmd->redirect_count = 0;
}

void	error_127(t_data *data, t_cmd *cmd, char *path)
{
	ft_putstr_fd(RED"maxishell: '"YELLOW, 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(RED"' : command not found\n"RESET, 2);
	free_cmd(cmd);
	if (path)
		free(path);
	if (data)
		data->exit_status = 127;
	exit(127);
}

void	error(t_data *data)
{
	perror(RED"maxishell: error");
	if (data)
		data->exit_status = 1;
	exit(1);
}
