/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_movement_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:30:23 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/16 14:32:48 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	interact_door(t_data *data)
{
	int	door_x;
	int	door_y;

	door_x = (int)(data->player->pos.x + data->player->dir_p.x);
	door_y = (int)(data->player->pos.y + data->player->dir_p.y);
	if (data->player->pos.x == door_x && data->player->pos.y == door_y)
		return ;
	if (data->map->map[door_y][door_x] == 'P')
		data->map->map[door_y][door_x] = '2';
	else if (data->map->map[door_y][door_x] == '2')
		data->map->map[door_y][door_x] = 'P';
}

void	interact_tp(t_data *data)
{
	int	tp_x;
	int	tp_y;

	tp_x = (int)(data->player->pos.x + data->player->dir_p.x);
	tp_y = (int)(data->player->pos.y + data->player->dir_p.y);
	if (data->player->pos.x == tp_x && data->player->pos.y == tp_y)
		return ;
	if (data->map->map[tp_y][tp_x] == '3' && data->map->teleporter_3)
		data->player->pos = (t_vector){data->map->teleporter_4->pos.x + 0.5,
			data->map->teleporter_4->pos.y + 0.5};
	else if (data->map->map[tp_y][tp_x] == '4' && data->map->teleporter_4)
		data->player->pos = (t_vector){data->map->teleporter_3->pos.x + 0.5,
			data->map->teleporter_3->pos.y + 0.5};
	else if (data->map->map[tp_y][tp_x] == '5' && data->map->teleporter_5)
		data->player->pos = (t_vector){data->map->teleporter_6->pos.x + 0.5,
			data->map->teleporter_6->pos.y + 0.5};
	else if (data->map->map[tp_y][tp_x] == '6' && data->map->teleporter_6)
		data->player->pos = (t_vector){data->map->teleporter_5->pos.x + 0.5,
			data->map->teleporter_5->pos.y + 0.5};
}
