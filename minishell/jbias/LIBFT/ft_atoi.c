/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:32:57 by jbias             #+#    #+#             */
/*   Updated: 2025/01/21 15:21:55 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((nptr[i] <= 13 && nptr[i] >= 9) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
	i++;
	}
	if (!(nptr[i] <= '9' && nptr[i] >= '0'))
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - 48);
		i++;
	}
	return (result * sign);
}
/*
int	main(void)
{
	const char a[20] = "    +--+- 2154";
	const char aa[20] = "    +--+-2154";
	const char aaa[20] = "    -2154";
	const char aaaa[20] = "    +l--+- 2154";
	const char aaaaa[20] = "21 54";
	const char aaaaaa[20] = "-2j154";

	printf("%d\n", ft_atoi(a));
	printf("%d\n", ft_atoi(aa));
	printf("%d\n", ft_atoi(aaa));
	printf("%d\n", ft_atoi(aaaa));
	printf("%d\n", ft_atoi(aaaaa));
	printf("%d\n", ft_atoi(aaaaaa));

	return (0);
}*/
