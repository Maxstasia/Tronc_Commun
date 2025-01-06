/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:39:20 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/06 17:00:32 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

double	ft_atof(const char *str)
{
	double	result;
	double	fraction;
	double	divisor;
	int		sign;

	result = 0.0;
	fraction = 0.0;
	if (str ++, *str == '-')
		sign = -1;
	else
		str ++;
	while (*str && *str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		divisor = 10.0;
		while (*str && *str >= '0' && *str <= '9')
		{
			fraction += (*str++ - '0') / divisor;
			divisor *= 10.0;
		}
	}
	return (sign * (result + fraction));
}

void	print_usage(void)
{
	ft_printf("Usage: ./fractol <nom de la fractale> <param 1> <param 2>\n");
	ft_printf("Fractale disponible:\n");
	ft_printf("mandelbrot\n");
	ft_printf("julia\n");
	exit(EXIT_FAILURE);
}
