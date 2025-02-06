/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:39:22 by mstasiak          #+#    #+#             */
/*   Updated: 2025/02/06 13:45:14 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	get_color(int iter, int palette)
{
	if (palette == 0)
		return (WHITE_PIXEL / MAX_ITER * iter);
	else if (palette == 1)
		return (GREEN_PIXEL / MAX_ITER * iter);
	else if (palette == 2)
		return (RED_PIXEL / MAX_ITER * iter);
	else if (palette == 3)
		return (0xFFFF00 / MAX_ITER * iter);
	else if (palette == 4)
		return (0xFF00FF / MAX_ITER * iter);
	else if (palette == 5)
		return (iter * BLUE_PIXEL);
	else if (palette == 6)
		return (iter * GREEN_PIXEL);
	else if (palette == 7)
		return (iter * RED_PIXEL);
	else if (palette == 8)
		return (iter * 010101);
	else if (palette == 9)
		return (iter * 0F0F0F);
	return (iter * WHITE_PIXEL);
}
