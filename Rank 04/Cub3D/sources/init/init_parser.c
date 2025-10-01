/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:57:31 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/01 14:32:25 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_parser(t_data *data)
{
	data->parser->fd = -1;
	data->parser->line = NULL;
	data->parser->first_line = NULL;
	data->parser->map = NULL;
	data->parser->count = 0;
	data->parser->len = 0;
	data->parser->i = 0;
	data->parser->j = 0;
	return (0);
}
