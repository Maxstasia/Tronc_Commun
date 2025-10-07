/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:07:32 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/07 18:52:15 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	set_player_direction(t_data *data)
{
	if (data->map->player_direction == 'N')
	{
		data->player->dir_p.x = 0;
		data->player->dir_p.y = -1;
		data->player->fov.x = tan(FOV / 2);
		data->player->fov.y = 0;
	}
	else if (data->map->player_direction == 'S')
	{
		data->player->dir_p.x = 0;
		data->player->dir_p.y = 1;
		data->player->fov.x = -tan(FOV / 2);
		data->player->fov.y = 0;
	}
	else if (data->map->player_direction == 'E')
	{
		data->player->dir_p.x = 1;
		data->player->dir_p.y = 0;
		data->player->fov.x = 0;
		data->player->fov.y = tan(FOV / 2);
	}
	else if (data->map->player_direction == 'W')
	{
		data->player->dir_p.x = -1;
		data->player->dir_p.y = 0;
		data->player->fov.x = 0;
		data->player->fov.y = -tan(FOV / 2);
	}
}

void	find_player_position(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (data->map->map[i][j] == 'N' || data->map->map[i][j] == 'S'
				|| data->map->map[i][j] == 'E' || data->map->map[i][j] == 'W')
			{
				data->player->pos.x = j + 0.5;
				data->player->pos.y = i + 0.5;
				set_player_direction(data);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	init_player(t_data *data)
{
	data->player->pos.x = 0;
	data->player->pos.y = 0;
	data->player->dir_p.x = 0;
	data->player->dir_p.y = 0;
	data->player->fov.x = 0;
	data->player->fov.y = 0;
}
