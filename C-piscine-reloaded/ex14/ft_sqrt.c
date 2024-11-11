/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:43:20 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/05 14:43:27 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int		i;

	if (nb < 0)
		return (0);
	i = 0;
	while (i * i <= nb && i <= 46340)
	{
		if (i * i == nb)
			return (i);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%d, %d, %d", ft_sqrt(25), ft_sqrt(81), ft_sqrt(2147483646));
	return (0);
}*/
