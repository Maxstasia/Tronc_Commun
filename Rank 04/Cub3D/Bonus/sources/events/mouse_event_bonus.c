/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:43:26 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/15 13:45:24 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	handle_destroy(t_data *data)
{
	free_all(data);
	exit(0);
	return (0);
}

int	handle_mouse_move(int x, int y, t_data *data)
{
	int		delta_x;
	double	angle;

	(void)y;
	if (data->last_mouse_x == -1)
	{
		data->last_mouse_x = x;
		return (0);
	}
	delta_x = x - data->last_mouse_x;
	if (delta_x != 0)
	{
		angle = delta_x * data->mouse_sensitivity;
		rotate_by_angle(data, angle);
	}
	data->last_mouse_x = x;
	if (x <= 10 || x >= WIN_WIDTH - 10)
	{
		mlx_mouse_move(data->mlx_ptr, data->win_ptr,
			WIN_WIDTH / 2, WIN_HEIGHT / 2);
		data->last_mouse_x = WIN_WIDTH / 2;
	}
	return (0);
}
