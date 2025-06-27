/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_advanced2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:36:43 by jbias             #+#    #+#             */
/*   Updated: 2025/06/17 10:36:44 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_separator(char c, char quote)
{
	if (quote)
		return (0);
	if (c == ' ' || c == '\t' || c == '|')
		return (1);
	return (0);
}

t_cmd	*init_cmd_array(int cmd_count)
{
	t_cmd	*result;
	int		i;

	result = malloc(sizeof(t_cmd) * cmd_count);
	if (!result)
		return (NULL);
	i = 0;
	while (i < cmd_count)
	{
		result[i].args = NULL;
		result[i].redirects = NULL;
		result[i].redirect_count = 0;
		i++;
	}
	return (result);
}

int	is_redirect(char *str)
{
	return (ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, "<<") == 0 || ft_strcmp(str, ">>") == 0);
}

static int	count_quote_loop(char *input, int *i, char *quote)
{
	*quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != *quote)
		(*i)++;
	if (input[*i] == *quote)
		(*i)++;
	else
		return (1);
	return (0);
}

int	count_token_split(char *input)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (input[i] && input[i] != '|')
	{
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		if (!input[i] || input[i] == '|')
			break ;
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (count_quote_loop(input, &i, &quote) == 1)
				return (count);
		}
		else
			while (input[i] && !is_separator(input[i], quote))
				i++;
		count++;
	}
	return (count);
}
