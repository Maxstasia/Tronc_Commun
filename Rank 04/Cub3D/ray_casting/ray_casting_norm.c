/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_norm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:27:01 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/09 11:27:21 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*draw_wall_slice_norm(t_data *data)
{
	char	*tex_data;

	if (data->ray->side == 0)
	{
		if (data->ray->step_x > 0)
			tex_data = mlx_get_data_addr(data->map->img_east,
					&data->texture->bpp, &data->texture->l_len,
					&data->texture->endian);
		if (data->ray->step_x < 0)
			tex_data = mlx_get_data_addr(data->map->img_west,
					&data->texture->bpp, &data->texture->l_len,
					&data->texture->endian);
	}
	else
	{
		if (data->ray->step_y > 0)
			tex_data = mlx_get_data_addr(data->map->img_south,
					&data->texture->bpp, &data->texture->l_len,
					&data->texture->endian);
		if (data->ray->step_y < 0)
			tex_data = mlx_get_data_addr(data->map->img_north,
					&data->texture->bpp, &data->texture->l_len,
					&data->texture->endian);
	}
	return (tex_data);
}
