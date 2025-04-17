/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:36:04 by jbias             #+#    #+#             */
/*   Updated: 2024/11/14 17:21:33 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;

	i = 0;
	while (src[i])
		i++;
	if (siz == 0)
		return (i);
	i = 0;
	while ((i < (siz - 1)) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	i = 0;
	while (src[i])
		i++;
	return (i);
}
/*
int	main(void)
{
	char	a[7];
	char	b[11] = "youplaboom\0";

	printf("taille de la src: %zu\n", ft_strlcpy(a, b, 7));
	return (0);
}*/
