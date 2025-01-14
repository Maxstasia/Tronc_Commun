/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:05:04 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/14 16:44:07 by mstasiak         ###   ########.fr       */
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
	else if (keysym == XK_e && data->cur_img == 1)
	{
		data->c_re += 0.01;
		data->c_im -= 0.01;
		render_background(&data->img, WHITE_PIXEL);
		julia(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.mlx_img, 0, 0);
	}
	else if (keysym == XK_q && data->cur_img == 1)
	{
		data->c_re -= 0.001;
		data->c_im += 0.001;
		render_background(&data->img, WHITE_PIXEL);
		julia(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.mlx_img, 0, 0);
	}
	else if (keysym == XK_a && data->cur_img == 1)
		data->animate *= -1;
	else if (keysym == XK_Left)
	{
	    double range_x = data->max_x - data->min_x;
	    data->min_x -= MOVE_STEP * range_x;
	    data->max_x -= MOVE_STEP * range_x;
	    render(data);
	}
	else if (keysym == XK_Right)
	{
	    double range_x = data->max_x - data->min_x;
	    data->min_x += MOVE_STEP * range_x;
	    data->max_x += MOVE_STEP * range_x;
	    render(data);
	}
	else if (keysym == XK_Up)
	{
	    double range_y = data->max_y - data->min_y;
	    data->min_y -= MOVE_STEP * range_y;
	    data->max_y -= MOVE_STEP * range_y;
	    render(data);
	}
	else if (keysym == XK_Down)
	{
	    double range_y = data->max_y - data->min_y;
	    data->min_y += MOVE_STEP * range_y;
	    data->max_y += MOVE_STEP * range_y;
	    render(data);
	}
	else if (keysym == XK_Escape)
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

int	update_frame(t_data *data)
{
	if (data->animate == -1)
	{
		if (data->c_re < -1.5 || data->c_re > 1.5
			|| data->c_im < -1.5 || data->c_im > 1.5)
			data->speed = 0.04;
		else
			data->speed = 0.001;
		data->c_re += (data->speed * data->direction);
		data->c_im -= (data->speed * data->direction);
		if (data->c_re < -2 || data->c_re > 2
			|| data->c_im < -2 || data->c_im > 2)
			data->direction *= -1;
		render_background(&data->img, WHITE_PIXEL);
		julia(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	}
	return (0);
}

void	print_command(void)
{
	ft_printf("Command :\n");
	ft_printf("	For All :\n");
	ft_printf("\n");
	ft_printf("	- Button 5 (mouse scroll) : zoom;\n");
	ft_printf("	- Button 4 (mouse scroll) : unzoom;\n");
	ft_printf("	- Space, Enter and Return : change color;\n");
	ft_printf("	- Arrow keys : move the view;\n");
	ft_printf("\n");
	ft_printf("	For Julia :\n");
	ft_printf("	- Keybord 'e' or 'q': change value/parameter;\n");
	ft_printf("	- Keybord 'a' : change value/parameter automatically;\n");
}