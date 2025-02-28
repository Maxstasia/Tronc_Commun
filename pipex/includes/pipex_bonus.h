/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/02/28 14:33:25 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/*--------------------bibliotheques--------------------*/

// # include <errno.h>			  // errno (utile avec strerror et perror)
// # include <string.h>			  // strerror
// # include <stdlib.h>			  // malloc, free, exit
// # include <unistd.h>			  // open, close, read, write, access, dup, dup2

# include <stdio.h>				  // perror
# include <fcntl.h>				  // open
# include <sys/wait.h>			  // wait, waitpid, fork, pipe, unlink

# include "Libft/libft.h"		  // Pour toutes les fonction
# include "ft_printf/ft_printf.h" // Pour l'affichage formaté

/*--------------------structures--------------------*/

/*--------------------fonctions--------------------*/
/*----------sources----------*/
/*-----utils_bonus.c-----*/

void	execute(char *argv, char **envp);

int		open_file(char *argv, int i);

int		get_next_line(char **line);

/*-----error_bonus.c-----*/

void	usage(void);

void	error(void);

#endif
