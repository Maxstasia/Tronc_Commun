/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:42:16 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/08 14:48:31 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_recursive_factorial(int nb)
{
	if (nb == 0)
		return (1);
	else if (nb < 0 || nb > 12)
		return (0);
	else
		return (nb * ft_recursive_factorial(nb - 1));
}

/*
#include <stdio.h>

int	main(void)
{
	printf("0, %d\n", ft_recursive_factorial(-5));
	printf("1, %d\n", ft_recursive_factorial(0));
	printf("120, %d\n", ft_recursive_factorial(5));
}*/
