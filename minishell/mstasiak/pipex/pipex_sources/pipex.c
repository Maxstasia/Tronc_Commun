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
	char	*clean_line;
	int		len;
	char	*fd_str;

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
	// Configurer le signal SIGINT pour le heredoc
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		ft_putstr_fd(GREEN"──(heredoc)── "RESET, STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		// Ctrl+D (EOF) - terminer proprement
		if (!line)
			break;
		// Nettoyer la ligne (enlever le \n final)
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
		{
			clean_line = ft_substr(line, 0, len - 1);
			if (!clean_line)
			{
				free(line);
				break;
			}
		}
		else
		{
			clean_line = ft_strdup(line);
			if (!clean_line)
			{
				free(line);
				break;
			}
		}
		// Vérifier si c'est le délimiteur
		if (ft_strcmp(clean_line, expanded_delim) == 0)
		{
			free(line);
			free(clean_line);
			break;
		}
		// Écrire la ligne dans le pipe (avec le \n original)
		write(fd[1], line, ft_strlen(line));
		free(line);
		free(clean_line);
	}
	// Restaurer le signal SIGINT
	signal(SIGINT, handle_signals);
	free(expanded_delim);
	close(fd[1]);
	// NE PAS libérer l'ancien pointeur - il sera géré par free_pipex
	// Stocker le fd dans une chaîne temporaire
	fd_str = ft_itoa(fd[0]);
	if (fd_str)
	{
		// Remplacer le contenu au lieu de remplacer le pointeur
		free(redirect->file);
		redirect->file = fd_str;
	}
	else
	{
		// En cas d'échec, fermer le fd et garder l'ancien pointeur
		close(fd[0]);
	}
}

void apply_redirects(t_data *data, t_cmd *cmd)
{
	int i;
	int fd;

	i = -1;
	while (++i, i < cmd->redirect_count)
	{
		printf(YELLOW"DEBUG : redirect.file = %s\n"RESET, cmd->redirects[i].file);
		if (ft_strcmp(cmd->redirects[i].type, "<") == 0)
		{
			fd = open(cmd->redirects[i].file, O_RDONLY);
			if (fd < 0)
				error(data);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (ft_strcmp(cmd->redirects[i].type, ">") == 0)
		{
			fd = open(cmd->redirects[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				error(data);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (ft_strcmp(cmd->redirects[i].type, ">>") == 0)
		{
			fd = open(cmd->redirects[i].file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				error(data);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (ft_strcmp(cmd->redirects[i].type, "<<") == 0)
		{
			handle_here_doc(data, &cmd->redirects[i]);
			if (cmd->redirects[i].file)  // Vérifier que handle_here_doc a réussi
			{
				fd = ft_atoi(cmd->redirects[i].file);
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
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
