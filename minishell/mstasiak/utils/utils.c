/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:48:52 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/18 13:18:34 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_var_name(const char *input, int *i)
{
	int		j;
	char	*name;

	j = *i;
	if (input[j] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (input[j] && (ft_isalnum(input[j]) || input[j] == '_'))
		j++;
	name = ft_substr(input, *i, j - *i);
	*i = j;
	return (name);
}

int	expand_variable(char *input, char *result, int *i, t_data *data)
{
	char	*var_name;
	char	*var_value;
	int		len;
	int		k;

	(*i)++;
	var_name = get_var_name(input, i);
	if (!var_name)
		return (-1);
	var_value = get_variable_value(var_name, data);
	len = 0;
	if (var_value)
	{
		len = ft_strlen(var_value);
		k = -1;
		while (++k < len)
			result[k] = var_value[k];
		result[len] = '\0';
	}
	if (ft_strcmp(var_name, "?") == 0)
		free(var_value);
	free(var_name);
	return (len);
}

int	should_expand_variable(char *input, int i, char quote)
{
	return (input[i] == '$' && quote != '\'' && input[i + 1]
		&& (ft_isalnum(input[i + 1]) || input[i + 1] == '?'));
}

int	process_character(char *input, char *result, t_data *data, char quote)
{
	int			var_len;

	handle_quote(input[data->tmp->x], &quote);
	if (handle_escaped_dollar(input, result, &data->tmp->x, &data->tmp->y))
		return (0);
	if (should_expand_variable(input, data->tmp->x, quote))
	{
		var_len = expand_variable(input, result + data->tmp->y,
				&data->tmp->x, data);
		if (var_len == -1)
			return (-1);
		data->tmp->y += var_len;
		return (0);
	}
	result[(data->tmp->y)++] = input[(data->tmp->x)++];
	return (0);
}

char	*expand_variables(char *input, t_data *data)
{
	char	*result;
	size_t	input_len;
	size_t	len;
	char	quote;

	if (!input)
		return (NULL);
	quote = 0;
	input_len = ft_strlen(input);
	len = calculate_buffer_size(input, data);
	if (len < input_len)
		len = input_len;
	result = malloc(sizeof(char) * len + 20);
	if (!result)
		return (NULL);
	data->tmp->x = 0;
	data->tmp->y = 0;
	while (input[data->tmp->x])
	{
		if (process_character(input, result, data, quote) == -1)
			return (free(result), NULL);
	}
	result[data->tmp->y] = '\0';
	return (result);
}
