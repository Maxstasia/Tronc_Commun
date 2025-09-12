/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:58:01 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/12 15:49:09 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_image	img;
	t_map	map;

	data.argc = argc;
	data.argv = argv;
	if (init_all(&data, &img, &map))
		return (free_all(&data), 1);
	loop(&data);
	free_all(&data);
	return (0);
}
