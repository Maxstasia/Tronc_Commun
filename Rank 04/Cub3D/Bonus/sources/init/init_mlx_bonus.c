/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:22:01 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/13 16:48:41 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	setup_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (print_error(MLX_INIT_ERROR, data), MLX_ERROR);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	if (data->win_ptr == NULL)
		return (print_error(WINDOW_ERROR, data), MLX_ERROR);
	data->img->mlx_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (data->img->mlx_img == NULL)
		return (print_error(IMAGE_ERROR, data), MLX_ERROR);
	data->img->addr = mlx_get_data_addr(data->img->mlx_img,
			&data->img->bpp, &data->img->l_len, &data->img->endian);
	if (data->img->addr == NULL)
		return (print_error(IMAGE_ADDR_ERROR, data), MLX_ERROR);
	return (0);
}

static int	game_loop(t_data *data)
{
	update_player(data);
	update_animations(data);
	render_frame(data);
	return (0);
}

int	loop(t_data *data)
{
	if (data)
	{
		mlx_hook(data->win_ptr,
			KeyPress, KeyPressMask, &handle_keypress, data);
		mlx_hook(data->win_ptr,
			KeyRelease, KeyReleaseMask, &handle_keyrelease, data);
		mlx_hook(data->win_ptr,
			DestroyNotify, NoEventMask, &handle_destroy, data);
		mlx_loop_hook(data->mlx_ptr, &game_loop, data);
		mlx_loop(data->mlx_ptr);
	}
	else
		return (clean_up(data), MLX_ERROR);
	return (0);
}

void	init_mlx(t_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->img->mlx_img = NULL;
	data->img->addr = NULL;
	data->img->bpp = 0;
	data->img->l_len = 0;
	data->img->endian = 0;
}
