/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:05:04 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/24 16:05:39 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	handle_destroy(t_data *data)
{
	if (data->win_ptr)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		data->win_ptr = NULL;
		free(data->mlx_ptr);
	}
	exit(0);
	return (0);
}

int	handle_scroll(int button, int x, int y, t_data *data)
{
	double	center_re;
	double	center_im;
	double	zoom_factor;

	(void)x;
	(void)y;
	center_re = (data->min_x + data->max_x) / 2.0;
	center_im = (data->min_y + data->max_y) / 2.0;
	if (button == 4)
		zoom_factor = 0.9;
	else if (button == 5)
		zoom_factor = 1.1;
	else
		return (0);
	data->min_x = center_re + (data->min_x - center_re) * zoom_factor;
	data->max_x = center_re + (data->max_x - center_re) * zoom_factor;
	data->min_y = center_im + (data->min_y - center_im) * zoom_factor;
	data->max_y = center_im + (data->max_y - center_im) * zoom_factor;
	render(data);
	return (0);
}
