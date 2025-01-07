/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:39:15 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/07 14:56:19 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	julia(t_data *data, double c_re, double c_im)
{
	int		x;
	int		y;
	int		iter;
	double	z_re;
	double	z_im;
	double	temp;

	y = -1;
	while (y ++, y < WINDOW_HEIGHT)
	{
		x = -1;
		while (x ++, x < WINDOW_WIDTH)
		{
			// Convertir coordonnées pixel -> coordonnées complexes
			z_re = data->min_x + x * (data->max_x - data->min_x) / WINDOW_WIDTH;
			z_im = data->min_y + y * (data->max_y - data->min_y) / WINDOW_HEIGHT;
			iter = 0;
			// Itérations Julia
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

void	julia_wrapper(t_data *data, double c_re, double c_im)
{
	data->cur_img = 1;
	render_background(&data->img, WHITE_PIXEL); // Effacer l'image
	julia(data, c_re, c_im); // Dessiner Julia avec les constantes données
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}
