/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:17:10 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/18 13:35:21 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free_tab(char **str, int len)
{
	int	i;

	i = -1;
	while (i++, i < len)
		free(str[i]);
	return (free(str), NULL);
}

static int	ft_countword(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static char	*ft_dostr(char *s, char c)
{
	int		i;
	int		len_word;
	char	*str;

	i = -1;
	len_word = 0;
	while (s[len_word] != c && s[len_word])
		len_word++;
	str = (char *)malloc(sizeof(char) * len_word + 1);
	if (!str)
		return (free(str), NULL);
	while (i++, i < len_word)
		str[i] = s[i];
	return (str[i] = '\0', str);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	i;

	if (!s)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (ft_countword((char *)s, c) + 1));
	if (!strs)
		return (free(strs), NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			strs[i] = ft_dostr((char *)s, c);
			if (!strs[i])
				return (ft_free_tab(strs, i));
			i++;
		}
		while (*s != c && *s)
			s++;
	}
	return (strs[i] = 0, strs);
}
