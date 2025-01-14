/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:30:59 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/14 16:48:15 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	burning_ship(t_data *data)
{
	t_complex	c;
	int			x;
	int			y;
	int			iter;
	double		temp;

	y = -1;
	while (y ++, y < WINDOW_HEIGHT)
	{
		x = -1;
		while (x ++, x < WINDOW_WIDTH)
		{
			c.c_re = data->min_x + x
				* (data->max_x - data->min_x) / WINDOW_WIDTH;
			c.c_im = data->min_y + y
				* (data->max_y - data->min_y) / WINDOW_HEIGHT;
			c.z_re = 0;
			c.z_im = 0;
			iter = 0;
			while ((c.z_re * c.z_re + c.z_im * c.z_im) < 4 && ++iter < MAX_ITER)
			{
				temp = c.z_re * c.z_re - c.z_im * c.z_im + c.c_re;
				c.z_im = 2 * fabs(c.z_re * c.z_im) + c.c_im;
				c.z_re = fabs(temp);
			}
			if (iter == MAX_ITER)
				img_pix_put(&data->img, x, y, BLACK_PIXEL);
			else
				img_pix_put(&data->img, x, y, get_color(iter, data->color_palette));
		}
	}
}

void	burning_ship_wrapper(t_data *data)
{
	data->cur_img = 2;
	render_background(&data->img, WHITE_PIXEL);
	burning_ship(data);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->img.mlx_img, 0, 0);
}
