/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:35:30 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/13 15:36:17 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins_utils.h"

void	print_export(t_data *data)
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
