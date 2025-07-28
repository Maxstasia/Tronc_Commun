/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:47:05 by jbias             #+#    #+#             */
/*   Updated: 2025/07/24 14:41:18 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	validate_syntax(char *expanded_line)
{
	if (validate_redirection_syntax(expanded_line) != 0)
	{
		if (ft_strstr(expanded_line, ">>")
			&& !has_file_after_redirection(expanded_line, ">>"))
			ft_putstr_fd(RED"minishell: syntax error\n"RESET, 2);
		else if (ft_strstr(expanded_line, ">")
			&& !has_file_after_redirection(expanded_line, ">"))
			ft_putstr_fd(RED"minishell: syntax error\n"RESET, 2);
		else if (ft_strstr(expanded_line, "<<")
			&& !has_file_after_redirection(expanded_line, "<<"))
			ft_putstr_fd(RED"minishell: syntax error\n"RESET, 2);
		else if (ft_strstr(expanded_line, "<")
			&& !has_file_after_redirection(expanded_line, "<"))
			ft_putstr_fd(RED"minishell: syntax error\n"RESET, 2);
		else
			ft_putstr_fd(RED"minishell: syntax error\n"RESET, 2);
		return (2);
	}
	if (validate_pipe_syntax(expanded_line) != 0)
		return (ft_putstr_fd(RED"minishell: syntax error « | »\n"RESET, 2), 2);
	return (0);
}

static char	*add_space_after_redir_norm(char *line, int i,
			int redir_len, char *new_line)
{
	int		j;
	int		k;
	int		need_space_before;

	need_space_before = 0;
	if (i > 0 && line[i - 1] != ' ' && line[i - 1] != '\t')
		need_space_before = 1;
	j = 0;
	k = 0;
	while (k < i)
		new_line[j++] = line[k++];
	if (need_space_before)
		new_line[j++] = ' ';
	k = 0;
	while (k < redir_len)
		new_line[j++] = line[i + k++];
	new_line[j++] = ' ';
	while (line[i + redir_len])
		new_line[j++] = line[i + redir_len++];
	new_line[j] = '\0';
	return (new_line);
}

char	*add_space_after_redir(char *line, int i, int redir_len)
{
	char	*new_line;
	int		new_len;
	int		need_space_before;

	need_space_before = 0;
	if (i > 0 && line[i - 1] != ' ' && line[i - 1] != '\t')
		need_space_before = 1;
	new_len = ft_strlen(line) + 1 + need_space_before;
	new_line = malloc(new_len + 1);
	if (!new_line)
		return (NULL);
	new_line = add_space_after_redir_norm(line, i, redir_len, new_line);
	if (!new_line)
		return (free(new_line), NULL);
	return (new_line);
}

static char	*preprocess_redirection_only(char *line)
{
	char	*current;
	int		i;

	current = ft_strdup(line);
	if (!current)
		return (NULL);
	i = 0;
	while (current[i])
	{
		if (current[i] == '<' || current[i] == '>')
		{
			current = redir_loop(current, &i);
			if (!current)
				return (NULL);
		}
		else
			i++;
	}
	return (current);
}

int	process_input_line(t_data *data, char *line,
		t_token_list *token_list)
{
	t_pipex	pipex;
	int		syntax_error;

	init_pipex(&pipex);
	data->preprocessed_line = preprocess_redirection_only(line);
	if (!data->preprocessed_line)
		return (ft_putstr_fd(RED"minishell: malloc failed\n"RESET, 2),
			data->exit_status = 1, free_pipex(&pipex, 0), -1);
	syntax_error = validate_syntax(data->preprocessed_line);
	if (syntax_error != 0)
		return (free_pipex(&pipex, 0), data->exit_status = syntax_error,
			free(data->preprocessed_line), data->preprocessed_line = NULL, -1);
	data->expanded = expand_variables(data->preprocessed_line, data);
	if (!data->expanded)
		return (ft_putstr_fd(RED"minishell: malloc failed\n"RESET, 2),
			data->exit_status = 1, free_pipex(&pipex, 0),
			free(data->preprocessed_line), data->preprocessed_line = NULL, -1);
	if (parse_input(data->expanded, token_list) != 0)
		return (free(data->expanded), data->expanded = NULL,
			free(data->preprocessed_line), data->preprocessed_line = NULL,
			free_pipex(&pipex, 0), data->exit_status = 2, -1);
	return (parse_line(data->expanded, &pipex),
		handle_command_execution(data, token_list, &pipex, data->expanded),
		free_pipex(&pipex, 0), free(data->expanded), data->expanded = NULL,
		free(data->preprocessed_line), data->preprocessed_line = NULL, 0);
}
