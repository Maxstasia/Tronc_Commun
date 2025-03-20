/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/20 16:14:48 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex_bonus.h"

static void	child_process(t_pipex *pipex)
{
	int	file;

	if (pipex->is_first)
	{
		file = open(pipex->filein, O_RDONLY);
		if (file < 0 && !pipex->here_doc)
			error();
		if (pipex->here_doc)
			dup2(pipex->prev_fd, STDIN_FILENO);
		else if (file >= 0)
			dup2(file, STDIN_FILENO), close(file);
	}
	else
		dup2(pipex->prev_fd, STDIN_FILENO);
	if (!pipex->is_last)
		dup2(pipex->fd[1], STDOUT_FILENO);
	else
	{
		file = open(pipex->fileout, O_WRONLY | O_CREAT | (pipex->here_doc ? O_APPEND : O_TRUNC), 0644);
		if (file < 0)
			error();
		dup2(file, STDOUT_FILENO), close(file);
	}
	close(pipex->fd[0]), close(pipex->fd[1]), execute(pipex);
}

static void	handle_here_doc(t_pipex *pipex)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) < 0)
		error();
	while (1)
	{
		ft_putstr_fd("pipex heredoc> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line || ft_strncmp(line, pipex->argv[2], ft_strlen(pipex->argv[2])) == 0)
			break ;
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
	free(line), close(fd[1]), pipex->prev_fd = fd[0];
}

static void	fork_process(t_pipex *pipex, int i, int cmd_count)
{
	pid_t	pid;

	if (pipe(pipex->fd) < 0)
		error();
	pid = fork();
	if (pid < 0)
		error();
	if (pid == 0)
	{
		pipex->is_first = (i == (pipex->here_doc ? 2 : 1));
		pipex->is_last = (i == cmd_count - 1);
		pipex->argv = &pipex->argv[i + 1];
		child_process(pipex);
		exit(0);
	}
	close(pipex->prev_fd), pipex->prev_fd = pipex->fd[0], close(pipex->fd[1]);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;
	int		cmd_count;
	int		status;

	if (argc < 5)
		usage();
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.here_doc = (ft_strcmp(argv[1], "here_doc") == 0);
	pipex.filein = argv[1], pipex.fileout = argv[argc - 1], pipex.prev_fd = -1;
	cmd_count = argc - (pipex.here_doc ? 4 : 3);
	if (pipex.here_doc)
		handle_here_doc(&pipex);
	else
		pipex.prev_fd = open(pipex.filein, O_RDONLY);
	i = (pipex.here_doc ? 2 : 1) - 1;
	while (++i < cmd_count)
		fork_process(&pipex, i, cmd_count);
	close(pipex.prev_fd);
	while (wait(&status) > 0)
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return (WEXITSTATUS(status));
	return (0);
}
