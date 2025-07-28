/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:53:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/03 00:24:00 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	single_quoted(char *token, int i)
{
	int		j;

	j = i + 1;
	while (token[j] && token[j] != '\'')
		j++;
	if (token[j] == '\'')
	{
		i = j + 1;
		return (i);
	}
	else
		return (-1);
}

int	double_quoted(char *token, int i)
{
	int		j;

	j = i + 1;
	while (token[j] && token[j] != '\"')
		j++;
	if (token[j] == '\"')
	{
		return (j + 1);
	}
	else
		return (-1);
}

static int	valid_quotes(int i, char *token)
{
	if (token[i] == '\'')
	{
		i = single_quoted(token, i);
		if (i == -1)
			return (ft_putstr_fd(RED"Error: Unmatched single quotes\n"RESET, 2),
				-1);
	}
	else if (token[i] == '\"')
	{
		i = double_quoted(token, i);
		if (i == -1)
			return (ft_putstr_fd(RED"Error: Unmatched double quotes\n"RESET, 2),
				-1);
	}
	return (i);
}

static char	*parsed_token_loop_norm(char *token, int i, int token_len)
{
	char	*parsed_token;

	while (i < token_len && token[i] != '\0')
	{
		if (token[i] == '\'' || token[i] == '\"')
		{
			i = valid_quotes(i, token);
			if (i == -1)
				return (NULL);
		}
		else if (token[i] == ' ' || token[i] == '\t')
			break ;
		else
			i++;
	}
	parsed_token = ft_substr(token, 0, i);
	if (!parsed_token)
		return (NULL);
	return (parsed_token);
}

char	*parsed_token(char *token)
{
	char	*parsed_token;
	int		i;
	int		token_len;

	if (!token)
		return (NULL);
	i = 0;
	token_len = ft_strlen(token);
	while (i < token_len && (token[i] == ' ' || token[i] == '\t'))
		i++;
	parsed_token = parsed_token_loop_norm(token, i, token_len);
	if (!parsed_token)
		return (free(token), NULL);
	return (free(token), parsed_token);
}
