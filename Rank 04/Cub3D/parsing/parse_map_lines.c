/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:01:06 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/02 15:06:40 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_map_line(char *line)
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

static int	count_map_lines(int fd, char *first_line)
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

static int	part_1(t_data *data, t_parser *parser)
{
	parser->count = count_map_lines(parser->fd, parser->first_line);
	if (parser->first_line)
    {
        free(parser->first_line);
        parser->first_line = NULL;
        parser->line = NULL;
    }
	if (parser->count == 0)
		return (printf("No valid map found"), 1);
	close(parser->fd);
	parser->fd = open(data->argv[1], O_RDONLY);
	if (parser->fd < 0)
		return (printf("Cannot reopen file"), 1);
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
	{
		free(parser->line);
		parser->line = NULL;
		return (print_error(MALLOC_ERROR, data), 1);
	}
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
	if (part_1(data, parser))
		return (1);
	if (part_2(data, parser))
		return (1);
	while (parser->line)
	{
		parser->i = 0;
		while (parser->line[parser->i] && (parser->line[parser->i] == ' '
				|| parser->line[parser->i] == '\t'
				|| parser->line[parser->i] == '\n'
				|| parser->line[parser->i] == '\0'))
			parser->i ++;
		if (parser->line[parser->i] != '\0' && parser->line[parser->i] != '\n'
			&& parser->line[parser->i] != '\t'
			&& parser->line[parser->i] != ' ')
			data->nothing_after_map = false;
		free(parser->line);
		parser->line = get_next_line(parser->fd);
	}
	if (parser->line)
	{
		free(parser->line);
		parser->line = NULL;
	}
	parser->map[parser->count] = NULL;
	data->map->map = parser->map;
	close(parser->fd);
	parser->fd = 0;
	return (0);
}
