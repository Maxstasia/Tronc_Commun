/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_helper_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:26:22 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/13 14:27:17 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;
	int	screen_x;
	int	screen_y;

	i = 0;
	while (i < data->minimap->tile_size)
	{
		j = 0;
		while (j < data->minimap->tile_size)
		{
			screen_x = data->minimap->offset_x + x
				* data->minimap->tile_size + i;
			screen_y = data->minimap->offset_y + y
				* data->minimap->tile_size + j;
			if (screen_x >= data->minimap->offset_x
				&& screen_x < data->minimap->offset_x + data->minimap->size
				&& screen_y >= data->minimap->offset_y
				&& screen_y < data->minimap->offset_y + data->minimap->size)
				img_pix_put(data->img, screen_x, screen_y, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_helper(t_data *data, t_minimap *minimap, int x, int y)
{
	y = -1;
	while (y ++, y < minimap->map_height
		&& y < minimap->size / minimap->tile_size)
	{
		x = -1;
		minimap->map_width = ft_strlen(data->map->map[y]);
		while (x ++, x < minimap->map_width
			&& x < minimap->size / minimap->tile_size)
		{
			if (data->map->map[y][x] == '1')
				draw_square(data, x, y, minimap->wall_color);
			if (data->map->map[y][x] == 'P')
				draw_square(data, x, y, minimap->door_color);
			if (data->map->map[y][x] == '2')
				draw_square(data, x, y, minimap->door_open_color);
			else if (data->map->map[y][x] == '0'
				|| data->map->map[y][x] == 'N'
				|| data->map->map[y][x] == 'S'
				|| data->map->map[y][x] == 'E'
				|| data->map->map[y][x] == 'W')
				draw_square(data, x, y, minimap->floor_color);
		}
	}
}
