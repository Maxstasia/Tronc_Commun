/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:03:14 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/15 14:20:46 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_map(t_data *data)
{
	data->map->texture_north = NULL;
	data->map->texture_south = NULL;
	data->map->texture_west = NULL;
	data->map->texture_east = NULL;
	data->map->img_north = NULL;
	data->map->img_south = NULL;
	data->map->img_west = NULL;
	data->map->img_east = NULL;
	data->map->tex_width = 0;
	data->map->tex_height = 0;
	data->map->color_floor = NULL;
	data->map->color_ceiling = NULL;
	data->map->map = NULL;
	data->map->player_direction = '\0';
}
