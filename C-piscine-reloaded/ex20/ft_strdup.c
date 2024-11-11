/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:18:56 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/05 15:19:01 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	char	*dup;
	int		i;
	int		len;

	len = 0;
	while (src[len] != '\0')
		len++;
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/*
#include <stdio.h>

int main(void)
{
    char *source = "Hello, 42!";
    char *copy;

    copy = ft_strdup(source);
    if (copy == NULL)
    {
        printf("Erreur : malloc a échoué.\n");
        return (1);
    }
    printf("Source : %s\n", source);
    printf("Copie : %s\n", copy);
    free(copy);
    return (0);
}*/
