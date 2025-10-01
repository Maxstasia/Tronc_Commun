/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:21:16 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/01 14:54:42 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	free_parser(t_parser *parser)
{
	if (!parser)
		return ;
	if (parser->fd)
		close(parser->fd);
	if (parser->line)
		free(parser->line);
	if (parser->first_line && parser->first_line != parser->line)
		free(parser->first_line);
	if (parser->count)
		parser->count = 0;
	if (parser->len)
		parser->len = 0;
	if (parser->i)
		parser->i = 0;
	if (parser->j)
		parser->j = 0;
	if (parser)
		free(parser);
}

void	free_data(t_data *data)
{
	free_map(data->map);
	free_img(data);
	free_parser(data->parser);
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
