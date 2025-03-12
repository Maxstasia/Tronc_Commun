/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/12 14:41:40 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

/**
 * find_path - Trouve le chemin absolu d'une commande.
 * 
 * - @cmd: Nom de la commande.
 * - @envp: Tableau des variables d'environnement.
 * Return: Chemin absolu de la commande ou NULL si introuvable.
 */
static char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split((envp[i] + 5), ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, 0) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split_advanced(argv);
	if (!cmd || !cmd[0])
	{
		ft_putstr_fd(RED"Error: Command not found\033[0m\n", 2);
		exit(127);
	}
	path = find_path(cmd[0], envp);
	if (!path)
	{
		ft_putstr_fd(RED"Error: Command not found\033[0m\n", 2);
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		exit(127);
	}
	if (execve(path, cmd, envp) == -1)
	{
		perror(RED"Error\033[0m");
		exit(127);
	}
}

int	open_file(char *argv, int i)
{
	int	file;

	if (!argv)
	{
		write(2, RED"Error: Invalid file name\033[0m\n", 25);
		return (-1);
	}
	if (i == 0)
		file = open(argv, (O_WRONLY | O_CREAT | O_TRUNC), 0644);
	else if (i == 1)
		file = open(argv, (O_WRONLY | O_CREAT | O_APPEND), 0644);
	else if (i == 2)
		file = open(argv, O_RDONLY);
	else
	{
		write(2, RED"Error: Invalid mode\033[0m\n", 20);
		return (-1);
	}
	if (file == -1)
		error();
	return (file);
}

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}
