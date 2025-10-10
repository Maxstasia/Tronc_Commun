/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:57:44 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/10 17:42:03 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	clean_up(t_data *data)
{
	free_all(data);
	get_next_line(-1);
	exit(MLX_ERROR);
}

void	free_tab(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	destroy_sprites(t_data *data)
{
	if (!data || !data->map || !data->mlx_ptr)
		return ;
	if (data->map->img_north)
		mlx_destroy_image(data->mlx_ptr, data->map->img_north);
	if (data->map->img_south)
		mlx_destroy_image(data->mlx_ptr, data->map->img_south);
	if (data->map->img_west)
		mlx_destroy_image(data->mlx_ptr, data->map->img_west);
	if (data->map->img_east)
		mlx_destroy_image(data->mlx_ptr, data->map->img_east);
	if (data->map->img_door)
		mlx_destroy_image(data->mlx_ptr, data->map->img_door);
}
