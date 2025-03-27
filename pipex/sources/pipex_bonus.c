/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:39:35 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/27 17:56:15 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	infinity_loop(int fd[2], char *delim)
{
	char	*line;

	line = NULL;
	while (1)
	{
		ft_putstr_fd(GREEN"──(pipe heredoc)── "RESET, STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			free(delim);
			break ;
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			free(delim);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
}

void	handle_here_doc(t_pipex *pipex)
{
	int		fd[2];
	char	*delim;

	if (pipe(fd) < 0)
		error();
	delim = ft_strjoin(pipex->argv[2], "\n");
	if (!delim)
		error();
	infinity_loop(fd, delim);
	close(fd[1]);
	pipex->prev_fd = fd[0];
}

void	setup_first_process(t_pipex *pipex)
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
		dup2(pipex->prev_fd, STDIN_FILENO);
	}
	else if (file >= 0)
	{
		dup2(file, STDIN_FILENO);
		close(file);
	}
}

int	child_process(t_pipex *pipex)
{
	int	file;

	if (pipex->is_first)
		setup_first_process(pipex);
	else
		dup2(pipex->prev_fd, STDIN_FILENO);
	if (pipex->is_last)
	{
		file = open(pipex->fileout, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file < 0)
			return (error(), 1);
		dup2(file, STDOUT_FILENO);
		close(file);
	}
	else
		dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	execute(pipex);
	return (0);
}

pid_t	fork_process(t_pipex *pipex, int i, t_temp *tmp)
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
		return (child_process(pipex), exit(0), 0);
	}
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	pipex->prev_fd = pipex->fd[0];
	return (close(pipex->fd[1]), pid);
}
