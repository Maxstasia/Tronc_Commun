/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:39:14 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/28 19:25:14 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	usage(void)
{
	ft_putstr_fd(RED"maxishell: invalid arguments\n"RESET, 2);
	exit(1);
}

void	free_tab(char **tab)
{
	int i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	free(tab);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (cmd->args)
		free_tab(cmd->args);
	if (cmd->redirects)
	{
		for (i = 0; i < cmd->redirect_count; i++)
		{
			free(cmd->redirects[i].type);
			free(cmd->redirects[i].file);
		}
		free(cmd->redirects);
	}
}

void error_127(t_data *data, t_cmd *cmd, char *path)
{
	ft_putstr_fd(RED"maxishell: '"YELLOW, 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(RED"' : command not found\n"RESET, 2);
	free_cmd(cmd); if (path) free(path);
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