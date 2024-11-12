/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:01:08 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/12 17:03:24 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	
}

char	*ft_strjoin_suite(int size, char **strs, char *sep, int total_length)
{
	int		i;
	char	*result;

	/* result = (char *)malloc(sizeof(char) * (total_length + 1));
	if (!result)
		return (NULL);
	result[total_length] = '\0'; */
	i = -1;
	while (i ++, i < size)
	{
		ft_strcat(result, strs[i]);
		if (i < size - 1)
			ft_strcat(result, sep);
	}
	return (result);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		total_length;

	total_length = ft_strlen(s1) + ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (total_length + 1));
	if (!result)
		return (NULL);
	result[total_length] = '\0';
}