/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:19:37 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/11 17:29:04 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_data(t_data *data, t_image *img, t_map *map)
{
	img = malloc(sizeof(t_image));
	if (!img)
		return (img = NULL, print_error(MALLOC_ERROR, data), 1);
	data->img = img;
	map = malloc(sizeof(t_map));
	if (!map)
		return (map = NULL, print_error(MALLOC_ERROR, data), 1);
	data->map = map;
	init_map(data);
	init_mlx(data);
	if (parse_file(data))
		return (1);
	if (setup_mlx(data))
		return (clean_up(data), 1);
	return (0);
}
