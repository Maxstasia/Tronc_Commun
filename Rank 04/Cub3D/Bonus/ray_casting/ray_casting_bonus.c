/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:56:36 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/09 19:10:17 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

// Calculate ray position and direction
static void	ray_cast_init(t_data *data, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	data->ray->dir.x = data->player->dir_p.x + data->player->fov.x * camera_x;
	data->ray->dir.y = data->player->dir_p.y + data->player->fov.y * camera_x;
	data->ray->map_x = (int)(data->player->pos.x);
	data->ray->map_y = (int)(data->player->pos.y);
	data->ray->delta_dist_x = fabs(1 / data->ray->dir.x);
	data->ray->delta_dist_y = fabs(1 / data->ray->dir.y);
}

// Calculate step and initial sideDist
static void	cacl_step_and_dist(t_data *data)
{
	if (data->ray->dir.x < 0)
	{
		data->ray->step_x = -1;
		data->ray->side_dist_x = (data->player->pos.x - data->ray->map_x)
			* data->ray->delta_dist_x;
	}
	else
	{
		data->ray->step_x = 1;
		data->ray->side_dist_x = (data->ray->map_x + 1.0 - data->player->pos.x)
			* data->ray->delta_dist_x;
	}
	if (data->ray->dir.y < 0)
	{
		data->ray->step_y = -1;
		data->ray->side_dist_y = (data->player->pos.y - data->ray->map_y)
			* data->ray->delta_dist_y;
	}
	else
	{
		data->ray->step_y = 1;
		data->ray->side_dist_y = (data->ray->map_y + 1.0 - data->player->pos.y)
			* data->ray->delta_dist_y;
	}
}

static void	dda(t_data *data)
{
	bool	hit;

	hit = false;
	while (!hit)
	{
		if (data->ray->side_dist_x < data->ray->side_dist_y)
		{
			data->ray->side_dist_x += data->ray->delta_dist_x;
			data->ray->map_x += data->ray->step_x;
			data->ray->side = 0;
		}
		else
		{
			data->ray->side_dist_y += data->ray->delta_dist_y;
			data->ray->map_y += data->ray->step_y;
			data->ray->side = 1;
		}
		if (data->map->map[data->ray->map_y][data->ray->map_x] == '1')
			hit = true;
	}
}

static void	draw_wall_slice(t_data *data, int x, int wall_height)
{
	double	wall_x;
	int		tex_x;

	if (data->ray->side == 0)
		wall_x = data->player->pos.y + data->ray->perp_dist * data->ray->dir.y;
	else
		wall_x = data->player->pos.x + data->ray->perp_dist * data->ray->dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)data->map->tex_width);
	if (data->ray->side == 0 && data->ray->dir.x > 0)
		tex_x = data->map->tex_width - tex_x - 1;
	if (data->ray->side == 1 && data->ray->dir.y < 0)
		tex_x = data->map->tex_width - tex_x - 1;
	draw_wall_slice_helper(data, x, wall_height, tex_x);
}

int	ray_casting(t_data *data)
{
	int		x;
	int		wall_height;

	x = 0;
	while (x < WIN_WIDTH)
	{
		ray_cast_init(data, x);
		cacl_step_and_dist(data);
		dda(data);
		if (data->ray->side == 0)
			data->ray->perp_dist = (data->ray->map_x - data->player->pos.x
					+ (1 - data->ray->step_x) / 2) / data->ray->dir.x;
		else
			data->ray->perp_dist = (data->ray->map_y - data->player->pos.y
					+ (1 - data->ray->step_y) / 2) / data->ray->dir.y;
		wall_height = (int)(WIN_HEIGHT / data->ray->perp_dist);
		draw_wall_slice(data, x, wall_height);
		x ++;
	}
	return (0);
}
