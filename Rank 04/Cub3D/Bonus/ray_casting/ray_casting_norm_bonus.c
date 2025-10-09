/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_norm_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:27:01 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/09 19:10:17 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static char	*draw_wall_slice_norm(t_data *data)
{
	char	*tex_data;

	if (data->ray->side == 0)
	{
		if (data->ray->step_x > 0)
			tex_data = mlx_get_data_addr(data->map->img_east,
					&data->texture->bpp, &data->texture->l_len,
					&data->texture->endian);
		if (data->ray->step_x < 0)
			tex_data = mlx_get_data_addr(data->map->img_west,
					&data->texture->bpp, &data->texture->l_len,
					&data->texture->endian);
	}
	else
	{
		if (data->ray->step_y > 0)
			tex_data = mlx_get_data_addr(data->map->img_south,
					&data->texture->bpp, &data->texture->l_len,
					&data->texture->endian);
		if (data->ray->step_y < 0)
			tex_data = mlx_get_data_addr(data->map->img_north,
					&data->texture->bpp, &data->texture->l_len,
					&data->texture->endian);
	}
	return (tex_data);
}

void	draw_wall_slice_helper(t_data *data, int x, int wall_height, int tex_x)
{
	int		wall_start;
	int		wall_end;
	int		y;
	double	step;
	double	tex_pos;

	wall_start = (WIN_HEIGHT - wall_height) / 2;
	if (wall_start < 0)
		wall_start = 0;
	wall_end = (WIN_HEIGHT + wall_height) / 2;
	if (wall_end >= WIN_HEIGHT)
		wall_end = WIN_HEIGHT - 1;
	step = 1.0 * data->map->tex_height / wall_height;
	tex_pos = (wall_start - WIN_HEIGHT / 2 + wall_height / 2) * step;
	y = wall_start;
	while (y < wall_end)
	{
		img_pix_put(data->img, x, y, *(int *)(draw_wall_slice_norm(data)
				+ (((int)tex_pos & (data->map->tex_height - 1))
					* data->texture->l_len + tex_x
					* (data->texture->bpp / 8))));
		tex_pos += step;
		y++;
	}
}
