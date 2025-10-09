/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:57:31 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/09 19:10:17 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	init_parser(t_data *data)
{
	data->parser->fd = -1;
	data->parser->line = NULL;
	data->parser->first_line = NULL;
	data->parser->map = NULL;
	data->parser->floor_split = NULL;
	data->parser->ceiling_split = NULL;
	data->parser->count = 0;
	data->parser->len = 0;
	data->parser->i = 0;
	data->parser->j = 0;
	return (0);
}
