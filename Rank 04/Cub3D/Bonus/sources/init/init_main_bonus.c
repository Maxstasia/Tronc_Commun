/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:16:55 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/10 17:49:07 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	init_all(t_data *data)
{
	if (data->argc != 2)
		return (print_error(USAGE_ERROR, data), 1);
	if (init_data(data))
		return (1);
	if (parse_file(data, data->parser))
		return (1);
	precalculate_colors(data);
	if (setup_mlx(data))
		return (clean_up(data), 1);
	if (load_textures(data))
		return (clean_up(data), 1);
	find_player_position(data);
	render_frame(data);
	return (0);
}
