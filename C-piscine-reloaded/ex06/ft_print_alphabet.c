/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_alphabet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:06:06 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/08 14:48:31 by mstasiak         ###   ########.fr       */
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
