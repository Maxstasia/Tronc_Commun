/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:40:27 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/13 13:57:14 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	init_minimap(t_data *data)
{
	data->minimap = malloc(sizeof(t_minimap));
	if (!data->minimap)
		return ;
	data->minimap->map_height = 0;
	data->minimap->map_width = 0;
	data->minimap->size = 300;
	data->minimap->offset_x = WIN_WIDTH - data->minimap->size - 20;
	data->minimap->offset_y = 20;
	data->minimap->wall_color = 0x333333;
	data->minimap->door_color = 0x996633;
	data->minimap->door_open_color = 0x00FF00;
	data->minimap->floor_color = 0xCCCCCC;
	data->minimap->player_color = 0xFF0000;
	data->minimap->border_color = 0x000000;
	data->minimap->tile_size = 10;
}
