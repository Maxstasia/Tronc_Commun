/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:31:43 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/18 16:33:32 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	usage(void)
{
	ft_putstr_fd((char *)RED"Error: Bad arguments\033[0m\n", 2);
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

void	error_127(char **cmd, char *path)
{
	ft_putstr_fd(RED"Error: Command not found\033[0m\n", 2);
	free_tab(cmd);
	if (path)
		free(path);
	exit(127);
}

void	error(void)
{
	perror(RED"Error\033[0m");
	exit(1);
}
