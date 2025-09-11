/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:16:55 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/11 12:15:57 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_all(int argc, char **argv, t_data *data, t_image *img)
{
	if (argc != 2)
	{
		ft_putstr_fd((char *)"Error\nUsage:\n./cub3D path_to_map.cub\n", 2);
		return (1);
	}
	if (init_data(argc, argv, data, img))
		return (1);
	return (0);
}