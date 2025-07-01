/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:02:16 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/01 16:46:58 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void	execute_builtin_with_redirects(t_data *data,
			t_token_list *token_list, t_pipex *pipex)
{
	int	redir_error;

	data->saved_stdout = dup(STDOUT_FILENO);
	data->saved_stdin = dup(STDIN_FILENO);
	data->has_saved_fds = 1;
	redir_error = 0;
	if (pipex->commands && pipex->commands[0].redirect_count > 0)
	{
		redir_error = apply_redirects(data, &pipex->commands[0],
				pipex->commands[0].redirects);
	}
	if (redir_error == 0)
		execute_builtin(data, token_list, &pipex->commands[0]);
	else
		data->exit_status = redir_error;
	dup2(data->saved_stdout, STDOUT_FILENO);
	dup2(data->saved_stdin, STDIN_FILENO);
	close_saved_fds(data);
}

static void	norm_redirect_input(t_pipex *pipex)
{
	int		i;

	i = -1;
	while (++i < pipex->commands[0].redirect_count)
		if (ft_strcmp(pipex->commands[0].redirects[i].type, "<<") == 0)
			break ;
}

static int	redirect_input(t_data *data, t_pipex *pipex)
{
	int		saved_stdin;
	int		redir_error;

	if (pipex->commands && (!pipex->commands[0].args[0]
			|| !pipex->commands[0].args[0][0]))
	{
		if ((pipex->commands[0].redirect_count > 0))
		{
			saved_stdin = dup(STDIN_FILENO);
			if (preprocess_all_heredocs(data, pipex) == -1)
				return (dup2(saved_stdin, STDIN_FILENO), close(saved_stdin),
					data->exit_status = 1, 1);
			redir_error = apply_redirects_no_heredoc(data, &pipex->commands[0],
					pipex->commands[0].redirects);
			if (redir_error != 0)
				return (dup2(saved_stdin, STDIN_FILENO), close(saved_stdin),
					data->exit_status = redir_error, 1);
			norm_redirect_input(pipex);
			return (dup2(saved_stdin, STDIN_FILENO),
				close(saved_stdin), data->exit_status = 0, 1);
		}
	}
	return (0);
}

static int	handle_command_execution_norm(t_data *data,
				t_token_list *token_list, t_pipex *pipex)
{
	if (redirect_input(data, pipex) == 1)
		return (-1);
	if (!token_list->token || ft_strlen(token_list->token) == 0)
	{
		if (g_signal_exit_status == 0)
			data->exit_status = 0;
		return (-1);
	}
	else if (is_builtin(token_list->token))
		execute_builtin_with_redirects(data, token_list, pipex);
	else
	{
		pipex->envp = data->envp;
		if (pipex->commands)
			execute_pipeline(data, pipex);
	}
	return (0);
}

void	handle_command_execution(t_data *data, t_token_list *token_list,
			t_pipex *pipex, char *expanded_line)
{
	if (!has_pipes(expanded_line))
	{
		if (handle_command_execution_norm(data, token_list, pipex) == -1)
			return ;
	}
	else
	{
		if (all_commands_empty(pipex))
		{
			if (preprocess_all_heredocs(data, pipex) == -1)
				data->exit_status = 1;
			else if (g_signal_exit_status == 0)
				data->exit_status = 0;
			return ;
		}
		pipex->envp = data->envp;
		if (pipex->commands)
			execute_pipeline(data, pipex);
	}
}
