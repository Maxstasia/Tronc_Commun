/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:58:58 by jbias             #+#    #+#             */
/*   Updated: 2025/07/03 18:09:33 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_data_envp(t_data *data)
{
	int	i;

	if (data->envp)
	{
		i = 0;
		while (data->envp[i])
			free(data->envp[i++]);
		free(data->envp);
		data->envp = NULL;
	}
}

void	cleanup_parsing_error(t_data *data, t_token_list **token_list,
		char *preprocessed_line, char *expanded_line)
{
	if (preprocessed_line)
		free(preprocessed_line);
	if (expanded_line)
		free(expanded_line);
	if (token_list && *token_list)
		free_token_list(token_list);
	data->exit_status = 2;
}

void	free_data_fields_part1(t_data *data)
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
}

void	free_data_fields_part2(t_data *data)
{
	if (!data)
		return ;
	if (data->tmp)
	{
		free(data->tmp);
		data->tmp = NULL;
	}
	if (data->preprocessed_line)
	{
		free(data->preprocessed_line);
		data->preprocessed_line = NULL;
	}
	if (data->expanded)
	{
		free(data->expanded);
		data->expanded = NULL;
	}
}
