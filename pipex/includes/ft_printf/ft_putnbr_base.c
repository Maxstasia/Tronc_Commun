/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:21:03 by mstasiak          #+#    #+#             */
/*   Updated: 2024/12/11 18:43:21 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(unsigned long nbr, char *base)
{
	int	base_len;
	int	len;

	len = 0;
	base_len = 0;
	while (base[base_len])
		base_len++;
	if (nbr >= (unsigned long)base_len)
		len += ft_putnbr_base(nbr / base_len, base);
	len += ft_putchar(base[nbr % base_len]);
	return (len);
}

int	ft_putnbr_base0x(unsigned long nbr, char *base)
{
	int	base_len;
	int	len;

	len = 0;
	base_len = 0;
	while (base[base_len])
		base_len++;
	if (nbr == 0)
	{
		len += ft_putstr_fd_printf("(nil)", 1);
		return (len);
	}
	len += ft_putstr_fd_printf("0x", 1);
	len += ft_putnbr_base(nbr, base);
	return (len);
}
