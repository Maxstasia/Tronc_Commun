/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/11 17:31:31 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/*--------------------macro--------------------*/

# define RED	"\033[31m"

/*--------------------bibliotheques--------------------*/

// # include <string.h>			  // strerror
// # include <stdlib.h>			  // malloc, free, exit
// # include <unistd.h>			  // open, close, read, write, access, dup, dup2

# include <errno.h>				  // errno (utile avec strerror et perror)
# include <stdio.h>				  // perror
# include <fcntl.h>				  // open
# include <sys/wait.h>			  // wait, waitpid, fork, pipe, unlink

# include "Libft/libft.h"		  // Pour toutes les fonction
# include "ft_printf/ft_printf.h" // Pour l'affichage formaté

/*--------------------structures--------------------*/

/*--------------------fonctions--------------------*/
/*----------sources----------*/
/*-----utils_bonus.c-----*/

/**
 * execute - Exécute une commande avec ses arguments.
 * 
 * - @argv: Commande et arguments sous forme de chaîne.
 * - @envp: Tableau des variables d'environnement.
 */
void	execute(char *argv, char **envp);

/**
 * open_file - Ouvre un fichier avec les bons droits.
 * 
 * - @argv: Nom du fichier.
 * - @i: Indicateur du mode d'ouverture.
 * Return: Le descripteur de fichier ouvert.
 */
int		open_file(char *argv, int i);

/**
 * get_next_line - Lit une ligne de l'entrée standard.
 * 
 * - @line: Pointeur pour stocker la ligne lue.
 * Return: Nombre d'octets lus ou -1 en cas d'erreur.
 */
int		get_next_line(char **line);

/*-----ft_split_advanced_bonus.c-----*/

/**
 * ft_split_advanced - Sépare une commande en arguments en respectant
 * les guillemets.
 * 
 * - @s: La commande à séparer.
 * Return: Un tableau de chaînes de caractères (les arguments).
 */
char	**ft_split_advanced(const char *s);

/*-----error_bonus.c-----*/

/**
 * usage - Affiche un message d'erreur pour une mauvaise utilisation
 * du programme et quitte l'exécution.
 */
void	usage(void);

/**
 * error - Affiche un message d'erreur avec perror et quitte le programme.
 */
void	error(void);

#endif
