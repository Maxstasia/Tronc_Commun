/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_door_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:14:18 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/10 17:37:30 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	asignation_door(t_data *data, char *path, char *line, char **split)
{
	if (ft_strncmp(line, "DO ", 3) == 0)
	{
		if (data->map->texture_door)
			return (free_split(split), print_error(TEXTURE_ERROR, data), 1);
		else
		{
			data->map->texture_door = ft_strdup(path);
			if (!data->map->texture_door)
				return (free_split(split), print_error(MALLOC_ERROR, data), 1);
		}
	}
	return (0);
}
