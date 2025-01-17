/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:30:59 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/17 12:31:35 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	burning_ship(t_data *data)
{
	int			x;
	int			y;
	int			iter;

	y = -1;
	while (y ++, y < WINDOW_HEIGHT)
	{
		x = -1;
		while (x ++, x < WINDOW_WIDTH)
		{
			iter = burning_ship_calcul(data, x, y);
			if (iter == MAX_ITER)
				img_pix_put(data, x, y, BLACK_PIXEL);
			else
				img_pix_put(data, x, y, get_color(iter, data->color_palette));
		}
	}
}

int	burning_ship_calcul(t_data *data, int x, int y)
{
	double	temp;
	int		iter;

	data->c.c_re = data->min_x + x
		* (data->max_x - data->min_x) / WINDOW_WIDTH;
	data->c.c_im = data->min_y + y
		* (data->max_y - data->min_y) / WINDOW_HEIGHT;
	data->c.z_re = 0;
	data->c.z_im = 0;
	iter = 0;
	while ((data->c.z_re * data->c.z_re + data->c.z_im * data->c.z_im)
		< 4 && ++iter < MAX_ITER)
	{
		temp = data->c.z_re
			* data->c.z_re - data->c.z_im * data->c.z_im + data->c.c_re;
		data->c.z_im = 2 * fabs(data->c.z_re * data->c.z_im) + data->c.c_im;
		data->c.z_re = fabs(temp);
	}
	return (iter);
}

void	burning_ship_wrapper(t_data *data)
{
	data->cur_img = 2;
	render_background(data, WHITE_PIXEL);
	burning_ship(data);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->img.mlx_img, 0, 0);
}
