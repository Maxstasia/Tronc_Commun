/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_movement_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:27:37 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/10 18:28:09 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	rotate_left(t_data *data)
{
	double	old_dir_x;
	double	old_fov_x;

	old_dir_x = data->player->dir_p.x;
	data->player->dir_p.x = data->player->dir_p.x * cos(-ROT_SPEED)
		- data->player->dir_p.y * sin(-ROT_SPEED);
	data->player->dir_p.y = old_dir_x * sin(-ROT_SPEED)
		+ data->player->dir_p.y * cos(-ROT_SPEED);
	old_fov_x = data->player->fov.x;
	data->player->fov.x = data->player->fov.x * cos(-ROT_SPEED)
		- data->player->fov.y * sin(-ROT_SPEED);
	data->player->fov.y = old_fov_x * sin(-ROT_SPEED)
		+ data->player->fov.y * cos(-ROT_SPEED);
}

void	rotate_right(t_data *data)
{
	double	old_dir_x;
	double	old_fov_x;

	old_dir_x = data->player->dir_p.x;
	data->player->dir_p.x = data->player->dir_p.x * cos(ROT_SPEED)
		- data->player->dir_p.y * sin(ROT_SPEED);
	data->player->dir_p.y = old_dir_x * sin(ROT_SPEED)
		+ data->player->dir_p.y * cos(ROT_SPEED);
	old_fov_x = data->player->fov.x;
	data->player->fov.x = data->player->fov.x * cos(ROT_SPEED)
		- data->player->fov.y * sin(ROT_SPEED);
	data->player->fov.y = old_fov_x * sin(ROT_SPEED)
		+ data->player->fov.y * cos(ROT_SPEED);
}
