/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:50:56 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/23 11:23:41 by mstasiak         ###   ########.fr       */
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

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] != '1' && line[i] != '0' && line[i] != ' ')
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

int	count_map_lines(int fd, char *first_line)
{
	char	*line;
	int		count;

	line = first_line;
	count = 0;
	while (line)
	{
		if (is_map_line(line))
		{
			count++;
		}
		if (line != first_line)
			free(line);
		line = get_next_line(fd);
	}
	return (count);
}

int	parse_map_lines(t_data *data, int fd, char *first_line)
{
	char	**map;
	char	*line;
	int		count;
	int		i;
	size_t	len;

	count = count_map_lines(fd, first_line);
	if (count == 0)
		return (printf("No valid map found"), 1);
	close(fd);
	fd = open(data->argv[1], O_RDONLY);
	if (fd < 0)
		return (printf("Cannot reopen file"), 1);
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line))
		{
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	map = malloc(sizeof(char *) * (count + 1));
	if (!map)
		return (free(line), print_error(MALLOC_ERROR, data), 1);
	i = 0;
	while (line && i < count)
	{
		if (is_map_line(line))
		{
			len = ft_strlen(line);
			if (len > 0 && line[len - 1] == '\n')
				line[len - 1] = '\0';
			map[i] = ft_strdup(line);
			if (!map[i])
				return (free_tab(map), free(line),
					print_error(MALLOC_ERROR, data), 1);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		i = 0;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'
				|| line[i] == '\n' || line[i] == '\0'))
			i ++;
		if (line[i] != '\0' && line[i] != '\n'
			&& line[i] != '\t' && line[i] != ' ')
			data->nothing_after_map = false;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (map[count] = NULL, data->map->map = map, close(fd), 0);
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
				if (i == 0 || !data->map->map[i + 1] || j == 0
					|| !data->map->map[i][j + 1]
					|| data->map->map[i - 1][j] == ' '
					|| data->map->map[i + 1][j] == ' ')
					return (print_error(MAP_ERROR, data), 1);
				if (data->map->map[i][j - 1] == ' '
					|| data->map->map[i][j + 1] == ' ')
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
			else if (data->map->map[i][j] != '0' && data->map->map[i][j] != '1'
				&& data->map->map[i][j] != ' ')
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
	if (!data->map->texture_north || !data->map->texture_south
		|| !data->map->texture_west || !data->map->texture_east
		|| !data->map->color_floor || !data->map->color_ceiling
		|| !data->map->map)
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
	if (ft_strncmp(tmp, "NO ", 3) == 0 || ft_strncmp(tmp, "SO ", 3) == 0
		|| ft_strncmp(tmp, "WE ", 3) == 0 || ft_strncmp(tmp, "EA ", 3) == 0)
	{
		if (parse_textures(data, tmp))
			return (1);
		return (0);
	}
	else if (ft_strncmp(tmp, "F ", 2) == 0 || ft_strncmp(tmp, "C ", 2) == 0)
	{
		if (parse_colors(data, tmp))
			return (1);
		return (0);
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

	fd = open(data->argv[1], O_RDONLY);
	if (fd < 0)
		return (print_error(FILE_OPEN_ERROR, data), 1);
	while ((line = get_next_line(fd)) != NULL)
	{
		tmp = line;
		map_started = check_first_part(data, tmp);
		if (map_started == 1)
			return (free(tmp), close(fd), 1);
		else if (map_started == 2)
		{
			if (parse_map_lines(data, fd, tmp))
				return (free(line), close(fd), 1);
			if (data->nothing_after_map == false)
				return (free(line), close(fd), print_error(MAP_ERROR, data), 1);
			free(line);
			break ;
		}
		free(line);
	}
	close(fd);
	if (validate_map(data))
		return (1);
	return (0);
}
