/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:25:14 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/29 15:46:40 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_formatos(va_list str, char i)
{
	int	len;

	len = 0;
	if (i == 'c')
		len += ft_putchar(va_arg(str, int));
	else if (i == 's')
		len += ft_putstr_fd(va_arg(str, char *), 1);
	else if (i == 'p')
		len += ft_putnbr_base0x(va_arg(str, unsigned long), "0123456789abcdef");
	else if (i == 'd' || i == 'i')
		len += ft_putnbr(va_arg(str, int));
	else if (i == 'u')
		len += ft_putnbr_base(va_arg(str, unsigned int), "0123456789");
	else if (i == 'x')
		len += ft_putnbr_base(va_arg(str, unsigned int), "0123456789abcdef");
	else if (i == 'X')
		len += ft_putnbr_base(va_arg(str, unsigned int), "0123456789ABCDEF");
	else if (i == '%')
		len += ft_putchar('%');
	else
		return (0);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		len;
	va_list	str;

	va_start(str, format);
	i = -1;
	len = 0;
	while (i++, format[i])
	{
		if (format[i] == '%')
		{
			len += ft_formatos(str, format[i + 1]);
			i++;
		}
		else
		{
			len += ft_putchar(format[i]);
		}
	}
	va_end(str);
	return (len);
}
