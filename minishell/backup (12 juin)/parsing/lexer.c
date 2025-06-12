/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:53:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/11 16:21:58 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		count_tokens(char *str)
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
				if (str[i] == '\'')
					i = single_quoted(str, i);
				else if (str[i] == '\"')
					i = double_quoted(str, i);
				if (i == -1)
					return (-1);
				if (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\0')
					count++;
			}
			else
			{
				if (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\0')
					count++;
			}
			i++;
		}
	}
	printf(YELLOW"DEBUG: Total tokens counted: %d\n"RESET, count);
	return (count);
}

t_token_type	get_token_type(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(token, "<") == 0)
		return (REDIR_IN);
	else if (ft_strcmp(token, ">") == 0)
		return (REDIR_OUT);
	else if (ft_strcmp(token, "<<") == 0)
		return (REDIR_HEREDOC);
	else if (ft_strcmp(token, ">>") == 0)
		return (REDIR_APPEND);
	else
		return (TXT);
}

char 	*extract_tokens(char *input, char *token, int *index)
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
	{
		i++;
		token = ft_substr(input, j, 1);
		*index = i;
		return (token);
	}
	else if (input[i] == '<')
	{
		if (input[i + 1] == '<')
		{
			i += 2;
			token = ft_substr(input, j, 2);
		}
		else
		{
			i++;
			token = ft_substr(input, j, 1);
		}
		*index = i;
		return (token);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
		{
			i += 2;
			token = ft_substr(input, j, 2);
		}
		else
		{
			i++;
			token = ft_substr(input, j, 1);
		}
		*index = i;
		return (token);
	}
	else
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
					return (ft_putstr_fd(RED"Error: Unmatched quotes\n"RESET, 2), NULL);
			}
			else if (input[i] == ' ' || input[i] == '\t' ||
				input[i] == '|' || input[i] == '<' || input[i] == '>')
				break ;
			else
				i++;
		}
		token = ft_substr(input, j, i - j);
		printf(YELLOW"DEBUG: Extracted token: '%s'\n"RESET, token);
		if (!token)
			return (NULL);
		*index = i;
		return (token);
	}
	return (NULL);
}
