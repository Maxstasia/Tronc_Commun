/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:53:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/10 14:58:46 by mstasiak         ###   ########.fr       */
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
	printf(YELLOW"DEBUG: Nombre de commandes : %d\n"RESET, count);
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
	t_token_list *temp;
	int 	index;

	index = 0;
	if (init_first_value_token_list(input, token_list, &index) == -1)
		return (-1);
	data->input = input;
	count = count_tokens(input);
	if (count > 1)
	{
		i = 1;
		temp = token_list;
		printf(YELLOW"DEBUG COUNT = %d ////// i = %d\n"RESET, count, i);
		while (i < count)
		{
			temp->next = malloc(sizeof(t_token_list));
			if (!temp->next)
			{
				ft_putstr_fd(RED"Error: Memory allocation failed\n"RESET, STDERR_FILENO);
				return (-1);
			}
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
	printf(YELLOW"DEBUG: FIN de boucle \n"RESET);
	
	return (0);
}
