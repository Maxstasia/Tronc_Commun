/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_case_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:53:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/27 15:26:56 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*cas_1(char *line, char *trimmed)
{
	char	*result;

	result = malloc(ft_strlen(line) + 5);
	if (!result)
		return (NULL);
	ft_strlcpy(result, ": >> ", 6);
	ft_strlcat(result, trimmed + 2, ft_strlen(line) + 5);
	return (result);
}

char	*cas_2(char *line, char *trimmed)
{
	char	*result;

	result = malloc(ft_strlen(line) + 5);
	if (!result)
		return (NULL);
	ft_strlcpy(result, ": << ", 6);
	ft_strlcat(result, trimmed + 2, ft_strlen(line) + 5);
	return (result);
}

char	*cas_3(char *line, char *trimmed)
{
	char	*result;

	result = malloc(ft_strlen(line) + 4);
	if (!result)
		return (NULL);
	ft_strlcpy(result, ": > ", 5);
	ft_strlcat(result, trimmed + 1, ft_strlen(line) + 4);
	return (result);
}

char	*cas_4(char *line, char *trimmed)
{
	char	*result;

	result = malloc(ft_strlen(line) + 4);
	if (!result)
		return (NULL);
	ft_strlcpy(result, ": ", 3);
	ft_strlcat(result, trimmed, ft_strlen(line) + 4);
	return (result);
}

char	*cas_5(char *line)
{
	char	*result;

	result = malloc(ft_strlen(line) + 3);
	if (!result)
		return (NULL);
	ft_strlcpy(result, ": ", 3);
	ft_strlcat(result, line, ft_strlen(line) + 3);
	return (result);
}
