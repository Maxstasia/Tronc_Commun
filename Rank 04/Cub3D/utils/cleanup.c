/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:57:44 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/11 13:52:13 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_error(int error_code, t_data *data)
{
	if (error_code == 1)
		ft_putstr_fd((char *)"Error\nFailed to initialize MLX\n", 2);
	else if (error_code == 2)
		ft_putstr_fd((char *)"Error\nFailed to create window\n", 2);
	else if (error_code == 3)
		ft_putstr_fd((char *)"Error\nFailed to create image\n", 2);
	else if (error_code == 4)
		ft_putstr_fd((char *)"Error\nFailed to get image address\n", 2);
	else
		ft_putstr_fd((char *)"Error\nAn unknown error occurred\n", 2);
	clean_up(data);
}

void	clean_up(t_data *data)
{
	if (data)
	{
		if (data->img->mlx_img && data->mlx_ptr)
			mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
		if (data->win_ptr && data->mlx_ptr)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		if (data->mlx_ptr)
		{
			mlx_destroy_display(data->mlx_ptr);
			data->win_ptr = NULL;
			free(data->mlx_ptr);
		}
		if (data->img)
			free(data->img);
		exit(MLX_ERROR);
	}
	exit(MLX_ERROR);
}
