/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main(ft_printf).c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:14:09 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/29 16:02:26 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_fd(char *s, int fd)
{
	int	len;

	len = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (*s)
	{
		write(fd, s, 1);
		s++;
		len++;
	}
	return (len);
}

int	ft_putnbr(int nb)
{
	long int	n;
	int			len;

	n = nb;
	len = 0;
	if (nb < 0)
	{
		len += ft_putchar('-');
		n *= -1;
	}
	if (n < 10)
		len += ft_putchar(n + '0');
	else
	{
		len += ft_putnbr(n / 10);
		len += ft_putnbr(n % 10);
	}
	return (len);
}

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
		len += ft_putstr_fd("(nil)", 1);
		return (len);
	}
	len += ft_putstr_fd("0x", 1);
	len += ft_putnbr_base(nbr, base);
	return (len);
}

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

int	main()
{
	int	i;

	i = printf(" %d %d %d %d %d ", -1, 10, 11, 12, 4294967294);
	printf("%d", i);
	printf("\n");
	i = ft_printf(" %d %d %d %d %d ", -1, 10, 11, 12, 4294967294);
	printf("%d", i);
	return 0;
}