/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:31:43 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/03 16:46:48 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	usage(void)
{
	ft_putstr_fd((char *)RED"Error: Bad arguments"RESET"\n", 2);
	ft_putstr_fd((char *)"Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	exit(1);
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	error_127(t_pipex *pipex, char **cmd, char *path)
{
	perror(RED"Error"RESET);
	free_tab(cmd);
	if (path)
		free(path);
	if (pipex->pids)
		free(pipex->pids);
	exit(127);
}

void	error(t_pipex *pipex)
{
	perror(RED"Error"RESET);
	if (pipex->pids)
		free(pipex->pids);
	exit(1);
}
