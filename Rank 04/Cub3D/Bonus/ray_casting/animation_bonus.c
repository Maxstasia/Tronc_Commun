/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:20:56 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/16 14:05:34 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

char	*create_frame_path(char *base_path, int frame_num)
{
	char	*path_without_ext;
	char	*frame_str;
	char	*temp;
	char	*result;
	int		len;

	len = ft_strlen(base_path);
	if (len < 4 || ft_strncmp(&base_path[len - 4], ".xpm", 4) != 0)
		return (NULL);
	path_without_ext = ft_substr(base_path, 0, len - 4);
	if (!path_without_ext)
		return (NULL);
	frame_str = ft_itoa(frame_num);
	if (!frame_str)
		return (free(path_without_ext), NULL);
	temp = ft_strjoin(path_without_ext, "_");
	free(path_without_ext);
	if (!temp)
		return (free(frame_str), NULL);
	result = ft_strjoin(temp, frame_str);
	free(temp);
	free(frame_str);
	if (!result)
		return (NULL);
	return (temp = ft_strjoin(result, ".xpm"), free(result), temp);
}

static int	load_single_animation(t_data *data, t_anim *anim,
		char *base_path)
{
	char	*frame_path;
	int		i;
	int		width;
	int		height;

	anim->frames[0] = mlx_xpm_file_to_image(data->mlx_ptr,
			base_path, &width, &height);
	if (!anim->frames[0])
		return (-1);
	i = 1;
	while (i < anim->frame_count)
	{
		frame_path = create_frame_path(base_path, i);
		if (!frame_path)
			return (-1);
		anim->frames[i] = mlx_xpm_file_to_image(data->mlx_ptr,
				frame_path, &width, &height);
		free(frame_path);
		if (!anim->frames[i])
			return (-1);
		i++;
	}
	return (0);
}

int	load_all_animations(t_data *data)
{
	if (data->map->anim_north.is_animated)
		if (load_single_animation(data, &data->map->anim_north,
				data->map->texture_north) < 0)
			return (-1);
	if (data->map->anim_south.is_animated)
		if (load_single_animation(data, &data->map->anim_south,
				data->map->texture_south) < 0)
			return (-1);
	if (data->map->anim_west.is_animated)
		if (load_single_animation(data, &data->map->anim_west,
				data->map->texture_west) < 0)
			return (-1);
	if (data->map->anim_east.is_animated)
		if (load_single_animation(data, &data->map->anim_east,
				data->map->texture_east) < 0)
			return (-1);
	if (data->map->texture_door && data->map->anim_door.is_animated)
		if (load_single_animation(data, &data->map->anim_door,
				data->map->texture_door) < 0)
			return (-1);
	if (data->map->texture_teleport && data->map->anim_teleport.is_animated)
		if (load_single_animation(data, &data->map->anim_teleport,
				data->map->texture_teleport) < 0)
			return (-1);
	return (0);
}

static void	anim_door_and_tp(t_data *data)
{
	if (data->map->texture_door && data->map->anim_door.is_animated)
		data->map->anim_door.current_frame
			= (data->map->anim_door.current_frame + 1)
			% data->map->anim_door.frame_count;
	if (data->map->texture_teleport && data->map->anim_teleport.is_animated)
		data->map->anim_teleport.current_frame
			= (data->map->anim_teleport.current_frame + 1)
			% data->map->anim_teleport.frame_count;
}

void	update_animations(t_data *data)
{
	if (++ data->anim_counter >= data->anim_speed)
	{
		data->anim_counter = 0;
		if (data->map->anim_north.is_animated)
			data->map->anim_north.current_frame
				= (data->map->anim_north.current_frame + 1)
				% data->map->anim_north.frame_count;
		if (data->map->anim_south.is_animated)
			data->map->anim_south.current_frame
				= (data->map->anim_south.current_frame + 1)
				% data->map->anim_south.frame_count;
		if (data->map->anim_west.is_animated)
			data->map->anim_west.current_frame
				= (data->map->anim_west.current_frame + 1)
				% data->map->anim_west.frame_count;
		if (data->map->anim_east.is_animated)
			data->map->anim_east.current_frame
				= (data->map->anim_east.current_frame + 1)
				% data->map->anim_east.frame_count;
		anim_door_and_tp(data);
	}
}
