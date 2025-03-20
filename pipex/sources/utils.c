/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/20 13:44:48 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	**first_step(t_pipex *pipex)
{
	int		i;
	char	**paths;

	i = 0;
	while (pipex->envp && pipex->envp[i] && ft_strnstr(pipex->envp[i], "PATH", 4) == 0)
		i++;
	if (!pipex->envp || !pipex->envp[i])
	{
		paths = ft_split("/bin:/usr/bin", ':');
		if (!paths)
			ft_putstr_fd(RED"Error: PATH not found in environment variables\033[0m\n", 2);
		return (paths);
	}
	paths = ft_split((pipex->envp[i] + 5), ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*find_path(t_pipex *pipex, char *cmd_name)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;


	if (!pipex->envp || !*pipex->envp)
	{
		ft_putstr_fd(RED"Error: PATH not found in environment variables\033[0m\n", 2);
		return (NULL);
	}
	paths = first_step(pipex);
	if (!paths)
	{
		perror(RED"Error\033[0m");
		return (NULL);
	}
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd_name);
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
		path = find_path(pipex, cmd[0]);
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
}
