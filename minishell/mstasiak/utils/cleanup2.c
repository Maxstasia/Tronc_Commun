/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:58:58 by jbias             #+#    #+#             */
/*   Updated: 2025/06/19 14:59:01 by jbias            ###   ########.fr       */
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
