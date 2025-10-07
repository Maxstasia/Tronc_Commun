/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:16:42 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/07 11:26:44 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	asiganation_f_c(t_data *data, char *line, char *color, char **split)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (data->map->color_floor)
			return (free(color), free_split(split),
				print_error(COLOR_ERROR, data), 1);
		else
			data->map->color_floor = color;
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (data->map->color_ceiling)
			return (free(color), free_split(split),
				print_error(COLOR_ERROR, data), 1);
		else
			data->map->color_ceiling = color;
	}
	return (0);
}

int	parse_colors(t_data *data, char *line)
{
	char	**split;
	char	*color;
	size_t	len;

	split = ft_split(line, ' ');
	if (!split || !split[1] || (split[2] && split[2][0] != '\n'))
		return (free_split(split), print_error(COLOR_ERROR, data), 1);
	color = ft_strdup(split[1]);
	if (!color)
		return (free_split(split), print_error(MALLOC_ERROR, data), 1);
	len = ft_strlen(color);
	if (len > 0 && color[len - 1] == '\n')
		color[len - 1] = '\0';
	if (asiganation_f_c(data, line, color, split))
		return (1);
	free_split(split);
	return (0);
}

static int	spliter(t_data *data)
{
	data->parser->floor_split = ft_split(data->map->color_floor, ',');
	if (!data->parser->floor_split || !data->parser->floor_split[0]
		|| !data->parser->floor_split[1] || !data->parser->floor_split[2]
		|| data->parser->floor_split[3])
		return (free_split(data->parser->floor_split),
			print_error(COLOR_ERROR, data), 1);
	data->parser->ceiling_split = ft_split(data->map->color_ceiling, ',');
	if (!data->parser->ceiling_split || !data->parser->ceiling_split[0]
		|| !data->parser->ceiling_split[1]
		|| !data->parser->ceiling_split[2] || data->parser->ceiling_split[3])
		return (free_split(data->parser->floor_split),
			free_split(data->parser->ceiling_split),
			print_error(COLOR_ERROR, data), 1);
	return (0);
}

static int	check_commas(t_data *data, t_map *map)
{
	int	num_commas;
	int	i;

	num_commas = 0;
	i = -1;
	while (++ i, map->color_floor && map->color_floor[i])
	{
		if (map->color_floor[i] == ',')
			num_commas++;
	}
	if (num_commas != 2)
		return (print_error(COLOR_ERROR, data), 1);
	num_commas = 0;
	i = -1;
	while (++ i, map->color_ceiling && map->color_ceiling[i])
	{
		if (map->color_ceiling[i] == ',')
			num_commas++;
	}
	if (num_commas != 2)
		return (print_error(COLOR_ERROR, data), 1);
	return (0);
}

int	validate_colors(t_data *data)
{
	int		f;
	int		c;

	if (check_commas(data, data->map))
		return (1);
	if (spliter(data))
		return (1);
	data->parser->i = -1;
	while (++ data->parser->i, data->parser->i < 3)
	{
		f = ft_atoi(data->parser->floor_split[data->parser->i]);
		c = ft_atoi(data->parser->ceiling_split[data->parser->i]);
		if (f < 0 || f > 255 || c < 0 || c > 255)
			return (free_split(data->parser->floor_split),
				free_split(data->parser->ceiling_split),
				print_error(COLOR_ERROR, data), 1);
	}
	return (free_split(data->parser->floor_split),
		free_split(data->parser->ceiling_split), 0);
}
