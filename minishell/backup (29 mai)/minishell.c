/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:02:16 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/28 21:01:52 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static int has_pipes(const char *input)
{
	int i = 0;
	char quote = 0;
	
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
			return (1);
		i++;
	}
	return (0);
}

int main(int ac, char **av, char **envp)
{
	(void)av;
	t_data data;
	char *line;
	char *expanded_line;
	t_pipex pipex;
	t_token_list *token_list;

	if (ac != 1)
	{
		ft_putstr_fd(RED"Error: ./maxishell takes no arguments\n"RESET, 2);
		return (1);
	}
	token_list = malloc(sizeof(t_token_list));
	if (!token_list)
	{
		ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
		return (1);
	}
	init_token_list(token_list);
	init_signals();
	init_data(&data, envp);
	while (1)
	{
		line = readline(CYAN"maxishell$ "RESET);
		if (!line)
		{
			ft_putstr_fd(PINK"exit\n"RESET, STDOUT_FILENO);
			free_data(&data);
			break;
		}
		if (*line)
		{
			add_history(line);
			expanded_line = expand_variables(line, &data);
			if (!expanded_line)
			{
				ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
				free(line);
				data.exit_status = 1;
				continue;
			}
			pipex = parse_line(expanded_line, token_list);
			if (!has_pipes(expanded_line))
			{
				if (parse_input(&data, expanded_line, token_list) == 0)
				{
					if (is_builtin(token_list->token))
						execute_builtin(&data, token_list, &pipex.commands[0]);
					else
					{
						pipex.envp = data.envp;
						if (pipex.commands)
						{
							execute_pipeline(&data, &pipex);
							free_pipex(&pipex);
						}
					}
					free_token_list(token_list);
					token_list = malloc(sizeof(t_token_list));
					if (!token_list)
					{
						ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2);
						free_data(&data);
						exit(1);
					}
					init_token_list(token_list);
				}
			}
			else
			{
				pipex.envp = data.envp;
				if (pipex.commands)
				{
					execute_pipeline(&data, &pipex);
					free_pipex(&pipex);
				}
			}
			free(expanded_line);
		}
		free(line);
	}
	return (data.exit_status);
}
