/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:28:18 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/13 14:39:05 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_pipex	parse_line(char *line, t_token_list *token_list)
{
	t_pipex	pipex;

	t_pipex_init(&pipex, line, token_list);
	if (!pipex.commands)
	{
		error_malloc();
		exit(EXIT_FAILURE);
	}
	return (pipex);
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
		i = 1;
		temp = token_list;
		while (i < count)
		{
			temp->next = malloc(sizeof(t_token_list));
			if (!temp->next)
				return (error_malloc(), -1);
			temp = temp->next;
			init_token_list(temp);
			temp->token = extract_tokens(input, temp->token, &index);
			if (!temp->token)
				return (-1);
			temp->token = parsed_token(temp->token);
			if (!temp->token)
				return (-1);
			temp->type = get_token_type(temp->token);
			i++;
		}
	}
	return (0);
}
