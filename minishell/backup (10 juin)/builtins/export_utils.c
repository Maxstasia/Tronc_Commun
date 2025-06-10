/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:28:59 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/13 17:24:08 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins_utils.h"

int is_valid_identifier(char *str)
{
    int i;

    if (!str || !str[0] || ft_isdigit(str[0]))
        return (0);
    if (str[0] != '_' && !ft_isalpha(str[0]))
        return (0);
    i = 0;
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    if (str[i] == '=')
    {
        i++;
        if (str[i] == '"' && !ft_strchr(&str[i + 1], '"'))
            return (0);
    }
    return (1);
}

char *remove_quotes(char *value)
{
    char *clean_value;
    int len;
    int i;
    int j;

    if (!value || !value[0])
        return (ft_strdup(""));
    len = ft_strlen(value);
    if (len >= 2 && value[0] == '"' && value[len - 1] == '"')
    {
        clean_value = malloc(len - 1);
        if (!clean_value)
            return (NULL);
        i = 1;
        j = 0;
        while (i < len - 1)
            clean_value[j++] = value[i++];
        clean_value[j] = '\0';
        return (clean_value);
    }
    if (value[0] == '"' || value[len - 1] == '"')
        return (NULL);
    return (ft_strdup(value));
}

int	update_existing_var(t_data *data, char *arg)
{
	int		i;
	int		name_len;

	i = -1;
	if (ft_strchr(arg, '='))
		name_len = ft_strchr(arg, '=') - arg;
	else
		name_len = ft_strlen(arg);
	while (i ++, data->envp[i])
	{
		if (ft_strncmp(data->envp[i], arg, name_len) == 0
			&& (data->envp[i][name_len] == '='
			|| data->envp[i][name_len] == '\0'))
		{
			free(data->envp[i]);
			data->envp[i] = ft_strdup(arg);
			if (!data->envp[i])
			{
				data->exit_status = 1;
				return (1);
			}
			return (0);
		}
	}
	return (-1);
}

int	add_new_var(t_data *data, char *arg)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (data->envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return (1);
	i = -1;
	while (i ++, data->envp[i])
	{
		new_envp[i] = ft_strdup(data->envp[i]);
		if (!new_envp[i])
			return (data->exit_status = 1, free_tab(new_envp), 1);
	}
	new_envp[i] = ft_strdup(arg);
	if (!new_envp[i])
		return (data->exit_status = 1, free_tab(new_envp), 1);
	new_envp[++i] = NULL;
	free_tab(data->envp);
	return (data->envp = new_envp, 0);
}
