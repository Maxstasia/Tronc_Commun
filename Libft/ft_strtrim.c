/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:25:33 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/13 15:26:04 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_str;
	size_t	start;
	size_t	end;
	size_t	len;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_isset(s1[start], set))
		start++;
	end = strlen(s1);
	while (end > start && ft_isset(s1[end - 1], set))
		end--;
	len = end - start;
	trimmed_str = (char *)malloc((len + 1) * sizeof(char));
	if (!trimmed_str)
		return (NULL);
	i = -1;
	while (i++, i < len)
		trimmed_str[i] = s1[start + i];
	trimmed_str[i] = '\0';
	return (trimmed_str);
}
