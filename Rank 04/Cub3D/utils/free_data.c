/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:21:16 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/02 12:13:26 by mstasiak         ###   ########.fr       */
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
	map = NULL;
}

void	free_img(t_data *data)
{
	if (!data || !data->img)
		return ;
	if (data->img->mlx_img && data->mlx_ptr)
	{
		mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
		data->img->mlx_img = NULL;
	}
	data->img->addr = NULL;
	data->img->bpp = 0;
	data->img->l_len = 0;
	data->img->endian = 0;
	free(data->img);
	data->img = NULL;
}

void	free_parser(t_parser *parser)
{
	if (!parser)
		return ;
	if (parser->fd)
	{
		close(parser->fd);
		parser->fd = 0;
	}
	if (parser->line)
	{
		free(parser->line);
		parser->line = NULL;
	}
	if (parser->first_line && parser->first_line != parser->line)
	{
		free(parser->first_line);
		parser->first_line = NULL;
	}
	parser->count = 0;
	parser->len = 0;
	parser->i = 0;
	parser->j = 0;
	free(parser);
	parser = NULL;
}

void	free_data(t_data *data)
{
	free_map(data->map);
	data->map = NULL;
	free_img(data);
	data->img = NULL;
	free_parser(data->parser);
	data->parser = NULL;
	get_next_line(-42);
	data->argc = 0;
	if (data->argv)
		data->argv = NULL;
	if (data->win_ptr && data->mlx_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		data->win_ptr = NULL;
	}
	free(data);
}
