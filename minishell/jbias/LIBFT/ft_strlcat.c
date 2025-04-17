/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:17:56 by jbias             #+#    #+#             */
/*   Updated: 2024/11/18 14:43:31 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlcat(char	*dst, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < n && dst[i])
		i++;
	while ((i + j + 1) < n && src[j])
	{
		dst[i + j] = src[j];
	j++;
	}
	if (i < n)
		dst[i + j] = '\0';
	j = 0;
	while (src[j])
		j++;
	return (i + j);
}
/*
int	main(void)
{
	char s[10] = "coucou ";
	char st[10] = "ca va?";
	printf("%zu\n", ft_strlcat(s, st, 10));
	return (0);
}*/
