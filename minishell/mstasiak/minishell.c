/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:02:16 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/02 14:09:16 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void init_signals(void)
{
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
}

void free_pipex(t_pipex *pipex)
{
	int i;
	
	i = 0;
	while (pipex->commands[i].args)
	{
		free_cmd(&pipex->commands[i]);
		i++;
	}
	free(pipex->commands);
}

void free_data(t_data *data)
{
	int i;
	
	i = 0;
	if (data->envp)
	{
		while (data->envp[i])
			free(data->envp[i++]);
		free(data->envp);
	}
	if (data->cmd)
		free_tab(data->cmd);
	if (data->pwd)
		free(data->pwd);
	if (data->oldpwd)
		free(data->oldpwd);
}

void init_data(t_data *data, char **envp)
{
	data->envp = copy_envp(envp);
	if (!data->envp)
	{
		ft_putstr_fd(RED"maxishell: envp copy failed\n"RESET, 2);
		exit(EXIT_FAILURE);
	}
	data->cmd = NULL;
	data->exit_status = 0;
	data->pwd = getcwd(NULL, 0);
	if (!data->pwd)
	{
		ft_putstr_fd(RED"maxishell: getcwd failed\n"RESET, 2);
		exit(EXIT_FAILURE);
	}
	data->oldpwd = NULL;
}

char **copy_envp(char **envp)
{
	int i;
	char **new_envp;
	
	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	if (!new_envp)
		return (NULL);
	i = -1;
	while (++i, envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			free_tab(new_envp);
			return (NULL);
		}
	}
	new_envp[i] = NULL;
	return (new_envp);
}

static int has_pipes(const char *input)
{
	int i = 0;
	char quote = 0;
	
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
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
	
	if (ac != 1)
	{
		ft_putstr_fd(RED"Error: ./maxishell takes no arguments\n"RESET, 2);
		return (1);
	}
	init_signals();
	init_data(&data, envp);
	while (1)
	{
		line = readline(CYAN"maxishell$ "RESET);
		if (!line)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
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
				data.exit_status = 1;
				free(line);
				continue;
			}
			if (!has_pipes(expanded_line))
			{
				if (parse_input(&data, expanded_line) == 0 && data.cmd)
				{
					if (ft_strcmp(data.cmd[0], "echo") == 0)
						echo_builtin(&data);
					else if (ft_strcmp(data.cmd[0], "cd") == 0)
						builtin_cd(data.cmd, &data);
					else if (ft_strcmp(data.cmd[0], "pwd") == 0)
						pwd(&data);
					else if (ft_strcmp(data.cmd[0], "export") == 0)
						ft_export(&data);
					else if (ft_strcmp(data.cmd[0], "unset") == 0)
						ft_unset(&data);
					else if (ft_strcmp(data.cmd[0], "env") == 0)
						env(&data);
					else if (ft_strcmp(data.cmd[0], "exit") == 0)
						exit_builtin(&data);
					else
					{
						pipex = parse_line(expanded_line);
						pipex.envp = data.envp;
						if (pipex.commands)
						{
							execute_pipeline(&data, &pipex);
							free_pipex(&pipex);
						}
					}
					free_tab(data.cmd);
					data.cmd = NULL;
				}
			}
			else
			{
				pipex = parse_line(expanded_line);
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
