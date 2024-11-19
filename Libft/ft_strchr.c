/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:34:51 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/19 15:44:52 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (i++, s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
	}
	if ((char)c != '\0')
		return (NULL);
	return ((char *)s + i);
}
