/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/13 15:55:15 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

/**
 * child_process - Crée un processus enfant pour exécuter une commande.
 * 
 * - @argv: Tableau des arguments.
 * - @envp: Tableau des variables d'environnement.
 * - @fd: Tableau contenant les descripteurs de fichier.
 */
static void	child_process(char **argv, char **envp, int *fd)
{
	int		filein;

	filein = open(argv[1], O_RDONLY);
	if (filein == -1)
		error();
	dup2(fd[1], 1);
	dup2(filein, 0);
	close(fd[0]);
	execute(argv[2], envp);
}

/**
 * parent_process - Exécute une commande dans le processus parent.
 * 
 * - @argv: Tableau des arguments.
 * - @envp: Tableau des variables d'environnement.
 * - @fd: Tableau contenant les descripteurs de fichier.
 */
static void	parent_process(char **argv, char **envp, int *fd)
{
	int		fileout;

	fileout = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fileout == -1)
		error();
	dup2(fd[0], 0);
	dup2(fileout, 1);
	close(fd[1]);
	execute(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error();
		pid1 = fork();
		if (pid1 == -1)
			error();
		if (pid1 == 0)
			child_process(argv, envp, fd);
		waitpid(pid1, NULL, 0);
		parent_process(argv, envp, fd);
	}
	else
	{
		ft_putstr_fd((char *)RED"Error: Bad arguments\033[0m\n", 2);
		ft_putstr_fd((char *)"Ex:	./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	return (0);
}
