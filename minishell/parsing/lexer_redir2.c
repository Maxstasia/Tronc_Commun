/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:37:19 by jbias             #+#    #+#             */
/*   Updated: 2025/06/30 20:37:21 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*redir_in_case(char *current, int *i)
{
	char	*temp;

	temp = add_space_after_redir(current, *i, 1);
	if (!temp)
		return (free(current), NULL);
	free(current);
	(*i) += 1;
	return (temp);
}

char	*redir_out_case(char *current, int *i)
{
	char	*temp;

	temp = add_space_after_redir(current, *i, 1);
	if (!temp)
		return (free(current), NULL);
	free(current);
	(*i) += 1;
	return (temp);
}

char	*heredoc_case(char *current, int *i)
{
	char	*temp;

	temp = add_space_after_redir(current, *i, 2);
	if (!temp)
		return (free(current), NULL);
	free(current);
	(*i) += 2;
	return (temp);
}

char	*append_case(char *current, int *i)
{
	char	*temp;

	temp = add_space_after_redir(current, *i, 2);
	if (!temp)
		return (free(current), NULL);
	free(current);
	(*i) += 2;
	return (temp);
}

char	*redir_loop(char *current, int *i)
{
	char	*result;

	result = handle_single_redirects(current, i);
	if (result)
		return (result);
	result = handle_double_redirects(current, i);
	if (result)
		return (result);
	skip_redirects(current, i);
	return (current);
}
