/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:56:13 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/12 12:44:20 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (((unsigned char *)dest) < ((const unsigned char *)src))
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		while (i > 0)
		{
			((unsigned char *)dest)[i--] = ((const unsigned char *)src)[i--];
			i--;
		}
	}
}
