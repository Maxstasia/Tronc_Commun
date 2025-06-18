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

void	free_token_list(t_token_list *token)
{
	t_token_list	*current;
	t_token_list	*next;

	current = token;
	if (!token)
		return ;
	while (current)
	{
		next = current->next;
		if (current->token)
		{
			free(current->token);
			current->token = NULL;
		}
		free(current);
		current = next;
	}
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
}
