/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:53:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/06 18:06:41 by mstasiak         ###   ########.fr       */
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

void	ft_cleanup(t_data *data, t_token_list *token_list)
{
	free_token_list(token_list);
	if (data->envp)
	{
		free_tab(data->envp);
		data->envp = NULL;
	}
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
}