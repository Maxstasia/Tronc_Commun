/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/01 16:50:01 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	**first_step(t_pipex *pipex)
{
	int		i;
	char	**paths;

	i = 0;
	while (pipex->envp && pipex->envp[i]
		&& ft_strnstr(pipex->envp[i], "PATH", 4) == 0)
		i++;
	if (!pipex->envp || !pipex->envp[i])
	{
		paths = ft_split("/bin:/usr/bin:/usr/local/bin", ':');
		if (!paths)
			return (perror(RED"Error"RESET), NULL);
		return (paths);
	}
	paths = ft_split((pipex->envp[i] + 5), ':');
	if (!paths)
		return (perror(RED"Error"RESET), NULL);
	return (paths);
}

char	*find_path(t_pipex *pipex, char *cmd_name)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	paths = first_step(pipex);
	if (!paths)
		return (NULL);
	i = -1;
	while (++i, paths[i])
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

void	execute(t_pipex *pipex)
{
	char	**cmd;
	char	*path;

	cmd = ft_split_advanced(pipex->argv[0]);
	if (!cmd || !cmd[0])
		error_127(cmd, NULL);
	if (ft_strncmp(cmd[0], "/", 1) == 0 || ft_strncmp(cmd[0], "./", 2) == 0
		|| ft_strncmp(cmd[0], "../", 3) == 0)
		path = ft_strdup(cmd[0]);
	else
		path = find_path(pipex, cmd[0]);
	if (!path || access(path, X_OK) == -1)
		error_127(cmd, path);
	if (execve(path, cmd, pipex->envp) == -1)
		error_127(cmd, path);
}
