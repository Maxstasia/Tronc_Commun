/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:19:37 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/11 14:07:34 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_data(int argc, char **argv, t_data *data, t_image *img)
{
	img = malloc(sizeof(t_image));
	if (!img)
		return (img = NULL, 1);
	data->img = img;
	if (init_mlx(data))
		return (1);
	data->argc = argc;
	data->argv = argv;
	return (0);
}
