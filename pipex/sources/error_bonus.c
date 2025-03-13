/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:31:43 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/13 15:46:15 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	usage(void)
{
	ft_putstr_fd(RED"Error: Bad argument\n\e[0m", 2);
	ft_putstr_fd("Ex:	./pipex <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
	ft_putstr_fd(
		"	./pipex \"here_doc\" <LIMITER> <cmd> <cmd1> <...> <file>\n", 1);
	exit(0);
}

void	error(void)
{
	perror(RED"Error\033[0m");
	exit(1);
}
