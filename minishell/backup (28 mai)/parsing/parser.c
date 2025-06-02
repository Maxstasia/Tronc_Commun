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

int		single_quoted(char *token, int i)
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
	{
		ft_putstr_fd(RED"Error: Unmatched quotes\n"RESET, 2);
		return (-1);
	}
}

int		double_quoted(char *token, int i)
{
	int		j;

	j = i + 1;
	while (token[j] && token[j] != '\"')
		j++;
	if (token[j] == '\"')
	{
		i = j + 1;
		return (i);
	}
	else
	{
		ft_putstr_fd(RED"Error: Unmatched quotes\n"RESET, 2);
		return (-1);
	}
}
char	*parsed_token(char *token)
{
	char	*parsed_token;
	int		i;

	i = 0;
	while (token[i] && (token[i] == ' ' && token[i] == '\t'))
		i++;
	while (token[i] && (token[i] != ' ' && token[i] != '\t'))
	{
		if (token[i] == '\'')
		{
			i = single_quoted(token, i);
			if (i == -1)
				return (NULL);
		}
		else if (token[i] == '\"')
		{
			i = double_quoted(token, i);
			if (i == -1)
				return (NULL);
		}
		else
			i++;
	}
	parsed_token = ft_substr(token, 0, i);
	if (!parsed_token)
		return (NULL);
	return (free(token), parsed_token);
}