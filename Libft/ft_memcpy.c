/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:14:17 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/11 16:21:12 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int ft_memcpy(void *dst, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dst;
    unsigned char *s = (unsigned char *)src;
    size_t i;

    i = 0;
    while (i < n)
    {
        d[i] = s[i];
        i++;
    }
    return (dst);
}