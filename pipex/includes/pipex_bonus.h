/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/01 16:40:39 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/*--------------------macro--------------------*/

# define RED	"\033[31m"
# define GREEN  "\033[32m"
# define RESET  "\033[0m"

/*--------------------bibliotheques--------------------*/

// # include <string.h>			  // strerror

# include <fcntl.h>				  // open
# include <unistd.h>			  // close, read, write, access, dup, dup2, execve
# include <stdlib.h>			  // malloc, free, exit
# include <stdio.h>				  // perror
# include <sys/wait.h>			  // fork, pipe, unlink, wait, waitpid

# include "Libft/libft.h"		  		// Pour toutes les fonction
# include "ft_printf/ft_printf.h" 		// Pour l'affichage formaté
# include "get_next_line/get_next_line.h"// Pour lire une ligne

/*--------------------structures--------------------*/

typedef struct s_pipex
{
	char	**argv;
	char	**envp;
	char	*filein;
	char	*fileout;
	int		fd[2];
	int		prev_fd;
	int		is_first;
	int		is_last;
	int		here_doc;
}					t_pipex;

typedef struct s_temp
{
	int		cmd_count;
	int		last_status;
	int		status;
}					t_temp;

/*--------------------fonctions--------------------*/
/*----------sources----------*/
/*-----error_bonus.c-----*/

/**
 * usage - Affiche un message d'erreur d'utilisation et quitte le programme.
 */
void	usage(void);

/**
 * free_tab - Libère la mémoire allouée pour un tableau de chaînes
 * de caractères.
 * 
 * - @tab: Le tableau à libérer.
 */
void	free_tab(char **tab);

/**
 * error_127 - Affiche un message d'erreur et quitte le programme avec
 * le code 127.
 * 
 * - @cmd: Tableau des arguments de la commande.
 * - @path: Chemin d'accès à la commande.
 */
void	error_127(char **cmd, char *path);

/**
 * error - Affiche un message d'erreur avec perror et quitte le programme.
 */
void	error(void);

/*-----pipex_bonus.c-----*/

/**
 * child_process - Exécute un processus enfant.
 * 
 * combiné avec les fonctions setup_first_process et setup_last_process.
 * - @pipex: Structure contenant les données nécessaires.
 * Return: 0 si tout s'est bien passé, 1 sinon.
 */
void		child_process(t_pipex *pipex);

/**
 * handle_here_doc - Gère la redirection de l'entrée standard avec
 * la commande here_doc.
 * 
 * combiné avec la fonction infinite_loop.
 * - @pipex: Structure contenant les données nécessaires.
 */
void	handle_here_doc(t_pipex *pipex);

/**
 * fork_process - Crée un processus enfant.
 * 
 * - @pipex: Structure contenant les données nécessaires.
 * - @i: L'index du processus.
 * - @tmp: Structure contenant des données temporaires.
 * Return: L'identifiant du processus enfant.
 */
pid_t	fork_process(t_pipex *pipex, int i, t_temp *tmp);

/*----------utils----------*/
/*-----ft_split_advanced_bonus.c-----*/

/**
 * ft_split_advanced - Sépare une commande en arguments en respectant
 * les guillemets.
 * 
 * - @s: La commande à séparer.
 * Return: Un tableau de chaînes de caractères (les arguments).
 */
char	**ft_split_advanced(const char *s);

/*-----utils_bonus.c-----*/

/**
 * find_path - Recherche le chemin d'accès à une commande en utilisant
 * les variables d'environnement.
 * 
 * - @cmd: Le nom de la commande à rechercher.
 * - @envp: Tableau des variables d'environnement.
 * Return: Le chemin complet de la commande si trouvé, sinon NULL.
 */
char	*find_path(t_pipex *pipex, char *cmd_name);

/**
 * execute - Exécute une commande avec ses arguments.
 * 
 * - @pipex: Structure contenant les données nécessaires.
 */
void	execute(t_pipex *pipex);

#endif
