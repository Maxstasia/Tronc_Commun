/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:00:55 by jbias             #+#    #+#             */
/*   Updated: 2024/11/18 16:56:25 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	i = 0;
	d = (unsigned char *) dest;
	s = (const unsigned char *) src;
	if ((dest == (void *)0 && src == (void *)0) || n == 0)
		return (dest);
	if (dest < src)
	{
		ft_memcpy(d, s, n);
		return (dest);
	}
	i = n;
	while (i--)
		d[i] = s[i];
	return (dest);
}
/*
int	main(void)
{

	******* si dest > src : risque d'overflap *******

	char	a[8] = "Coucouu\0";
	char	b[7] = "Salute\0";

	printf("%s\n", (char*)ft_memmove(a, b, 3));
	return (0);
}*/
