/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:39:18 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/07 14:53:49 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	mandelbrot(t_data *data)
{
	int		x;
	int		y;
	int		iter;
	double	z_re;
	double	z_im;
	double	c_re;
	double	c_im;
	double	temp;

	y = -1;
	while (y ++, y < WINDOW_HEIGHT)
	{
		x = -1;
		while (x ++, x < WINDOW_WIDTH)
		{
			// Convertir coordonnées pixel -> coordonnées complexes
			c_re = data->min_x + x * (data->max_x - data->min_x) / WINDOW_WIDTH;
			c_im = data->min_y + y * (data->max_y - data->min_y) / WINDOW_HEIGHT;
			z_re = 0;
			z_im = 0;
			iter = 0;
			// Itérations Mandelbrot
			while ((z_re * z_re + z_im * z_im) < 4 && ++iter < MAX_ITER)
			{
				temp = z_re * z_re - z_im * z_im + c_re;
				z_im = 2 * z_re * z_im + c_im;
				z_re = temp;
			}
			// Colorier le pixel en fonction du nombre d'itérations
			if (iter == MAX_ITER)
				img_pix_put(&data->img, x, y, BLACK_PIXEL);
			else
				img_pix_put(&data->img, x, y, get_color(iter, data->color_palette));
		}
	}
}

void	mandelbrot_wrapper(t_data *data)
{
	data->cur_img = 0;
	render_background(&data->img, WHITE_PIXEL); // Effacer l'image
	mandelbrot(data); // Dessiner Mandelbrot
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}
