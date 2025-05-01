#include "../includes/minishell.h"

char	*new_envp(const char *name, const char *value)
{
	char	*tmp;
	char	*new_envp;

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

char	**add_envp(char **new, char **envp, const char *name, const char *val)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		new[i] = ft_strdup(envp[i]);
		if (!new[i])
			return (free_tab(new), NULL);
		i++;
	}
	new[i] = new_envp(name, val);
	if (!new[i])
		return (free_tab(new), NULL);
	i++;
	new[i] = NULL;
	return (new);
}

void	update_env_var(char ***envp, const char *name, const char *value)
{
	int		i;
	size_t	len;
	char	**new_var;

	i = 0;
	len = ft_strlen(name);
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], name, len) == 0 && (*envp)[i][len] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = new_envp(name, value);
			if (!(*envp)[i])
				return ;
			return ;
		}
		i++;
	}
	new_var = ft_calloc(i + 2, sizeof(char *));
	if (!new_var)
		return ;
	if (!add_envp(new_var, *envp, name, value))
		return (free_tab(new_var));
	free(*envp);
	*envp = new_var;
}

char	*get_env_var(char **envp, const char *name)
{
	int		i;
	size_t	len;

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

/*void	builtin_cd(char **cmd, t_data *data)
{
	char	*path;
	char	buff_pwd[1024];
	char	buff_oldpwd[1024];

	if (getcwd(buff_oldpwd, sizeof(buff_oldpwd)) == NULL)
		buff_oldpwd[0] = '\0';

	if (!cmd[1] || ft_strcmp(cmd[1], "~") == 0)
	{
		path = get_env_var(data->env, "HOME");
		if (path == NULL)
		{
			data->exit_status = 1;
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2));
		}
	}
	else if (ft_strcmp(cmd[1], "-") == 0)
	{
		path = get_env_var(data->env, "OLDPWD");
		if (path == NULL)
		{
			data->exit_status = 1;
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2));
		}
		ft_putstr_fd(path, 1);
		ft_putchar_fd('\n', 1);
	}
	else
		path = cmd[1];
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->exit_status = 1;
		return ;
	}
	if (getcwd(buff_pwd, sizeof(buff_pwd)) == NULL)
	{
		data->exit_status = 1;
		return (ft_putstr_fd("minishell: cd: getcwd failed\n", 2));
	}
	update_env_var(&data->env, "PWD", buff_pwd);
	if (data->pwd)
		free(data->pwd);
	data->pwd = ft_strdup(buff_pwd);
	if (!data->pwd)
		return (data->exit_status = 1);	
	if (buff_oldpwd[0] != '\0')
	{
		update_env_var(&data->env, "OLDPWD", buff_oldpwd);
		if (data->oldpwd)
			free(data->oldpwd);
		data->oldpwd = ft_strdup(buff_oldpwd);
		if (!data->oldpwd)
			return (data->exit_status = 1);
	}
	data->exit_status = 0;
}*/
