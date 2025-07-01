/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:24:29 by jbias             #+#    #+#             */
/*   Updated: 2025/07/01 15:31:24 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	init_heredoc(t_data *data, t_redirect *redirect,
	int *fd, char **expanded_delim)
{
	redirect->is_heredoc_fd = 0;
	if (pipe(fd) < 0)
	{
		error(data);
		return (-1);
	}
	*expanded_delim = expand_variables(redirect->file, data);
	if (!*expanded_delim)
	{
		ft_putstr_fd(RED"minishell: malloc failed\n"RESET, 2);
		data->exit_status = 1;
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	g_signal_exit_status = 0;
	signal(SIGINT, handle_heredoc_signals);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

static int	process_heredoc_line(int fd_write, char *line, char *delim)
{
	char	*clean_line;
	int		len;

	if (!line)
		return (1);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
	{
		clean_line = ft_substr(line, 0, len - 1);
		if (!clean_line)
			return (free(line), 1);
	}
	else
	{
		clean_line = ft_strdup(line);
		if (!clean_line)
			return (free(line), 1);
	}
	if (ft_strcmp(clean_line, delim) == 0)
		return (free(line), free(clean_line), 1);
	write(fd_write, line, ft_strlen(line));
	free(line);
	free(clean_line);
	return (0);
}

static void	finish_heredoc(t_data *data, int *fd, char *expanded_delim,
			t_redirect *redirect)
{
	int	new_stdin;

	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
	free(expanded_delim);
	if (g_signal_exit_status == 130)
	{
		close(fd[0]);
		close(fd[1]);
		redirect->is_heredoc_fd = -1;
		data->exit_status = 130;
		if (fcntl(STDIN_FILENO, F_GETFD) == -1)
		{
			new_stdin = open("/dev/tty", O_RDONLY);
			if (new_stdin != -1)
				dup2(new_stdin, STDIN_FILENO);
			if (new_stdin > 2)
				close(new_stdin);
		}
	}
	else
	{
		close(fd[1]);
		redirect->is_heredoc_fd = fd[0];
	}
}

static char	*read_line_from_stdin(void)
{
	char	buffer[1000];
	int		i;
	int		bytes_read;
	char	c;

	i = -1;
	while (++i < 999)
	{
		if (g_signal_exit_status == 130)
			return (NULL);
		bytes_read = read(STDIN_FILENO, &c, 1);
		if (bytes_read <= 0)
		{
			if (g_signal_exit_status == 130)
				return (NULL);
			if (bytes_read == 0)
				return (NULL);
			return (NULL);
		}
		if (c == '\n')
			return (buffer[i] = c, buffer[i + 1] = '\0',
				ft_strdup(buffer));
		buffer[i] = c;
	}
	return (buffer[i] = '\0', ft_strdup(buffer));
}

void	handle_here_doc(t_data *data, t_redirect *redirect)
{
	int		fd[2];
	char	*line;
	char	*expanded_delim;

	if (init_heredoc(data, redirect, fd, &expanded_delim) == -1)
		return ;
	while (1)
	{
		if (g_signal_exit_status == 130)
		{
			data->exit_status = 130;
			break ;
		}
		ft_putstr_fd(GREEN"──(heredoc)──"RESET, STDERR_FILENO);
		line = read_line_from_stdin();
		if (!line)
		{
			heredoc_loop_norm(data, expanded_delim);
			break ;
		}
		if (process_heredoc_line(fd[1], line, expanded_delim))
			break ;
	}
	finish_heredoc(data, fd, expanded_delim, redirect);
	g_signal_exit_status = reset_signal_exit(g_signal_exit_status);
}

void	handle_here_doc_delayed(t_data *data, t_redirect *redirect)
{
	if (redirect->is_heredoc_fd > 0)
		return ;
	handle_here_doc(data, redirect);
}

int	preprocess_all_heredocs(t_data *data, t_pipex *pipex)
{
	int		i;
	int		j;
	t_cmd	*cmd;

	i = -1;
	while (++i < pipex->cmd_count)
	{
		cmd = &pipex->commands[i];
		j = -1;
		while (++j < cmd->redirect_count)
		{
			if (ft_strcmp(cmd->redirects[j].type, "<<") == 0)
			{
				handle_here_doc(data, &cmd->redirects[j]);
				if (cmd->redirects[j].is_heredoc_fd == -1)
					return (-1);
			}
		}
	}
	return (0);
}
