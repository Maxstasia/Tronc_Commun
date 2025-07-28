/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:00:53 by jbias             #+#    #+#             */
/*   Updated: 2025/06/17 11:00:55 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_escaped_in_quotes(char *str,
		char *quotes_free, t_quote *data)
{
	if (str[data->i] == '\\' && str[data->i + 1] == data->quote
		&& data->in_quotes == 1)
	{
		quotes_free[data->j++] = str[data->i + 1];
		data->i += 2;
		return (1);
	}
	return (0);
}

static int	handle_quote_start(char *str, t_quote *data)
{
	if (data->in_quotes == 0 && (str[data->i] == '\'' || str[data->i] == '\"'))
	{
		data->quote = str[data->i++];
		data->in_quotes = 1;
		return (1);
	}
	return (0);
}

static int	handle_quote_end(char *str, t_quote *data)
{
	if (data->in_quotes == 1 && str[data->i] == data->quote)
	{
		data->in_quotes = 0;
		data->quote = 0;
		data->i++;
		return (1);
	}
	return (0);
}

static int	process_special_chars(char *str, char *quotes_free, t_quote *data)
{
	if (data->in_quotes == 0 && str[data->i] == '\\'
		&& (str[data->i + 1] == '\'' || str[data->i + 1] == '\"'))
	{
		if (handle_escaped_quote(str, quotes_free, data))
			return (1);
	}
	else if (handle_escaped_in_quotes(str, quotes_free, data))
		return (1);
	else if (handle_quote_start(str, data))
		return (1);
	else if (handle_quote_end(str, data))
		return (1);
	return (0);
}

char	*process_quotes(char *str, char *quotes_free)
{
	t_quote	data;

	data.i = 0;
	data.j = 0;
	data.in_quotes = 0;
	data.quote = 0;
	while (str[data.i])
	{
		if (process_special_chars(str, quotes_free, &data))
			continue ;
		else
			quotes_free[data.j++] = str[data.i++];
	}
	quotes_free[data.j] = '\0';
	return (quotes_free);
}
