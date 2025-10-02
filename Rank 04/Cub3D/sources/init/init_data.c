/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:19:37 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/02 10:49:30 by mstasiak         ###   ########.fr       */
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
	init_map(data);
	init_mlx(data);
	init_parser(data);
	data->nothing_after_map = true;
	return (0);
}
