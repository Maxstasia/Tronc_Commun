/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:50:56 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/12 11:31:46 by mstasiak         ###   ########.fr       */
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

int	parse_colors(t_data *data, char *line)
{
	char	**split;
	char	*color;

	split = ft_split(line, ' ');
	if (!split || !split[1] || split[2])
		return (free_split(split), print_error(COLOR_ERROR, data), 1);
	color = ft_strdup(split[1]);
	if (!color)
		return (free_split(split), print_error(MALLOC_ERROR, data), 1);
	// Remove trailing \n
	size_t len = ft_strlen(color);
	if (len > 0 && color[len - 1] == '\n')
		color[len - 1] = '\0';
	if (ft_strncmp(line, "F ", 2) == 0)
		data->map->color_floor = color;
	else if (ft_strncmp(line, "C ", 2) == 0)
		data->map->color_ceiling = color;
	free_split(split);
	return (0);
}

void	free_map(char **map, int count)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < count)
		free(map[i++]);
	free(map);
}

int	parse_map_lines(t_data *data, int fd, char *first_line)
{
	char	**map;
	char	*line;
	int		count;

	map = NULL;
	count = 0;
	line = first_line;
	while (line)
	{
		if (ft_strchr(line, '1') || ft_strchr(line, '0') || ft_strchr(line, 'N') ||
			ft_strchr(line, 'S') || ft_strchr(line, 'E') || ft_strchr(line, 'W'))
		{
			map = realloc(map, sizeof(char *) * (count + 1));
			if (!map)
				return (free_map(map, count), print_error(MALLOC_ERROR, data), 1);
			// Remove trailing \n
			size_t len = ft_strlen(line);
			if (len > 0 && line[len - 1] == '\n')
				line[len - 1] = '\0';
			map[count] = ft_strdup(line);
			if (!map[count])
				return (free_map(map, count), print_error(MALLOC_ERROR, data), 1);
			count++;
		}
		if (line != first_line)
			free(line);
		line = get_next_line(fd);
	}
	map = realloc(map, sizeof(char *) * (count + 1));
	if (!map)
		return (free_map(map, count), print_error(MALLOC_ERROR, data), 1);
	map[count] = NULL;
	data->map->map = map;
	return (0);
}

int	validate_colors(t_data *data)
{
	char	**floor_split;
	char	**ceiling_split;
	int		i;

	floor_split = ft_split(data->map->color_floor, ',');
	if (!floor_split || !floor_split[0] || !floor_split[1] || !floor_split[2] || floor_split[3])
		return (free_split(floor_split), print_error(COLOR_ERROR, data), 1);
	ceiling_split = ft_split(data->map->color_ceiling, ',');
	if (!ceiling_split || !ceiling_split[0] || !ceiling_split[1] || !ceiling_split[2] || ceiling_split[3])
		return (free_split(floor_split), free_split(ceiling_split), print_error(COLOR_ERROR, data), 1);
	i = 0;
	while (i < 3)
	{
		int f = ft_atoi(floor_split[i]);
		int c = ft_atoi(ceiling_split[i]);
		if (f < 0 || f > 255 || c < 0 || c > 255)
		{
			return (free_split(floor_split), free_split(ceiling_split), print_error(COLOR_ERROR, data), 1);
		}
		i++;
	}
	free_split(floor_split);
	free_split(ceiling_split);
	return (0);
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	check_closed_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (data->map->map[i][j] == '0' || is_player(data->map->map[i][j]))
			{
				if (i == 0 || !data->map->map[i + 1] ||
					j == 0 || !data->map->map[i][j + 1] ||
					data->map->map[i - 1][j] == ' ' || data->map->map[i + 1][j] == ' ')
					return (print_error(MAP_ERROR, data), 1);
				if (data->map->map[i][j - 1] == ' ' || data->map->map[i][j + 1] == ' ')
					return (print_error(MAP_ERROR, data), 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_map_structure(t_data *data)
{
	int		player_count;
	int		i;
	int		j;

	player_count = 0;
	i = 0;
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (data->map->map[i][j] == 'N' || data->map->map[i][j] == 'S' ||
				data->map->map[i][j] == 'E' || data->map->map[i][j] == 'W')
			{
				player_count++;
				data->map->player_direction = data->map->map[i][j];
			}
			else if (data->map->map[i][j] != '0' && data->map->map[i][j] != '1' && data->map->map[i][j] != ' ')
				return (print_error(MAP_ERROR, data), 1);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (print_error(MAP_ERROR, data), 1);
	if (check_closed_map(data))
		return (1);
	return (0);
}

int	validate_map(t_data *data)
{
	if (!data->map->texture_north || !data->map->texture_south ||
		!data->map->texture_west || !data->map->texture_east ||
		!data->map->color_floor || !data->map->color_ceiling ||
		!data->map->map)
		return (print_error(MAP_ERROR, data), 1);
	if (validate_colors(data))
		return (1);
	if (validate_map_structure(data))
		return (1);
	return (0);
}

int	check_first_part(t_data *data, char *tmp)
{
	while (tmp && (*tmp == ' ' || *tmp == '\t'))
		tmp++;
	if (ft_strncmp(tmp, "NO ", 3) == 0 || ft_strncmp(tmp, "SO ", 3) == 0 ||
		ft_strncmp(tmp, "WE ", 3) == 0 || ft_strncmp(tmp, "EA ", 3) == 0)
	{
		if (parse_textures(data, tmp))
			return (1);
	}
	else if (ft_strncmp(tmp, "F ", 2) == 0 || ft_strncmp(tmp, "C ", 2) == 0)
	{
		if (parse_colors(data, tmp))
			return (1);
	}
	else if (*tmp == '1' || *tmp == '0')
		return (2);
	return (0);
}

int	parse_file(t_data *data)
{
	int		fd;
	char	*line;
	char	*tmp;
	int		map_started;

	map_started = 0;
	fd = open(data->argv[1], O_RDONLY);
	if (fd < 0)
		return (print_error(FILE_OPEN_ERROR, data), 1);
	while ((line = get_next_line(fd)) != NULL)
	{
		tmp = line;
		if (map_started != 2)
		{
			map_started = check_first_part(data, tmp);
			if (map_started == 1)
				return (free(tmp), close(fd), 1);
		}
		if (map_started == 2)
		{
			if (parse_map_lines(data, fd, tmp))
				return (close(fd), 1);
			break ;
		}
		free(line);
	}
	close(fd);
	if (validate_map(data))
		return (1);
	return (0);
}
