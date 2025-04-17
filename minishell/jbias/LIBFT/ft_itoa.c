/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:42:47 by jbias             #+#    #+#             */
/*   Updated: 2024/11/20 19:21:09 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	ft_size(long int bn)
{
	size_t	l;

	l = 0;
	if (bn == 0)
	{
		l++;
		return (l);
	}
	if (bn < 0)
	{
		bn *= -1;
		l++;
	}
	while (bn > 0)
	{
		bn /= 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	size_t		len;
	long int	nb;
	char		*str;
	size_t		i;

	i = 0;
	nb = n;
	len = ft_size(nb);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb < 0)
	{
		str[i] = '-';
		i++;
		nb *= -1;
	}
	while (len-- > i)
	{
		str[len] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}
/*
int	main(void)
{
	printf("%s\n", ft_itoa(-129));
	printf("%s\n", ft_itoa(129));
	return (0);
}*/
