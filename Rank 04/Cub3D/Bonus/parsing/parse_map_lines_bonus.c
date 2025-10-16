/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_lines_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:01:06 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/16 11:35:38 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] != 'P'
		&& line[i] != '3' && line[i] != '4' && line[i] != '5' && line[i] != '6')
		return (0);
	while (line[i] && line[i] != '\n')
		i++;
	return (1);
}

static int	count_file_map_lines(int fd, char *first_line)
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
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

static int	part_1(t_data *data, t_parser *parser)
{
	parser->count = count_file_map_lines(parser->fd, parser->line);
	parser->first_line = NULL;
	parser->line = NULL;
	if (parser->count == 0)
		return (get_next_line(-1), 1);
	close(parser->fd);
	parser->fd = open(data->argv[1], O_RDONLY);
	if (parser->fd < 0)
		return (get_next_line(-1), 1);
	parser->line = get_next_line(parser->fd);
	while (parser->line)
	{
		if (is_map_line(parser->line))
			break ;
		free(parser->line);
		parser->line = get_next_line(parser->fd);
	}
	parser->map = malloc(sizeof(char *) * (parser->count + 1));
	if (!parser->map)
		return (free(parser->line), parser->line = NULL,
			get_next_line(-1), print_error(MALLOC_ERROR, data), 1);
	return (0);
}

static int	part_2(t_data *data, t_parser *parser)
{
	parser->i = 0;
	while (parser->line && parser->i < parser->count)
	{
		if (is_map_line(parser->line))
		{
			parser->len = ft_strlen(parser->line);
			if (parser->len > 0 && parser->line[parser->len - 1] == '\n')
				parser->line[parser->len - 1] = '\0';
			parser->map[parser->i] = ft_strdup(parser->line);
			if (!parser->map[parser->i])
			{
				free_tab(parser->map);
				free(parser->line);
				parser->line = NULL;
				get_next_line(-1);
				return (print_error(MALLOC_ERROR, data), 1);
			}
			parser->i++;
		}
		free(parser->line);
		parser->line = get_next_line(parser->fd);
	}
	return (0);
}

int	parse_map_lines(t_data *data, t_parser *parser)
{
	int	i;

	if (part_1(data, parser))
		return (1);
	if (part_2(data, parser))
		return (1);
	while (parser->line)
	{
		i = 0;
		while (parser->line[i] && (parser->line[i] == ' '
				|| parser->line[i] == '\t' || parser->line[i] == '\n'
				|| parser->line[i] == '\0'))
			i ++;
		if (parser->line[i] != '\0' && parser->line[i] != '\n'
			&& parser->line[i] != '\t' && parser->line[i] != ' ')
			data->nothing_after_map = false;
		free(parser->line);
		parser->line = get_next_line(parser->fd);
	}
	if (parser->line)
		free(parser->line);
	parser->line = NULL;
	parser->map[parser->count] = NULL;
	data->map->map = parser->map;
	return (close(parser->fd), get_next_line(-1), 0);
}
