/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_alphabet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:06:06 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/05 14:35:26 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
*/

void	ft_putchar(char c);

void	ft_print_alphabet(void)
{
	char	*c;
	int		i;

	c = "abcdefghijklmnopqrstuvwxyz";
	i = 0;
	while (i < 26)
	{
		ft_putchar(c[i]);
		i ++;
	}
}
/*
int	main(void)
{
	ft_print_alphabet();
}*/
