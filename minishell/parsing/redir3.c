/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:49:30 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/01 16:51:15 by mstasiak         ###   ########.fr       */
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

char	set_quote(char *input, int i, char quote)
{
	if (input[i] == '\'' || input[i] == '\"')
	{
		if (!quote)
			quote = input[i];
		else if (quote == input[i])
			quote = 0;
	}
	return (quote);
}
