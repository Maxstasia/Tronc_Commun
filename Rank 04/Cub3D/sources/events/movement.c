/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:05:58 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/08 10:50:21 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_forward(t_data *data)
{
    double	new_x;
    double	new_y;

    new_x = data->player->pos.x + data->player->dir_p.x * MOV_SPEED;
    new_y = data->player->pos.y + data->player->dir_p.y * MOV_SPEED;

    if (data->map->map[(int)new_y][(int)data->player->pos.x] != '1')
        data->player->pos.y = new_y;
    if (data->map->map[(int)data->player->pos.y][(int)new_x] != '1')
        data->player->pos.x = new_x;
}

void	move_backward(t_data *data)
{
    double	new_x;
    double	new_y;

    new_x = data->player->pos.x - data->player->dir_p.x * MOV_SPEED;
    new_y = data->player->pos.y - data->player->dir_p.y * MOV_SPEED;

    if (data->map->map[(int)new_y][(int)data->player->pos.x] != '1')
        data->player->pos.y = new_y;
    if (data->map->map[(int)data->player->pos.y][(int)new_x] != '1')
        data->player->pos.x = new_x;
}

void	move_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos.x - data->player->fov.x * MOV_SPEED;
	new_y = data->player->pos.y - data->player->fov.y * MOV_SPEED;

	if (data->map->map[(int)new_y][(int)data->player->pos.x] != '1')
		data->player->pos.y = new_y;
	if (data->map->map[(int)data->player->pos.y][(int)new_x] != '1')
		data->player->pos.x = new_x;
}

void	move_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos.x + data->player->fov.x * MOV_SPEED;
	new_y = data->player->pos.y + data->player->fov.y * MOV_SPEED;

	if (data->map->map[(int)new_y][(int)data->player->pos.x] != '1')
		data->player->pos.y = new_y;
	if (data->map->map[(int)data->player->pos.y][(int)new_x] != '1')
		data->player->pos.x = new_x;
}
