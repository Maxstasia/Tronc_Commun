/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:16:42 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/01 13:17:41 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_colors(t_data *data, char *line)
{
	char	**split;
	char	*color;
	size_t	len;

	split = ft_split(line, ' ');
	if (!split || !split[1] || split[2])
		return (free_split(split), print_error(COLOR_ERROR, data), 1);
	color = ft_strdup(split[1]);
	if (!color)
		return (free_split(split), print_error(MALLOC_ERROR, data), 1);
	len = ft_strlen(color);
	if (len > 0 && color[len - 1] == '\n')
		color[len - 1] = '\0';
	if (ft_strncmp(line, "F ", 2) == 0)
		data->map->color_floor = color;
	else if (ft_strncmp(line, "C ", 2) == 0)
		data->map->color_ceiling = color;
	free_split(split);
	return (0);
}

int	validate_colors(t_data *data)
{
	char	**floor_split;
	char	**ceiling_split;
	int		i;
	int		f;
	int		c;

	floor_split = ft_split(data->map->color_floor, ',');
	if (!floor_split || !floor_split[0] || !floor_split[1]
		|| !floor_split[2] || floor_split[3])
		return (free_split(floor_split), print_error(COLOR_ERROR, data), 1);
	ceiling_split = ft_split(data->map->color_ceiling, ',');
	if (!ceiling_split || !ceiling_split[0] || !ceiling_split[1]
		|| !ceiling_split[2] || ceiling_split[3])
		return (free_split(floor_split), free_split(ceiling_split),
			print_error(COLOR_ERROR, data), 1);
	i = -1;
	while (++i, i < 3)
	{
		f = ft_atoi(floor_split[i]);
		c = ft_atoi(ceiling_split[i]);
		if (f < 0 || f > 255 || c < 0 || c > 255)
			return (free_split(floor_split), free_split(ceiling_split),
				print_error(COLOR_ERROR, data), 1);
	}
	return (free_split(floor_split), free_split(ceiling_split), 0);
}
