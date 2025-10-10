/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_keys_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 11:36:58 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/10 11:38:07 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	init_keys(t_data *data)
{
	data->keys->w = 0;
	data->keys->a = 0;
	data->keys->s = 0;
	data->keys->d = 0;
	data->keys->left = 0;
	data->keys->right = 0;
}
