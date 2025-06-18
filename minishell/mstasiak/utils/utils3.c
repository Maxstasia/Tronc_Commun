/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:57:49 by jbias             #+#    #+#             */
/*   Updated: 2025/06/17 12:57:50 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	handle_escaped_dollar_size(int *i)
{
	*i += 2;
	return (1);
}

static size_t	handle_variable_expansion(char *input, int *i, t_data *data)
{
	char	*var_name;
	char	*var_value;
	char	*status;
	size_t	var_size;

	(*i)++;
	var_name = get_var_name(input, i);
	if (!var_name)
		return (0);
	var_size = 0;
	if (ft_strcmp(var_name, "?") == 0)
	{
		status = ft_itoa(data->exit_status);
		if (status)
			var_size = ft_strlen(status);
		free(status);
	}
	else
	{
		var_value = get_env_var(data->envp, var_name);
		if (var_value)
			var_size = ft_strlen(var_value);
	}
	free(var_name);
	return (var_size);
}

static int	update_quote_state(char c, char *quote)
{
	if (c == '\'' && !*quote)
		*quote = '\'';
	else if (c == '\'' && *quote == '\'')
		*quote = 0;
	else if (c == '"' && !*quote)
		*quote = '"';
	else if (c == '"' && *quote == '"')
		*quote = 0;
	else
		return (0);
	return (1);
}

static size_t	for_norm(int *i, size_t size)
{
	(*i)++;
	size++;
	return (size);
}

size_t	calculate_buffer_size(char *input, t_data *data)
{
	size_t	size;
	int		i;
	char	quote;

	size = 1;
	i = 0;
	quote = 0;
	while (input[i])
	{
		if (update_quote_state(input[i], &quote))
			for_norm(&i, size);
		else if (input[i] == '\\' && input[i + 1] == '$' && quote == '"')
			size += handle_escaped_dollar_size(&i);
		else if (input[i] == '$' && quote != '\'' && input[i + 1]
			&& (ft_isalnum(input[i + 1]) || input[i + 1] == '?'))
			size += handle_variable_expansion(input, &i, data);
		else
			for_norm(&i, size);
	}
	return (size);
}
