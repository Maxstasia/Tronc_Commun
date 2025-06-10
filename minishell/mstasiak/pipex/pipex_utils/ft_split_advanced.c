/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_advanced.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:38:10 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/28 14:10:38 by mstasiak         ###   ########.fr       */
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

static int count_token(const char *input)
{
	int i = 0;
	int count = 0;
	char quote = 0;

	if (!input || !*input)
		return (0);
	while (input[i] && input[i] != '|')
	{
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		if (!input[i] || input[i] == '|')
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
	int		start;
	int		end;
	char quote = 0;

	*token = NULL;
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		(*i)++;
	start = *i;
	if (!input[*i])
		return (-1);
	while (input[*i] && !is_separator(input[*i], 0))
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			quote = input[(*i)++];
			while (input[*i] && input[*i] != quote)
				(*i)++;
			if (!input[*i])
				return (ft_putstr_fd(RED"Error: Unmatched quotes\n"RESET, 2), -1);
			(*i)++;
		}
		else
			(*i)++;
	}
	end = *i;
	*token = ft_substr(input, start, end - start);
	if (!*token)
		return (-1);
	return (end - start);
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

static char	*remove_quotes(char *str)
{
	char	*quotes_free;
	int		i;
	int		j;
	int		in_quotes;
	char	quote;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	in_quotes = 0;
	quotes_free = malloc(ft_strlen(str) + 1);
	if (!quotes_free)
		return (NULL);
	while (str[i])
	{
		if (in_quotes == 0 && str[i] == '\\' && (str[i + 1] == '\'' || str[i + 1] == '\"'))
		{
			quotes_free[j++] = str[i + 1];
			i += 2;
		}
		else if (str[i] == '\\' && str[i + 1] == quote && in_quotes == 1)
		{
			quotes_free[j++] = str[i + 1];
			i += 2;
			continue;
		}
		else if (in_quotes == 0 && (str[i] == '\'' || str[i] == '\"'))
		{
			quote = str[i++];
			in_quotes = 1;
		}
		else if (in_quotes == 1 && str[i] == quote)
		{
			in_quotes = 0;
			quote = 0;
			i++;
		}
		else
			quotes_free[j++] = str[i++];
	}
	quotes_free[j] = '\0';
	free(str);
	return (quotes_free);
}

t_cmd *ft_split_advanced(char *s, int cmd_count)
{
	t_cmd *result;
	int i;
	int j;
	int k;
	int token_len;
	char *arg;
	char *file;
	
	if (!s)
		return (NULL);
	fflush(stdout);
	result = malloc(sizeof(t_cmd) * cmd_count);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
	//	printf("1111111111111111111111111111");
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (!s[i])
			break;
	//	printf("2222222222222222222222222222");
		result[j].args = malloc(sizeof(char *) * (count_token(s + i) + 1));
		if (!result[j].args)
			return (free_cmds(result, j), NULL);
	//	printf("3333333333333333333333333333");
		result[j].redirects = malloc(sizeof(t_redirect) * cmd_count);
		if (!result[j].redirects)
			return (free_cmds(result, j), free(result[j].args), NULL);
		//printf("4444444444444444444444444444");
		result[j].redirect_count = 0;
		k = 0;
		while (s[i] && s[i] != '|')
		{
		//	printf("5555555555555555555555555555");
			while (s[i] && (s[i] == ' ' || s[i] == '\t'))
				i++;
			if (!s[i] || s[i] == '|')
				break;
		//	printf("6666666666666666666666666666");
			token_len = extract_token(s, &i, &arg);
		//	printf("7777777777777777777777777777");
			if (token_len < 0 || !arg)
			{
				if (arg)
					free(arg);
				return (free_cmds(result, j), NULL);
			}
			if (!arg)
				return (free_cmds(result, j), NULL);
		//	printf("8888888888888888888888888888");
			if (is_redirect(arg))
			{
				token_len = extract_token(s, &i, &file);
	//			printf("9999999999999999999999999999");
				if (token_len < 0 || !file)
				{
					if (file)
						free(file);
					return (free(arg), free_cmds(result, j), NULL);
				}	
				result[j].redirects[result[j].redirect_count].type = arg;
				result[j].redirects[result[j].redirect_count].file = remove_quotes(file);
				result[j].redirect_count++;
//				printf("123456789123456789123456789");
			}
			else
				result[j].args[k++] = remove_quotes(arg);
		}
		result[j].args[k] = NULL;
		if (s[i] == '|')
			i++;
		j++;
		printf("result : %s \n",result[j - 1].args[0]); //DEBUG
		fflush(stdout);
	}
	return (result);
}
