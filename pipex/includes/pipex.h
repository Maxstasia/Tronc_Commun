/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/17 17:27:12 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*--------------------macro--------------------*/

# define RED	"\033[31m"

/*--------------------bibliotheques--------------------*/

# include <stdio.h>				  // perror
# include <fcntl.h>				  // open
# include <errno.h>				  // errno (utile avec strerror et perror)
# include <string.h>			  // strerror
# include <stdlib.h>			  // malloc, free, exit
# include <unistd.h>			  // close, read, write, access, dup, dup2
# include <sys/wait.h>			  // wait, waitpid, fork, pipe, unlink

# include "Libft/libft.h"		  // Pour toutes les fonction
# include "ft_printf/ft_printf.h" // Pour l'affichage formaté

/*--------------------structures--------------------*/

typedef struct s_cmd
{
	pid_t			pid;
	struct s_cmd	*next;
	char			*cmd;
	char			*absolute_path;
}							t_cmd;

/*--------------------fonctions--------------------*/
/*----------sources----------*/
/*-----ft_split_advanced.c-----*/

/**
 * ft_split_advanced - Sépare une commande en arguments en respectant
 * les guillemets.
 * 
 * - @s: La commande à séparer.
 * Return: Un tableau de chaînes de caractères (les arguments).
 */
char	**ft_split_advanced(const char *s);

/*-----utils.c-----*/

/**
 * find_path - Recherche le chemin d'accès à une commande en utilisant
 * les variables d'environnement.
 * 
 * - @cmd: Le nom de la commande à rechercher.
 * - @envp: Tableau des variables d'environnement.
 * Return: Le chemin complet de la commande si trouvé, sinon NULL.
 */
char	*find_path(char *cmd, char **envp);

/**
 * execute - Exécute une commande avec ses arguments.
 * 
 * - @argv: Commande et arguments sous forme de chaîne.
 * - @envp: Tableau des variables d'environnement.
 */
void	execute(char *argv, char **envp);

/**
 * error - Affiche un message d'erreur avec perror et quitte le programme.
 */
void	error(void);

#endif
