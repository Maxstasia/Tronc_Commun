/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:17:59 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/03 18:54:35 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

/*--variables globales--*/

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

# define MLX_ERROR 1
# define MAX_ITER 50

# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0x00FF00
# define BLUE_PIXEL 0x0000FF
# define WHITE_PIXEL 0xFFFFFF
# define BLACK_PIXEL 0x000000

/*--bibliotheques--*/

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

# include "ft_printf.h"
# include "libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"

/*--structures--*/

typedef struct s_image
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	img;
	int		color_palette;
	int		cur_img;
	double	c_re;
	double	c_im;
}	t_data;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rect;

/*--fonctions--*/

void	img_pix_put(t_image *img, int x, int y, int color);
int 	render_rect(t_image *img, t_rect rect);
void	render_background(t_image *img, int color);
int		handle_keypress(int keysym, t_data *data);
int		handle_destroy(t_data *data);
int		render(t_data *data);

void	mandelbrot(t_data *data);

void	julia(t_data *data, double c_re, double c_im);

int		get_color(int iter, int palette);

double	ft_atof(const char *str);

#endif
