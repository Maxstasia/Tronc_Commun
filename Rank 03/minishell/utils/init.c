/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:30:12 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/24 14:43:24 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_signals(void)
{
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
}

void	init_data(t_data *data, char **envp)
{
	data->envp = init_envp(data, envp);
	if (!data->envp)
		malloc_failed(data);
	data->exit_status = 0;
	data->pwd = getcwd(NULL, 0);
	if (!data->pwd)
		malloc_failed(data);
	data->oldpwd = NULL;
	data->tmp = malloc(sizeof(t_tmp));
	if (!data->tmp)
		malloc_failed(data);
	data->tmp->x = 0;
	data->tmp->y = 0;
	data->saved_stdin = -1;
	data->saved_stdout = -1;
	data->has_saved_fds = 0;
	data->should_exit = 0;
	data->preprocessed_line = NULL;
	data->expanded = NULL;
}

void	init_token_list(t_token_list *token_list)
{
	token_list->token = NULL;
	token_list->type = 0;
	token_list->next = NULL;
}

int	init_first_value_token_list(char *input, t_token_list *token_list,
		int *index)
{
	token_list->token = extract_tokens(input, token_list->token, index);
	if (!token_list->token)
		return (-1);
	token_list->token = parsed_token(token_list->token);
	if (!token_list->token)
		return (-1);
	token_list->type = get_token_type(token_list->token);
	token_list->next = NULL;
	return (0);
}

void	init_pipex(t_pipex *pipex)
{
	if (!pipex)
		return ;
	pipex->commands = NULL;
	pipex->cmd_count = 0;
	pipex->envp = NULL;
	pipex->fd[0] = -1;
	pipex->fd[1] = -1;
	pipex->prev_fd = -1;
	pipex->is_first = 0;
	pipex->is_last = 0;
	pipex->pids = NULL;
}
