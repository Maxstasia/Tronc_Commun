/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:02:30 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/01 17:02:31 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**init_envp(t_data *data, char **envp)
{
	if (!envp || !envp[0])
	{
		data->envp = malloc(sizeof(char *) * 3);
		if (!data->envp)
			malloc_failed(data);
		data->envp[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
		data->envp[1] = ft_strdup("SHLVL=1");
		data->envp[2] = NULL;
		if (!data->envp[0] || !data->envp[1])
		{
			free(data->envp[0]);
			free(data->envp[1]);
			free(data->envp);
			malloc_failed(data);
		}
	}
	else
		data->envp = copy_envp(envp);
	return (data->envp);
}
