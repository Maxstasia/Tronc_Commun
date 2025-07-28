/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:48:16 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/03 17:21:09 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	setup_first_process(t_pipex *pipex)
{
	int	file;

	file = open(pipex->filein, O_RDONLY);
	if (file < 0)
	{
		file = open("/dev/null", O_RDONLY, 0644);
		if (file < 0)
		{
			close(pipex->fd[0]);
			close(pipex->fd[1]);
			error(pipex);
		}
		perror(RED"Error"RESET);
	}
	if (file >= 0)
	{
		dup2(file, STDIN_FILENO);
		close(file);
	}
}

static void	setup_last_process(t_pipex *pipex)
{
	int	file;

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
