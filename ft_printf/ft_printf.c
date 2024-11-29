/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:25:14 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/28 11:20:37 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_formatos(va_list str, char i)
{
	if (i == 'c')
		ft_putchar(va_arg(str, int));
	else if (i == 's')
		ft_putstr_fd(va_arg(str, char *), 1);
	else if (i == 'p')
	{
		ft_putstr_fd("0x", 1);
		ft_putnbr_base(va_arg(str, unsigned long), "0123456789abcdef");
	}
	else if (i == 'd' || i == 'i')
		ft_putnbr(va_arg(str, int));
	else if (i == 'u')
		ft_putnbr_base(va_arg(str, unsigned int), "0123456789");
	else if (i == 'x')
		ft_putnbr_base(va_arg(str, unsigned int), "0123456789abcdef");
	else if (i == 'X')
		ft_putnbr_base(va_arg(str, unsigned int), "0123456789ABCDEF");
	else if (i == '%')
		ft_putchar('%');
	else
		return (0);
	return (1);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	str;

	va_start(str, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			ft_formatos(str, format[i + 1]);
			i ++;
		}
		else
		{
			ft_putchar(format[i]);
		}
		i++;
	}
	va_end(str);
	return (1);
}
