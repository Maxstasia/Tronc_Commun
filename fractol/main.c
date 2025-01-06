/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:23:44 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/06 16:51:54 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2 || (ft_strcmp(argv[1], "julia") == 0 && argc != 4))
		print_usage();
	data.color_palette = 0;
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "Fractol");
	if (data.win_ptr == NULL)
		return (free(data.win_ptr), MLX_ERROR);
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
	{
		data.min_x = -2.0;
		data.max_x = 2.0;
		data.min_y = -2.0;
		data.max_y = 2.0;
	}
	else if (ft_strcmp(argv[1], "julia") == 0)
	{
		data.min_x = -1.5;
		data.max_x = 1.5;
		data.min_y = -1.5;
		data.max_y = 1.5;
	}
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
	mlx_mouse_hook(data.win_ptr, &handle_scroll, &data);
	mlx_loop(data.mlx_ptr);
	// Libérer les ressources
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}
