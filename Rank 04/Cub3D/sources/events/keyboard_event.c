/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_event.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:38:09 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/08 11:42:24 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	rotate_left(t_data *data)
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

static void	rotate_right(t_data *data)
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

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape || keysym == XK_BackSpace || keysym == XK_Delete)
	{
		free_all(data);
		exit(0);
	}
	if (keysym == XK_w || keysym == XK_W)
		data->keys->w = 1;
	if (keysym == XK_s || keysym == XK_S)
		data->keys->s = 1;
	if (keysym == XK_a || keysym == XK_A)
		data->keys->a = 1;
	if (keysym == XK_d || keysym == XK_D)
		data->keys->d = 1;
	if (keysym == XK_Left || keysym == XK_q || keysym == XK_Q)
		data->keys->left = 1;
	if (keysym == XK_Right || keysym == XK_e || keysym == XK_E)
		data->keys->right = 1;
	return (0);
}

int	handle_keyrelease(int keysym, t_data *data)
{
	if (keysym == XK_w || keysym == XK_W)
		data->keys->w = 0;
	if (keysym == XK_s || keysym == XK_S)
		data->keys->s = 0;
	if (keysym == XK_a || keysym == XK_A)
		data->keys->a = 0;
	if (keysym == XK_d || keysym == XK_D)
		data->keys->d = 0;
	if (keysym == XK_Left || keysym == XK_q || keysym == XK_Q)
		data->keys->left = 0;
	if (keysym == XK_Right || keysym == XK_e || keysym == XK_E)
		data->keys->right = 0;
	return (0);
}

void	update_player(t_data *data)
{
	if (data->keys->w)
		move_forward(data);
	if (data->keys->s)
		move_backward(data);
	if (data->keys->a)
		move_left(data);
	if (data->keys->d)
		move_right(data);
	if (data->keys->left)
		rotate_left(data);
	if (data->keys->right)
		rotate_right(data);
}
