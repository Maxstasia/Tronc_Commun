/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:47:15 by mstasiak          #+#    #+#             */
/*   Updated: 2025/02/12 15:51:05 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(c));
}

void	ft_putstr_fd(const char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i++], 1);
	}
}

void	ft_putendl_fd(char *str, int fd)
{
	if (str)
	{
		ft_putstr_fd(str, fd);
		ft_putchar_fd('\n', fd);
	}
}
