/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:56:15 by jbias             #+#    #+#             */
/*   Updated: 2024/11/19 14:40:24 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		i;
	char	*str;

	len = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	len = 0;
	while (s2[len])
	{
		str[i] = s2[len];
		len++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*int	main(void)
{
	const char a[6] = "salut";
	const char b[7] = "coucou";

	printf("%s\n", ft_strjoin(a, b));
	return (0);
}*/
