/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:25:14 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/27 14:53:33 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

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
}

/*
test avec programiz.pro :

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_putchar(int c)
{
	write(1, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
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
		ft_putchar(n + '0');
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

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

int	ft_printf(const char *format,...)
{
	int	i;
	va_list	str;
	
	va_start(str,format);
	i = 0;
	while(format[i])
	{
		if(format[i] == '%')
		{
			ft_formatos(str,format[i+1]);
			i++;
		}
		else
		{
			ft_putchar(format[i]);
		}
		i++;
	}
	va_end(str);
}
int	main() {
	printf("Character: %c, String: %s, Pointer: %p\n", 'A', "Hello", &printf);
	printf("Decimal: %d, Unsigned: %u, Hex (lower): %x, Hex (upper): %X\n", -42, 42, 255, 255);
	ft_printf("Character: %c, String: %s, Pointer: %p\n", 'A', "Hello", &printf);
	ft_printf("Decimal: %d, Unsigned: %u, Hex (lower): %x, Hex (upper): %X\n", -42, 42, 255, 255);
	return 0;
}
*/