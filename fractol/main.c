/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:23:44 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/02 14:55:44 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	img_pix_put(t_image *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		// big endian, MSB is the leftmost bit
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		// little endian, LSB is the leftmost bit
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
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
	}
	else if (keysym == XK_z)
	{
		render_rect(&data->img, (t_rect){0, 0, 300, 300, WHITE_PIXEL});
		render_rect(&data->img, (t_rect){100, 100, 300, 300, RED_PIXEL});
	}
	return (0);
}

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img, WHITE_PIXEL);
	render_rect(&data->img, (t_rect){WINDOW_WIDTH - 300, WINDOW_HEIGHT - 300, 300, 300, GREEN_PIXEL});
	render_rect(&data->img, (t_rect){0, 0, 300, 300, RED_PIXEL});

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);

	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Fractol");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	// Setup hooks
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

	mlx_loop(data.mlx_ptr);

	// we will exit the loop if there's no window left, and execute this code
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}

/* int	handle_no_event(void *data)
{
    return (data = data, 0);
}

int	handle_input(int keysym, t_data *data)
{
    if (keysym == XK_Escape)
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
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
	int		width = 500;
	int		height = 500;
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
    mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data); // ADDED
    mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data); // CHANGED

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
} */