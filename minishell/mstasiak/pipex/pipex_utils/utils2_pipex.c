/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/28 19:33:11 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**first_step(t_data *data)
{
	int		i;
	char	**paths;

	i = 0;
	while (data->envp && data->envp[i]
		&& ft_strnstr(data->envp[i], "PATH", 4) == 0)
		i++;
	if (!data->envp || !data->envp[i])
	{
		paths = ft_split("/bin:/usr/bin:/usr/local/bin", ':');
		if (!paths)
			return (perror(RED"maxishell: error"RESET), NULL);
		return (paths);
	}
	paths = ft_split((data->envp[i] + 5), ':');
	if (!paths)
		return (perror(RED"maxishell: error"RESET), NULL);
	return (paths);
}

char	*find_path(t_data *data, char *cmd_name)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

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

void	execute(t_data *data, t_cmd *cmd)
{
	char	*path;

	if (!cmd->args || !cmd->args[0])
		error_127(data, cmd, NULL);
	if (ft_strncmp(cmd->args[0], "/", 1) == 0
		|| ft_strncmp(cmd->args[0], "./", 2) == 0
		|| ft_strncmp(cmd->args[0], "../", 3) == 0)
		path = ft_strdup(cmd->args[0]);
	else
		path = find_path(data, cmd->args[0]);
	if (!path || access(path, X_OK) == -1)
		error_127(data, cmd, path);
	if (execve(path, cmd->args, data->envp) == -1)
		error_127(data, cmd, path);
}

void	t_pipex_init(t_pipex *pipex, char *input, t_token_list *current)
{
	pipex->cmd_count = count_cmd(current);
	pipex->commands = ft_split_advanced(input, pipex->cmd_count);
	pipex->is_first = 1;
}
