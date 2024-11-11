/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foreach.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:04:57 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/05 17:12:39 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_foreach(int *tab, int length, void (*f)(int))
{
	int	i;

	i = -1;
	while (i ++, i < length)
		f(tab[i]);
}

/*
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	long int	n;

	n = nb;
	if (nb < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	if (n < 10)
	{
		ft_putchar(n + '0');
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

void	ft_sqrt(int nb)
{
	int	i;

	if (nb < 0)
		ft_putnbr(0);
	i = 0;
	while (i * i <= nb && i <= 46340)
	{
		if (i * i == nb)
		{
			ft_putnbr(i);
			return;
		}
		i++;
	}
	ft_putnbr(0);
}

int	main(void)
{
	int	tab[] = {154, 24354, 65, 546, 81, 9};
	ft_foreach(tab, 6, &ft_putnbr);
	ft_putchar('\n');
	ft_foreach(tab, 6, &ft_sqrt);
}*/
