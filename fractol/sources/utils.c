/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:39:20 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/10 18:20:22 by mstasiak         ###   ########.fr       */
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
	divisor = 10.0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		result = result * 10.0 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			fraction += (*str++ - '0') / divisor;
			divisor *= 10.0;
		}
	}
	return (sign * (result + fraction));
}

void	print_usage(void)
{
	ft_printf("Usage: ./fractol <nom de la fractale>\n");
	ft_printf("Fractale disponible:\n");
	ft_printf("mandelbrot\n");
	ft_printf("julia <param 1> <param 2>\n");
	exit(EXIT_FAILURE);
}

int	is_end(t_data *data)
{
	return (data->c_re < -1.5 || data->c_re > 1.5
		|| data->c_im < -1.5 || data->c_im > 1.5);
}

void	clean_up(t_data *data)
{
	if (data->img.mlx_img)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		free(data->img.mlx_img);
	}
	if (data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free(data->win_ptr);
	}
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	if (data->img.addr)
		free(data->img.addr);
}
