/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 00:00:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/10 18:59:38 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/**
 * Calcule la taille des tuiles en fonction de la taille de la map
 */
static void	calculate_tile_size(t_data *data)
{
	int	map_height;
	int	max_width;
	int	tile_w;
	int	tile_h;
	int	y;

	map_height = 0;
	max_width = 0;
	while (data->map->map[map_height])
	{
		y = ft_strlen(data->map->map[map_height]);
		if (y > max_width)
			max_width = y;
		map_height++;
	}
	if (max_width == 0 || map_height == 0)
	{
		data->minimap->tile_size = 10;
		return ;
	}
	tile_w = (data->minimap->size - 4) / max_width;
	tile_h = (data->minimap->size - 4) / map_height;
	if (tile_w < tile_h)
		data->minimap->tile_size = tile_w;
	else
		data->minimap->tile_size = tile_h;
	if (data->minimap->tile_size < 2)
		data->minimap->tile_size = 2;
}

/**
 * Initialise la minimap avec les paramètres par défaut
 */
void	init_minimap(t_data *data)
{
	data->minimap = malloc(sizeof(t_minimap));
	if (!data->minimap)
		return ;
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

/**
 * Dessine un carré plein sur la minimap
 */
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

/**
 * Dessine un cercle pour représenter le joueur
 */
static void	draw_player(t_data *data, int center_x, int center_y)
{
	int		i;
	int		j;
	int		dx;
	int		dy;
	int		radius;

	radius = data->minimap->tile_size / 2;
	i = -radius;
	while (i <= radius)
	{
		j = -radius;
		while (j <= radius)
		{
			dx = i;
			dy = j;
			if (dx * dx + dy * dy <= radius * radius)
			{
				if (center_x + i >= data->minimap->offset_x
					&& center_x + i
					< data->minimap->offset_x + data->minimap->size
					&& center_y + j >= data->minimap->offset_y
					&& center_y + j
					< data->minimap->offset_y + data->minimap->size)
					img_pix_put(data->img, center_x + i - 2, center_y + j - 2,
						data->minimap->player_color);
			}
			j++;
		}
		i++;
	}
}

/**
 * Dessine la bordure de la minimap
 */
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

/**
 * Dessine la minimap complète
 */
void	draw_minimap(t_data *data)
{
	int		x;
	int		y;
	int		map_height;
	int		map_width;
	int		player_x;
	int		player_y;

	if (!data->minimap || !data->map || !data->map->map)
		return ;
	calculate_tile_size(data);
	map_height = 0;
	while (data->map->map[map_height])
		map_height++;
	y = 0;
	while (y < map_height && y < data->minimap->size / data->minimap->tile_size)
	{
		x = 0;
		map_width = ft_strlen(data->map->map[y]);
		while (x < map_width && x < data->minimap->size
			/ data->minimap->tile_size)
		{
			if (data->map->map[y][x] == '1')
				draw_square(data, x, y, data->minimap->wall_color);
			if (data->map->map[y][x] == 'P')
				draw_square(data, x, y, data->minimap->door_color);
			if (data->map->map[y][x] == '2')
				draw_square(data, x, y, data->minimap->door_open_color);
			else if (data->map->map[y][x] == '0'
				|| data->map->map[y][x] == 'N'
				|| data->map->map[y][x] == 'S'
				|| data->map->map[y][x] == 'E'
				|| data->map->map[y][x] == 'W')
				draw_square(data, x, y, data->minimap->floor_color);
			x++;
		}
		y++;
	}
	player_x = data->minimap->offset_x
		+ (int)(data->player->pos.x * data->minimap->tile_size)
		+ data->minimap->tile_size / 2;
	player_y = data->minimap->offset_y
		+ (int)(data->player->pos.y * data->minimap->tile_size)
		+ data->minimap->tile_size / 2;
	draw_player(data, player_x, player_y);
	draw_minimap_border(data);
}
