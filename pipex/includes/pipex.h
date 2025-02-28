/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/02/28 14:27:15 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*--------------------bibliotheques--------------------*/

// # include <errno.h>			  // errno (utile avec strerror et perror)
// # include <string.h>			  // strerror
// # include <stdlib.h>			  // malloc, free, exit
// # include <unistd.h>			  // close, read, write, access, dup, dup2

# include <stdio.h>				  // perror
# include <fcntl.h>				  // open
# include <sys/wait.h>			  // wait, waitpid, fork, pipe, unlink

# include "Libft/libft.h"		  // Pour toutes les fonction
# include "ft_printf/ft_printf.h" // Pour l'affichage formaté

/*--------------------structures--------------------*/

/*--------------------fonctions--------------------*/
/*----------sources----------*/
/*-----utils.c-----*/

void	error(void);

void	execute(char *argv, char **envp);

#endif
