/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:16:55 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/12 15:48:50 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_all(t_data *data, t_image *img, t_map *map)
{
	if (data->argc != 2)
		return (print_error(USAGE_ERROR, data), 1);
	if (init_data(data, img, map))
		return (1);
	return (0);
}
