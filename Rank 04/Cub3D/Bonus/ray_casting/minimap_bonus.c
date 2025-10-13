/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 00:00:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/13 14:28:50 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	calculate_tile_size(t_data *data)
{
	int	map_height;
	int	max_width;
	int	tile_w;
	int	tile_h;
	int	y;

	map_height = -1;
	max_width = 0;
	while (map_height ++, data->map->map[map_height])
	{
		y = ft_strlen(data->map->map[map_height]);
		if (y > max_width)
			max_width = y;
	}
	if (max_width == 0 || map_height == 0)
		return (data->minimap->tile_size = 10, 0);
	tile_w = (data->minimap->size - 4) / max_width;
	tile_h = (data->minimap->size - 4) / map_height;
	if (tile_w < tile_h)
		data->minimap->tile_size = tile_w;
	else
		data->minimap->tile_size = tile_h;
	if (data->minimap->tile_size < 2)
		data->minimap->tile_size = 2;
	return (0);
}

static void	draw_player(t_data *data, int center_x, int center_y)
{
	int		i;
	int		j;
	int		dx;
	int		dy;
	int		radius;

	radius = data->minimap->tile_size / 2;
	i = -radius - 1;
	while (i ++, i <= radius)
	{
		j = -radius - 1;
		while (j ++, j <= radius)
		{
			dx = i;
			dy = j;
			if (dx * dx + dy * dy <= radius * radius)
				if (center_x + i >= data->minimap->offset_x
					&& center_x + i < data->minimap->offset_x
					+ data->minimap->size && center_y
					+ j >= data->minimap->offset_y && center_y + j
					< data->minimap->offset_y + data->minimap->size)
					img_pix_put(data->img, center_x + i - 2, center_y + j - 2,
						data->minimap->player_color);
		}
	}
}

static void	draw_minimap_border(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->minimap->size)
	{
		img_pix_put(data->img, data->minimap->offset_x + i,
			data->minimap->offset_y, data->minimap->border_color);
		img_pix_put(data->img, data->minimap->offset_x + i,
			data->minimap->offset_y + data->minimap->size - 1,
			data->minimap->border_color);
		img_pix_put(data->img, data->minimap->offset_x,
			data->minimap->offset_y + i, data->minimap->border_color);
		img_pix_put(data->img, data->minimap->offset_x
			+ data->minimap->size - 1,
			data->minimap->offset_y + i, data->minimap->border_color);
		i++;
	}
}

void	draw_minimap(t_data *data, t_minimap *minimap)
{
	int		player_x;
	int		player_y;

	if (!data->minimap || !data->map || !data->map->map)
		return ;
	calculate_tile_size(data);
	while (data->map->map[minimap->map_height])
		minimap->map_height++;
	draw_minimap_helper(data, minimap, 0, 0);
	player_x = minimap->offset_x + (int)(data->player->pos.x
			* minimap->tile_size) + minimap->tile_size / 2;
	player_y = minimap->offset_y + (int)(data->player->pos.y
			* minimap->tile_size) + minimap->tile_size / 2;
	draw_player(data, player_x, player_y);
	draw_minimap_border(data);
}
