/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:53:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/13 14:32:23 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	has_file_after_redirection(const char *input, const char *redir)
{
	char	*pos;

	pos = ft_strstr(input, redir);
	if (!pos)
		return (1);
	pos += ft_strlen(redir);
	while (*pos && (*pos == ' ' || *pos == '\t'))
		pos++;
	if (!*pos || *pos == '|' || *pos == '<' || *pos == '>')
		return (0);
	return (1);
}

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
