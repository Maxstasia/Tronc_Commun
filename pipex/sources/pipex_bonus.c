/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:39:35 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/03 17:22:00 by mstasiak         ###   ########.fr       */
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
		error(pipex);
	delim = ft_strjoin(pipex->argv[2], "\n");
	if (!delim)
		error(pipex);
	infinity_loop(fd, delim);
	close(fd[1]);
	pipex->prev_fd = fd[0];
}

static int	setup_first_process(t_pipex *pipex)
{
	int	file;

	file = open(pipex->filein, O_RDONLY);
	if (file < 0 && !pipex->here_doc)
	{
		file = open("/dev/null", O_RDONLY, 0644);
		if (file < 0 && !pipex->here_doc)
			return (close(pipex->fd[0]), close(pipex->fd[1]), error(pipex), 1);
		perror(RED"Error"RESET);
	}
	if (pipex->here_doc)
	{
		if (pipex->prev_fd == -1)
			return (close(pipex->fd[0]), close(pipex->fd[1]), error(pipex), 1);
		dup2(pipex->prev_fd, STDIN_FILENO);
		close(pipex->prev_fd);
	}
	else if (file >= 0)
	{
		dup2(file, STDIN_FILENO);
		close(file);
	}
	return (0);
}

static void	setup_last_process(t_pipex *pipex)
{
	int	file;

	if (pipex->here_doc)
		file = open(pipex->fileout, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		file = open(pipex->fileout, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file < 0)
	{
		if (pipex->prev_fd != -1)
			close(pipex->prev_fd);
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		error(pipex);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
}

void	child_process(t_pipex *pipex)
{
	if (pipex->is_first)
		setup_first_process(pipex);
	else
	{
		dup2(pipex->prev_fd, STDIN_FILENO);
		if (pipex->prev_fd != -1)
			close(pipex->prev_fd);
	}
	if (pipex->is_last)
		setup_last_process(pipex);
	else
		dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	execute(pipex);
}
