/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_doors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:42:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/15 16:47:11 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	has_doors_in_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'P')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_doors(t_data *data)
{
	if (has_doors_in_map(data->map) && !data->map->texture_door)
	{
		data->map->texture_door = ft_strdup("textures/door_64x64.xpm");
		if (!data->map->texture_door)
			return (print_error(MALLOC_ERROR, data), 1);
	}
	return (0);
}
