/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:16:55 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/11 14:20:47 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_all(int argc, char **argv, t_data *data, t_image *img)
{
	if (argc != 2)
		return (print_error(USAGE_ERROR, data), 1);
	if (init_data(argc, argv, data, img))
		return (1);
	return (0);
}
