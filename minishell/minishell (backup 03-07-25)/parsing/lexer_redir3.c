/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:47:08 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/01 16:47:09 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*handle_single_redirects(char *current, int *i)
{
	if (current[*i] == '<' && current[*i + 1] && current[*i + 1] != '<'
		&& current[*i + 1] != ' ' && current[*i + 1] != '\t')
	{
		return (redir_in_case(current, i));
	}
	else if (current[*i] == '>' && current[*i + 1] && current[*i + 1] != '>'
		&& current[*i + 1] != ' ' && current[*i + 1] != '\t')
	{
		return (redir_out_case(current, i));
	}
	return (NULL);
}

char	*handle_double_redirects(char *current, int *i)
{
	if (current[*i] == '<' && current[*i + 1] == '<'
		&& current[*i + 2] && current[*i + 2] != ' '
		&& current[*i + 2] != '\t')
	{
		return (heredoc_case(current, i));
	}
	else if (current[*i] == '>' && current[*i + 1] == '>'
		&& current[*i + 2] && current[*i + 2] != ' '
		&& current[*i + 2] != '\t')
	{
		return (append_case(current, i));
	}
	return (NULL);
}

void	skip_redirects(char *current, int *i)
{
	if (current[*i] == '<' && current[*i + 1] == '<')
		(*i) += 2;
	else if (current[*i] == '>' && current[*i + 1] == '>')
		(*i) += 2;
	else if (current[*i] == '<' || current[*i] == '>')
		(*i) += 1;
	else
		(*i) += 1;
}
