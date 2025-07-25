/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:53:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/03 18:09:29 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_cmds(t_cmd *cmd, int j)
{
	while (j > 0)
	{
		j--;
		free_cmd(&cmd[j]);
	}
	free(cmd);
}

void	free_token_list(t_token_list **token_list)
{
	t_token_list	*current;
	t_token_list	*next;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	while (current)
	{
		next = current->next;
		free(current->token);
		free(current);
		current = next;
	}
	*token_list = NULL;
}

void	free_pipex(t_pipex *pipex, int bool)
{
	int		i;

	if (!pipex)
		return ;
	if (pipex->commands && pipex->cmd_count)
	{
		i = 0;
		while (i < pipex->cmd_count)
		{
			free_cmd(&pipex->commands[i]);
			i++;
		}
	}
	if (pipex->commands)
	{
		free(pipex->commands);
		pipex->commands = NULL;
	}
	if (pipex->pids)
	{
		free(pipex->pids);
		pipex->pids = NULL;
	}
	if (bool == 1)
		free(pipex);
}

void	free_data_fields(t_data *data)
{
	free_data_fields_part1(data);
	free_data_fields_part2(data);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	close_saved_fds(data);
	free_data_fields_part1(data);
	free_data_fields_part2(data);
}
