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
