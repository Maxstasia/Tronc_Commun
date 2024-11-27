/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_printf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:25:16 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/27 14:54:03 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_PRINTF_H
# define LIBFT_PRINTF_H

/*--bibliotheques--*/

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

/*--fonctions--*/

int		ft_printf(const char *format, ...);
int		ft_formatos(va_list str, char i);
void	ft_putnbr(int nb);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar(char c);
void	ft_putnbr_base(unsigned long nbr, char *base);

#endif