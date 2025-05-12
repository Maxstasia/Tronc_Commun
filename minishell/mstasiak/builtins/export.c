/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:38:31 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/12 16:41:17 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins_utils.h"

static void	print_export(t_data *data)
{
	int		i;
	int		j;
	int		count;
	char	**sorted_envp;
	char	*temp;
	char	*equal_sign;
	char	*name;
	char	*value;

	count = 0;
	while (data->envp[count])
		count++;
	sorted_envp = malloc(sizeof(char *) * (count + 1));
	if (!sorted_envp)
	{
		ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
		data->exit_status = 1;
		return;
	}
	for (i = 0; i < count; i++)
	{
		sorted_envp[i] = ft_strdup(data->envp[i]);
		if (!sorted_envp[i])
		{
			ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
			free_tab(sorted_envp);
			data->exit_status = 1;
			return;
		}
	}
	sorted_envp[count] = NULL;
	for (i = 0; i < count - 1; i++)
	{
		for (j = 0; j < count - i - 1; j++)
		{
			if (ft_strcmp(sorted_envp[j], sorted_envp[j + 1]) > 0)
			{
				temp = sorted_envp[j];
				sorted_envp[j] = sorted_envp[j + 1];
				sorted_envp[j + 1] = temp;
			}
		}
	}
	i = 0;
	while (sorted_envp[i])
	{
		if (ft_strncmp(sorted_envp[i], "_=", 2) == 0)
		{
			i++;
			continue;
		}
		equal_sign = ft_strchr(sorted_envp[i], '=');
		if (equal_sign)
		{
			name = ft_substr(sorted_envp[i], 0, equal_sign - sorted_envp[i]);
			if (!name)
			{
				ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
				free_tab(sorted_envp);
				data->exit_status = 1;
				return;
			}
			value = ft_strdup(equal_sign + 1);
			if (!value)
			{
				free(name);
				ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
				free_tab(sorted_envp);
				data->exit_status = 1;
				return;
			}
			ft_putstr_fd("export ", 1);
			ft_putstr_fd(name, 1);
			if (value[0] != '\0')
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(value, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putchar_fd('\n', 1);
			free(name);
			free(value);
		}
		else
		{
			ft_putstr_fd("export ", 1);
			ft_putstr_fd(sorted_envp[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	free_tab(sorted_envp);
	data->exit_status = 0;
}

int	ft_export(t_data *data)
{
	int		i;
	char	*arg_with_equal;
	char	*equal_sign;
	char	*name;
	char	*value;
	char	*clean_value;

	if (!data->cmd[1])
		return (print_export(data), 0);
	i = 1;
	data->exit_status = 0;
	while (data->cmd[i])
	{
		if (!is_valid_identifier(data->cmd[i]))
		{
			ft_putstr_fd(RED"maxishell: export: '"YELLOW, 2);
			ft_putstr_fd(data->cmd[i], 2);
			ft_putstr_fd(RED"' : not a valid identifier\n"RESET, 2);
			data->exit_status = 1;
		}
		else
		{
			equal_sign = ft_strchr(data->cmd[i], '=');
			if (!equal_sign)
			{
				arg_with_equal = ft_strjoin(data->cmd[i], "=");
				if (!arg_with_equal)
				{
					ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
					data->exit_status = 1;
					return (1);
				}
			}
			else
			{
				name = ft_substr(data->cmd[i], 0, equal_sign - data->cmd[i]);
				if (!name)
				{
					ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
					data->exit_status = 1;
					return (1);
				}
				value = ft_strdup(equal_sign + 1);
				if (!value)
				{
					free(name);
					ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
					data->exit_status = 1;
					return (1);
				}
				clean_value = remove_quotes(value);
				free(value);
				if (!clean_value)
				{
					free(name);
					ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
					data->exit_status = 1;
					return (1);
				}
				arg_with_equal = ft_strjoin(name, "=");
				free(name);
				if (!arg_with_equal)
				{
					free(clean_value);
					ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
					data->exit_status = 1;
					return (1);
				}
				name = arg_with_equal;
				arg_with_equal = ft_strjoin(name, clean_value);
				free(name);
				free(clean_value);
				if (!arg_with_equal)
				{
					ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
					data->exit_status = 1;
					return (1);
				}
			}
			if (update_existing_var(data, arg_with_equal) == -1)
			{
				if (add_new_var(data, arg_with_equal) == 1)
				{
					free(arg_with_equal);
					return (1);
				}
			}
			free(arg_with_equal);
		}
		i++;
	}
	return (0);
}
