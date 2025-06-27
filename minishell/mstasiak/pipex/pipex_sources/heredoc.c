/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:24:29 by jbias             #+#    #+#             */
/*   Updated: 2025/06/16 17:24:30 by jbias            ###   ########.fr       */
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
		ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
		data->exit_status = 1;
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	signal(SIGINT, SIG_DFL);
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

static void	finish_heredoc(int *fd, char *expanded_delim, t_redirect *redirect)
{
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	free(expanded_delim);
	close(fd[1]);
	redirect->is_heredoc_fd = fd[0];
}

static char	*read_line_from_stdin(void)
{
	char	buffer[1000];
	int		i;
	int		bytes_read;
	char	c;

	i = 0;
	while (i < 999)
	{
		bytes_read = read(STDIN_FILENO, &c, 1);
		if (bytes_read <= 0)
			return (NULL);
		if (c == '\n')
		{
			buffer[i] = c;
			buffer[i + 1] = '\0';
			return (ft_strdup(buffer));
		}
		buffer[i] = c;
		i++;
	}
	buffer[i] = '\0';
	return (ft_strdup(buffer));
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
		ft_putstr_fd(GREEN"──(heredoc)── "RESET, STDOUT_FILENO);
		line = read_line_from_stdin();
		if (!line)
		{
			ft_putstr_fd("bash: warning: heredoc delim by EOF (wanted `", 2);
			ft_putstr_fd(expanded_delim, 2);
			ft_putstr_fd("')\n", 2);
			break ;
		}
		if (process_heredoc_line(fd[1], line, expanded_delim))
			break ;
	}
	finish_heredoc(fd, expanded_delim, redirect);
}
