/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/17 17:28:57 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex_bonus.h"

/**
 * child_process - Crée un processus enfant pour exécuter une commande.
 * 
 * - @argv: Tableau des arguments.
 * - @envp: Tableau des variables d'environnement.
 */
static void	child_process(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execute(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(pid, NULL, 0);
	}
	if (ft_strncmp(argv, "cat", 3) == 0)
		execute((char *)"head -c 1024", envp);
}

/**
 * here_doc - Gère l'entrée standard depuis un "here document".
 * 
 * - @limiter: La chaîne qui indique la fin de l'entrée.
 * - @argc: Le nombre d'arguments passés au programme.
 */
static void	here_doc(char *limiter, int argc)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (argc < 6)
		usage();
	if (pipe(fd) == -1)
		error();
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		ft_printf(">  ");
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(0);
			ft_printf(">  ");
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		wait(NULL);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	filein;
	int	fileout;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			fileout = open_file(argv[argc - 1], 0);
			here_doc(argv[2], argc);
		}
		else
		{
			i = 2;
			fileout = open_file(argv[argc - 1], 0);
			filein = open_file(argv[1], 1);
			dup2(filein, 0);
		}
		while (i < argc - 2)
			child_process(argv[i++], envp);
		dup2(fileout, 1);
		execute(argv[argc - 2], envp);
	}
	usage();
}


///////////////////

/* create_pipe(t_cmd *cmd)
{
	int fd[2];
	pid_t pid;
	
	pipe(fd)
	pid = fork();
	cmd->pid = pid;
	if(pid== 0)
		enfant();
	parent();
}

launch_cmd(t_cmd *cmd)
{
	int status;
	t_cmd *current;
	
	current = *cmd;
	while(current)
	{
		create_pipe(current);
		current = current->next;
	}
	current = *cmd;
	while(current)
	{
		waitpid(current->pid, &status, 0);
		current = current->next;
	}
} */