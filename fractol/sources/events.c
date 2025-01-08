/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:05:04 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/08 14:57:08 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
		exit(0);
	}
	else if ((keysym == XK_space)
		|| (keysym == XK_Return) || (keysym == XK_KP_Enter))
	{
		data->color_palette = (data->color_palette + 1) % 10;
		render(data);
	}
	return (0);
}

int	handle_destroy(t_data *data)
{
	if (data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	exit(0);
	return (0);
}

int	handle_scroll(int button, int x, int y, t_data *data)
{
	double	mouse_re;
	double	mouse_im;
	double	zoom_factor;

	// Convertir la position de la souris dans le plan complexe
	mouse_re = data->min_x + x * (data->max_x - data->min_x) / WINDOW_WIDTH;
	mouse_im = data->min_y + y * (data->max_y - data->min_y) / WINDOW_HEIGHT;
	if (button == 4)
		zoom_factor = 0.9;
	else if (button == 5)
		zoom_factor = 1.1;
	else
		return (0);
	// Ajuster les limites en fonction du zoom
	data->min_x = mouse_re + (data->min_x - mouse_re) * zoom_factor;
	data->max_x = mouse_re + (data->max_x - mouse_re) * zoom_factor;
	data->min_y = mouse_im + (data->min_y - mouse_im) * zoom_factor;
	data->max_y = mouse_im + (data->max_y - mouse_im) * zoom_factor;
	render(data);
	return (0);
}
