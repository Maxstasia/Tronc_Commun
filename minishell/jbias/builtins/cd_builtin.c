#include "../includes/minishell.h"

static char *cd_handle_oldpwd(t_data *data)
{
	char *path;

	path = get_env_var(data->envp, "OLDPWD");
	if (!path)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		data->exit_status = 1;
		return (NULL);
	}
	ft_putstr_fd(path, 1);
	ft_putchar_fd('\n', 1);
	return (path);
}

static char *cd_get_path(char **cmd, t_data *data)
{
	char *path;
	if (!cmd[1] || ft_strcmp(cmd[1], "~") == 0)
	{
		path = get_env_var(data->envp, "HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			data->exit_status = 1;
			return (NULL);
		}
	}
	else if (ft_strcmp(cmd[1], "-") == 0)
		return (cd_handle_oldpwd(data));
	else if (!cmd[1])
	{
		ft_putstr_fd("minishell: cd: invalid argument\n", 2);
		data->exit_status = 1;
		return (NULL);
	}
	else
		path = cmd[1];
	return (path);
}

static int cd_change_dir(char *path, char *buff_oldpwd, char *buff_pwd, t_data *data)
{
	if (getcwd(buff_oldpwd, sizeof(buff_oldpwd)) == NULL)
	    buff_oldpwd[0] = '\0';
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->exit_status = 1;
		return (1);
	}
	if (getcwd(buff_pwd, sizeof(buff_pwd)) == NULL)
	{
		ft_putstr_fd("minishell: cd: getcwd failed\n", 2);
		data->exit_status = 1;
		return (1);
	}
	return (0);
}

static void cd_update_env(t_data *data, char *buff_pwd, char *buff_oldpwd)
{
	update_env_var(&data->envp, "PWD", buff_pwd);
	if (data->pwd)
		free(data->pwd);
	data->pwd = ft_strdup(buff_pwd);
	if (!data->pwd)
	{
		ft_putstr_fd("minishell: cd: malloc failed\n", 2);
		data->exit_status = 1;
		return;
	}
	if (buff_oldpwd[0] != '\0')
	{
		update_env_var(&data->envp, "OLDPWD", buff_oldpwd);
		if (data->oldpwd)
			free(data->oldpwd);
		data->oldpwd = ft_strdup(buff_oldpwd);
		if (!data->oldpwd)
		{
			ft_putstr_fd("minishell: cd: malloc failed\n", 2);
			data->exit_status = 1;
			return ;
		}
	}
	else
		data->exit_status = 0;
}

void builtin_cd(char **cmd, t_data *data)
{
	char *path;
	char buff_pwd[1024];
	char buff_oldpwd[1024];
	path = cd_get_path(cmd, data);
	if (!path)
		return;
	if (cd_change_dir(path, buff_oldpwd, buff_pwd, data))
		return ;
	cd_update_env(data, buff_pwd, buff_oldpwd);
}