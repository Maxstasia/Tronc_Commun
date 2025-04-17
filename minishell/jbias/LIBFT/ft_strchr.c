/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:32:03 by jbias             #+#    #+#             */
/*   Updated: 2024/11/18 12:08:02 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
	i++;
	}
	if ((char)c != '\0')
		return (NULL);
	return ((char *)s + i);
}
/*
int	main(void)
{
	const char *a = "teste";

	printf("%s\n", ft_strchr(a, 1024));
	return (0);
}*/
