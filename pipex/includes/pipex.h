/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/02/17 14:52:31 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*--------------------bibliotheques--------------------*/

# include <stdio.h>					// perror
# include <errno.h>					// errno (utile avec strerror et perror)
# include <string.h>				// strerror
# include <stdlib.h>				// malloc, free, exit
# include <unistd.h>				// open, close, read, write, access, dup, dup2
# include <sys/types.h>				// wait, waitpid, fork, pipe, unlink

# include "Libft/libft.h"			// Pour toutes les fonction
# include "ft_printf/ft_printf.h"	// Pour l'affichage formaté

/*--------------------structures--------------------*/

/*--------------------fonctions--------------------*/
/*----------sources----------*/

/*----------utils----------*/

#endif
