/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:53:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/18 13:34:08 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_cmd(t_token_list *token_list)
{
	int				count;
	t_token_list	*current;

	if (!token_list)
		return (0);
	count = 1;
	current = token_list;
	while (current)
	{
		if (current->type == PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

t_pipex	parse_line(char *line, t_token_list *token_list)
{
	t_pipex	pipex;

	t_pipex_init(&pipex, line, token_list);
	if (!pipex.commands)
	{
		ft_putstr_fd(RED"Error: Memory allocation failed\n"RESET, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (pipex);
}

static int	parse_input_loop(char *input, t_token_list *temp, int *index)
{
	temp = temp->next;
	init_token_list(temp);
	temp->token = extract_tokens(input, temp->token, index);
	if (!temp->token)
		return (-1);
	temp->token = parsed_token(temp->token);
	if (!temp->token)
		return (-1);
	temp->type = get_token_type(temp->token);
	return (0);
}

int	parse_input(t_data *data, char *input, t_token_list *token_list)
{
	int				count;
	int				i;
	t_token_list	*temp;
	int				index;

	index = 0;
	if (init_first_value_token_list(input, token_list, &index) == -1)
		return (-1);
	data->input = input;
	count = count_tokens(input);
	if (count > 1)
	{
		i = 0;
		temp = token_list;
		while (++i < count)
		{
			temp->next = malloc(sizeof(t_token_list));
			if (!temp->next)
				return (ft_putstr_fd("Error: Memory allocation failed\n",
						STDERR_FILENO), -1);
			if (parse_input_loop(input, temp, &index) == -1)
				return (free_token_list(token_list), -1);
		}
	}
	return (0);
}
