/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:47:05 by jbias             #+#    #+#             */
/*   Updated: 2025/06/17 12:47:05 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	execute_builtin_with_redirects(t_data *data,
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

static int	process_input_line(t_data *data, char *line,
		t_token_list *token_list)
{
	char	*expanded_line;
	t_pipex	pipex;
	int		syntax_error;

	expanded_line = expand_variables(line, data);
	printf(YELLOW"DEBUG: Expanded line: '%s'\n"RESET, expanded_line);
	if (!expanded_line)
	{
		ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
		data->exit_status = 1;
		return (-1);
	}
	syntax_error = validate_syntax(expanded_line);
	if (syntax_error != 0)
	{
		data->exit_status = syntax_error;
		return (free(expanded_line), -1);
	}
	if (parse_input(data, expanded_line, token_list) != 0)
		return (free(expanded_line), -1);
	pipex = parse_line(expanded_line, token_list);
	printf(YELLOW"DEBUG: Parsed commands count: %d\n"RESET, pipex.cmd_count);
	handle_command_execution(data, token_list, &pipex, expanded_line);
	return (free(expanded_line), 0);
}

static int	init_minishell(int ac, t_token_list **token_list,
		t_data *data, char **envp)
{
	if (ac != 1)
	{
		ft_putstr_fd(RED"Error: ./maxishell takes no arguments\n"RESET, 2);
		return (1);
	}
	*token_list = malloc(sizeof(t_token_list));
	if (!*token_list)
	{
		ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
		return (1);
	}
	init_token_list(*token_list);
	init_signals();
	init_data(data, envp);
	return (0);
}

static void	main_loop(t_data *data, t_token_list **token_list)
{
	char	*line;

	while (1)
	{
		line = readline(CYAN"maxishell$ "RESET);
		if (!line)
		{
			ft_putstr_fd(PINK"exit\n"RESET, STDOUT_FILENO);
			free_data(data);
			break ;
		}
		if (*line)
		{
			add_history(line);
			if (process_input_line(data, line, *token_list) == 0)
				*token_list = reinit_token_list(*token_list, data);
		}
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data			data;
	t_token_list	*token_list;

	(void)av;
	if (init_minishell(ac, &token_list, &data, envp) != 0)
		return (1);
	main_loop(&data, &token_list);
	return (data.exit_status);
}
