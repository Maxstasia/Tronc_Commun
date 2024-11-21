/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:17:10 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/21 11:09:07 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free_tab(char **str, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
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

	i = 0;
	len_word = 0;
	while (s[len_word] != c && s[len_word])
		len_word++;
	str = (char *)malloc(sizeof(char) * len_word + 1);
	if (!str)
		return (NULL);
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
	size_t	i;

	if (!s)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (ft_countword((char *)s, c) + 1));
	if (!strs)
		return (NULL);
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
	strs[i] = 0;
	return (strs);
}

/* 
int main(void)
{
	ft_split("   Test Split Function   ", ' ');
} */