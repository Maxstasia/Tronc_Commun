/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:35:48 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/18 12:45:21 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

char	**add_envp(char **news, char **envp, const char *name, const char *val)
{
	int		i;

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

void	update_env_var(char **envp, const char *name, const char *value)
{
	int		i;
	size_t	len;
	char	**new_var;

	i = 0;
	len = ft_strlen(name);
	while ((envp)[i])
	{
		if (ft_strncmp((envp)[i], name, len) == 0 && (envp)[i][len] == '=')
		{
			free((envp)[i]);
			(envp)[i] = new_envp(name, value);
			if (!(*envp)[i])
				return ;
			return ;
		}
		i++;
	}
	new_var = ft_calloc(i + 2, sizeof(char *));
	if (!new_var)
		return ;
	if (!add_envp(new_var, envp, name, value))
		return (free_tab(new_var));
	free(envp);
	envp = new_var;
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
