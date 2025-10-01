/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:57:31 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/01 11:30:01 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_parser(t_parser *parser)
{
	parser->fd = -1;
	parser->line = NULL;
	parser->first_line = NULL;
	parser->map = NULL;
	parser->count = 0;
	parser->len = 0;
	parser->i = 0;
	parser->j = 0;
	return (0);
}
