/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_security_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:43:28 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/24 16:41:19 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol_bonus.h"

int	mandelbrot_security(char **argv, t_data *data)
{
	if (argv[2])
	{
		if (ft_str_is_numeric(argv[2]) && (ft_atoi(argv[2]) >= 0
				&& ft_atoi(argv[2]) <= 9))
			data->color_palette = ft_atoi(argv[2]);
		else
			return (clean_up(data), MLX_ERROR);
	}
	else
		data->color_palette = 0;
	data->min_x = -3.0;
	data->max_x = 2.0;
	data->min_y = -2.0;
	data->max_y = 2.0;
	mandelbrot_wrapper(data);
	return (0);
}

int	julia_security(char **argv, t_data *data)
{
	data->move.animate = 1;
	data->move.direction = -1;
	if (!argv[2] || !argv[3]
		|| !ft_str_is_float(argv[2]) || !ft_str_is_float(argv[3]))
		return (clean_up(data), MLX_ERROR);
	if (argv[4])
	{
		if (ft_str_is_numeric(argv[4]) && (ft_atoi(argv[4]) >= 0
				&& ft_atoi(argv[4]) <= 9))
			data->color_palette = ft_atoi(argv[4]);
		else
			return (clean_up(data), MLX_ERROR);
	}
	else
		data->color_palette = 0;
	data->min_x = -1.5;
	data->max_x = 1.5;
	data->min_y = -1.5;
	data->max_y = 1.5;
	data->c.c_re = ft_atof(argv[2]);
	data->c.c_im = ft_atof(argv[3]);
	julia_wrapper(data);
	return (0);
}

int	burning_ship_security(char **argv, t_data *data)
{
	if (argv[2])
	{
		if (ft_str_is_numeric(argv[2])
			&& (ft_atoi(argv[2]) >= 0 && ft_atoi(argv[2]) <= 9))
			data->color_palette = ft_atoi(argv[2]);
		else
			return (clean_up(data), MLX_ERROR);
	}
	else
		data->color_palette = 0;
	data->min_x = -2.5;
	data->max_x = 1.5;
	data->min_y = -2.0;
	data->max_y = 2.0;
	burning_ship_wrapper(data);
	return (0);
}
