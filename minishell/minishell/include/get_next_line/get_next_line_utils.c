/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:05:13 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/18 13:37:39 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	int		i;

	if (!s1 || !s2)
	{
		s1 = (char *)malloc(1);
		if (!s1 || !s2)
			return (NULL);
		s1[0] = '\0';
	}
	len1 = ft_strlen_gnl(s1);
	len2 = ft_strlen_gnl(s2);
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	i = -1;
	while (s2[++i])
		result[len1 + i] = s2[i];
	result[len1 + len2] = '\0';
	return (free(s1), result);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
