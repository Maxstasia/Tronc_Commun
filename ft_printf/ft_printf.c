/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:25:14 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/25 17:38:24 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

int	ft_formatos(va_list str, char i)
{
	if(i == 'c')
		ft_putchar(va_arg(str,char));
	else if(i == 's')
		ft_putstr_fd(va_arg(str,char*),1);
	else if(i == 'p')
	else if(i == 'd')
	else if(i == 'i')
	else if(i == 'u')
	else if(i == 'x')
	else if(i == 'X')
	else if(i == '%')
		ft_putchar('%');
	
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

void	ft_formatos(va_list str, char i)
{
	if(i == 'c')
		ft_putchar(va_arg(str,int));
  else if(i == 's')
		ft_putstr_fd(va_arg(str,char*),1);
	else if(i == '%')
		ft_putchar('%');
	
}

void	ft_printf(const char *format,...)
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
      i ++;
		}
		else
			ft_putchar(format[i]);
		i++;
	}
	va_end(str);
}
int main() {
  printf("%c holamundooooo %s asdasdasd %%\n", 'a',"blabla");
  ft_printf("%c holamundooooo %s asdasdasd %%\n", 'a',"blabla");
  return 0;
}
*/