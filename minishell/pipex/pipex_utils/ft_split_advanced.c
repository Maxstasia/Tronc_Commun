/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_advanced.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:38:10 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/02 14:08:26 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_redirection(t_cmd *cmd, char *s, int *i, char *arg)
{
	char	*file;
	int		token_len;

	token_len = extract_token_split(s, i, &file);
	if (token_len < 0 || !file)
	{
		if (file)
			free(file);
		return (-1);
	}
	cmd->redirects[cmd->redirect_count].type = arg;
	cmd->redirects[cmd->redirect_count].file = remove_quotes_split(file);
	cmd->redirect_count++;
	return (0);
}

static int	process_single_token(t_cmd *cmd, char *s, int *i, int *k)
{
	char	*arg;
	int		token_len;

	token_len = extract_token_split(s, i, &arg);
	if (token_len < 0 || !arg)
	{
		if (arg)
			free(arg);
		return (-1);
	}
	if (is_redirect(arg))
	{
		if (handle_redirection(cmd, s, i, arg) == -1)
		{
			free(arg);
			return (-1);
		}
	}
	else
		cmd->args[(*k)++] = remove_quotes_split(arg);
	return (0);
}

static int	parse_command_tokens(t_cmd *cmd, char *s, int *i)
{
	int	k;

	k = 0;
	while (s[*i] && s[*i] != '|')
	{
		while (s[*i] && (s[*i] == ' ' || s[*i] == '\t'))
			(*i)++;
		if (!s[*i] || s[*i] == '|')
			break ;
		if (process_single_token(cmd, s, i, &k) == -1)
			return (-1);
	}
	cmd->args[k] = NULL;
	return (0);
}

static int	skip_whitespace_and_check(char *s, int *i)
{
	while (s[*i] && (s[*i] == ' ' || s[*i] == '\t'))
		(*i)++;
	if (!s[*i])
		return (1);
	return (0);
}

t_cmd	*ft_split_advanced(char *s, int cmd_count)
{
	t_cmd	*result;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	result = init_cmd_array(cmd_count);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < cmd_count)
	{
		if (skip_whitespace_and_check(s, &i))
			break ;
		if (allocate_cmd_memory(&result[j], s, i) == -1)
			return (free_cmds(result, j), NULL);
		if (parse_command_tokens(&result[j], s, &i) == -1)
			return (free_cmds(result, j + 1), NULL);
		if (s[i] == '|')
			i++;
		j++;
	}
	return (result);
}
