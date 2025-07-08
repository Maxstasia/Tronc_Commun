/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_advanced3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:36:49 by jbias             #+#    #+#             */
/*   Updated: 2025/07/03 00:27:07 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	cmd_mem_norm(t_cmd *cmd, int cmd_count)
{
	int	j;

	j = 0;
	while (j < cmd_count)
	{
		cmd->redirects[j].type = NULL;
		cmd->redirects[j].file = NULL;
		cmd->redirects[j].is_heredoc_fd = 0;
		j++;
	}
}

int	allocate_cmd_memory(t_cmd *cmd, char *s, int i)
{
	int		j;
	int		token_count;

	j = 0;
	cmd->args = NULL;
	cmd->redirects = NULL;
	token_count = count_token_split(s + i);
	if (token_count == -1)
		return (-1);
	cmd->args = malloc(sizeof(char *) * (token_count + 5));
	if (!cmd->args)
		return (-1);
	while (j <= token_count + 4)
	{
		cmd->args[j] = NULL;
		j++;
	}
	cmd->redirects = malloc(sizeof(t_redirect) * (token_count + 5));
	if (!cmd->redirects)
		return (free(cmd->args), cmd->args = NULL, -1);
	cmd_mem_norm(cmd, token_count + 5);
	cmd->redirect_count = 0;
	return (0);
}

static int	is_separator(char c, char quote)
{
	if (quote)
		return (0);
	if (c == ' ' || c == '\t' || c == '|')
		return (1);
	return (0);
}

static int	extract_token_loop(char *input, char quote, int *i)
{
	if (input[*i] == '\'' || input[*i] == '\"')
	{
		quote = input[(*i)++];
		while (input[*i] && input[*i] != quote)
			(*i)++;
		if (!input[*i])
		{
			ft_putstr_fd("Error: Unmatched quotes\n", 2);
			return (-1);
		}
		else
			(*i)++;
	}
	else
		(*i)++;
	return (0);
}

int	extract_token_split(char *input, int *i, char **token)
{
	int		start;
	int		end;
	char	quote;

	quote = 0;
	*token = NULL;
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		(*i)++;
	start = *i;
	if (!input[*i])
		return (-1);
	while (input[*i] && !is_separator(input[*i], 0))
	{
		if (extract_token_loop((char *)input, quote, i) == -1)
			return (-1);
	}
	end = *i;
	if (start == end)
		return (-1);
	*token = ft_substr(input, start, end - start);
	if (!*token)
		return (-1);
	return (end - start);
}
