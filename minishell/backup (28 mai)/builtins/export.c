/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:38:31 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/28 15:34:20 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins_utils.h"

static int for_without_equal(t_data *data, t_export *export, char *cmd)
{
    char *name;
    char *value;
    char *clean_value;

    name = ft_substr(cmd, 0, export->equal_sign - cmd);
    if (!name)
        return (ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2),
                data->exit_status = 1, 1);
    value = ft_strdup(export->equal_sign + 1);
    if (!value)
        return (free(name), ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2),
                data->exit_status = 1, 1);
    clean_value = remove_quotes(value);
    free(value);
    if (!clean_value)
        return (free(name), ft_putstr_fd(RED"maxishell: export: invalid value\n"RESET, 2),
                data->exit_status = 1, 1);
    export->arg_with_equal = ft_strjoin(name, "=");
    free(name);
    if (!export->arg_with_equal)
        return (free(clean_value), ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2),
                data->exit_status = 1, 1);
    name = export->arg_with_equal;
    export->arg_with_equal = ft_strjoin(name, clean_value);
    free(name);
    free(clean_value);
    if (!export->arg_with_equal)
        return (ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2),
                data->exit_status = 1, 1);
    return (0);
}

static int	principal_loop(t_data *data, t_export *export, char *cmd)
{
	export->equal_sign = ft_strchr(cmd, '=');
	if (!export->equal_sign)
	{
		export->arg_with_equal = ft_strjoin(cmd, "=");
		if (!export->arg_with_equal)
			return (ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2),
				data->exit_status = 1, 1);
	}
	else
	{
		if (for_without_equal(data, export, cmd) == 1)
			return (1);
	}
	if (update_existing_var(data, export->arg_with_equal) == -1)
	{
		if (add_new_var(data, export->arg_with_equal) == 1)
			return (free(export->arg_with_equal), 1);
	}
	free(export->arg_with_equal);
	return (0);
}

int ft_export(t_data *data, t_token_list *token_list)
{
	t_token_list *tmp;
    t_export *export;

	tmp = token_list;
    if (!tmp->next || !tmp->next->token)
	{
        return (print_export(data), 0);
	}
	tmp = tmp->next;
    export = malloc(sizeof(t_export));
    if (!export)
        return (ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2),
            data->exit_status = 1, 1);
    data->exit_status = 0;
    while (tmp)
    {
        if (!is_valid_identifier(tmp->token))
        {
            ft_putstr_fd(RED"maxishell: export: '"YELLOW, 2);
            ft_putstr_fd(tmp->token, 2);
            ft_putstr_fd(RED"' : not a valid identifier\n"RESET, 2);
            data->exit_status = 1;
            continue;
        }
        if (principal_loop(data, export, tmp->token) == 1)
            return (free(export), 1);
		tmp = tmp->next;
    }
    return (free(export), 0);
}
