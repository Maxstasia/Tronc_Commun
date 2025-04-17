/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_advanced.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:26:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/17 17:29:32 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int is_separator(char c, char quote)
{
    if (quote)
        return (0);
    if (c == ' ' || c == '\t' || c == '|')
        return (1);
    return (0);
}

static int is_redirect(char *str)
{
    return (ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">") == 0 ||
            ft_strcmp(str, "<<") == 0 || ft_strcmp(str, ">>") == 0);
}

static char *get_next_arg(const char *s, int *i)
{
    char *arg;
    int k;
    char quote;

    arg = malloc(sizeof(char) * 256);
    if (!arg)
        return (NULL);
    quote = 0;
    k = 0;
    while (s[*i] && (!is_separator(s[*i], quote) || quote))
    {
        if ((s[*i] == '\'' || s[*i] == '\"') && (!quote || quote == s[*i]))
        {
            if (quote == 0)
                quote = s[*i];
            else
                quote = 0;
        }
        else
            arg[k++] = s[*i];
        (*i)++;
    }
    arg[k] = '\0';
    return (arg);
}

static void free_cmd(t_cmd *cmd, int j)
{
    int k;

    while (j > 0)
    {
        j--;
        if (cmd[j].args)
            free_tab(cmd[j].args);
        if (cmd[j].redirects)
        {
            for (k = 0; k < cmd[j].redirect_count; k++)
            {
                free(cmd[j].redirects[k].type);
                free(cmd[j].redirects[k].file);
            }
            free(cmd[j].redirects);
        }
    }
    free(cmd);
}

t_cmd *ft_split_advanced(const char *s)
{
    t_cmd *result;
    int i, j, k;

    if (!s)
        return (NULL);
    result = malloc(sizeof(t_cmd) * 256);
    if (!result)
        return (NULL);
    i = 0;
    j = 0;
    while (s[i])
    {
        while (s[i] && (s[i] == ' ' || s[i] == '\t'))
            i++;
        if (!s[i])
            break;
        result[j].args = malloc(sizeof(char *) * 256);
        result[j].redirects = malloc(sizeof(t_redirect) * 256);
        result[j].redirect_count = 0;
        k = 0;
        while (s[i] && s[i] != '|')
        {
            while (s[i] && (s[i] == ' ' || s[i] == '\t'))
                i++;
            if (!s[i] || s[i] == '|')
                break;
            char *arg = get_next_arg(s, &i);
            if (!arg)
                return (free_cmd(result, j), NULL);
            if (is_redirect(arg))
            {
                char *file = get_next_arg(s, &i);
                if (!file)
                    return (free(arg), free_cmd(result, j), NULL);
                result[j].redirects[result[j].redirect_count].type = arg;
                result[j].redirects[result[j].redirect_count].file = file;
                result[j].redirect_count++;
            }
            else
                result[j].args[k++] = arg;
        }
        result[j].args[k] = NULL;
        if (s[i] == '|')
            i++;
        j++;
    }
    result[j].args = NULL;
    return (result);
}