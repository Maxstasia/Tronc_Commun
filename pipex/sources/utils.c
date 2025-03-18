/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/18 16:39:14 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	**first_step(t_pipex *pipex)
{
	int		i;
	char	**paths;

	i = 0;
	while (pipex->envp[i] && ft_strnstr(pipex->envp[i], "PATH", 4) == 0)
		i++;
	if (!pipex->envp[i])
		return (NULL);
	paths = ft_split((pipex->envp[i] + 5), ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*find_path(t_pipex *pipex)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	paths = first_step(pipex);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, pipex->argv[0]);
		free(part_path);
		if (access(path, 0) == 0)
		{
			free_tab(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_tab(paths);
	return (NULL);
}

void	execute(t_pipex *pipex)
{
	char	**cmd;
	char	*path;

	cmd = ft_split_advanced(pipex->argv[0]);
	if (!cmd || !cmd[0])
		error_127(cmd, NULL);
	if (cmd[0][0] == '/' || (cmd[0][0] == '.' && cmd[0][1] == '/'))
		path = ft_strdup(cmd[0]);
	else
		path = find_path(pipex);
	if (!path || access(path, X_OK) == -1)
		error_127(cmd, path);
	if (execve(path, cmd, pipex->envp) == -1)
	{
		perror(RED"Error\033[0m");
		free_tab(cmd);
		free(path);
		if (errno == EACCES)
			exit(126);
		exit(127);
	}
	free_tab(cmd);
	free(path);
}
