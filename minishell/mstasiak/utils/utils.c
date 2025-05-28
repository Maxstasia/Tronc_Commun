/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:48:52 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/02 11:55:44 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char *get_var_name(const char *input, int *i)
{
	int j = *i;
	char *name;
	
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

static size_t calculate_buffer_size(char *input, t_data *data)
{
	size_t size = 1; // Pour le '\0'
	int i = 0;
	char quote = 0;
	
	while (input[i])
	{
		if (input[i] == '\'' && !quote)
			quote = '\'';
		else if (input[i] == '\'' && quote == '\'')
			quote = 0;
		else if (input[i] == '"' && !quote)
			quote = '"';
		else if (input[i] == '"' && quote == '"')
			quote = 0;
		else if (input[i] == '$' && quote != '\'' && input[i + 1] && (ft_isalnum(input[i + 1]) || input[i + 1] == '?'))
		{
			i++;
			char *var_name = get_var_name(input, &i);
			if (!var_name)
				return (size);
			if (ft_strcmp(var_name, "?") == 0)
			{
				char *status = ft_itoa(data->exit_status);
				if (status)
					size += ft_strlen(status);
				free(status);
			}
			else
			{
				char *var_value = get_env_var(data->envp, var_name);
				if (var_value)
				size += ft_strlen(var_value);
			}
			free(var_name);
			continue;
		}
		size++;
		i++;
	}
	return (size);
}

char *expand_variables(char *input, t_data *data)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	int		i;
	int		j;
	char	quote;
	size_t	len;
	
	i = 0;
	j = 0;
	quote = 0;
	len = calculate_buffer_size(input, data);
	result = ft_calloc(len, sizeof(char));
	if (!result)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '\'' && !quote)
			quote = '\'';
		else if (input[i] == '\'' && quote == '\'')
			quote = 0;
		else if (input[i] == '"' && !quote)
			quote = '"';
		else if (input[i] == '"' && quote == '"')
			quote = 0;
		else if (input[i] == '$' && quote != '\'' && input[i + 1] && (ft_isalnum(input[i + 1]) || input[i + 1] == '?'))
		{
			i++;
			var_name = get_var_name(input, &i);
			if (!var_name)
			{
				free(result);
				return (NULL);
			}
			if (ft_strcmp(var_name, "?") == 0)
				var_value = ft_itoa(data->exit_status);
			else
				var_value = get_env_var(data->envp, var_name);
			if (var_value)
			{
				ft_strlcat(result, var_value, len);
				j += ft_strlen(var_value);
			}
			if (ft_strcmp(var_name, "?") == 0)
				free(var_value);
			free(var_name);
			continue;
		}
		result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}

void	init_token_list(t_token_list *token_list)
{
	token_list->token = NULL;
	token_list->type = 0;
	token_list->next = NULL;
}

void	init_next(t_token_list *token_list)
{
	token_list->next = malloc(sizeof(t_token_list));
	if (!token_list->next)
	{
		free(token_list->token);
		free(token_list);
		token_list = NULL;
		return;
	}
	init_token_list(token_list->next);
}