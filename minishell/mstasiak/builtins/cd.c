/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:35:41 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/01 15:48:39 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*cd_handle_oldpwd(t_data *data)
{
	char	*path;
	
	path = get_env_var(data->envp, "OLDPWD");
	if (!path)
	{
		ft_putstr_fd(RED"maxishell: cd: OLDPWD not set\n"RESET, 2);
		data->exit_status = 1;
		return (NULL);
	}
	ft_putstr_fd(path, 1);
	ft_putchar_fd('\n', 1);
	return (path);
}

static char	*cd_get_path(char **cmd, t_data *data)
{
	char	*path;
	
	if (!cmd[1] || ft_strcmp(cmd[1], "~") == 0)
	{
		path = get_env_var(data->envp, "HOME");
		if (!path)
		{
			ft_putstr_fd(RED"maxishell: cd: HOME not set\n"RESET, 2);
			data->exit_status = 1;
			return (NULL);
		}
	}
	else if (ft_strcmp(cmd[1], "-") == 0)
		return (cd_handle_oldpwd(data));
	else
		path = cmd[1];
	return (path);
}

static int	cd_change_dir(char *path, t_data *data)
{
	char	*oldpwd;
	
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		ft_putstr_fd(RED"maxishell: cd: '"YELLOW, 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(RED"' : No such file or directory\n"RESET, 2);
		data->exit_status = 1;
		free(oldpwd);
		return (1);
	}
	free(data->oldpwd);
	data->oldpwd = oldpwd;
	free(data->pwd);
	data->pwd = getcwd(NULL, 0);
	if (!data->pwd)
	{
		ft_putstr_fd(RED"maxishell: cd: getcwd failed: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n"RESET, 2);
		data->exit_status = 1;
		return (1);
	}
	return (0);
}

static void	cd_update_env(t_data *data)
{
	update_env_var(&data->envp, "PWD", data->pwd);
	if (data->oldpwd)
		update_env_var(&data->envp, "OLDPWD", data->oldpwd);
	data->exit_status = 0;
}

void	builtin_cd(char **cmd, t_data *data)
{
	char	*path;
	
	path = cd_get_path(cmd, data);
	if (!path)
		return;
	if (cd_change_dir(path, data))
		return;
	cd_update_env(data);
}
