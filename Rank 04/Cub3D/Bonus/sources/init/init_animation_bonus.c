/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_animation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:00:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/15 15:15:22 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	init_anim_texture(t_anim *anim)
{
	anim->frames = NULL;
	anim->frame_count = 0;
	anim->current_frame = 0;
	anim->is_animated = 0;
}

void	init_animations(t_data *data)
{
	init_anim_texture(&data->map->anim_north);
	init_anim_texture(&data->map->anim_south);
	init_anim_texture(&data->map->anim_west);
	init_anim_texture(&data->map->anim_east);
	init_anim_texture(&data->map->anim_door);
	init_anim_texture(&data->map->anim_teleport);
	data->anim_counter = 0;
	data->anim_speed = 5;
}
