/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:14:18 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/07 11:28:17 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	asignation_no_so(t_data *data, char *path, char *line, char **split)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "N ", 2) == 0)
	{
		if (data->map->texture_north)
			return (free_split(split), print_error(TEXTURE_ERROR, data), 1);
		else
			data->map->texture_north = path;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "S ", 2) == 0)
	{
		if (data->map->texture_south)
			return (free_split(split), print_error(TEXTURE_ERROR, data), 1);
		else
			data->map->texture_south = path;
	}
	return (0);
}

static int	asignation_ea_we(t_data *data, char *path, char *line, char **split)
{
	if (ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "W ", 2) == 0)
	{
		if (data->map->texture_west)
			return (free_split(split), print_error(TEXTURE_ERROR, data), 1);
		else
			data->map->texture_west = path;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "E ", 2) == 0)
	{
		if (data->map->texture_east)
			return (free_split(split), print_error(TEXTURE_ERROR, data), 1);
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

static int	is_valid_texture(t_data *data, t_parser *parser, char **path)
{
	int		fd;

	parser->len = ft_strlen(path[1]);
	parser->i = parser->len - 1;
	while (parser->i >= 0
		&& (path[1][parser->i] == ' ' || path[1][parser->i] == '\t'
		|| path[1][parser->i] == '\n' || path[1][parser->i] == '\0'))
	{
		path[1][parser->i] = '\0';
		parser->i--;
	}
	parser->len = ft_strlen(path[1]);
	if (parser->len < 4
		|| ft_strncmp(&path[1][parser->len - 4], ".xpm", 4) != 0)
		return (parser->len = 0, 0);
	parser->len = 0;
	fd = open(path[1], O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	if (set_textures(data, path[1], data->parser->first_line, path))
		return (0);
	return (1);
}

int	parse_textures(t_data *data, t_parser *parser)
{
	char	**split;

	split = ft_split(data->parser->first_line, ' ');
	if (!split || !split[1] || (split[2] && split[2][0] != '\n'))
		return (free_split(split), 1);
	if (is_valid_texture(data, parser, split))
		return (free_split(split), split = NULL, 0);
	return (free_split(split), 1);
}
