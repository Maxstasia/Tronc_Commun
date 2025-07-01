/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:22:29 by jbias             #+#    #+#             */
/*   Updated: 2025/07/01 16:55:21 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	skip_redir(const char *input, int i)
{
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			i += 2;
		else
			i += 1;
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			i += 2;
		else
			i += 1;
	}
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	if (!input[i] || input[i] == '|' || input[i] == '<' || input[i] == '>')
		return (-1);
	return (i);
}

static char	set_file_quote(char *input, int *i, char file_quote)
{
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			file_quote = input[*i];
			(*i)++;
			while (input[*i] && input[*i] != file_quote)
				(*i)++;
			if (input[*i] == file_quote)
				(*i)++;
		}
		else
			(*i)++;
	}
	return (file_quote);
}

static int	validate_redirection_syntax_norm(const char *input)
{
	int		i;
	char	quote;
	char	file_quote;

	i = 0;
	quote = 0;
	file_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			set_quote((char *)input, i, quote);
		else if (!quote)
		{
			if (input[i] == '<' || input[i] == '>')
			{
				i = skip_redir(input, i);
				if (i == -1)
					return (-1);
				file_quote = set_file_quote((char *)input, &i, file_quote);
				continue ;
			}
		}
		i++;
	}
	return (0);
}

int	validate_redirection_syntax(const char *input)
{
	if (validate_heredoc_pipe_syntax(input) == -1)
		return (-1);
	if (validate_redirection_syntax_norm(input) == -1)
		return (-1);
	return (0);
}
