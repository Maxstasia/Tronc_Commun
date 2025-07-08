/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:53:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/03 19:37:02 by mstasiak         ###   ########.fr       */
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
	if (!data)
		return ;
	if (data->envp)
		free_data_envp(data);
	if (data->pwd)
	{
		free(data->pwd);
		data->pwd = NULL;
	}
	if (data->oldpwd)
	{
		free(data->oldpwd);
		data->oldpwd = NULL;
	}
	if (data->tmp)
	{
		free(data->tmp);
		data->tmp = NULL;
	}
	free_data_temp(data);
}

void	free_data_temp(t_data *data)
{
	if (!data)
		return ;
	if (data->temp_preprocessed)
	{
		free(data->temp_preprocessed);
		data->temp_preprocessed = NULL;
	}
	if (data->temp_expanded)
	{
		free(data->temp_expanded);
		data->temp_expanded = NULL;
	}
	if (data->temp_parsed_token)
	{
		free(data->temp_parsed_token);
		data->temp_parsed_token = NULL;
	}
	if (data->temp_pipeline_fd)
	{
		free(data->temp_pipeline_fd);
		data->temp_pipeline_fd = NULL;
	}
	if (data->temp_cmd_array)
	{
		free_cmds(data->temp_cmd_array, data->temp_cmd_count);
		data->temp_cmd_array = NULL;
		data->temp_cmd_count = 0;
	}
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	close_saved_fds(data);
	if (data->envp)
		free_data_envp(data);
	if (data->pwd)
	{
		free(data->pwd);
		data->pwd = NULL;
	}
	if (data->oldpwd)
	{
		free(data->oldpwd);
		data->oldpwd = NULL;
	}
	if (data->tmp)
	{
		free(data->tmp);
		data->tmp = NULL;
	}
}
