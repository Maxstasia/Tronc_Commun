/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:11:20 by jbias             #+#    #+#             */
/*   Updated: 2024/11/21 17:48:56 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*static void	*ft_free(char **spl, int len)
{
	while (len >= 0)
	{
		free(spl[len]);
		len--;
	}
	free (spl);
	return (0);
}*/

static	int	ft_countstr(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i++] == '\'')
			while (str[i] != '\'')
				i++;
		if (str[i] && str[i] != c)
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

static int	ft_len(char *s, char c, int len)
{
	int		in_quotes;
	int		quotes;

	quotes = 0;
	in_quotes = 0;
	while ((s[len] != c || in_quotes) && s[len] != '\0')
	{
		if (s[len] == '\'')
			in_quotes = !in_quotes;
		else
			quotes++;
		len++;
	}
	return (quotes);
}

static char	*ft_dostr(char *s, char c)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	len = ft_len(s, c, len);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		if (*s != '\'')
			str[i++] = *s++;
		else
			s++;
	}
	str[i] = '\0';
	return (str);
}

static char	**ft_cut(char const *s, char c, char **spl, size_t i)
{
	int			in_quotes;

	in_quotes = 0;
	while (*s)
	{
		while ((*s == c && !in_quotes) && *s)
			s++;
		if (*s)
		{
			spl[i] = ft_dostr((char *)s, c);
			if (!spl[i])
				return (free_tab(spl), NULL);
			i++;
		}
		in_quotes = 0;
		while ((*s != c || in_quotes) && *s)
		{
			if (*s == '\'')
				in_quotes = !in_quotes;
			s++;
		}
	}
	spl[i] = NULL;
	return (spl);
}

char	**ft_split(char const *s, char c)
{
	size_t		i;
	char		**spl;

	i = 0;
	if (!s)
		return (NULL);
	spl = (char **)malloc(sizeof(char *) * (ft_countstr((char *)s, c) + 2));
	if (!spl)
		return (NULL);
	spl = ft_cut(s, c, spl, i);
	if (!spl)
		return (NULL);
	return (spl);
}

/*int	main(void)
char **split;
	
	split = ft_split("xxxxxxxxhello!", 'x');
	return (0);
}*/
