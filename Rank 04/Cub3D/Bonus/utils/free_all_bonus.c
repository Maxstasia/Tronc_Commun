/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:57:44 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/16 13:44:14 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	free_teleporters(t_map *map)
{
	if (!map)
		return ;
	if (map->teleporter_3)
		free(map->teleporter_3);
	map->teleporter_3 = NULL;
	if (map->teleporter_4)
		free(map->teleporter_4);
	map->teleporter_4 = NULL;
	if (map->teleporter_5)
		free(map->teleporter_5);
	map->teleporter_5 = NULL;
	if (map->teleporter_6)
		free(map->teleporter_6);
	map->teleporter_6 = NULL;
}

void	free_all(t_data *data)
{
	destroy_sprites(data);
	free_data(data);
}
