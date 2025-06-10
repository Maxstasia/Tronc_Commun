#include "../include/minishell.h"

char **copy_envp(char **envp)
{
	int i;
	char **new_envp;
	
	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	if (!new_envp)
		return (NULL);
	i = -1;
	while (++i, envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			free_tab(new_envp);
			return (NULL);
		}
	}
	new_envp[i] = NULL;
	return (new_envp);
}

char *new_envp(const char *name, const char *value)
{
	char *tmp;
	char *new_envp;
	
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

char **add_envp(char **news, char **envp, const char *name, const char *val)
{
	int i;
	
	i = 0;
	while (envp[i])
	{
		news[i] = ft_strdup(envp[i]);
		if (!news[i])
			return (free_tab(news), NULL);
		i++;
	}
	news[i] = new_envp(name, val);
	if (!news[i])
		return (free_tab(news), NULL);
	i++;
	news[i] = NULL;
	return (news);
}
