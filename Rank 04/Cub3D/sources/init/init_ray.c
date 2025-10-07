/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:22:49 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/07 14:25:19 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_ray(t_data *data)
{
	data->ray->dir.x = 0;
	data->ray->dir.y = 0;
	data->ray->perp_dist = 0;
	data->ray->map_x = 0;
	data->ray->map_y = 0;
	data->ray->side = 0;
	data->ray->side_dist_x = 0;
	data->ray->side_dist_y = 0;
	data->ray->delta_dist_x = 0;
	data->ray->delta_dist_y = 0;
	data->ray->step_x = 0;
	data->ray->step_y = 0;
}
