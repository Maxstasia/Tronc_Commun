/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:39:47 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/13 18:41:30 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_rec(int n, int fd)
{
	if (n >= 10 || n <= -10)
		ft_putnbr_rec(n / 10, fd);
	write(fd, &"0123456789"[n % 10 * (n < 0 ? -1 : 1)], 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	ft_putnbr_rec(n, fd);
}