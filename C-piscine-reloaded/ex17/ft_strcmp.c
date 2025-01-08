/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:55:12 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/08 14:48:31 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
#include <stdio.h>

int	main(void)
{
	char str1[] = "Hello";
	char str2[] = "Hello";
	printf("Comparing '%s' and '%s': %d\n", str1, str2, ft_strcmp(str1, str2));

	char str3[] = "Hello";
	char str4[] = "Hellp";
	printf("Comparing '%s' and '%s': %d\n", str3, str4, ft_strcmp(str3, str4));

	char str5[] = "Hello";
	char str6[] = "Hell";
	printf("Comparing '%s' and '%s': %d\n", str5, str6, ft_strcmp(str5, str6));

	char str7[] = "";
	char str8[] = "Hello";
	printf("Comparing '%s' and '%s': %d\n", str7, str8, ft_strcmp(str7, str8));

	char str9[] = "abcd";
	char str10[] = "xyz";
	printf("Comparing '%s' and '%s': %d\n", str9, str10, ft_strcmp(str9, str10));
}*/
