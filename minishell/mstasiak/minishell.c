/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:02:16 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/18 13:26:54 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	validate_syntax(char *expanded_line)
{
	if (validate_pipe_syntax(expanded_line) != 0)
	{
		ft_putstr_fd("maxishell: erreur de syntaxe « | »\n", 2);
		return (2);
	}
	if (validate_redirection_syntax(expanded_line) != 0)
	{
		if (ft_strstr(expanded_line, ">>")
			&& !has_file_after_redirection(expanded_line, ">>"))
			ft_putstr_fd("maxishell: erreur de syntaxe « newline »\n", 2);
		else if (ft_strstr(expanded_line, ">")
			&& !has_file_after_redirection(expanded_line, ">"))
			ft_putstr_fd("maxishell: erreur de syntaxe « newline »\n", 2);
		else if (ft_strstr(expanded_line, "<<")
			&& !has_file_after_redirection(expanded_line, "<<"))
			ft_putstr_fd("maxishell: erreur de syntaxe « newline »\n", 2);
		else if (ft_strstr(expanded_line, "<")
			&& !has_file_after_redirection(expanded_line, "<"))
			ft_putstr_fd("maxishell: erreur de syntaxe « newline »\n", 2);
		return (2);
	}
	return (0);
}

static int	has_pipes(char *input)
{
	int		i;
	int		len;
	char	quote;

	if (!input)
		return (0);
	len = ft_strlen(input);
	i = 0;
	quote = 0;
	while (i < len)
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (!quote)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
		else if (input[i] == '|' && !quote)
			return (1);
		i++;
	}
	return (0);
}

static void	execute_builtin_with_redirects(t_data *data,
			t_token_list *token_list, t_pipex *pipex)
{
	data->saved_stdout = dup(STDOUT_FILENO);
	data->saved_stdin = dup(STDIN_FILENO);
	data->has_saved_fds = 1;
	if (pipex->commands && pipex->commands[0].redirect_count > 0)
	{
		apply_redirects(data, &pipex->commands[0],
			pipex->commands[0].redirects);
	}
	execute_builtin(data, token_list, &pipex->commands[0]);
	dup2(data->saved_stdout, STDOUT_FILENO);
	dup2(data->saved_stdin, STDIN_FILENO);
	close_saved_fds(data);
}

static int	redirect_input(t_data *data, t_pipex *pipex)
{
	int		i;
	int		saved_stdin;
	char	buffer[1024];

	if (pipex->commands && (!pipex->commands[0].args[0]
			|| !pipex->commands[0].args[0][0]))
	{
		if ((pipex->commands[0].redirect_count > 0))
		{
			saved_stdin = dup(STDIN_FILENO);
			apply_redirects(data, &pipex->commands[0],
				pipex->commands[0].redirects);
			i = -1;
			while (++i < pipex->commands[0].redirect_count)
			{
				if (ft_strcmp(pipex->commands[0].redirects[i].type, "<<") == 0)
					while (read(STDIN_FILENO, buffer, sizeof(buffer)) > 0)
						;
			}
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
			return (data->exit_status = 0, 1);
		}
	}
	return (0);
}

void	handle_command_execution(t_data *data, t_token_list *token_list,
			t_pipex *pipex, char *expanded_line)
{
	if (!has_pipes(expanded_line))
	{
		if (redirect_input(data, pipex) == 1)
			return ;
		if (!token_list->token || ft_strlen(token_list->token) == 0)
		{
			data->exit_status = 0;
			return ;
		}
		else if (is_builtin(token_list->token))
			execute_builtin_with_redirects(data, token_list, pipex);
		else
		{
			pipex->envp = data->envp;
			if (pipex->commands)
				execute_pipeline(data, pipex);
		}
	}
	else
	{
		pipex->envp = data->envp;
		if (pipex->commands)
			execute_pipeline(data, pipex);
	}
}
