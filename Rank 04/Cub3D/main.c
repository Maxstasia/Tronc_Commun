/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:58:01 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/01 14:07:40 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_data		data;
	t_image		img;
	t_map		map;
	t_parser	parser;

	ft_memset(&data, 0, sizeof(t_data));
	ft_memset(&img, 0, sizeof(t_image));
	ft_memset(&map, 0, sizeof(t_map));
	ft_memset(&parser, 0, sizeof(t_parser));
	data.argc = argc;
	data.argv = argv;
	if (init_all(&data, &img, &map, &parser))
		return (free_all(&data), 1);
	loop(&data);
	free_all(&data);
	return (0);
}
