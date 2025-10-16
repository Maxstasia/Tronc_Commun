/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_teleporters_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:48:36 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/16 11:04:03 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	teleporters_3_to_6(t_map *map, int i, int j)
{
	if (map->map[i][j] == '3')
		return (map->teleporter_3->numbers++, 1);
	if (map->map[i][j] == '4')
		return (map->teleporter_4->numbers++, 1);
	if (map->map[i][j] == '5')
		return (map->teleporter_5->numbers++, 1);
	if (map->map[i][j] == '6')
		return (map->teleporter_6->numbers++, 1);
	return (0);
}

static int	has_teleporters_in_map(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (i ++, map->map[i])
	{
		j = -1;
		while (j ++, map->map[i][j])
		{
			if (teleporters_3_to_6(map, i, j))
				return (1);
		}
	}
	return (0);
}

int	check_teleporters(t_data *data)
{
	if (has_teleporters_in_map(data->map) && !data->map->texture_teleport)
	{
		data->map->texture_teleport = ft_strdup("textures/teleport_64x64.xpm");
		if (!data->map->texture_teleport)
			return (print_error(MALLOC_ERROR, data), 1);
	}
	if (data->map->teleporter_3->numbers > 1
		|| data->map->teleporter_4->numbers > 1
		|| data->map->teleporter_5->numbers > 1
		|| data->map->teleporter_6->numbers > 1)
		return (print_error(TOO_MANY_TELEPORTERS_ERROR, data), 1);
	return (0);
}
