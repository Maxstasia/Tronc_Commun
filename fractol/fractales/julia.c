/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:39:15 by mstasiak          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/01/08 17:30:07 by mstasiak         ###   ########.fr       */
=======
/*   Updated: 2025/01/07 14:56:19 by mstasiak         ###   ########.fr       */
>>>>>>> 3eb167efb220bee2cf39692333508d1919ace0d9
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* void	julia(t_data *data, double c_re, double c_im)
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
			c.z_re = data->min_x + x
				* (data->max_x - data->min_x) / WINDOW_WIDTH;
			c.z_im = data->min_y + y
				* (data->max_y - data->min_y) / WINDOW_HEIGHT;
			iter = 0;
<<<<<<< HEAD
			while ((c.z_re * c.z_re + c.z_im * c.z_im) < 4 && ++iter < MAX_ITER)
			{
				temp = c.z_re * c.z_re - c.z_im * c.z_im + c_re;
				c.z_im = 2 * c.z_re * c.z_im + c_im;
				c.z_re = temp;
				//printf("x=%d, y=%d, z_re=%f, z_im=%f, iter=%d\n", x, y, c.z_re, c.z_im, iter);
=======
			// Itérations Julia
			while ((z_re * z_re + z_im * z_im) < 4 && ++iter < MAX_ITER)
			{
				temp = z_re * z_re - z_im * z_im + c_re;
				z_im = 2 * z_re * z_im + c_im;
				z_re = temp;
>>>>>>> 3eb167efb220bee2cf39692333508d1919ace0d9
			}
			if (iter == MAX_ITER)
				img_pix_put(&data->img, x, y, BLACK_PIXEL);
			else
				img_pix_put(&data->img,
					x, y, get_color(iter, data->color_palette));
			// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
		}
	}
}

void	julia_wrapper(t_data *data, double c_re, double c_im)
{
	data->min_x = -2.0;
	data->max_x = 2.0;
	data->min_y = -2.0;
	data->max_y = 2.0;
	data->c_re = -0.8;
	data->c_im = 0.156;
	data->cur_img = 1;
	render_background(&data->img, WHITE_PIXEL);
	julia(data, c_re, c_im);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->img.mlx_img, 0, 0);
} */

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
