/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:57:44 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/12 15:50:57 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	clean_up(t_data *data)
{
	free_all(data);
	exit(MLX_ERROR);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->texture_north)
		free(map->texture_north);
	if (map->texture_south)
		free(map->texture_south);
	if (map->texture_west)
		free(map->texture_west);
	if (map->texture_east)
		free(map->texture_east);
	if (map->color_floor)
		free(map->color_floor);
	if (map->color_ceiling)
		free(map->color_ceiling);
	if (map->map)
		free_tab(map->map);
	free(map);
}

void	free_img(t_data *data)
{
	if (!data || !data->img)
		return ;
	if (data->img->mlx_img && data->mlx_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
	if (data->img->addr)
		data->img->addr = NULL;
	if (data->img->bpp)
		data->img->bpp = 0;
	if (data->img->l_len)
		data->img->l_len = 0;
	if (data->img->endian)
		data->img->endian = 0;
	if (data->img)
		free(data->img);
}

void	free_data(t_data *data)
{
	free_map(data->map);
	free_img(data);
	if (data)
	{
		data->argc = 0;
		if (data->argv)
			data->argv = NULL;
		if (data->win_ptr && data->mlx_ptr)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		if (data->mlx_ptr)
		{
			mlx_destroy_display(data->mlx_ptr);
			data->win_ptr = NULL;
			free(data->mlx_ptr);
		}
			data = NULL;
	}
}

void	free_all(t_data *data)
{
	free_data(data);
}
