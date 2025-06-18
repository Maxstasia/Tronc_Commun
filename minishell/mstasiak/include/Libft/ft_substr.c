/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:31:39 by jbias             #+#    #+#             */
/*   Updated: 2025/06/18 13:36:02 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_mallocsize(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	if (!(start > ft_strlen(s)))
	{
		while (s[start] != '\0' && i < len)
		{
			res++;
			start++;
			i++;
		}
	}
	res++;
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		size;
	size_t	i;

	size = ft_mallocsize(s, start, len);
	i = 0;
	str = malloc(sizeof(char) * (size));
	if (!str)
		return (NULL);
	if (!(start > ft_strlen(s)))
	{
		while (s[start] != '\0' && i < len)
		{
			str[i] = s[start];
			start++;
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}

static int	skip_quotes(int start, char *s, char quote)
{
	while (s[start] == quote && s[start + 1] == quote)
		start += 2;
	return (start);
}

char	*ft_substr_quotes(char const *s, unsigned int start,
			size_t len, char quote)
{
	char	*str;
	int		size;
	size_t	i;

	size = ft_mallocsize(s, start, len);
	i = 0;
	str = malloc(sizeof(char) * (size));
	if (!str)
		return (NULL);
	if (!(start > ft_strlen(s)))
	{
		while (s[start] != '\0' && i < len)
		{
			start = skip_quotes(start, (char *)s, quote);
			if (s[start] == quote && s[start + 1] != '\0')
				start++;
			else if (s[start] == quote && s[start + 1] == '\0')
				return (str[i] = '\0', str);
			str[i++] = s[start++];
		}
	}
	return (str[i] = '\0', str);
}
