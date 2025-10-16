/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:18:40 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/16 14:48:30 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_closed_map(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (i ++, data->map->map[i])
	{
		j = -1;
		while (j ++, data->map->map[i][j])
		{
			if (data->map->map[i][j] == '0' || is_player(data->map->map[i][j])
				|| data->map->map[i][j] == 'P' || data->map->map[i][j] == '3'
				|| data->map->map[i][j] == '4' || data->map->map[i][j] == '5'
				|| data->map->map[i][j] == '6')
			{
				if (i == 0 || j == 0 || data->map->map[i - 1][j] == ' '
					|| !data->map->map[i + 1] || !data->map->map[i][j + 1]
					|| data->map->map[i + 1][j] == ' ')
					return (print_error(MAP_ERROR, data), 1);
				if (data->map->map[i][j - 1] == ' '
					|| data->map->map[i][j + 1] == ' ')
					return (print_error(MAP_ERROR, data), 1);
			}
		}
	}
	return (0);
}

static int	map_structure_norm(t_data *data, int player_count, int i, int j)
{
	if (data->map->map[i][j] == 'N' || data->map->map[i][j] == 'S' ||
		data->map->map[i][j] == 'E' || data->map->map[i][j] == 'W')
	{
		player_count++;
		data->map->player_direction = data->map->map[i][j];
	}
	else if (data->map->map[i][j] != '0' && data->map->map[i][j] != '1'
		&& data->map->map[i][j] != ' ' && data->map->map[i][j] != 'P'
		&& data->map->map[i][j] != '3' && data->map->map[i][j] != '4'
		&& data->map->map[i][j] != '5' && data->map->map[i][j] != '6')
		return (print_error(MAP_ERROR, data), 2);
	return (player_count);
}

static int	validate_map_structure(t_data *data)
{
	int		player_count;
	int		i;
	int		j;

	player_count = 0;
	i = -1;
	while (++ i, data->map->map[i])
	{
		j = -1;
		while (++ j, data->map->map[i][j])
		{
			if (data->map->map[i][j] == '3')
				data->map->teleporter_3->pos = (t_vector){j, i};
			else if (data->map->map[i][j] == '4')
				data->map->teleporter_4->pos = (t_vector){j, i};
			else if (data->map->map[i][j] == '5')
				data->map->teleporter_5->pos = (t_vector){j, i};
			else if (data->map->map[i][j] == '6')
				data->map->teleporter_6->pos = (t_vector){j, i};
			player_count = map_structure_norm(data, player_count, i, j);
		}
	}
	if (player_count != 1)
		return (print_error(MAP_ERROR, data), 1);
	return (0);
}

int	validate_map(t_data *data, t_map *map)
{
	int	map_height;

	map_height = count_map_lines(map->map);
	if (!map->texture_north || !map->texture_south
		|| !map->texture_west || !map->texture_east
		|| !map->color_floor || !map->color_ceiling
		|| !map->map)
		return (print_error(MAP_ERROR, data), 1);
	if (check_doors(data))
		return (1);
	if (check_teleporters(data))
		return (1);
	if (validate_colors(data))
		return (1);
	if (validate_map_structure(data))
		return (1);
	if (map->map[map_height - 2][ft_strlen(map->map[map_height - 1])]
		&& map->map[map_height - 2][ft_strlen(map->map[map_height - 1])] != '1')
		return (print_error(MAP_ERROR, data), 1);
	if (check_closed_map(data))
		return (1);
	return (0);
}
