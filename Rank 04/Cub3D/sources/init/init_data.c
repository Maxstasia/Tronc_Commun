/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:19:37 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/11 15:11:03 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_data(t_data *data, t_image *img, t_map *map)
{
	img = malloc(sizeof(t_image));
	if (!img)
		return (img = NULL, 1);
	data->img = img;
	if (init_mlx(data))
		return (clean_up(data), 1);
	map = malloc(sizeof(t_map));
	if (!map)
		return (map = NULL, 1);
	data->map = map;
	if (init_map(data))
		return (clean_up(data), 1);
	return (0);
}
