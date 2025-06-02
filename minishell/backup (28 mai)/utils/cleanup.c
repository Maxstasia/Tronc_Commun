/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:53:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/28 19:29:11 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_token_list(t_token_list *token)
{
	t_token_list	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->token);
		free(tmp);
	}
}

void	free_pipex(t_pipex *pipex)
{
	int i;
	
	i = 0;
	while (i < pipex->cmd_count)
	{
		free_cmd(&pipex->commands[i]);
		i++;
	}
	free(pipex->commands);
}

void free_data(t_data *data)
{
	int i;
	
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
