/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:31:39 by jbias             #+#    #+#             */
/*   Updated: 2024/11/19 14:33:04 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
