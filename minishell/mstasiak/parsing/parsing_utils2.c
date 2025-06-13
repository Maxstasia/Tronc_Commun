/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:28:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/13 14:32:31 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	validate_redirection_syntax(const char *input)
{
	int		i;
	char	file_quote;
	char	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (!quote)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
		else if (!quote)
		{
			if (input[i] == '<' || input[i] == '>')
			{
				if (input[i] == '<')
				{
					if (input[i + 1] == '<')
						i += 2;
					else
						i++;
				}
				else if (input[i] == '>')
				{
					if (input[i + 1] == '>')
						i += 2;
					else
						i++;
				}
				while (input[i] && (input[i] == ' ' || input[i] == '\t'))
					i++;
				if (!input[i] || input[i] == '|'
					|| input[i] == '<' || input[i] == '>')
					return (-1);
				while (input[i] && input[i] != ' ' && input[i] != '\t'
					&& input[i] != '|' && input[i] != '<' && input[i] != '>')
				{
					if (input[i] == '\'' || input[i] == '\"')
					{
						file_quote = input[i];
						i++;
						while (input[i] && input[i] != file_quote)
							i++;
						if (input[i] == file_quote)
							i++;
					}
					else
						i++;
				}
				continue ;
			}
		}
		i++;
	}
	return (0);
}

int	validate_pipe_syntax(const char *input)
{
	int		i;
	int		j;
	char	quote;
	int		last_was_pipe;

	i = 0;
	quote = 0;
	last_was_pipe = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	if (input[i] == '|')
		return (-1);
	if (validate_redirection_syntax(input) != 0)
		return (-1);
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (!quote)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
		else if (input[i] == '|' && !quote)
		{
			if (last_was_pipe)
				return (-1);
			last_was_pipe = 1;
			j = i + 1;
			while (input[j] && (input[j] == ' ' || input[j] == '\t'))
				j++;
			if (!input[j] || input[j] == '|')
				return (-1);
		}
		else if (input[i] != ' ' && input[i] != '\t')
			last_was_pipe = 0;
		i++;
	}
	if (last_was_pipe)
		return (-1);
	return (0);
}
