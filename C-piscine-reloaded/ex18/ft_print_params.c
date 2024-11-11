/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:00:17 by mstasiak          #+#    #+#             */
/*   Updated: 2024/11/05 15:00:20 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}*/

void	ft_putchar(char c);

int	main(int argc, char **argv)
{
	int		i;
	int		j;
	char	c;

	if (argc < 2)
		return (0);
	i = 1;
	j = 0;
	while (i != argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			c = argv[i][j];
			ft_putchar(c);
			j ++;
		}
		ft_putchar('\n');
		i ++;
	}
	return (0);
}
