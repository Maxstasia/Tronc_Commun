/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:52:17 by jbias             #+#    #+#             */
/*   Updated: 2025/06/13 13:52:19 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*if_pipe(char *input, char *token, int *i, int *index)
{
	int	j;

	j = *i;
	if (input[*i] == '|')
	{
		*i += 1;
		token = ft_substr(input, j, 1);
		if (!token)
			return (NULL);
		*index = *i;
		return (token);
	}
	return (NULL);
}

char	*if_redir_in(char *input, char *token, int *i, int *index)
{
	int	j;

	j = *i;
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			*i += 2;
			token = ft_substr(input, j, 2);
		}
		else
		{
			*i += 1;
			token = ft_substr(input, j, 1);
		}
		if (!token)
			return (NULL);
		*index = *i;
		return (token);
	}
	return (NULL);
}

char	*if_redir_out(char *input, char *token, int *i, int *index)
{
	int	j;

	j = *i;
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			*i += 2;
			token = ft_substr(input, j, 2);
		}
		else
		{
			*i += 1;
			token = ft_substr(input, j, 1);
		}
		if (!token)
			return (NULL);
		*index = *i;
		return (token);
	}
	return (NULL);
}
