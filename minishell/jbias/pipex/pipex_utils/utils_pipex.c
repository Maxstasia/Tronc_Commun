/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/02 14:15:56 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *new_envp(const char *name, const char *value)
{
	char *tmp;
	char *new_envp;
	
	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (NULL);
	new_envp = ft_strjoin(tmp, value);
	if (!new_envp)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (new_envp);
}

char **add_envp(char **news, char **envp, const char *name, const char *val)
{
	int i;
	
	i = 0;
	while (envp[i])
	{
		news[i] = ft_strdup(envp[i]);
		if (!news[i])
			return (free_tab(news), NULL);
		i++;
	}
	news[i] = new_envp(name, val);
	if (!news[i])
		return (free_tab(news), NULL);
	i++;
	news[i] = NULL;
	return (news);
}

void update_env_var(char ***envp, const char *name, const char *value)
{
	int i;
	size_t len;
	char **new_var;
	
	i = 0;
	len = ft_strlen(name);
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], name, len) == 0 && (*envp)[i][len] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = new_envp(name, value);
			if (!(*envp)[i])
				return;
			return;
		}
		i++;
	}
	new_var = ft_calloc(i + 2, sizeof(char *));
	if (!new_var)
		return;
	if (!add_envp(new_var, *envp, name, value))
		return (free_tab(new_var));
	free_tab(*envp);
	*envp = new_var;
}

char *get_env_var(char **envp, const char *name)
{
	int i;
	size_t len;
	
	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

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
			return (perror("maxishell: error"), NULL);
		return (paths);
	}
	paths = ft_split((data->envp[i] + 5), ':');
	if (!paths)
		return (perror("maxishell: error"), NULL);
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
	ft_putstr_fd("DEBUG: exec_builtin called for ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd("\n", 2);
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

void execute(t_data *data, t_cmd *cmd)
{
	char *path;
	int status;
	
	if (!cmd->args || !cmd->args[0])
		error_127(data, cmd, NULL);
	if (is_builtin(cmd->args[0]))
	{
		status = exec_builtin(data, cmd);
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
