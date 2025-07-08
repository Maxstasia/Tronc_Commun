/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:00:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/01 17:31:55 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	skip_heredoc_delimiter(const char *input, int *i)
{
	*i += 2;
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		(*i)++;
	while (input[*i] && input[*i] != ' '
		&& input[*i] != '\t' && input[*i] != '|')
		(*i)++;
	(*i)--;
	return (0);
}

static int	handle_heredoc_and_pipe(const char *input, int *i, char quote,
	int *has_command_after_heredoc)
{
	if (!quote && input[*i] == '<' && input[(*i) + 1] == '<')
	{
		*has_command_after_heredoc = 0;
		skip_heredoc_delimiter(input, i);
		return (1);
	}
	else if (!quote && input[*i] == '|')
		*has_command_after_heredoc = 0;
	return (0);
}

static void	handle_command_token(char quote, char c, int has_heredoc,
	int *has_command_after_heredoc)
{
	if (!quote && c != ' ' && c != '\t' && c != '<' && c != '>')
	{
		if (has_heredoc)
			*has_command_after_heredoc = 1;
	}
}

static int	syntax_heredoc_norm(int result, int *i)
{
	if (result == 1)
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	validate_heredoc_pipe_syntax(const char *input)
{
	int		i;
	char	quote;
	int		has_heredoc;
	int		has_command_after_heredoc;

	i = 0;
	quote = 0;
	has_command_after_heredoc = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			quote = set_quote((char *)input, i, quote);
		has_heredoc = handle_heredoc_and_pipe(input, &i, quote,
				&has_command_after_heredoc);
		if (syntax_heredoc_norm(has_heredoc, &i) == 1)
			continue ;
		else if (has_heredoc == -1)
			return (-1);
		handle_command_token(quote, input[i], has_heredoc,
			&has_command_after_heredoc);
		i++;
	}
	return (0);
}
