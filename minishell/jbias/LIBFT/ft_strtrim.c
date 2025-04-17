/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:00:27 by jbias             #+#    #+#             */
/*   Updated: 2024/11/22 11:54:56 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	ssize_t			i;
	ssize_t			start;
	ssize_t			j;
	char			*str;

	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	start = i;
	i = ft_strlen(s1);
	while (i >= start && ft_strrchr(set, s1[i]))
		i--;
	str = (char *)malloc(sizeof(char) * (i - start + 2));
	if (!str)
		return (NULL);
	j = 0;
	while (start <= i)
	{
		str[j] = s1[start];
		start++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

/*
#include <stdio.h>
int	main(int ac, char **av)
{
	printf("%s\n", ft_strtrim(av[1], " \n\t"));
	return (0);
}*/
