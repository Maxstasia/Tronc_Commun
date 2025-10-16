/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_teleporters_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:50:16 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/16 10:57:28 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	init_teleporters(t_map *map)
{
	map->teleporter_3 = malloc(sizeof(t_teleporter));
	if (!map->teleporter_3)
		return ;
	map->teleporter_3->numbers = 0;
	map->teleporter_4 = malloc(sizeof(t_teleporter));
	if (!map->teleporter_4)
		return ;
	map->teleporter_4->numbers = 0;
	map->teleporter_5 = malloc(sizeof(t_teleporter));
	if (!map->teleporter_5)
		return ;
	map->teleporter_5->numbers = 0;
	map->teleporter_6 = malloc(sizeof(t_teleporter));
	if (!map->teleporter_6)
		return ;
	map->teleporter_6->numbers = 0;
}
