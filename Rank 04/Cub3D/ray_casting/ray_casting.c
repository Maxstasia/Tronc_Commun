/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:56:36 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/11 14:12:15 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void		ray_cast_init(t_data *data, int x)
{
	// Calculate ray position and direction
	double camera_x = 2 * x / (double)WIN_WIDTH - 1;
	data->ray->dir.x = data->player->dir_p.x + data->player->fov.x * camera_x;
	data->ray->dir.y = data->player->dir_p.y + data->player->fov.y * camera_x;
	data->ray->map_x = (int)(data->player->pos.x);
	data->ray->map_y = (int)(data->player->pos.y);
	data->ray->delta_dist_x = fabs(1 / data->ray->dir.x);
	data->ray->delta_dist_y = fabs(1 / data->ray->dir.y);
}

static void		cacl_step_and_dist(t_data *data)
{
	// Calculate step and initial sideDist
	if (data->ray->dir.x < 0)
	{
		data->ray->step_x = -1;
		data->ray->side_dist_x = (data->player->pos.x - data->ray->map_x) * data->ray->delta_dist_x;
	}
	else
	{
		data->ray->step_x = 1;
		data->ray->side_dist_x = (data->ray->map_x + 1.0 - data->player->pos.x) * data->ray->delta_dist_x;
	}
	if (data->ray->dir.y < 0)
	{
		data->ray->step_y = -1;
		data->ray->side_dist_y = (data->player->pos.y - data->ray->map_y) * data->ray->delta_dist_y;
	}
	else
	{
		data->ray->step_y = 1;
		data->ray->side_dist_y = (data->ray->map_y + 1.0 - data->player->pos.y) * data->ray->delta_dist_y;
	}
}

static void		dda(t_data *data)
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

int		ray_casting(t_data *data)
{
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		ray_cast_init(data, x);
		cacl_step_and_dist(data);
		dda(data);

		// Anti fisheye
		if (data->ray->side == 0)
			data->ray->perp_dist = (data->ray->map_x - data->player->pos.x
				+ (1 - data->ray->step_x) / 2) / data->ray->dir.x;
		else
			data->ray->perp_dist = (data->ray->map_y - data->player->pos.y
				+ (1 - data->ray->step_y) / 2) / data->ray->dir.y;
	}
	return (0);
}
