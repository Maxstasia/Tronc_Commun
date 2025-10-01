/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:14:18 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/01 13:14:40 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_textures(t_data *data, char *line)
{
	char	**split;
	char	*path;

	split = ft_split(line, ' ');
	if (!split || !split[1] || split[2])
		return (free_split(split), print_error(TEXTURE_ERROR, data), 1);
	path = ft_strdup(split[1]);
	if (!path)
		return (free_split(split), print_error(MALLOC_ERROR, data), 1);
	if (ft_strncmp(line, "NO ", 3) == 0)
		data->map->texture_north = path;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		data->map->texture_south = path;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		data->map->texture_west = path;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		data->map->texture_east = path;
	free_split(split);
	return (0);
}
