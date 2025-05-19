/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:53:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/06 18:06:41 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	ft_cleanup(t_data *data)
{
	if (data->cmd)
	{
		free_tab(data->cmd);
		data->cmd = NULL;
	}
	if (data->envp)
	{
		free_tab(data->envp);
		data->envp = NULL;
	}
	if (data->pwd)
	{
		free(data->pwd);
		data->pwd = NULL;
	}
	if (data->oldpwd)
	{
		free(data->oldpwd);
		data->oldpwd = NULL;
	}
}

static int 	count_tokens(char *input)
{
	int		i;
	int		j;
	int		count;
	char	quote;
	int		quotes_nb;
	
	quotes_nb = 0;
	count = 0;
	i = 0;
	j = 0;
	if (!input || !*input)
		return (0);
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		while (input[i] && !ft_isspace(input[i]))
		{
			if (input[i] == '\'' || input[i] == '\"')
			{
				quote = input[i++];
				quotes_nb++;
				j = i;
				while (input[j] && (input[j] != quote))
					j++;
				if (input[j] == quote)
				{
					quotes_nb++;
					count++;
				}
				if (input[j] == '\0' && (quotes_nb % 2 != 0))
					return (ft_putstr_fd("maxishell: Parsing error\n", 2), -1);

				if (input[j] == quote && input[j + 1] && !ft_isspace(input[j + 1]))
					count--;
				i = j + 1;
			}
			else
			{
				count++;
				while (input[i] && (!ft_isspace(input[i]) || input[i] == '\'' || input[i] == '\"'))
					i++;
			}
		}
	}
	printf("count_Total = %d\n", count); // Debug
	return (count);
}

static int	extract_token(char *input, char **token, int *was_quoted)
{
	int		i;
	char	quote;
	char	*start;
	int		len;
	int		quotes_nb;

	*was_quoted = 0;
	quotes_nb = 0;
	i = 0;
	if (!input || !*input)
		return (-1);
	while (input[i] && ft_isspace(input[i]))
		i++;
	start = input + i;
	if (input[i] == '\'' || input[i] == '\"')
	{
		quotes_nb++;
		quote = input[i++];
		start = input + i;
		while (input[i] && (input[i] != quote))
		{
			i++;
			if (input[i] == quote && input[i + 1] == quote)
			{
				i += 2;
				quotes_nb += 2;
				while ((input[i] && input[i] != quote) || ft_isspace(input[i]))
				{	
					i++;
					if (input[i] == quote)
					{
						quotes_nb++;
						i++;
					}
				}
				if (quotes_nb % 2 == 0)
				{
					if (ft_isspace(input[i]))
						break;
				}
			}
			
			else if (input[i] == quote && input[i + 1] && !ft_isspace(input[i + 1]))
			{
				i++;
				quotes_nb++;
			}
		}
		printf("test\n"); // Debug
		//if (!input[i])
		//	return (-1);
		printf("debug\n"); // Debug
		if (input[i] == quote || quotes_nb % 2 == 0)
			*was_quoted = 1;
		printf("debug2\n"); // Debug
		*token = ft_substr_quotes(start, 0, i - (start - input), quote);
		if (!*token)
			return (-1);
		return (i + 1);
	}
	while (input[i] && !ft_isspace(input[i]))
		i++;
	len = i - (start - input);
	while (len > 0 && ft_isspace(input[len - 1]))
		len--;
	*token = ft_substr(start, 0, len);
	if (!*token)
		return (-1);
	return (i); 
}

t_pipex parse_line(const char *line)
{
	t_pipex pipex;

	pipex.commands = ft_split_advanced(line);
	pipex.cmd_count = 0;
	while (pipex.commands[pipex.cmd_count].args)
		pipex.cmd_count++;
	pipex.envp = NULL;
	pipex.prev_fd = -1;
	pipex.is_first = 0;
	pipex.is_last = 0;
	pipex.pids = NULL;
	return (pipex);
}

int	parse_input(t_data *data, char *input)
{
	int	i;
	int	live_index;
	int	count;

	if (!input || !*input)
		return (free_tab(data->cmd), data->cmd = NULL, 0);
	free_tab(data->cmd);
	data->cmd = NULL;
	count = count_tokens(input);
	if (count < 0)
		return (data->exit_status = 1, 1);
	data->was_quoted = (int *)malloc(sizeof(int) * count);
	data->cmd = malloc(sizeof(char *) * (count + 1));
	if (!data->cmd || !data->was_quoted)
		return (ft_putstr_fd("maxishell: malloc failed\n", 2), data->exit_status = 1, 1);
	i = 0;
	live_index = 0;
	while (i < count)
	{
		live_index += extract_token(input + live_index, &data->cmd[i], &data->was_quoted[i]) + 1;
		printf("live_index = %d\n", live_index); // Debug
		printf("data->cmd[%d] = %s\n", i, data->cmd[i]); // Debug
		if (live_index < 0 || !data->cmd[i])
		{
			free_tab(data->cmd);
			data->cmd = NULL;
			printf("%s", __func__); // Debug
			return (ft_putstr_fd("maxishell: Parsing error, %s\n", 2), data->exit_status = 1, 1);
		}
		i++;
	}
	data->cmd[i] = NULL;
	return (0);
}

void	minishell_loop(t_data *data)
{
	char	*input;

	while (1)
	{
		input = readline("maxishell$ ");
		if (!input)
		{
			ft_cleanup(data);
			break;
		}
		if (*input)
			add_history(input);
		if (parse_input(data, input) == 0 && data->cmd)
		{
			if (ft_strcmp(data->cmd[0], "unset") == 0)
				ft_unset(data);
			else if (ft_strcmp(data->cmd[0], "cd") == 0)
				builtin_cd(data->cmd, data);
			else if (ft_strcmp(data->cmd[0], "export") == 0)
				ft_export(data);
			else if (ft_strcmp(data->cmd[0], "echo") == 0)
				echo_builtin(data);
			else if (ft_strcmp(data->cmd[0], "pwd") == 0)
				pwd(data);
			else if (ft_strcmp(data->cmd[0], "env") == 0)
				env(data);
			else if (ft_strcmp(data->cmd[0], "exit") == 0)
				exit_builtin(data);
		}
		free_tab(data->cmd);
		data->cmd = NULL;
		free(input);
	}
}
