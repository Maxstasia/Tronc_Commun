/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:07:11 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/07 18:55:49 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	img_pix_put(t_image *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->l_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

static int	get_color_from_map(t_data *data, int is_floor)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	int		color;

	if (is_floor)
		rgb = ft_split(data->map->color_floor, ',');
	else
		rgb = ft_split(data->map->color_ceiling, ',');
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_split(rgb);
	color = (r << 16) | (g << 8) | b;
	return (color);
}

static void	draw_floor_ceiling(t_data *data)
{
	int	x;
	int	y;
	int	floor_color;
	int	ceiling_color;

	floor_color = get_color_from_map(data, 1);
	ceiling_color = get_color_from_map(data, 0);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				img_pix_put(data->img, x, y, ceiling_color);
			else
				img_pix_put(data->img, x, y, floor_color);
			x++;
		}
		y++;
	}
}

int	render_frame(t_data *data)
{
	draw_floor_ceiling(data);
	ray_casting(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img->mlx_img, 0, 0);
	return (0);
}
