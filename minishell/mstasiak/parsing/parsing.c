/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:53:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/28 15:38:57 by mstasiak         ###   ########.fr       */
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

t_pipex parse_line(char *line, t_token_list *token_list)
{
	t_pipex pipex;

	t_pipex_init(&pipex, line, token_list);
	if (!pipex.commands)
	{
		ft_putstr_fd(RED"Error: Memory allocation failed\n"RESET, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (pipex);
}

int	parse_input(t_data *data, char *input, t_token_list *token_list)
{
	int		count;
	int		i;
	t_token_list *current;

	if (init_first_value_token_list(input, token_list) == -1)
		return (-1);
	data->input = input;
	count = count_tokens(input);
	if (count > 1)
	{
		i = 1;
		input += ft_strlen(token_list->token);
		current = token_list;
		while (i < count)
		{
			printf(YELLOW"DEBUG: data->input: %s, input: %s, i = %i, count = %i\n"RESET, data->input, input, i, count); // DEBUG
			printf(YELLOW"DEBUG: token_list->token: %s, token_list->type : %i\n"RESET, token_list->token, token_list->type); // DEBUG
			current->next = malloc(sizeof(t_token_list));
			if (!current->next)
			{
				ft_putstr_fd(RED"Error: Memory allocation failed\n"RESET, STDERR_FILENO);
				return (-1);
			}
			current = current->next;
			init_token_list(current);
			current->token = extract_tokens(input, current->token);
			if (!current->token)
				return (-1);
			current->token = parsed_token(current->token);
			if (!current->token)
				return (-1);
			current->type = get_token_type(current->token);
			i++;
			input += ft_strlen(current->token);
		}
		printf(YELLOW"DEBUG: data->input: %s, input: %s, i = %i, count = %i\n"RESET, data->input, input, i, count); // DEBUG
		printf(YELLOW"DEBUG: token_list->token: %s, token_list->type : %i, token_list->next->token : %s\n"RESET, token_list->token, token_list->type, token_list->next->token); // DEBUG
	}
	printf(YELLOW"DEBUG: FIN de boucle \n"RESET); // DEBUG
	
	return (0);
}
