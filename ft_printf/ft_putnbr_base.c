/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:21:03 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/25 19:23:23 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

void	ft_putnbr_base(unsigned long nbr, char *base)
{
	int	base_len;

	base_len = 0;
	while (base[base_len])
		base_len++;
	if (nbr >= (unsigned long)base_len)
		ft_putnbr_base(nbr / base_len, base);
	ft_putchar(base[nbr % base_len]);
}