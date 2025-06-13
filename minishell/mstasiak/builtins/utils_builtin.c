/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:15:57 by jbias             #+#    #+#             */
/*   Updated: 2025/06/13 11:16:06 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_data *data, t_token_list *token_list, t_cmd *cmd)
{
	if (ft_strcmp(token_list->token, "echo") == 0)
		echo_builtin(cmd, data);
	else if (ft_strcmp(token_list->token, "cd") == 0)
		builtin_cd(cmd->args, data);
	else if (ft_strcmp(token_list->token, "pwd") == 0)
		pwd(data);
	else if (ft_strcmp(token_list->token, "export") == 0)
		ft_export(cmd, data);
	else if (ft_strcmp(token_list->token, "unset") == 0)
		ft_unset(cmd, data);
	else if (ft_strcmp(token_list->token, "env") == 0)
		env(cmd, data);
	else if (ft_strcmp(token_list->token, "exit") == 0)
		exit_builtin(data, cmd);
}
