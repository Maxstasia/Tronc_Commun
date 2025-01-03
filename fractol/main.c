/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:23:44 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/03 18:58:37 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

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
			*pixel++ = (color >> (img->bpp - 8 - i)) &  WHITE_PIXEL;
		i -= 8;
	}
}

// The x and y coordinates of the rect corresponds to its upper left corner.
int render_rect(t_image *img, t_rect rect)
{
	int	i;
	int j;

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

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
		exit(0);
	}
	else if ((keysym == XK_space) || (keysym == XK_Return) || (keysym == XK_KP_Enter)) // Changer la palette de couleurs
	{
		data->color_palette = (data->color_palette + 1) % 10; // Boucle entre 10 palettes
		render(data); // Réafficher la fractale avec la nouvelle palette
	}
	return (0);
}

int	handle_destroy(t_data *data)
{
	if (data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	exit(0);
	return (0);
}

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);

	// Dessiner la fractale appropriée en fonction de la fractale choisie
	if (data->cur_img == 0)
		mandelbrot(data); // Appelle Mandelbrot si c'est le type de fractale sélectionné
	else if (data->cur_img == 1)
		julia(data, data->c_re, data->c_im); // Appelle Julia si c'est le type de fractale sélectionné

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

void	print_usage(void)
{
	ft_printf("Usage: ./fractol <nom de la fractale> <param 1> <param 2>\n");
	ft_printf("Fractale disponible:\n");
	ft_printf("mandelbrot\n");
	ft_printf("julia\n");
	exit(EXIT_FAILURE);
}

void	mandelbrot_wrapper(t_data *data)
{
	data->cur_img = 0;
	render_background(&data->img, WHITE_PIXEL); // Effacer l'image
	mandelbrot(data); // Dessiner Mandelbrot
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}

void	julia_wrapper(t_data *data, double c_re, double c_im)
{
	data->cur_img = 1;
	render_background(&data->img, WHITE_PIXEL); // Effacer l'image
	julia(data, c_re, c_im); // Dessiner Julia avec les constantes données
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2 || (ft_strcmp(argv[1], "julia") == 0 && argc != 4))
		print_usage();

	data.color_palette = 0;
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);

	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Fractol");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);

	// Vérifier le type de fractale
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
		mandelbrot_wrapper(&data);
	else if (ft_strcmp(argv[1], "julia") == 0)
	{
		data.c_re = ft_atof(argv[2]); // Convertir en double
		data.c_im = ft_atof(argv[3]);
		julia_wrapper(&data, data.c_re, data.c_im);
	}
	else
		print_usage();

	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, NoEventMask, &handle_destroy, &data);

	mlx_loop(data.mlx_ptr);

	// Libérer les ressources
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}
