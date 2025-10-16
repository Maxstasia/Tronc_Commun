/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:50:56 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/16 15:08:14 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	is_valid_name(t_parser *parser)
{
	if (ft_strncmp(parser->first_line, "NO ", 3) != 0
		&& ft_strncmp(parser->first_line, "SO ", 3) != 0
		&& ft_strncmp(parser->first_line, "WE ", 3) != 0
		&& ft_strncmp(parser->first_line, "EA ", 3) != 0
		&& ft_strncmp(parser->first_line, "DO ", 3) != 0
		&& ft_strncmp(parser->first_line, "TP ", 3) != 0
		&& ft_strncmp(parser->first_line, "N ", 2) != 0
		&& ft_strncmp(parser->first_line, "S ", 2) != 0
		&& ft_strncmp(parser->first_line, "W ", 2) != 0
		&& ft_strncmp(parser->first_line, "E ", 2) != 0
		&& ft_strncmp(parser->first_line, "D ", 2) != 0
		&& ft_strncmp(parser->first_line, "T ", 2) != 0)
		return (0);
	return (1);
}

static int	check_first_part(t_data *data, t_parser *parser)
{
	while (parser->first_line && (*parser->first_line == ' '
			|| *parser->first_line == '\t'))
		parser->first_line++;
	if (is_valid_name(parser))
	{
		if (parse_textures(data, parser))
			return (print_error(TEXTURE_ERROR, data), 1);
		return (0);
	}
	else if (ft_strncmp(parser->first_line, "F ", 2) == 0
		|| ft_strncmp(parser->first_line, "C ", 2) == 0)
	{
		if (parse_colors(data, parser->first_line))
			return (1);
		return (0);
	}
	else if (*parser->first_line == '1' || *parser->first_line == '0')
		return (2);
	else if (*parser->first_line == '\n' || *parser->first_line == '\0')
		return (0);
	else
		return (1);
	return (0);
}

static int	parse_file_helper(t_data *data, t_parser *parser)
{
	int	map_started;

	while (parser->line != NULL)
	{
		parser->first_line = parser->line;
		map_started = check_first_part(data, parser);
		if (map_started == 1)
			return (free(parser->line), parser->line = NULL, close(parser->fd),
				parser->fd = 0, 1);
		else if (map_started == 2)
		{
			if (parse_map_lines(data, parser))
				return (parser->fd = 0, 1);
			if (data->nothing_after_map == false)
				return (close(parser->fd),
					parser->fd = 0, print_error(MAP_ERROR, data), 1);
			break ;
		}
		free(parser->line);
		parser->line = get_next_line(parser->fd);
	}
	if (parser->line)
		return (free(parser->line), parser->line = NULL, 0);
	return (0);
}

int	parse_file(t_data *data, t_parser *parser)
{
	parser->fd = open(data->argv[1], O_RDONLY);
	if (parser->fd < 0)
		return (print_error(FILE_OPEN_ERROR, data), 1);
	parser->line = get_next_line(parser->fd);
	if (parse_file_helper(data, parser))
		return (print_error(MAP_ERROR, data), 1);
	close(parser->fd);
	parser->fd = 0;
	get_next_line(-1);
	if (validate_map(data, data->map))
		return (1);
	return (0);
}

int	count_map_lines(char **map)
{
	int	i;

	if (!map)
		return (0);
	i = 0;
	while (map[i])
		i++;
	return (i);
}
