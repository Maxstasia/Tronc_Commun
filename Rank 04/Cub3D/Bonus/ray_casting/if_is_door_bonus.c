/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_is_door_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:56:57 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/16 13:59:51 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

char	*if_is_door(t_data *data, t_map *map)
{
	char	*tex_data;
	void	*current_img;

	tex_data = NULL;
	if (data->ray->is_door == true)
	{
		if (!map->img_door)
		{
			tex_data = draw_wall_slice_norm(data, map);
			return (tex_data);
		}
		if (map->anim_door.is_animated)
			current_img = map->anim_door.frames[map->anim_door.current_frame];
		else
			current_img = map->img_door;
		tex_data = mlx_get_data_addr(current_img,
				&data->texture->bpp, &data->texture->l_len,
				&data->texture->endian);
		return (tex_data);
	}
	if (data->ray->is_tp == true)
		return (if_is_teleporter(data, map));
	tex_data = draw_wall_slice_norm(data, map);
	return (tex_data);
}

char	*if_is_teleporter(t_data *data, t_map *map)
{
	char	*tex_data;
	void	*current_img;

	tex_data = NULL;
	if (!map->img_teleport)
	{
		tex_data = draw_wall_slice_norm(data, map);
		return (tex_data);
	}
	if (map->anim_teleport.is_animated)
		current_img
			= map->anim_teleport.frames[map->anim_teleport.current_frame];
	else
		current_img = map->img_teleport;
	tex_data = mlx_get_data_addr(current_img,
			&data->texture->bpp, &data->texture->l_len,
			&data->texture->endian);
	return (tex_data);
}
