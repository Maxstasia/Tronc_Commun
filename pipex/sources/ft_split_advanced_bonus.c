/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_advanced.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:26:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/11 13:37:55 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	is_separator(char c, char quote)
{
	if (quote)
		return (0);
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

static char	*get_next_arg(const char *s, int *i)
{
	char	*arg;
	int		k;
	char	quote;

	arg = malloc(sizeof(char) * 256);
	if (!arg)
		return (NULL);
	quote = 0;
	k = 0;
	while (s[*i] && (!is_separator(s[*i], quote) || quote))
	{
		if ((s[*i] == '\'' || s[*i] == '\"') && (!quote || quote == s[*i]))
		{
			if (quote == 0)
				quote = s[*i];
			else
				quote = 0;
		}
		else
			arg[k++] = s[*i];
		(*i)++;
	}
	arg[k] = '\0';
	return (arg);
}

char	**ft_split_advanced(const char *s)
{
	char	**result;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	result = malloc(sizeof(char *) * 256);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && is_separator(s[i], 0))
			i++;
		if (!s[i])
			break ;
		result[j] = get_next_arg(s, &i);
		if (!result[j])
			return (NULL);
		j++;
	}
	result[j] = NULL;
	return (result);
}
