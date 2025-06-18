/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:22:22 by jbias             #+#    #+#             */
/*   Updated: 2025/06/16 13:22:24 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	pipe_loop_part(int *last_was_pipe, int *i, const char *input,
			int *found_command)
{
	int	j;

	if (*last_was_pipe)
		return (-1);
	*last_was_pipe = 1;
	*found_command = 0;
	j = *i + 1;
	while (input[j] && (input[j] == ' ' || input[j] == '\t'))
		j++;
	if (!input[j] || input[j] == '|')
		return (-1);
	return (0);
}

static int	init_pipe_validation(const char *input, int *i)
{
	*i = 0;
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		(*i)++;
	if (input[*i] == '|')
		return (-1);
	if (validate_redirection_syntax(input) != 0)
		return (-1);
	return (0);
}

static void	pipe_loop_part2(int *last_was_pipe, int *found_command)
{
	*last_was_pipe = 0;
	*found_command = 1;
}

static int	check_last(int last_was_pipe)
{
	if (last_was_pipe == 1)
		return (-1);
	return (0);
}

int	validate_pipe_syntax(char *input)
{
	int		i;
	char	quote;
	int		last_was_pipe;
	int		found_command;

	quote = 0;
	last_was_pipe = 0;
	found_command = 0;
	if (init_pipe_validation(input, &i) != 0)
		return (-1);
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			quote = set_quote(input, i, quote);
		else if (input[i] == '|' && !quote)
		{
			if (pipe_loop_part(&last_was_pipe, &i, input, &found_command) == -1)
				return (-1);
		}
		else if (input[i] != ' ' && input[i] != '\t')
			pipe_loop_part2(&last_was_pipe, &found_command);
		i++;
	}
	return (check_last(last_was_pipe));
}
