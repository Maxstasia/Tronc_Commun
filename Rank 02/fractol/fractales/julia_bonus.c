/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:39:15 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/24 15:45:00 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol_bonus.h"

void	julia(t_data *data)
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
			iter = julia_calcul(data, x, y);
			if (iter == MAX_ITER)
				img_pix_put(data, x, y, BLACK_PIXEL);
			else
				img_pix_put(data, x, y, get_color(iter, data->color_palette));
		}
	}
}

int	julia_calcul(t_data *data, int x, int y)
{
	double	temp;
	int		iter;

	data->c.z_re = data->min_x
		+ ((double)x / WINDOW_WIDTH) * (data->max_x - data->min_x);
	data->c.z_im = data->min_y
		+ ((double)y / WINDOW_HEIGHT) * (data->max_y - data->min_y);
	iter = 0;
	while ((data->c.z_re * data->c.z_re + data->c.z_im * data->c.z_im)
		<= 4 && iter < MAX_ITER)
	{
		temp = data->c.z_re
			* data->c.z_re - data->c.z_im * data->c.z_im + data->c.c_re;
		data->c.z_im = 2 * data->c.z_re * data->c.z_im + data->c.c_im;
		data->c.z_re = temp;
		iter++;
	}
	return (iter);
}

void	julia_wrapper(t_data *data)
{
	data->cur_img = 1;
	render_background(data, WHITE_PIXEL);
	julia(data);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->img.mlx_img, 0, 0);
	mlx_loop_hook(data->mlx_ptr, &update_frame, data);
}
