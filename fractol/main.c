/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:23:44 by mstasiak          #+#    #+#             */
/*   Updated: 2024/12/13 10:52:26 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int	main()
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		x = -1;
	//int		y = -1;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (0);
	ft_printf(" j'execute le programme \n");
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Hello");
	while(x ++, x < 250)
		mlx_pixel_put(mlx_ptr, win_ptr, x, 0, 0xffffff);
	ft_printf("test\n");
	mlx_loop(mlx_ptr);
	ft_printf(" j'ai fini \n");
	return 0;
}