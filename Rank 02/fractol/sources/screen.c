/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:34:38 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/24 15:45:24 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	img_pix_put(t_data *data, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = data->img.bpp - 8;
	pixel = data->img.addr + (y * data->img.l_len + x * (data->img.bpp / 8));
	while (i >= 0)
	{
		if (data->img.endian != 0)
			*pixel++ = (color >> i) & WHITE_PIXEL;
		else
			*pixel++ = (color >> (data->img.bpp - 8 - i)) & WHITE_PIXEL;
		i -= 8;
	}
}

void	render_background(t_data *data, int color)
{
	int	i;
	int	j;

	i = -1;
	while (i ++, i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			img_pix_put(data, j++, i, color);
	}
}

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	if (data->cur_img == 0)
		mandelbrot(data);
	else if (data->cur_img == 1)
		julia(data);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int	update_frame(t_data *data)
{
	if (data->move.animate == -1)
	{
		if (data->c.c_re < -1.5 || data->c.c_re > 1.5
			|| data->c.c_im < -1.5 || data->c.c_im > 1.5)
			data->move.speed = 0.04;
		else
			data->move.speed = 0.001;
		data->c.c_re += (data->move.speed * data->move.direction);
		data->c.c_im -= (data->move.speed * data->move.direction);
		if (data->c.c_re < -2 || data->c.c_re > 2
			|| data->c.c_im < -2 || data->c.c_im > 2)
			data->move.direction *= -1;
		render_background(data, WHITE_PIXEL);
		julia(data);
		mlx_put_image_to_window(data->mlx_ptr,
			data->win_ptr, data->img.mlx_img, 0, 0);
	}
	return (0);
}
