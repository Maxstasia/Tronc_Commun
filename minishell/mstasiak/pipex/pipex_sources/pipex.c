/* ************************************************************************** /
/                                                                            /
/                                                        :::      ::::::::   /
/   pipex_bonus.c                                      :+:      :+:    :+:   /
/                                                    +:+ +:+         +:+     /
/   By: mstasiak mstasiak@student.42.fr          +#+  +:+       +#+        /
/                                                Begins: pipex_bonus.c       /
/   Created: 2025/03/25 14:39:35 by mstasiak          #+#    #+#             /
/   Updated: 2025/04/17 10:00:00 by mstasiak         ###   ########.fr       /
/                                                                            /
/ ************************************************************************** */

#include "../../include/minishell.h"

void handle_here_doc(t_data *data, t_redirect *redirect)
{
	int		fd[2];
	char	*line;
	char	*expanded_delim;

	if (pipe(fd) < 0)
		error(data);
	expanded_delim = expand_variables(redirect->file, data);
	if (!expanded_delim)
	{
		ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
		data->exit_status = 1;
		close(fd[0]);
		close(fd[1]);
		return;
	}
	line = NULL;
	while (1)
	{
		ft_putstr_fd(GREEN" heredoc> "RESET, STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break;
		if (ft_strcmp(line, expanded_delim) == 0)
		{
			free(line);
			break;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	free(expanded_delim);
	close(fd[1]);
	redirect->file = ft_itoa(fd[0]); // Stocker le FD comme fichier temporaire
}

void apply_redirects(t_data *data, t_cmd *cmd)
{
	int i = -1;

	while (++i, i < cmd->redirect_count)
	{
		printf(YELLOW"DEBUG : redirect.file = %s\n"RESET, cmd->redirects[i].file); // DEBUG
		if (ft_strcmp(cmd->redirects[i].type, "<") == 0)
		{
			int fd = open(cmd->redirects[i].file, O_RDONLY);
			if (fd < 0)
				error(data);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (ft_strcmp(cmd->redirects[i].type, ">") == 0)
		{
			int fd = open(cmd->redirects[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				error(data);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (ft_strcmp(cmd->redirects[i].type, ">>") == 0)
		{
			int fd = open(cmd->redirects[i].file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				error(data);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (ft_strcmp(cmd->redirects[i].type, "<<") == 0)
		{
			handle_here_doc(data, &cmd->redirects[i]);
			int fd = ft_atoi(cmd->redirects[i].file);
			dup2(fd, STDIN_FILENO);
			close(fd);
			free(cmd->redirects[i].file);
			cmd->redirects[i].file = NULL;
		}
	}
}

static void setup_first_process(t_data *data, t_pipex *pipex, int cmd_index)
{
	if (pipex->commands[cmd_index].redirect_count > 0)
		apply_redirects(data, &pipex->commands[cmd_index]);
	else
	{
		if (pipex->prev_fd != -1)
		{
			dup2(pipex->prev_fd, STDIN_FILENO);
			close(pipex->prev_fd);
		}
	}
}

static void setup_last_process(t_data *data, t_pipex *pipex, int cmd_index)
{
	if (pipex->commands[cmd_index].redirect_count > 0)
		apply_redirects(data, &pipex->commands[cmd_index]);
	else
		dup2(pipex->fd[1], STDOUT_FILENO);
}

void child_process(t_data *data, t_pipex *pipex, int cmd_index)
{
	if (pipex->is_first)
		setup_first_process(data, pipex, cmd_index);
	else
	{
		dup2(pipex->prev_fd, STDIN_FILENO);
		if (pipex->prev_fd != -1)
			close(pipex->prev_fd);
	}
	if (!pipex->is_last)
		setup_last_process(data, pipex, cmd_index);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	execute(data, &pipex->commands[cmd_index]);
}
