/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:05:04 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/24 15:45:17 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	handle_keypress(int keysym, t_data *data)
{
	if (data->cur_img == 1)
		julia_keypress(keysym, data);
	if (keysym == XK_Escape
		|| keysym == XK_BackSpace || keysym == XK_Delete)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		data->win_ptr = NULL;
		free(data->mlx_ptr);
		exit(0);
	}
	return (0);
}

void	julia_keypress(int keysym, t_data *data)
{
	if (keysym == XK_e)
	{
		data->c.c_re += 0.001;
		data->c.c_im -= 0.001;
		render_background(data, WHITE_PIXEL);
		julia(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.mlx_img, 0, 0);
	}
	else if (keysym == XK_q)
	{
		data->c.c_re -= 0.001;
		data->c.c_im += 0.001;
		render_background(data, WHITE_PIXEL);
		julia(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.mlx_img, 0, 0);
	}
	else if (keysym == XK_a)
		data->move.animate *= -1;
}
