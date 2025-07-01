/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:01:00 by jbias             #+#    #+#             */
/*   Updated: 2025/06/17 11:01:01 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_quotes_split(char *str)
{
	char	*quotes_free;

	if (!str)
		return (NULL);
	quotes_free = malloc(ft_strlen(str) + 1);
	if (!quotes_free)
		return (NULL);
	quotes_free = process_quotes(str, quotes_free);
	free(str);
	return (quotes_free);
}

int	handle_escaped_quote(char *str, char *quotes_free, t_quote *data)
{
	if (data->in_quotes == 0 && str[data->i] == '\\'
		&& (str[data->i + 1] == '\'' || str[data->i + 1] == '\"'))
	{
		quotes_free[data->j++] = str[data->i + 1];
		data->i += 2;
		return (1);
	}
	return (0);
}
