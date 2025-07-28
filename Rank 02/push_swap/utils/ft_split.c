/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:15:58 by mstasiak          #+#    #+#             */
/*   Updated: 2025/02/14 15:00:23 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static char	*ft_dostr(const char *s, char c)
{
	int		len_word;
	char	*str;
	int		i;

	len_word = 0;
	while (s[len_word] != c && s[len_word] != '\0')
		len_word++;
	str = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len_word)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;

	if (!s)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (ft_countword(s, c) + 1));
	if (!strs)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			strs[i] = ft_dostr(s, c);
			if (!strs[i])
				return (ft_free_tab(strs, i));
			i++;
		}
		while (*s != c && *s)
			s++;
	}
	strs[i] = NULL;
	return (strs);
}
