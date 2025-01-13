/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:39:18 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/13 11:21:57 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	mandelbrot(t_data *data)
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
				c.z_im = 2 * c.z_re * c.z_im + c.c_im;
				c.z_re = temp;
			}
			if (iter == MAX_ITER)
			{
				img_pix_put(&data->img, x, y, BLACK_PIXEL);
				if (data->img.mlx_img == NULL || data->img.addr == NULL)
					clean_up(data);
			}
			else
			{
				img_pix_put(&data->img, x, y, get_color(iter, data->color_palette));
				if (data->img.mlx_img == NULL || data->img.addr == NULL)
					clean_up(data);
			}
		}
	}
}

void	mandelbrot_wrapper(t_data *data)
{
	data->cur_img = 0;
	render_background(&data->img, WHITE_PIXEL);
	mandelbrot(data);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->img.mlx_img, 0, 0);
}
