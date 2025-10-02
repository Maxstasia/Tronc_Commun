/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:16:55 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/02 10:47:57 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_all(t_data *data)
{
	if (data->argc != 2)
		return (print_error(USAGE_ERROR, data), 1);
	if (init_data(data))
		return (1);
	if (parse_file(data, data->parser))
		return (1);
	if (setup_mlx(data))
		return (clean_up(data), 1);
	return (0);
}
