/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:26:38 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/05 14:36:11 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}*/

void	ft_putchar(char c);

void	ft_print_numbers(void)
{
	char	*c;
	int		i;

	c = "0123456789";
	i = 0;
	while (i < 10)
	{
		ft_putchar(c[i]);
		i ++;
	}
}
/*
int	main(void)
{
	ft_print_numbers();
}*/
