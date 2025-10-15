/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_event_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:38:09 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/15 13:29:05 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static int	mouvement_keypress(int keysym, t_data *data)
{
	if (keysym == XK_w || keysym == XK_W || keysym == XK_Up)
		data->keys->w = 1;
	if (keysym == XK_s || keysym == XK_S || keysym == XK_Down)
		data->keys->s = 1;
	if (keysym == XK_a || keysym == XK_A)
		data->keys->a = 1;
	if (keysym == XK_d || keysym == XK_D)
		data->keys->d = 1;
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape || keysym == XK_BackSpace || keysym == XK_Delete)
	{
		free_all(data);
		exit(0);
	}
	if (mouvement_keypress(keysym, data))
		return (1);
	if (keysym == XK_space || keysym == XK_F || keysym == XK_f)
		interact_door(data);
	if (keysym == XK_Shift_L || keysym == XK_Shift_R)
		data->keys->shift = 1;
	if (keysym == XK_Left || keysym == XK_q || keysym == XK_Q)
		data->keys->left = 1;
	if (keysym == XK_Right || keysym == XK_e || keysym == XK_E)
		data->keys->right = 1;
	if (keysym == XK_plus || keysym == XK_KP_Add)
		data->mouse_sensitivity += 0.0005;
	if (keysym == XK_minus || keysym == XK_KP_Subtract)
		if (data->mouse_sensitivity > 0.0005)
			data->mouse_sensitivity -= 0.0005;
	return (0);
}

int	handle_keyrelease(int keysym, t_data *data)
{
	if (keysym == XK_w || keysym == XK_W || keysym == XK_Up)
		data->keys->w = 0;
	if (keysym == XK_s || keysym == XK_S || keysym == XK_Down)
		data->keys->s = 0;
	if (keysym == XK_a || keysym == XK_A)
		data->keys->a = 0;
	if (keysym == XK_d || keysym == XK_D)
		data->keys->d = 0;
	if (keysym == XK_Left || keysym == XK_q || keysym == XK_Q)
		data->keys->left = 0;
	if (keysym == XK_Right || keysym == XK_e || keysym == XK_E)
		data->keys->right = 0;
	if (keysym == XK_Shift_L || keysym == XK_Shift_R)
		data->keys->shift = 0;
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
	if (data->keys->shift)
		data->player->move_speed = MOV_SPEED * 2.5;
	else
		data->player->move_speed = MOV_SPEED;
}
