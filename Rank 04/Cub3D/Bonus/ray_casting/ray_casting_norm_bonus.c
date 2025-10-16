/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_norm_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:27:01 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/16 13:59:38 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static char	*draw_wall_ea_we(t_data *data, t_map *map)
{
	char	*tex_data;
	void	*current_img;

	tex_data = NULL;
	if (data->ray->step_x > 0)
	{
		if (map->anim_east.is_animated)
			current_img
				= map->anim_east.frames[map->anim_east.current_frame];
		else
			current_img = map->img_east;
		tex_data = mlx_get_data_addr(current_img, &data->texture->bpp,
				&data->texture->l_len, &data->texture->endian);
	}
	else if (data->ray->step_x < 0)
	{
		if (map->anim_west.is_animated)
			current_img
				= map->anim_west.frames[map->anim_west.current_frame];
		else
			current_img = map->img_west;
		tex_data = mlx_get_data_addr(current_img, &data->texture->bpp,
				&data->texture->l_len, &data->texture->endian);
	}
	return (tex_data);
}

static char	*draw_wall_no_so(t_data *data, t_map *map)
{
	char	*tex_data;
	void	*current_img;

	tex_data = NULL;
	if (data->ray->step_y > 0)
	{
		if (map->anim_south.is_animated)
			current_img
				= map->anim_south.frames[map->anim_south.current_frame];
		else
			current_img = map->img_south;
		tex_data = mlx_get_data_addr(current_img, &data->texture->bpp,
				&data->texture->l_len, &data->texture->endian);
	}
	else if (data->ray->step_y < 0)
	{
		if (map->anim_north.is_animated)
			current_img
				= map->anim_north.frames[map->anim_north.current_frame];
		else
			current_img = map->img_north;
		tex_data = mlx_get_data_addr(current_img, &data->texture->bpp,
				&data->texture->l_len, &data->texture->endian);
	}
	return (tex_data);
}

char	*draw_wall_slice_norm(t_data *data, t_map *map)
{
	char	*tex_data;

	tex_data = NULL;
	if (data->ray->side == 0)
		tex_data = draw_wall_ea_we(data, map);
	else
		tex_data = draw_wall_no_so(data, map);
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
		img_pix_put(data->img, x, y, *(int *)(if_is_door(data, data->map)
				+ (((int)tex_pos & (data->map->tex_height - 1))
					* data->texture->l_len + tex_x
					* (data->texture->bpp / 8))));
		tex_pos += step;
		y++;
	}
}
