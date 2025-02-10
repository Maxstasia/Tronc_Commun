/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:05:10 by mstasiak          #+#    #+#             */
/*   Updated: 2025/02/10 11:23:23 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol_bonus.h"

int	init_main(char **argv, t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (clean_up(data), MLX_ERROR);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "Fractol");
	if (data->win_ptr == NULL)
		return (clean_up(data), MLX_ERROR);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data->img.mlx_img == NULL)
		return (clean_up(data), MLX_ERROR);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img,
			&data->img.bpp, &data->img.l_len, &data->img.endian);
	if (data->img.addr == NULL)
		return (clean_up(data), MLX_ERROR);
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
		mandelbrot_security(argv, data);
	else if (ft_strcmp(argv[1], "julia") == 0)
		julia_security(argv, data);
	else if (ft_strcmp(argv[1], "burning_ship") == 0)
		burning_ship_security(argv, data);
	else
		return (clean_up(data), MLX_ERROR);
	print_command();
	return (0);
}

int	loop(t_data *data)
{
	if (data)
	{
		mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
		mlx_hook(data->win_ptr, DestroyNotify, NoEventMask, &handle_destroy, data);
		mlx_mouse_hook(data->win_ptr, &handle_scroll, data);
		mlx_loop(data->mlx_ptr);
	}
	else
		return (clean_up(data), MLX_ERROR);
	return (0);
}
