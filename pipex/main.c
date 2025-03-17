/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/17 17:28:00 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

/* *
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
	{
		perror(RED"Error: No such file or directory\033[0m");
		exit(1);
	}
	dup2(fd[1], 1);
	dup2(filein, 0);
	close(fd[0]);
	close(fd[1]);
	close(filein);
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
	{
		perror(RED"Error: Permission denied\033[0m");
		exit(1);
	}
	dup2(fd[0], 0);
	dup2(fileout, 1);
	close(fd[0]);
	close(fd[1]);
	close(fileout);
	execute(argv[3], envp);
}

static void create_pipe(t_cmd *cmd, char **argv, char **envp)
{
	int fd[2];
	pid_t pid;
	
	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
			error();
	cmd->pid = pid;
	if (pid == 0)
		child_process(argv, envp, fd);
	parent_process(argv, envp, fd);
}

// version de Chat GPT
/* static void create_pipe(t_cmd *cmd, char **argv, char **envp)
{
    int		fd[2];
    pid_t	pid;
    
    if (pipe(fd) == -1)
        error();
    pid = fork();
    if (pid == -1)
        error();
    cmd->pid = pid;
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        execute(cmd->cmd, envp);
    }
    else
    {
        close(fd[1]);
        dup2(fd[0], 0);
    }
} */

static void launch_cmd(t_cmd *cmd, char **argv, char **envp)
{
	int status;
	t_cmd *current;
	
	current = cmd;
	while(current)
	{
		create_pipe(current, argv, envp);
		current = current->next;
	}
	current = cmd;
	while(current)
	{
		waitpid(current->pid, &status, 0);
		current = current->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	t_cmd	*tmp_cmd;

	if (argc == 5)
	{
		while (argc -- > 1)
		{
			tmp_cmd = (t_cmd *)malloc(sizeof(t_cmd));
			if (!tmp_cmd)
				error();
			tmp_cmd->cmd = argv[argc];
			tmp_cmd->absolute_path = find_path(tmp_cmd->cmd, envp);
			tmp_cmd->next = cmd;
			cmd = tmp_cmd;
		}
		launch_cmd(cmd, argv, envp);
	}
	else
	{
		ft_putstr_fd((char *)RED"Error: Bad arguments\033[0m\n", 2);
		ft_putstr_fd((char *)"Ex:	./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	return (0);
}
