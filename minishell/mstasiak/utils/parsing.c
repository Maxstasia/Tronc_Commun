/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:53:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/02 15:53:20 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int count_tokens(char *input)
{
	int i;
	int count;
	char quote;
	
	count = 0;
	i = 0;
	if (!input || !*input)
		return (0);
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (!input[i])
			break;
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (input[i] == quote)
				i++;
			else
				return (count);
		}
		else
			while (input[i] && !ft_isspace(input[i]))
		i++;
		count++;
	}
	return (count);
}

static int extract_token(char *input, char **token)
{
	int i;
	char quote;
	char *start;
	
	i = 0;
	if (!input || !*input)
		return (-1);
	while (input[i] && ft_isspace(input[i]))
		i++;
	start = input + i;
	if (input[i] == '\'' || input[i] == '"')
	{
		quote = input[i++];
		start = input + i;
		while (input[i] && input[i] != quote)
			i++;
		if (!input[i])
			return (-1);
		*token = ft_substr(start, 0, i - (start - input));
		if (!*token)
			return (-1);
		return (i + 1);
	}
	while (input[i] && !ft_isspace(input[i]))
		i++;
	*token = ft_substr(start, 0, i);
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

int parse_input(t_data *data, char *input)
{
	int i;
	int live_index;
	int count;
	
	if (!input || !*input)
		return (free_tab(data->cmd), data->cmd = NULL, 0);
	free_tab(data->cmd);
	data->cmd = NULL;
	count = count_tokens(input);
	data->cmd = malloc(sizeof(char *) * (count + 1));
	if (!data->cmd)
		return (ft_putstr_fd(RED"maxishell: malloc failed\n"RESET, 2), data->exit_status = 1, 1);
	i = 0;
	live_index = 0;
	while (i < count)
	{
		live_index += extract_token(input + live_index, &data->cmd[i]);
		if (live_index < 0 || !data->cmd[i])
		{
			free_tab(data->cmd);
			data->cmd = NULL;
			return (ft_putstr_fd(RED"maxishell: Parsing error\n"RESET, 2), data->exit_status = 1, 1);
		}
		i++;
	}
	data->cmd[i] = NULL;
	return (0);
}
