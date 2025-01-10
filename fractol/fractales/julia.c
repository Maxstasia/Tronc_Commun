/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:39:15 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/10 15:30:59 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	julia(t_data *data)
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
			// Convertir coordonnées pixel -> coordonnées complexes
			c.z_re = data->min_x +
				((double)x / WINDOW_WIDTH) * (data->max_x - data->min_x);
			c.z_im = data->min_y +
				((double)y / WINDOW_HEIGHT) * (data->max_y - data->min_y);
			iter = 0;
			while ((c.z_re * c.z_re + c.z_im * c.z_im) <= 4 && iter < MAX_ITER)
			{
				temp = c.z_re * c.z_re - c.z_im * c.z_im + data->c_re;
				c.z_im = 2 * c.z_re * c.z_im + data->c_im;
				c.z_re = temp;
				iter++;
			}
			if (iter == MAX_ITER)
				img_pix_put(&data->img, x, y, BLACK_PIXEL);
			else
				img_pix_put(&data->img, x, y,
					get_color(iter, data->color_palette));
		}
	}
}

void	julia_wrapper(t_data *data)
{
	data->cur_img = 1;
	render_background(&data->img, WHITE_PIXEL);
	julia(data);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->img.mlx_img, 0, 0);
	mlx_loop_hook(data->mlx_ptr, &update_frame, data);
}
