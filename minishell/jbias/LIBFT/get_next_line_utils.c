/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:41:38 by jbias             #+#    #+#             */
/*   Updated: 2025/01/21 15:50:49 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strchrr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
	i++;
	}
	if (c != '\0')
		return (0);
	return (i);
}

char	*ft_strjoinn(char *s1, char *s2)
{
	long int		len;
	long int		i;
	char			*str;

	if (!s2)
		return (s1);
	len = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	len = 0;
	while (s2[len])
		str[i++] = s2[len++];
	free(s1);
	return (str);
}

int	ft_strlenn(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	*ft_callocc(int nmemb, int size)
{
	void	*ptr;
	int		i;

	i = 0;
	ptr = NULL;
	if (size > 0 && nmemb > (2147483647 / size))
		return (ptr);
	ptr = (char *)malloc(nmemb * size);
	if (!ptr)
		return (ptr);
	while (i < (size * nmemb))
	{
		((char *)ptr)[i] = '\0';
	i++;
	}
	return (ptr);
}
