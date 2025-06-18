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

static char	*get_clean_line(char *line)
{
	char	*clean_line;
	int		len;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
	{
		clean_line = ft_substr(line, 0, len - 1);
		if (!clean_line)
			return (NULL);
	}
	else
	{
		clean_line = ft_strdup(line);
		if (!clean_line)
			return (NULL);
	}
	return (clean_line);
}

static int	process_heredoc_line(int fd_write, char *line,
	char *clean_line, char *delim)
{
	if (ft_strcmp(clean_line, delim) == 0)
	{
		free(line);
		free(clean_line);
		return (1);
	}
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

void	handle_here_doc(t_data *data, t_redirect *redirect)
{
	int		fd[2];
	char	*line;
	char	*expanded_delim;
	char	*clean_line;

	if (init_heredoc(data, redirect, fd, &expanded_delim) == -1)
		return ;
	while (1)
	{
		ft_putstr_fd(GREEN"──(heredoc)── "RESET, STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		clean_line = get_clean_line(line);
		if (!clean_line)
		{
			free(line);
			break ;
		}
		if (process_heredoc_line(fd[1], line, clean_line, expanded_delim))
			break ;
	}
	finish_heredoc(fd, expanded_delim, redirect);
}
