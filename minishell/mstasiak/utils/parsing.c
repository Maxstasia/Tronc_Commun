/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:53:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/21 14:19:57 by mstasiak         ###   ########.fr       */
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

static int count_tokens(char *input)
{
    int		i = 0;
    int		count = 0;
    char	quote = 0;

    if (!input || !*input)
        return (0);

    while (input[i])
    {
        while (input[i] && ft_isspace(input[i]))
            i++;
        if (!input[i])
            break;
        count++;
        if (input[i] == '\'' || input[i] == '\"')
        {
            quote = input[i];
            i++;
            while (input[i] && input[i] != quote)
                i++;
            if (input[i] == quote)
                i++;
            else
            {
                ft_putstr_fd("maxishell: Parsing error: unclosed quote\n", 2);
                return (-1);
            }
        }
        else
        {
            while (input[i] && !ft_isspace(input[i]) && input[i] != '\'' && input[i] != '\"')
                i++;
        }
    }
    printf(YELLOW"count_Total = %d\n"RESET, count); // Debug
    return (count);
}

static int extract_token(char *input, char **token, int *was_quoted)
{
    int i = 0;
    char quote = 0;
    char *start;
    int len;

    *was_quoted = 0;
    if (!input || !*input)
        return (-1);

    while (input[i] && ft_isspace(input[i]))
        i++;
    start = input + i;
    if (!input[i])
        return (-1);

    if (input[i] == '\'' || input[i] == '\"')
    {
        quote = input[i];
        *was_quoted = 1;
        i++;
        start = input + i; // Début après le guillemet ouvrant
        while (input[i] && input[i] != quote)
            i++;
        if (input[i] != quote)
        {
            ft_putstr_fd("maxishell: Parsing error: unclosed quote\n", 2);
            return (-1);
        }
        len = i - (start - input);
        *token = ft_substr(input, start - input - 1, len + 2); // Inclut les guillemets
        if (!*token)
            return (-1);
        return (i + 1); // Passe le guillemet fermant
    }
    else
    {
        while (input[i] && !ft_isspace(input[i]) && input[i] != '\'' && input[i] != '\"')
            i++;
        len = i - (start - input);
        *token = ft_substr(start, 0, len);
        if (!*token)
            return (-1);
        return (i);
    }
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
	int advance;

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
        advance = extract_token(input + live_index, &data->cmd[i], &data->was_quoted[i]);
        if (advance < 0 || !data->cmd[i])
        {
            free_tab(data->cmd);
            free(data->was_quoted);
            data->cmd = NULL;
            data->was_quoted = NULL;
            return (ft_putstr_fd("maxishell: Parsing error\n", 2), data->exit_status = 1, 1);
        }
        live_index += advance;
        printf("live_index = %d\n", live_index); // Debug
        printf("data->cmd[%d] = %s\n", i, data->cmd[i]); // Debug
        i++;
    }
    data->cmd[i] = NULL;
    free(data->was_quoted);
    data->was_quoted = NULL;
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
