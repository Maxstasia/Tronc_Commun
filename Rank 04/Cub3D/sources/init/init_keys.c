/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 11:36:58 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/10 12:17:47 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_keys(t_data *data)
{
	data->keys->w = 0;
	data->keys->a = 0;
	data->keys->s = 0;
	data->keys->d = 0;
	data->keys->left = 0;
	data->keys->right = 0;
}
