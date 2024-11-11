/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:40:55 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/05 14:41:01 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_factorial(int nb)
{
	int	f;
	int	i;

	f = 1;
	i = 1;
	if (nb == 0)
		return (1);
	else if (nb < 0 || nb > 12)
		return (0);
	else
	{
		while (i <= nb)
		{
			f *= i;
			i ++;
		}
	}
	return (f);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("0, %d\n", ft_iterative_factorial(-5));
	printf("1, %d\n", ft_iterative_factorial(0));
	printf("120, %d\n", ft_iterative_factorial(5));
}*/
