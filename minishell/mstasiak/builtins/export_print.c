/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:35:30 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/18 13:38:39 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins_utils.h"

static char	**create_sorted_envp(t_data *data, int *count)
{
	char	**sorted_envp;
	int		i;

	*count = 0;
	while (data->envp[*count])
		(*count)++;
	sorted_envp = malloc(sizeof(char *) * (*count + 1));
	if (!sorted_envp)
	{
		data->exit_status = 1;
		return (ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2), NULL);
	}
	i = -1;
	while (i++, i < *count)
	{
		sorted_envp[i] = ft_strdup(data->envp[i]);
		if (!sorted_envp[i])
		{
			ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
			data->exit_status = 1;
			return (free_tab(sorted_envp), NULL);
		}
	}
	sorted_envp[*count] = NULL;
	return (sorted_envp);
}

static void	sort_envp_array(char **sorted_envp, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(sorted_envp[j], sorted_envp[j + 1]) > 0)
			{
				temp = sorted_envp[j];
				sorted_envp[j] = sorted_envp[j + 1];
				sorted_envp[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static int	print_var_with_value(char *env_var, t_data *data)
{
	char	*equal_sign;
	char	*name;
	char	*value;

	equal_sign = ft_strchr(env_var, '=');
	name = ft_substr(env_var, 0, equal_sign - env_var);
	if (!name)
	{
		ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
		return (data->exit_status = 1, 0);
	}
	value = ft_strdup(equal_sign + 1);
	if (!value)
	{
		free(name);
		ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
		return (data->exit_status = 1, 0);
	}
	printf("export %s", name);
	if (value[0] != '\0')
		printf("=\"%s\"", value);
	else
		printf("=\"\"");
	printf("\n");
	return (free(value), free(name), 1);
}

static void	print_sorted_env_vars(char **sorted_envp, t_data *data)
{
	int		i;
	char	*equal_sign;

	i = 0;
	while (sorted_envp[i])
	{
		if (ft_strncmp(sorted_envp[i], "_=", 2) == 0)
		{
			i++;
			continue ;
		}
		equal_sign = ft_strchr(sorted_envp[i], '=');
		if (equal_sign)
		{
			if (!print_var_with_value(sorted_envp[i], data))
				return (free_tab(sorted_envp));
		}
		else
			printf("export %s\n", sorted_envp[i]);
		i++;
	}
}

void	print_export(t_data *data)
{
	int		count;
	char	**sorted_envp;

	sorted_envp = create_sorted_envp(data, &count);
	if (!sorted_envp)
		return ;
	sort_envp_array(sorted_envp, count);
	print_sorted_env_vars(sorted_envp, data);
	free_tab(sorted_envp);
	data->exit_status = 0;
}
