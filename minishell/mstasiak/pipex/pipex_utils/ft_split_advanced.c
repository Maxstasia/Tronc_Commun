/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_advanced.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:38:10 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/18 16:47:27 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int is_separator(char c, char quote)
{
	if (quote)
		return (0);
	if (c == ' ' || c == '\t' || c == '|')
		return (1);
	return (0);
}

static int is_redirect(char *str)
{
	return (ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">") == 0 ||
		ft_strcmp(str, "<<") == 0 || ft_strcmp(str, ">>") == 0);
}

static int count_tokens(const char *input)
{
	int i = 0;
	int count = 0;
	char quote = 0;

	if (!input || !*input)
		return (0);
	while (input[i])
	{
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		if (!input[i])
			break;
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (input[i] == quote)
				i++;
			else
				return (count);
		}
		else
			while (input[i] && !is_separator(input[i], quote))
				i++;
		count++;
	}
	return (count);
}

static int extract_token(const char *input, int *i, char **token)
{
	int j = 0;
	char quote = 0;
	const char *start = input + *i;

	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		(*i)++;
	start = input + *i;
	if (!input[*i])
		return (-1);
	if (input[*i] == '\'' || input[*i] == '\"')
	{
		quote = input[(*i)++];
		start = input + *i;
		while (input[*i] && input[*i] != quote)
			(*i)++;
		if (!input[*i])
			return (-1);
		j = *i - (start - input);
		*token = ft_substr(start, 0, j);
		if (!*token)
			return (-1);
		(*i)++;
		return (j + 2);
	}
	while (input[*i] && !is_separator(input[*i], quote))
		(*i)++;
	j = *i - (start - input);
	*token = ft_substr(start, 0, j);
	if (!*token)
		return (-1);
	return (j);
}

static void free_cmds(t_cmd *cmd, int j)
{
	while (j > 0)
	{
		j--;
		free_cmd(&cmd[j]);
	}
	free(cmd);
}

t_cmd *ft_split_advanced(const char *s)
{
	t_cmd *result;
	int i, j, k, token_len;
	
	if (!s)
		return (NULL);
	result = malloc(sizeof(t_cmd) * 256);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (!s[i])
			break;
		result[j].args = malloc(sizeof(char *) * (count_tokens(s + i) + 1));
		result[j].redirects = malloc(sizeof(t_redirect) * 256);
		result[j].redirect_count = 0;
		k = 0;
		while (s[i] && s[i] != '|')
		{
			while (s[i] && (s[i] == ' ' || s[i] == '\t'))
				i++;
			if (!s[i] || s[i] == '|')
				break;
			char *arg;
			token_len = extract_token(s, &i, &arg);
			if (token_len < 0 || !arg)
				return (free_cmds(result, j), NULL);
			if (is_redirect(arg))
			{
				char *file;
				token_len = extract_token(s, &i, &file);
				if (token_len < 0 || !file)
					return (free(arg), free_cmds(result, j), NULL);
				result[j].redirects[result[j].redirect_count].type = arg;
				result[j].redirects[result[j].redirect_count].file = file;
				result[j].redirect_count++;
			}
			else
				result[j].args[k++] = arg;
		}
		result[j].args[k] = NULL;
		if (s[i] == '|')
			i++;
		j++;
	}
	result[j].args = NULL;
	return (result);
}
