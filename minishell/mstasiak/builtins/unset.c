/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:38:49 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/01 13:05:53 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int  is_valid_unset_identifier(char *str)
{
    if (!str || !str[0] || ft_isdigit(str[0]))
        return (0);
    if (str[0] != '_' && !ft_isalpha(str[0]))
        return (0);
    while (*str)
    {
        if (!ft_isalnum(*str) && *str != '_')
            return (0);
        str++;
    }
    return (1);
}

static int  remove_var(t_data *data, char *arg)
{
    int     i;
    int     j;
    char    **new_envp;

    i = 0;
    while (data->envp[i])
        i++;
    new_envp = malloc(sizeof(char *) * i + 1);
    if (!new_envp)
        return (data->exit_status = 1, 1);
    j = 0;
    i = -1;
    while (data->envp[++i])
    {
        if (ft_strncmp(data->envp[i], arg, ft_strlen(arg)) != 0
            || data->envp[i][ft_strlen(arg)] != '=')
        {
            new_envp[j] = ft_strdup(data->envp[i]);
            if (!new_envp[j])
                return (free_tab(new_envp), data->exit_status = 1, 1);
            j++;
        }
    }
    new_envp[j] = NULL;
    free_tab(data->envp);
    data->envp = new_envp;
    return (0);
}

char *get_start_cmd(char *cmd)
{
    int     i;
    char    *start_cmd;

    i = 0;
    while (cmd[i] && cmd[i] != '=')
        i++;
    start_cmd = malloc(sizeof(char) * (i + 1));
    if (!start_cmd)
        return (NULL);
    ft_strlcpy(start_cmd, cmd, i + 1);
    return (start_cmd);
}

int ft_unset(t_data *data, t_token_list *token_list)
{
    int     i;
    char    *cmd_start;
	t_token_list *tmp;

	tmp = token_list;
	if (!tmp)
		return (data->exit_status = 0, 0);
    i = 0;
    while (tmp->token)
    {
        cmd_start = get_start_cmd(tmp->token);
        if (cmd_start == NULL)
            return (data->exit_status = 1, 1);
        if (!is_valid_unset_identifier(cmd_start))
        {
            ft_putstr_fd(RED"maxishell: unset: '"YELLOW, 2);
            ft_putstr_fd(tmp->token, 2);
            ft_putstr_fd(RED"' : not a valid identifier\n"RESET, 2);
            data->exit_status = 1;
            free(cmd_start);
        }
        else
        {
            if (remove_var(data, cmd_start) == 1)
                return (free(cmd_start), 1);
        }
    }
    return (free_token_list(tmp), 0);
}