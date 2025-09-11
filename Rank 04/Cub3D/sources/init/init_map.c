/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:03:14 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/11 15:18:39 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_map(t_data *data)
{
	data->map->texture_north = NULL;
	data->map->texture_south = NULL;
	data->map->texture_west = NULL;
	data->map->texture_east = NULL;
	data->map->color_floor = NULL;
	data->map->color_ceiling = NULL;
	data->map->map = NULL;
	return (0);
}
