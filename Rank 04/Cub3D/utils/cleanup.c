/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:57:44 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/11 14:14:42 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	clean_up(t_data *data)
{
	if (data)
	{
		if (data->img->mlx_img && data->mlx_ptr)
			mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
		if (data->win_ptr && data->mlx_ptr)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		if (data->mlx_ptr)
		{
			mlx_destroy_display(data->mlx_ptr);
			data->win_ptr = NULL;
			free(data->mlx_ptr);
		}
		if (data->img)
			free(data->img);
		exit(MLX_ERROR);
	}
	exit(MLX_ERROR);
}
