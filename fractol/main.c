/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:23:44 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/01 18:37:58 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int	handle_no_event(void *data)
{
    /* This function needs to exist, but it is useless for the moment */
    return (data = data, 0);
}

int	handle_input(int keysym, t_data *data)
{
    if (keysym == XK_Escape)
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
    if (keysym == XK_Escape)
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	
    printf("Keypress: %d\n", keysym);
    return (0);
}

int	handle_keyrelease(int keysym, void *data)
{
    printf("Keyrelease: %d\n", keysym);
    return (data = data, 0);
}

int	main()
{
	t_data	data;
	int		width = 100;
	int		height = 100;
	int		x = -1;
	int		y = -1;
	int		color = 0x000000;

	data.mlx_ptr = mlx_init();
	// Protection
	if (!data.mlx_ptr)
		return (0);
	ft_printf("j'execute le programme \n");
	data.win_ptr = mlx_new_window(data.mlx_ptr, width, height, "Hello");
	// Protection
	if (data.win_ptr == NULL)
		return (free(data.win_ptr), free(data.mlx_ptr), 0);
	
	// Setup hooks
    mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
    mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data); /* ADDED */
    mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data); /* CHANGED */

	data.img_ptr = mlx_new_image(data.mlx_ptr, width, height);
	// Protection
	if (data.img_ptr == NULL)
		return (free(data.img_ptr), free(data.win_ptr), free(data.mlx_ptr), 0);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);
	while(++y, y < height)
	{
		while(++x, x < width)
		{
			mlx_pixel_put(data.mlx_ptr, data.win_ptr, x, y, color += 1);
			ft_printf("color : %x\n", color);
		}
		x = 0;
	}
	mlx_loop(data.mlx_ptr);
	ft_printf("j'ai fini \n");
	return (free(data.mlx_ptr), 0);
}