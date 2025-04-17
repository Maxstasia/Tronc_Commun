/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/17 17:28:06 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char **first_step(t_data *data)
{
    int i;
    char **paths;

    i = 0;
    while (data->envp && data->envp[i] && ft_strnstr(data->envp[i], "PATH", 4) == 0)
        i++;
    if (!data->envp || !data->envp[i])
    {
        paths = ft_split("/bin:/usr/bin:/usr/local/bin", ':');
        if (!paths)
            return (perror("minishell: error"), NULL);
        return (paths);
    }
    paths = ft_split((data->envp[i] + 5), ':');
    if (!paths)
        return (perror("minishell: error"), NULL);
    return (paths);
}

char *find_path(t_data *data, char *cmd_name)
{
    char **paths;
    char *path;
    char *tmp;
    int i;

    paths = first_step(data);
    if (!paths)
        return (NULL);
    i = -1;
    while (paths[++i])
    {
        tmp = ft_strjoin(paths[i], "/");
        if (!tmp)
            return (free_tab(paths), NULL);
        path = ft_strjoin(tmp, cmd_name);
        free(tmp);
        if (!path)
            return (free_tab(paths), NULL);
        if (access(path, F_OK) == 0)
            return (free_tab(paths), path);
        free(path);
    }
    return (free_tab(paths), NULL);
}

static int is_builtin(char *cmd_name)
{
    if (!cmd_name)
        return (0);
    if (ft_strcmp(cmd_name, "echo") == 0 ||
        ft_strcmp(cmd_name, "cd") == 0 ||
        ft_strcmp(cmd_name, "pwd") == 0 ||
        ft_strcmp(cmd_name, "export") == 0 ||
        ft_strcmp(cmd_name, "unset") == 0 ||
        ft_strcmp(cmd_name, "env") == 0 ||
        ft_strcmp(cmd_name, "exit") == 0)
        return (1);
    return (0);
}

static int exec_builtin(t_data *data, t_cmd *cmd)
{
    data->cmd = cmd->args;
    if (ft_strcmp(cmd->args[0], "echo") == 0)
        echo_builtin(data);
    else if (ft_strcmp(cmd->args[0], "cd") == 0)
        builtin_cd(cmd->args, data);
    else if (ft_strcmp(cmd->args[0], "pwd") == 0)
        return (pwd(data));
    else if (ft_strcmp(cmd->args[0], "export") == 0)
        return (ft_export(data));
    else if (ft_strcmp(cmd->args[0], "unset") == 0)
        return (ft_unset(data));
    else if (ft_strcmp(cmd->args[0], "env") == 0)
        return (env(data));
    else if (ft_strcmp(cmd->args[0], "exit") == 0)
        exit_builtin(data);
    return (data->exit_status);
}

void execute(t_data *data, t_cmd *cmd, t_pipex *pipex)
{
    char *path;

    if (!cmd->args || !cmd->args[0])
        error_127(data, cmd, NULL);
    if (is_builtin(cmd->args[0]))
    {
        int status = exec_builtin(data, cmd);
        free_cmd(cmd);
        exit(status);
    }
    if (ft_strncmp(cmd->args[0], "/", 1) == 0 || ft_strncmp(cmd->args[0], "./", 2) == 0
        || ft_strncmp(cmd->args[0], "../", 3) == 0)
        path = ft_strdup(cmd->args[0]);
    else
        path = find_path(data, cmd->args[0]);
    if (!path || access(path, X_OK) == -1)
        error_127(data, cmd, path);
    if (execve(path, cmd->args, data->envp) == -1)
        error_127(data, cmd, path);
}
