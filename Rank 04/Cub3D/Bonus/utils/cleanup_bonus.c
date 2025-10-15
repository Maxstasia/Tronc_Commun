/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:57:44 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/15 15:57:43 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	clean_up(t_data *data)
{
	free_all(data);
	get_next_line(-1);
	exit(MLX_ERROR);
}

void	free_tab(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

static void	destroy_anim_frames(t_data *data, t_anim *anim)
{
	int	i;

	if (!anim || !anim->frames)
		return ;
	i = 0;
	while (i < anim->frame_count)
	{
		if (anim->frames[i])
			mlx_destroy_image(data->mlx_ptr, anim->frames[i]);
		i++;
	}
	free(anim->frames);
	anim->frames = NULL;
	anim->frame_count = 0;
	anim->is_animated = 0;
}

void	destroy_sprites(t_data *data)
{
	if (!data || !data->map || !data->mlx_ptr)
		return ;
	destroy_anim_frames(data, &data->map->anim_north);
	destroy_anim_frames(data, &data->map->anim_south);
	destroy_anim_frames(data, &data->map->anim_west);
	destroy_anim_frames(data, &data->map->anim_east);
	destroy_anim_frames(data, &data->map->anim_door);
	destroy_anim_frames(data, &data->map->anim_teleport);
	if (data->map->img_north)
		mlx_destroy_image(data->mlx_ptr, data->map->img_north);
	if (data->map->img_south)
		mlx_destroy_image(data->mlx_ptr, data->map->img_south);
	if (data->map->img_west)
		mlx_destroy_image(data->mlx_ptr, data->map->img_west);
	if (data->map->img_east)
		mlx_destroy_image(data->mlx_ptr, data->map->img_east);
	if (data->map->img_door)
		mlx_destroy_image(data->mlx_ptr, data->map->img_door);
	if (data->map->img_teleport)
		mlx_destroy_image(data->mlx_ptr, data->map->img_teleport);
}
