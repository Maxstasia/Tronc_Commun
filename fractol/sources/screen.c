/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:34:38 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/06 17:04:43 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	img_pix_put(t_image *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & WHITE_PIXEL;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & WHITE_PIXEL;
		i -= 8;
	}
}

// The x and y coordinates of the rect corresponds to its upper left corner.
int	render_rect(t_image *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

void	render_background(t_image *img, int color)
{
	int	i;
	int	j;

	i = -1;
	while (i ++, i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			img_pix_put(img, j++, i, color);
	}
}

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	// Dessiner la fractale appropriée en fonction de la fractale choisie
	if (data->cur_img == 0)
		mandelbrot(data); // Appelle Mandelbrot si c le type de fractale
	else if (data->cur_img == 1)
		julia(data, data->c_re, data->c_im);//Appelle Julia si c le type fractal
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}
