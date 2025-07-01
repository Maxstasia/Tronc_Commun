/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:53:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/28 14:00:08 by mstasiak         ###   ########.fr       */
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
		i = j + 1;
		if (token[i] == '\0')
			return (i - 1);
		return (i);
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

char	*parsed_token(char *token)
{
	char	*parsed_token;
	int		i;

	i = 0;
	while (token[i] && (token[i] == ' ' || token[i] == '\t'))
		i++;
	while (token[i] != '\0')
	{
		i = valid_quotes(i, token);
		if (i == -1)
			return (NULL);
		else if (token[i] && (token[i] == ' ' || token[i] == '\t'))
			break ;
		else
			i++;
	}
	parsed_token = ft_substr(token, 0, i);
	if (!parsed_token)
		return (NULL);
	return (free(token), parsed_token);
}
