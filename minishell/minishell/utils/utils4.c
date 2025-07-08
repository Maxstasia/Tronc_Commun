/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:46:16 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/01 16:46:29 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	all_commands_empty(t_pipex *pipex)
{
	int	i;

	if (!pipex || !pipex->commands || pipex->cmd_count <= 0)
		return (1);
	i = -1;
	while (++i < pipex->cmd_count)
	{
		if (pipex->commands[i].args && pipex->commands[i].args[0]
			&& pipex->commands[i].args[0][0])
			return (0);
	}
	return (1);
}
