/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:32:48 by jbias             #+#    #+#             */
/*   Updated: 2024/11/21 10:08:05 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	if (s2[0] == '\0' || s1 == s2)
		return ((char *)s1);
	while (i < n && s1[i] != '\0')
	{
		j = 0;
		k = i;
		if (s1[k] == s2[j])
		{
			while (s1[k] == s2[j] && k < n && s1[k] && s2[j])
			{
				j++;
				k++;
			}
			if (s2[j] == '\0')
				return ((char *)&s1[i]);
		}
	i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	const char	a[152] = "coucou les amis";
	const char	b[152] = "les";

	printf("%s\n", ft_strnstr(a, b, 25));
	return (0);
}*/
