/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:19:37 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/01 14:32:29 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_data(t_data *data, t_image *img, t_map *map, t_parser *parser)
{
	img = malloc(sizeof(t_image));
	if (!img)
		return (img = NULL, print_error(MALLOC_ERROR, data), 1);
	data->img = img;
	map = malloc(sizeof(t_map));
	if (!map)
		return (map = NULL, print_error(MALLOC_ERROR, data), 1);
	data->map = map;
	parser = malloc(sizeof(t_parser));
	if (!parser)
		return (parser = NULL, print_error(MALLOC_ERROR, data), 1);
	data->parser = parser;
	init_map(data);
	init_mlx(data);
	init_parser(data);
	data->nothing_after_map = true;
	return (0);
}
