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
	char	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (!quote)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
		else if (input[i] == '|' && !quote)
		{
			printf(YELLOW"DEBUG: Found pipe at position %d\n"RESET, i);
			return (1);
		}
		i++;
	}
	printf(YELLOW"DEBUG: No pipes found in input\n"RESET);
	return (0);
}

static void	execute_builtin_with_redirects(t_data *data,
			t_token_list *token_list, t_pipex *pipex)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (pipex->commands && pipex->commands[0].redirect_count > 0)
	{
		apply_redirects(data, &pipex->commands[0],
			pipex->commands[0].redirects);
	}
	execute_builtin(data, token_list, &pipex->commands[0]);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

static void	exec_pipe(t_pipex *pipex, t_data *data)
{
	execute_pipeline(data, pipex);
	free_pipex(pipex);
}

void	handle_command_execution(t_data *data, t_token_list *token_list,
			t_pipex *pipex, char *expanded_line)
{
	if (!has_pipes(expanded_line))
	{
		if (!token_list->token || ft_strlen(token_list->token) == 0)
		{
			ft_putstr_fd("maxishell: syntax error near unexpected token\n", 2);
			data->exit_status = 2;
		}
		else if (is_builtin(token_list->token))
			execute_builtin_with_redirects(data, token_list, pipex);
		else
		{
			pipex->envp = data->envp;
			if (pipex->commands)
				exec_pipe(pipex, data);
		}
	}
	else
	{
		pipex->envp = data->envp;
		if (pipex->commands)
			exec_pipe(pipex, data);
	}
}
