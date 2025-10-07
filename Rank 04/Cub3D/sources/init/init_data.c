/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:19:37 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/07 14:28:14 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_data(t_data *data)
{
	data->img = malloc(sizeof(t_image));
	if (!data->img)
		return (data->img = NULL, print_error(MALLOC_ERROR, data), 1);
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		return (data->map = NULL, print_error(MALLOC_ERROR, data), 1);
	data->parser = malloc(sizeof(t_parser));
	if (!data->parser)
		return (data->parser = NULL, print_error(MALLOC_ERROR, data), 1);
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		return (data->player = NULL, print_error(MALLOC_ERROR, data), 1);
	data->ray = malloc(sizeof(t_ray));
	if (!data->ray)
		return (data->ray = NULL, print_error(MALLOC_ERROR, data), 1);
	init_map(data);
	init_mlx(data);
	init_parser(data);
	init_player(data);
	init_ray(data);
	data->nothing_after_map = true;
	return (0);
}
