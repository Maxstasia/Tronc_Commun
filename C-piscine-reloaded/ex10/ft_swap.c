/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:53:27 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/05 14:38:56 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/*
#include <stdio.h>

int	main(void)
{
	int	x;
	int	y;

	x = 5;
	y = 10;
	printf ("Avant :\n X = %d\n Y = %d\n\n", x, y);
	ft_swap(&x, &y);
	printf ("Après :\n X = %d\n Y = %d\n\n", x, y);
}*/
