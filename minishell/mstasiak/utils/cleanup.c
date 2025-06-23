/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:53:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/11 16:21:43 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_pipex_content(t_pipex *pipex)
{
	int	i;

	if (!pipex)
		return ;
	if (pipex->commands)
	{
		i = 0;
		while (i < pipex->cmd_count)
		{
			free_cmd(&pipex->commands[i]);
			i++;
		}
		free(pipex->commands);
	}
	if (pipex->pids)
		free(pipex->pids);
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

void	free_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count)
	{
		free_cmd(&pipex->commands[i]);
		i++;
	}
	free(pipex->commands);
	free(pipex->fd);
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
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->envp)
	{
		while (data->envp[i])
			free(data->envp[i++]);
		free(data->envp);
	}
	if (data->pwd)
		free(data->pwd);
	if (data->oldpwd)
		free(data->oldpwd);
	if (data->tmp)
		free(data->tmp);
	if (data->input)
		free(data->input);
	if (data->exit_status)
		data->exit_status = 0;
	if (data)
	{
		free(data);
		data = NULL;
	}
}
