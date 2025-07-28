/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:39:14 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/03 18:51:23 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	malloc_failed(t_data *data)
{
	ft_putstr_fd(RED"minishell: malloc failed\n"RESET, 2);
	if (data)
	{
		data->exit_status = EXIT_FAILURE;
		free_data(data);
	}
	exit(EXIT_FAILURE);
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->args)
		free_tab(cmd->args);
	if (cmd->redirects)
	{
		while (i < cmd->redirect_count)
		{
			free(cmd->redirects[i].type);
			free(cmd->redirects[i].file);
			if (cmd->redirects[i].is_heredoc_fd > 0)
				close(cmd->redirects[i].is_heredoc_fd);
			i++;
		}
		free(cmd->redirects);
	}
}

void	error_127(t_data *data, char *path, t_pipex *pipex, t_token_list *tok)
{
	ft_putstr_fd(RED"minishell: '"YELLOW, 2);
	if (pipex->commands && pipex->commands->args && pipex->commands->args
		&& pipex->commands->args[0])
		ft_putstr_fd(pipex->commands->args[0], 2);
	ft_putstr_fd(RED"' : command not found\n"RESET, 2);
	if (path)
		free(path);
	if (data)
		data->exit_status = 127;
	if (data)
		free_data(data);
	if (pipex)
		free_pipex(pipex, 0);
	if (tok)
		free_token_list(&tok);
	exit(127);
}

void	error(t_data *data)
{
	perror(RED"minishell: error");
	if (data)
		data->exit_status = 1;
	exit(1);
}
