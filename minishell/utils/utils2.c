/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:20:47 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/30 12:11:42 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_quote(char c, char *quote)
{
	if (c == '\'' && !*quote)
		*quote = '\'';
	else if (c == '\'' && *quote == '\'')
		*quote = 0;
	else if (c == '"' && !*quote)
		*quote = '"';
	else if (c == '"' && *quote == '"')
		*quote = 0;
}

int	handle_escaped_dollar(char *input, char *result, int *i, int *j)
{
	if (input[*i] == '\\' && input[*i + 1] == '$')
	{
		result[(*j)++] = '$';
		*i += 2;
		return (1);
	}
	return (0);
}

char	*get_variable_value(char *var_name, t_data *data)
{
	char	*var_value;

	if (ft_strcmp(var_name, "?") == 0)
		var_value = ft_itoa(data->exit_status);
	else
		var_value = get_env_var(data->envp, var_name);
	return (var_value);
}

void	close_saved_fds(t_data *data)
{
	if (data->has_saved_fds)
	{
		if (data->saved_stdin >= 0)
		{
			close(data->saved_stdin);
			data->saved_stdin = -1;
		}
		if (data->saved_stdout >= 0)
		{
			close(data->saved_stdout);
			data->saved_stdout = -1;
		}
		data->has_saved_fds = 0;
	}
}
