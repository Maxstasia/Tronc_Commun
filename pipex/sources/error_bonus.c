/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:31:43 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/27 17:53:30 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	usage(void)
{
	ft_putstr_fd(RED"Error: Bad argument\n\e[0m", 2);
	ft_putstr_fd("Ex:	./pipex_bonus <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
	ft_putstr_fd(
		"	./pipex_bonus \"here_doc\" <LIMITER> <cmd> <cmd1> <...> <file>\n", 1);
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
	ft_putstr_fd(RED"Error: Command not found"RESET"\n", 2);
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
