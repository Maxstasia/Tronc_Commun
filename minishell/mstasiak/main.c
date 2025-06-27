/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:47:05 by jbias             #+#    #+#             */
/*   Updated: 2025/06/27 12:48:08 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static t_token_list	*reinit_token_list(t_token_list *token_list, t_data *data)
{
	if (token_list)
		free_token_list(&token_list);
	token_list = malloc(sizeof(t_token_list));
	if (!token_list)
	{
		ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
		free_data(data);
		exit(1);
	}
	init_token_list(token_list);
	return (token_list);
}

static char	*preprocess_redirection_only(char *line)
{
	char	*trimmed;
	char	*result;
	
	trimmed = line;
	while (*trimmed && (*trimmed == ' ' || *trimmed == '\t'))
		trimmed++;
	if (*trimmed == '>' || *trimmed == '<')
	{
		if (trimmed[0] == '>' && trimmed[1] == '>' && trimmed[2] && trimmed[2] != ' ' && trimmed[2] != '\t')
		{
			result = malloc(ft_strlen(line) + 5);
			if (!result)
				return (NULL);
			ft_strlcpy(result, ": >> ", 6);
			ft_strlcat(result, trimmed + 2, ft_strlen(line) + 5);
		}
		else if (trimmed[0] == '<' && trimmed[1] == '<' && trimmed[2] && trimmed[2] != ' ' && trimmed[2] != '\t')
		{
			result = malloc(ft_strlen(line) + 5);
			if (!result)
				return (NULL);
			ft_strlcpy(result, ": << ", 6);
			ft_strlcat(result, trimmed + 2, ft_strlen(line) + 5);
		}
		else if (trimmed[0] == '>' && trimmed[1] && trimmed[1] != '>' && trimmed[1] != ' ' && trimmed[1] != '\t')
		{
			result = malloc(ft_strlen(line) + 4);
			if (!result)
				return (NULL);
			ft_strlcpy(result, ": > ", 5);
			ft_strlcat(result, trimmed + 1, ft_strlen(line) + 4);
		}
		else if (trimmed[0] == '<' && trimmed[1] && trimmed[1] != '<' && trimmed[1] != ' ' && trimmed[1] != '\t')
		{
			result = malloc(ft_strlen(line) + 4);
			if (!result)
				return (NULL);
			ft_strlcpy(result, ": < ", 5);
			ft_strlcat(result, trimmed + 1, ft_strlen(line) + 4);
		}
		else
		{
			result = malloc(ft_strlen(line) + 3);
			if (!result)
				return (NULL);
			ft_strlcpy(result, ": ", 3);
			ft_strlcat(result, line, ft_strlen(line) + 3);
		}
		return (result);
	}
	return (ft_strdup(line));
}

static int	process_input_line(t_data *data, char *line,
		t_token_list *token_list)
{
	char	*preprocessed_line;
	char	*expanded_line;
	t_pipex	pipex;
	int		syntax_error;

	init_pipex(&pipex);
	preprocessed_line = preprocess_redirection_only(line);
	if (!preprocessed_line)
	{
		ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
		data->exit_status = 1;
		return (free_pipex(&pipex, 0), -1);
	}
	syntax_error = validate_syntax(preprocessed_line);
	if (syntax_error != 0)
		return (free_pipex(&pipex, 0), data->exit_status = syntax_error, 
			free(preprocessed_line), -1);
	expanded_line = expand_variables(preprocessed_line, data);
	if (!expanded_line)
	{
		ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
		data->exit_status = 1;
		return (free_pipex(&pipex, 0), free(preprocessed_line), -1);
	}
	if (parse_input(expanded_line, token_list) != 0)
		return (free(expanded_line), free(preprocessed_line), -1);
	parse_line(expanded_line, token_list, &pipex);
	handle_command_execution(data, token_list, &pipex, expanded_line);
	free_pipex(&pipex, 0);
	return (free(expanded_line), free(preprocessed_line), 0);
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
		line = readline("\001"CYAN"\002maxishell$ \001"RESET"\002");
		if (!line)
		{
			ft_putstr_fd(PINK"exit\n"RESET, STDOUT_FILENO);
			clear_history();
			free_token_list(token_list);
			free_data(data);
			exit(data->exit_status);
		}
		if (*line)
		{
			add_history(line);
			process_input_line(data, line, *token_list);
			*token_list = reinit_token_list(*token_list, data);
			if (ft_strstr(line, "<<"))
				rl_on_new_line();
		}
	}
	exit(data->exit_status);
}

int	main(int ac, char **av, char **envp)
{
	t_data			data;
	t_token_list	*token_list;

	(void)av;
	if (init_minishell(ac, &token_list, &data, envp) != 0)
		return (1);
	using_history();
	main_loop(&data, &token_list);
	return (data.exit_status);
}
