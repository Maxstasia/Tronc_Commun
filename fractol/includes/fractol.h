/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:17:59 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/02 14:08:16 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#	define FRACTOL_H

#		define WINDOW_WIDTH 1920
#		define WINDOW_HEIGHT 1080

#		define MLX_ERROR 1

#		define RED_PIXEL 0xFF0000
#		define GREEN_PIXEL 0x00FF00
#		define WHITE_PIXEL 0xFFFFFF

typedef struct s_image
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	img;
	int		cur_img;
}	t_data;

typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;
}	t_rect;

/*--bibliotheques--*/

#	include <fcntl.h>
#	include <unistd.h>
#	include <stdlib.h>
#	include <stdio.h>
#	include <string.h>
#	include <math.h>

#	include "ft_printf.h"
#	include "libft.h"
#	include "minilibx-linux/mlx.h"
#	include "minilibx-linux/mlx_int.h"

/*--fonctions--*/

#endif
