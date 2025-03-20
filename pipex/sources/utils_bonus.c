/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/20 12:22:39 by mstasiak         ###   ########.fr       */
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

static void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split_advanced(argv);
	if (!cmd || !cmd[0])
	{
		ft_putstr_fd(RED"Error: Command not found\033[0m\n", 2);
		free_tab(cmd);
		exit(127);
	}
	if (cmd[0][0] == '/' || (cmd[0][0] == '.' && cmd[0][1] == '/'))
		path = ft_strdup(cmd[0]);
	else
		path = find_path(cmd[0], envp);
	if (!path || access(path, X_OK) == -1)
	{
		ft_putstr_fd(RED"Error: Command not found\033[0m\n", 2);
		free_tab(cmd);
		free(path);
		exit(127);
	}
	if (execve(path, cmd, envp) == -1)
	{
		perror(RED"Error\033[0m");
		free_tab(cmd);
		free(path);
		if (errno == EACCES)
			exit(126);
		exit(127);
	}
	free_tab(cmd);
}

int	open_file(char *argv, int i)
{
	int	ret;

	ret = -1;
	if (i == 0)
	{
		ret = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (ret == -1)
			error();
	}
	else if (i == 1)
		ret = open(argv, O_RDONLY, 0644);
	if (ret == -1)
		ret = open("/dev/null", O_RDONLY, 0644);
	return (ret);
}

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	buffer = (char *)malloc(4096);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0' && i <= 4093)
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
