/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_movement_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:30:23 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/10 18:54:23 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	interact_door(t_data *data)
{
	int	door_x;
	int	door_y;

	door_x = (int)(data->player->pos.x + data->player->dir_p.x);
	door_y = (int)(data->player->pos.y + data->player->dir_p.y);
	if (data->player->pos.x == 	door_x && data->player->pos.y == door_y)
		return ;
	if (data->map->map[door_y][door_x] == 'P')
		data->map->map[door_y][door_x] = '2';
	else if (data->map->map[door_y][door_x] == '2')
		data->map->map[door_y][door_x] = 'P';
}
