/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:22:29 by jbias             #+#    #+#             */
/*   Updated: 2025/06/27 12:25:13 by mstasiak         ###   ########.fr       */
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

char	set_quote(char *input, int i, char quote)
{
	if (input[i] == '\'' || input[i] == '\"')
	{
		if (!quote)
			quote = input[i];
		else if (quote == input[i])
			quote = 0;
	}
	return (quote);
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

int	validate_redirection_syntax(const char *input)
{
	int		i;
	char	quote;
	char	file_quote;

	if (validate_heredoc_pipe_syntax(input) == -1)
		return (-1);
	i = -1;
	quote = 0;
	file_quote = 0;
	while (input[++i])
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
	}
	return (0);
}

int	has_file_after_redirection(const char *input, const char *redir)
{
	char	*pos;

	pos = ft_strstr(input, redir);
	if (!pos)
		return (1);
	pos += ft_strlen(redir);
	while (*pos && (*pos == ' ' || *pos == '\t'))
		pos++;
	if (!*pos || *pos == '|' || *pos == '<' || *pos == '>')
		return (0);
	return (1);
}
