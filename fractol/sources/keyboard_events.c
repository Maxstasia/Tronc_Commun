/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:05:04 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/15 16:09:18 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	handle_keypress(int keysym, t_data *data)
{
	if ((keysym == XK_space)
		|| (keysym == XK_Return) || (keysym == XK_KP_Enter))
	{
		data->color_palette = (data->color_palette + 1) % 10;
		render(data);
	}
	julia_keypress(keysym, data);
	harrow_x_keypress(keysym, data);
	harrow_y_keypress(keysym, data);
	if (keysym == XK_Escape || keysym == XK_BackSpace || keysym == XK_Delete)
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
	if (keysym == XK_e && data->cur_img == 1)
	{
		data->c.c_re += 0.01;
		data->c.c_im -= 0.01;
		render_background(&data->img, WHITE_PIXEL);
		julia(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.mlx_img, 0, 0);
	}
	else if (keysym == XK_q && data->cur_img == 1)
	{
		data->c.c_re -= 0.001;
		data->c.c_im += 0.001;
		render_background(&data->img, WHITE_PIXEL);
		julia(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.mlx_img, 0, 0);
	}
	else if (keysym == XK_a && data->cur_img == 1)
		data->move.animate *= -1;
}

void	harrow_x_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Left)
	{
		data->move.range_x = data->max_x - data->min_x;
		data->min_x -= MOVE_STEP * data->move.range_x;
		data->max_x -= MOVE_STEP * data->move.range_x;
		render(data);
	}
	else if (keysym == XK_Right)
	{
		data->move.range_x = data->max_x - data->min_x;
		data->min_x += MOVE_STEP * data->move.range_x;
		data->max_x += MOVE_STEP * data->move.range_x;
		render(data);
	}
}

void	harrow_y_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Up)
	{
		data->move.range_y = data->max_y - data->min_y;
		data->min_y -= MOVE_STEP * data->move.range_y;
		data->max_y -= MOVE_STEP * data->move.range_y;
		render(data);
	}
	else if (keysym == XK_Down)
	{
		data->move.range_y = data->max_y - data->min_y;
		data->min_y += MOVE_STEP * data->move.range_y;
		data->max_y += MOVE_STEP * data->move.range_y;
		render(data);
	}
}
