/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:40:39 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/16 14:03:59 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	count_animation_frames(char *base_path)
{
	char	*frame_path;
	int		fd;
	int		count;

	count = 1;
	while (count < 100)
	{
		frame_path = create_frame_path(base_path, count);
		if (!frame_path)
			break ;
		fd = open(frame_path, O_RDONLY);
		free(frame_path);
		if (fd < 0)
			break ;
		close(fd);
		count++;
	}
	if (count == 1)
		return (0);
	return (count);
}

static int	detect_animation(t_data *data, t_anim *anim, char *texture_path)
{
	int	frame_count;

	if (!texture_path)
		return (0);
	frame_count = count_animation_frames(texture_path);
	if (frame_count > 0)
	{
		anim->is_animated = 1;
		anim->frame_count = frame_count;
		anim->current_frame = 0;
		anim->frames = malloc(sizeof(void *) * frame_count);
		if (!anim->frames)
			return (print_error(MALLOC_ERROR, data), -1);
		return (frame_count);
	}
	anim->is_animated = 0;
	return (0);
}

static int	load_textures_helper(t_data *data, int width, int height)
{
	detect_animation(data, &data->map->anim_north, data->map->texture_north);
	detect_animation(data, &data->map->anim_south, data->map->texture_south);
	detect_animation(data, &data->map->anim_west, data->map->texture_west);
	detect_animation(data, &data->map->anim_east, data->map->texture_east);
	if (data->map->texture_door)
		detect_animation(data, &data->map->anim_door, data->map->texture_door);
	if (data->map->texture_teleport)
		detect_animation(data, &data->map->anim_teleport,
			data->map->texture_teleport);
	if (load_all_animations(data) < 0)
		return (print_error(TEXTURE_ERROR, data), 1);
	data->map->img_north = mlx_xpm_file_to_image(data->mlx_ptr,
			data->map->texture_north, &width, &height);
	if (!data->map->img_north)
		return (print_error(TEXTURE_ERROR, data), 1);
	data->map->img_south = mlx_xpm_file_to_image(data->mlx_ptr,
			data->map->texture_south, &width, &height);
	if (!data->map->img_south)
		return (print_error(TEXTURE_ERROR, data), 1);
	return (data->map->tex_width = width, data->map->tex_height = height, 0);
}

static int	for_tp_and_door(t_data *data, int width, int height)
{
	if (data->map->texture_door)
	{
		data->map->img_door = mlx_xpm_file_to_image(data->mlx_ptr,
				data->map->texture_door, &width, &height);
		if (!data->map->img_door)
			return (print_error(TEXTURE_ERROR, data), 1);
	}
	if (data->map->texture_teleport)
	{
		data->map->img_teleport = mlx_xpm_file_to_image(data->mlx_ptr,
				data->map->texture_teleport, &width, &height);
		if (!data->map->img_teleport)
			return (print_error(TEXTURE_ERROR, data), 1);
	}
	return (data->map->tex_width = width, data->map->tex_height = height, 0);
}

int	load_textures(t_data *data)
{
	int	width;
	int	height;

	width = data->map->tex_width;
	height = data->map->tex_height;
	load_textures_helper(data, width, height);
	data->map->img_west = mlx_xpm_file_to_image(data->mlx_ptr,
			data->map->texture_west, &width, &height);
	if (!data->map->img_west)
		return (print_error(TEXTURE_ERROR, data), 1);
	data->map->img_east = mlx_xpm_file_to_image(data->mlx_ptr,
			data->map->texture_east, &width, &height);
	if (!data->map->img_east)
		return (print_error(TEXTURE_ERROR, data), 1);
	for_tp_and_door(data, width, height);
	return (data->map->tex_width = width, data->map->tex_height = height, 0);
}
