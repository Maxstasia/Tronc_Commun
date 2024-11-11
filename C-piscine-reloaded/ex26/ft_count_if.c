/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:21:57 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/05 17:26:06 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_if(char **tab, int (*f)(char*))
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tab[i] != 0)
	{
		if (f(tab[i]) == 1)
			count++;
		i++;
	}
	return (count);
}
/*
int	is_non_empty(char *str)
{
	return (str[0] != '\0');
}

#include <stdio.h>

int	main(void)
{
	char *tab[] = {"42", "", "Piscine", "", "C", 0};
	int count = ft_count_if(tab, &is_non_empty);
	printf("Nombre d'éléments non vides : %d\n", count);
	return (0);
}*/
