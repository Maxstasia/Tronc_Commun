/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:10:42 by jbias             #+#    #+#             */
/*   Updated: 2024/11/21 16:05:29 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	i = 0;
	p = (unsigned char *) s;
	while (i < n)
	{
		p[i] = (unsigned char) c;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	****** si int c est plus  grand que la range de unsigned char (256) 
	alors on fait : c % 256 *******
	
	char	c[10] = "012345679\0";
	printf("%s\n", (char*)ft_memset(c, 48, 5));
	printf("%s\n", (char*)memset(c, 48, 5));
	return (0);
}*/
