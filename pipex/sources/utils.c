/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/11 14:29:37 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * find_path - Recherche le chemin d'accès à une commande en utilisant
 * les variables d'environnement.
 * 
 * - @cmd: Le nom de la commande à rechercher.
 * - @envp: Tableau des variables d'environnement.
 * Return: Le chemin complet de la commande si trouvé, sinon NULL.
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

void	error(void)
{
	perror(RED"Error\033[0m");
	exit(1);
}
