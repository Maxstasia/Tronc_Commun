/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:38:31 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/18 12:55:58 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int is_valid_identifier(char *str)
{
    if (!str || !str[0] || ft_isdigit(str[0]))
        return (0);
    if (str[0] != '_' && (!ft_isalpha(str[0]) || str[0] == '='))
        return (0);
    if (ft_strchr(str, '=') == NULL)
        return (0);
    while (*str && *str != '=')
    {
        if (!ft_isalnum(*str) && *str != '_')
            return (0);
        str++;
    }
    return (1);
}

static int  update_existing_var(t_data *data, char *arg)
{
    int     i;
    char    *name;
    int     name_len;

    i = 0;
    name = ft_strchr(arg, '=');
    if (name == NULL)
        return (-1);
    name_len = name - arg;
    while (data->envp[i])
    {
        if (ft_strncmp(data->envp[i], arg, name_len) == 0
            && data->envp[i][name_len] == '=')
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
        i++;
    }
    return (-1);
}

static int add_new_var(t_data *data, char *arg)
{
    int     i;
    char    **new_envp;

    i = 0;
    while (data->envp[i])
        i++;
    new_envp = malloc(sizeof(char *) * (i + 2));
    if (!new_envp)
        return (1);
    i = 0;
    while (data->envp[i])
    {
        new_envp[i] = ft_strdup(data->envp[i]);
        if (!new_envp[i])
        {
            data->exit_status = 1;
            return (free_tab(new_envp), 1);
        }
        i++;
    }
    new_envp[i] = ft_strdup(arg);
    if (!new_envp[i])
    {
        data->exit_status = 1;
        return (free_tab(new_envp), 1);
    }
    new_envp[++i] = NULL;
    free_tab(data->envp);
    data->envp = new_envp;
    return (0);
}

static void print_export(t_data *data)
{
    int i;

    i = 0;
    while (data->envp[i])
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(data->envp[i], 1);
        ft_putchar_fd('\n', 1);
        i++;
    }
    data->exit_status = 0;
}

int ft_export(t_data *data)
{
    int i;

    if (!data->cmd[1])
        return (print_export(data), 0);
    i = 1;
    data->exit_status = 0;
    while (data->cmd[i])
    {
        if (!is_valid_identifier(data->cmd[i]))
        {
            ft_putstr_fd(RED"minishell: export: '"YELLOW, 2);
            ft_putstr_fd(data->cmd[i], 2);
            ft_putstr_fd(RED"' : not a valid identifier\n"RESET, 2);
            data->exit_status = 1;
        }
        else if (update_existing_var(data, data->cmd[i]) == -1)
        {
            if (add_new_var(data, data->cmd[i]) == 1)
                return (1);
        }
        i++;
    }
    return (0);
}