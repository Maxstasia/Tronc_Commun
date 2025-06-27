/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:47:05 by jbias             #+#    #+#             */
/*   Updated: 2025/06/27 15:49:27 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static char	*redirection_control(char *line, char *trimmed)
{
	char	*result;

	if (trimmed[0] == '>' && trimmed[1] == '>'
		&& trimmed[2] && trimmed[2] != ' ' && trimmed[2] != '\t')
		result = cas_1(line, trimmed);
	else if (trimmed[0] == '<' && trimmed[1] == '<'
		&& trimmed[2] && trimmed[2] != ' ' && trimmed[2] != '\t')
		result = cas_2(line, trimmed);
	else if (trimmed[0] == '>' && trimmed[1] && trimmed[1] != '>'
		&& trimmed[1] != ' ' && trimmed[1] != '\t')
		result = cas_3(line, trimmed);
	else if (trimmed[0] == '<' && trimmed[1] && trimmed[1] != '<'
		&& trimmed[1] != ' ' && trimmed[1] != '\t')
		result = cas_4(line, trimmed);
	else
		result = cas_5(line);
	if (!result)
		return (NULL);
	return (result);
}

static char	*preprocess_redirection_only(char *line)
{
	char	*trimmed;
	char	*result;

	trimmed = line;
	while (*trimmed && (*trimmed == ' ' || *trimmed == '\t'))
		trimmed ++;
	if (*trimmed == '>' || *trimmed == '<')
	{
		result = redirection_control(line, trimmed);
		if (!result)
			return (NULL);
		return (result);
	}
	return (ft_strdup(line));
}

int	process_input_line(t_data *data, char *line,
		t_token_list *token_list)
{
	char	*preprocessed_line;
	char	*expanded_line;
	t_pipex	pipex;
	int		syntax_error;

	init_pipex(&pipex);
	preprocessed_line = preprocess_redirection_only(line);
	if (!preprocessed_line)
		return (ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2),
			data->exit_status = 1, free_pipex(&pipex, 0), -1);
	syntax_error = validate_syntax(preprocessed_line);
	if (syntax_error != 0)
		return (free_pipex(&pipex, 0), data->exit_status = syntax_error,
			free(preprocessed_line), -1);
	expanded_line = expand_variables(preprocessed_line, data);
	if (!expanded_line)
		return (ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2),
			data->exit_status = 1, free_pipex(&pipex, 0),
			free(preprocessed_line), -1);
	if (parse_input(expanded_line, token_list) != 0)
		return (free(expanded_line), free(preprocessed_line), -1);
	return (parse_line(expanded_line, token_list, &pipex),
		handle_command_execution(data, token_list, &pipex, expanded_line),
		free_pipex(&pipex, 0), free(expanded_line), free(preprocessed_line), 0);
}
