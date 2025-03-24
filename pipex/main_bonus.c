/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/24 18:23:43 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex_bonus.h"

static void	setup_first_process(t_pipex *pipex)
{
	int	file;

	file = open(pipex->filein, O_RDONLY);
	if (file < 0 && !pipex->here_doc)
	{
		error();
		exit(1);
	}
	if (pipex->here_doc)
	{
		if (pipex->prev_fd == -1)
		{
			perror("Error");
			exit(1);
		}
		close(pipex->prev_fd);
	}
	else if (file >= 0)
		close(file);
}

static int	child_process(t_pipex *pipex)
{
	int	file;

	if (pipex->is_first)
		setup_first_process(pipex);
	if (pipex->prev_fd == -1)
	{
		perror("Error");
		exit(1);
	}
	if (pipex->is_last)
	{
		file = open(pipex->fileout, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file < 0)
		{
			error();
			return (1);
		}
		if (dup2(file, STDOUT_FILENO) == -1)
			perror("dup2 file to stdout failed");
		close(file);
	}
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	execute(pipex);
	return (0);
}

static void	handle_here_doc(t_pipex *pipex)
{
	char	buffer[1024];
	int		fd[2];
	size_t	delim_len;
	ssize_t	bytes_read;

	if (pipe(fd) < 0)
		error();
	delim_len = ft_strlen(pipex->argv[2]);
	while (1)
	{
		bytes_read = read(STDIN_FILENO, buffer, 1023);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		if (ft_strncmp(buffer, pipex->argv[2], delim_len) == 0
			&& buffer[delim_len] == '\n')
			break ;
	}
	close(fd[1]);
	pipex->prev_fd = fd[0];
}

static pid_t	fork_process(t_pipex *pipex, int i, t_temp *tmp)
{
	pid_t	pid;

	if (pipe(pipex->fd) < 0)
		error();
	pid = fork();
	if (pid < 0)
		error();
	if (pid == 0)
	{
		pipex->is_first = (i == 0);
		pipex->is_last = (i == tmp->cmd_count - 1);
		if (pipex->here_doc)
			pipex->argv = &pipex->argv[i + 3];
		else
			pipex->argv = &pipex->argv[i + 2];
		child_process(pipex);
		exit(0);
	}
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	pipex->prev_fd = pipex->fd[0];
	close(pipex->fd[1]);
	return (pid);
}

static void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp, t_temp *tmp)
{
	if (argc < 5)
		usage();
	tmp->last_status = 0;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->here_doc = (ft_strcmp(argv[1], "here_doc") == 0);
	pipex->filein = argv[1];
	pipex->fileout = argv[argc - 1];
	pipex->prev_fd = -1;
	if (pipex->here_doc)
	{
		handle_here_doc(pipex);
		tmp->cmd_count = argc - 4;
	}
	else
	{
		pipex->prev_fd = open(pipex->filein, O_RDONLY);
		tmp->cmd_count = argc - 3;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	t_temp	tmp;
	int		i;

	init_pipex(&pipex, argc, argv, envp, &tmp);
	i = -1;
	while (++i < tmp.cmd_count)
		tmp.last_pid = fork_process(&pipex, i, &tmp);
	if (pipex.prev_fd != -1)
		close(pipex.prev_fd);
	while (wait(NULL) > 0 && errno != ECHILD)
		;
	waitpid(tmp.last_pid, &tmp.status, 0);
	if (WIFEXITED(tmp.status))
		tmp.last_status = WEXITSTATUS(tmp.status);
	return (tmp.last_status);
}
