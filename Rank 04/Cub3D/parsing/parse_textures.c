/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:14:18 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/02 11:45:45 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	asignation_no_so(t_data *data, char *path, char *line, char **split)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (data->map->texture_north)
			return (free(path), free_split(split),
				print_error(TEXTURE_ERROR, data), 1);
		else
			data->map->texture_north = path;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (data->map->texture_south)
			return (free(path), free_split(split),
				print_error(TEXTURE_ERROR, data), 1);
		else
			data->map->texture_south = path;
	}
	return (0);
}

static int	asignation_ea_we(t_data *data, char *path, char *line, char **split)
{
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (data->map->texture_west)
			return (free(path), free_split(split),
				print_error(TEXTURE_ERROR, data), 1);
		else
			data->map->texture_west = path;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (data->map->texture_east)
			return (free(path), free_split(split),
				print_error(TEXTURE_ERROR, data), 1);
		else
			data->map->texture_east = path;
	}
	return (0);
}

static int	set_textures(t_data *data, char *path, char *line, char **split)
{
	if (asignation_no_so(data, path, line, split))
		return (1);
	if (asignation_ea_we(data, path, line, split))
		return (1);
	return (0);
}

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
	if (set_textures(data, path, line, split))
		return (1);
	free_split(split);
	return (0);
}
