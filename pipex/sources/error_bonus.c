/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:31:43 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/01 13:57:35 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	usage(void)
{
	ft_putstr_fd(RED"Error: Bad argument"RESET"\n", 2);
	ft_putstr_fd("Ex:	./pipex <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
	ft_putstr_fd(
		"	./pipex \"here_doc\" <LIMITER> <cmd> <cmd1> <...> <file>\n", 1);
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
	perror(RED"Error"RESET);
	free_tab(cmd);
	if (path)
		free(path);
	exit(127);
}

void	error(void)
{
	perror(RED"Error"RESET);
	exit(1);
}
