/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:02:16 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/03 17:36:05 by mstasiak         ###   ########.fr       */
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
	int saved_stdout;
	int saved_stdin;

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
					// Vérifier qu'il y a une commande à exécuter
					if (!token_list->token || ft_strlen(token_list->token) == 0)
					{
						ft_putstr_fd("maxishell: syntax error near unexpected token\n", 2);
						data.exit_status = 2;
					}
					else if (is_builtin(token_list->token))
					{
						// Sauvegarder les descripteurs originaux
						saved_stdout = dup(STDOUT_FILENO);
						saved_stdin = dup(STDIN_FILENO);
						// Appliquer les redirections si elles existent
						if (pipex.commands && pipex.commands[0].redirect_count > 0)
						{
							apply_redirects(&data, &pipex.commands[0]);
						}
						// Exécuter le builtin
						execute_builtin(&data, token_list, &pipex.commands[0]);
						// Restaurer les descripteurs originaux
						dup2(saved_stdout, STDOUT_FILENO);
						dup2(saved_stdin, STDIN_FILENO);
						close(saved_stdout);
						close(saved_stdin);
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
