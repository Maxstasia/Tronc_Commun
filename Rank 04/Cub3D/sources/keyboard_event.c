/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_event.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:38:09 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/12 15:47:19 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape
		|| keysym == XK_BackSpace || keysym == XK_Delete)
	{
		free_all(data);
		exit(0);
	}
	return (0);
}
