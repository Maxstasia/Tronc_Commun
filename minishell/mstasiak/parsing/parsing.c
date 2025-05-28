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

int count_cmd(t_token_list *token_list)
{
	if (!token_list)
		return 0;
	int count = 1;
	t_token_list *current = token_list;
	while (current)
	{
		if (current->type == PIPE)
			count++;
		current = current->next;
	}
	return count;
}

/*static int *count_tokens_in_cmd(t_token_list *token_list)
{
	int i;
	int *count;
	int j;
	
	count = malloc(sizeof(int) * count_cmd(token_list));
	if (!count)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	j = 0;
	i = 0;
	while (token_list)
	{
		if (token_list->type == PIPE)
		{
			count[j] = i;
			j++;
			i = 0;
		}
		else
			i++;
		token_list = token_list->next; 
	}
	count[j] = i;
	return (count);
}*/

t_pipex parse_line(char *line, t_token_list *token_list)
{
	t_pipex pipex;

	/*	int count;
	int		i;
	int		j;
	int *tokens_in_cmd;
	t_token_list *current;

	current = token_list;
	init_token_list(current);
	j = 0;
	tokens_in_cmd = count_tokens_in_cmd(token_list);
	if (!tokens_in_cmd)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	i = 0;
	count = count_tokens(line);*/
	t_pipex_init(&pipex, line, token_list);
	if (!pipex.commands)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	/*while (i < pipex.cmd_count)
	{
		pipex.commands[i].args = malloc(sizeof(char *) * (tokens_in_cmd[i] + 1));
		if (!pipex.commands[i].args)
		{
			ft_putstr_fd("Error: Memory allocation failed\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		while (j < tokens_in_cmd[i])
		{
			printf("current token: %s\n", current->token);
			pipex.commands[i].args[j] = ft_strdup(current->token);
			if (!pipex.commands[i].args[j])
			{
				ft_putstr_fd("Error: Memory allocation failed\n", STDERR_FILENO);
				exit(EXIT_FAILURE);
			}
			j++;
			current = current->next;
		}
		pipex.commands[i].args[j] = NULL; // Terminate the args array
		if (current && current->type == PIPE)
			current = current->next; // Skip the pipe token
		i++;
		j = 0;
	}*/
	return (pipex);
}

int	parse_input(t_data *data, char *input, t_token_list *token_list)
{
	int		count;
	int		i;
	int		index;
	int		j;

	data->input = input;
	i = 0;
	j = 0;
	index = 0;
	count = count_tokens(input);	
	while (i < count)
	{
		token_list->token = extract_tokens(input, token_list->token);
		if (!token_list->token)
			return (-1);
		index = get_index(input, i);
		while (j++ < index)
			input++;
		token_list->token = parsed_token(token_list->token);
		if (!token_list->token)
			return (-1);
		token_list->type = get_token_type(token_list->token);
		init_next(token_list);
		i++;
	}
	return (0);
}
