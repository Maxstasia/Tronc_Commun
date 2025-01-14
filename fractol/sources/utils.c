/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:39:20 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/14 16:19:47 by mstasiak         ###   ########.fr       */
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
	ft_printf("Usage: ./fractol <fractal> [options]\n");
	ft_printf("Available fractals:\n");
	ft_printf("- mandelbrot [palette: 0-9]\n");
	ft_printf("- julia <Re> <Im> [palette: 0-9]\n");
	ft_printf("- burning_ship [palette: 0-9]\n");
	exit(MLX_ERROR);
}


void	clean_up(t_data *data)
{
	print_usage();
	if (data->img.mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		data->win_ptr = NULL;
		free(data->mlx_ptr);
	}
	exit(MLX_ERROR);
}
