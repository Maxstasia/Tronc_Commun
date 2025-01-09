/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:39:15 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/09 10:02:13 by mstasiak         ###   ########.fr       */
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

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			// Convertir coordonnées pixel -> coordonnées complexes
			c.z_re = data->min_x + ((double)x / WINDOW_WIDTH) * (data->max_x - data->min_x);
			c.z_im = data->min_y + ((double)y / WINDOW_HEIGHT) * (data->max_y - data->min_y);
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
				img_pix_put(&data->img, x, y, get_color(iter, data->color_palette));
			x++;
		}
		y++;
	}
}

void	julia_wrapper(t_data *data)
{
	render_background(&data->img, WHITE_PIXEL);
	julia(data);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->img.mlx_img, 0, 0);
}
