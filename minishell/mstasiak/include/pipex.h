/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/17 15:16:05 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*--------------------macro--------------------*/

# define RED	"\033[31m"
# define GREEN  "\033[32m"
# define RESET  "\033[0m"

/*--------------------bibliotheques--------------------*/

// # include <string.h>		// strerror

# include <fcntl.h>			// open
# include <unistd.h>		// close, read, write, access, dup, dup2, execve
# include <stdlib.h>		// malloc, free, exit
# include <stdio.h>			// perror
# include <sys/wait.h>		// fork, pipe, unlink, wait, waitpid

# include "../pipex/includes/Libft/libft.h"
# include "../pipex/includes/ft_printf/ft_printf.h"
# include "../pipex/includes/get_next_line/get_next_line.h"

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
	pid_t	*pids;
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
/*-----error.c-----*/

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
void	error_127(t_pipex *pipex, char **cmd, char *path);

/**
 * error - Affiche un message d'erreur avec perror et quitte le programme.
 */
void	error(t_pipex *pipex);

/*-----pipex.c-----*/

/**
 * child_process - Exécute un processus enfant.
 * 
 * combiné avec les fonctions setup_first_process et setup_last_process.
 * - @pipex: Structure contenant les données nécessaires.
 */
void	child_process(t_pipex *pipex);

/**
 * handle_here_doc - Gère la redirection de l'entrée standard avec
 * la commande here_doc.
 * 
 * combiné avec la fonction infinite_loop.
 * - @pipex: Structure contenant les données nécessaires.
 */
void	handle_here_doc(t_pipex *pipex);

/*----------utils----------*/
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
char	*find_path(t_pipex *pipex, char *cmd_name);

/**
 * execute - Exécute une commande avec ses arguments.
 * 
 * - @pipex: Structure contenant les données nécessaires.
 */
void	execute(t_pipex *pipex);

#endif
