/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:53:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/18 13:32:50 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_quotes(char *str, int i, int *count)
{
	if (str[i] == '\'')
		i = single_quoted(str, i);
	else if (str[i] == '\"')
		i = double_quoted(str, i);
	if (i == -1)
		return (-1);
	if (i <= (int)ft_strlen(str) && (str[i] == ' '
			|| str[i] == '\t' || str[i] == '\0'))
		(*count)++;
	return (i);
}

static int	norm_count_tokens(char *str, int i, int count)
{
	if (str[i + 1] == ' ' || str[i + 1] == '\t'
		|| str[i + 1] == '\0')
		count++;
	return (count);
}

int	count_tokens(char *str)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		while (str[i] && str[i] != ' ' && str[i] != '\t')
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				i = handle_quotes(str, i, &count);
				if (i == -1)
					return (-1);
			}
			else
			{
				count = norm_count_tokens(str, i, count);
				i++;
			}
		}
	}
	return (count);
}

static int	extract_loop(char *input, int i)
{
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (input[i] == '\'')
				i = single_quoted(input, i);
			else if (input[i] == '\"')
				i = double_quoted(input, i);
			if (i == -1)
				return (ft_putstr_fd(RED"Error: Unmatched quotes\n"RESET, 2),
					-1);
		}
		else if (input[i] == ' ' || input[i] == '\t'
			|| input[i] == '|' || input[i] == '<' || input[i] == '>')
			break ;
		else
			i++;
	}
	return (i);
}

char	*extract_tokens(char *input, char *token, int *index)
{
	int		i;
	int		j;

	i = *index;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (!input[i])
		return (NULL);
	j = i;
	if (input[i] == '|')
		token = if_pipe(input, token, &j, &i);
	else if (input[i] == '<')
		token = if_redir_in(input, token, &j, &i);
	else if (input[i] == '>')
		token = if_redir_out(input, token, &j, &i);
	else
	{
		i = extract_loop(input, i);
		if (i == -1)
			return (NULL);
		token = ft_substr(input, j, i - j);
		printf(YELLOW"DEBUG: Extracted token: '%s'\n"RESET, token);
		*index = i;
	}
	return (token);
}
