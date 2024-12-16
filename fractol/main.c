/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:23:44 by mstasiak          #+#    #+#             */
/*   Updated: 2024/12/16 17:49:00 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int	main()
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		width = 1920;
	int		height = 1080;
	int		x = -1;
	int		y = -1;
	int		color = 0xffffff;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (0);
	ft_printf("j'execute le programme \n");
	win_ptr = mlx_new_window(mlx_ptr, width, height, "Hello");
	img_ptr = mlx_new_image(mlx_ptr, width, height);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	while(++y, y < height)
	{
		while(++x, x < width)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, color -= 1);
			ft_printf("color : %x\n", color);
		}
		x = 0;
	}
	ft_printf("test\n");
	mlx_loop(mlx_ptr);
	ft_printf(" j'ai fini \n");
	return 0;
}