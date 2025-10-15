/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:05:58 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/15 13:10:12 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos.x + data->player->dir_p.x
		* data->player->move_speed;
	new_y = data->player->pos.y + data->player->dir_p.y
		* data->player->move_speed;
	if (data->map->map[(int)new_y][(int)data->player->pos.x] != '1'
		&& data->map->map[(int)new_y][(int)data->player->pos.x] != 'P')
		data->player->pos.y = new_y;
	if (data->map->map[(int)data->player->pos.y][(int)new_x] != '1'
		&& data->map->map[(int)data->player->pos.y][(int)new_x] != 'P')
		data->player->pos.x = new_x;
}

void	move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos.x - data->player->dir_p.x
		* data->player->move_speed;
	new_y = data->player->pos.y - data->player->dir_p.y
		* data->player->move_speed;
	if (data->map->map[(int)new_y][(int)data->player->pos.x] != '1'
		&& data->map->map[(int)new_y][(int)data->player->pos.x] != 'P')
		data->player->pos.y = new_y;
	if (data->map->map[(int)data->player->pos.y][(int)new_x] != '1'
		&& data->map->map[(int)data->player->pos.y][(int)new_x] != 'P')
		data->player->pos.x = new_x;
}

void	move_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos.x - data->player->fov.x
		* data->player->move_speed;
	new_y = data->player->pos.y - data->player->fov.y
		* data->player->move_speed;
	if (data->map->map[(int)new_y][(int)data->player->pos.x] != '1'
		&& data->map->map[(int)new_y][(int)data->player->pos.x] != 'P')
		data->player->pos.y = new_y;
	if (data->map->map[(int)data->player->pos.y][(int)new_x] != '1'
		&& data->map->map[(int)data->player->pos.y][(int)new_x] != 'P')
		data->player->pos.x = new_x;
}

void	move_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos.x + data->player->fov.x
		* data->player->move_speed;
	new_y = data->player->pos.y + data->player->fov.y
		* data->player->move_speed;
	if (data->map->map[(int)new_y][(int)data->player->pos.x] != '1'
		&& data->map->map[(int)new_y][(int)data->player->pos.x] != 'P')
		data->player->pos.y = new_y;
	if (data->map->map[(int)data->player->pos.y][(int)new_x] != '1'
		&& data->map->map[(int)data->player->pos.y][(int)new_x] != 'P')
		data->player->pos.x = new_x;
}
