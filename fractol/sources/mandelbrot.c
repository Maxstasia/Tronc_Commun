/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:39:18 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/03 18:19:52 by mstasiak         ###   ########.fr       */
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
			c_re = (x - WINDOW_WIDTH / 2.0) * 4.0 / WINDOW_WIDTH;
			c_im = (y - WINDOW_HEIGHT / 2.0) * 4.0 / WINDOW_HEIGHT;
			z_re = 0;
			z_im = 0;
			iter = 0;

			// Itérations Mandelbrot
			while (z_re * z_re + z_im * z_im <= 4 && iter < MAX_ITER)
			{
				temp = z_re * z_re - z_im * z_im + c_re;
				z_im = 2 * z_re * z_im + c_im;
				z_re = temp;
				iter++;
			}

			// Colorier le pixel en fonction du nombre d'itérations
			if (iter == MAX_ITER)
				img_pix_put(&data->img, x, y, BLACK_PIXEL);
			else
				img_pix_put(&data->img, x, y, get_color(iter, data->color_palette));
		}
	}
}