/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:57:08 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/09 19:10:17 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	print_error(int error_code, t_data *data)
{
	if (error_code == MLX_INIT_ERROR)
		ft_putstr_fd((char *)"Error\nFailed to initialize MLX\n", 2);
	else if (error_code == WINDOW_ERROR)
		ft_putstr_fd((char *)"Error\nFailed to create window\n", 2);
	else if (error_code == IMAGE_ERROR)
		ft_putstr_fd((char *)"Error\nFailed to create image\n", 2);
	else if (error_code == IMAGE_ADDR_ERROR)
		ft_putstr_fd((char *)"Error\nFailed to get image address\n", 2);
	else if (error_code == USAGE_ERROR)
		ft_putstr_fd((char *)"Error\nUsage:\n./cub3D path_to_map.cub\n", 2);
	else if (error_code == MALLOC_ERROR)
		ft_putstr_fd((char *)"Error\nMemory allocation failed\n", 2);
	else if (error_code == FILE_OPEN_ERROR)
		ft_putstr_fd((char *)"Error\nFailed to open file\n", 2);
	else if (error_code == TEXTURE_ERROR)
		ft_putstr_fd((char *)"Error\nInvalid texture format\n", 2);
	else if (error_code == COLOR_ERROR)
		ft_putstr_fd((char *)"Error\nInvalid color format\n", 2);
	else if (error_code == MAP_ERROR)
		ft_putstr_fd((char *)"Error\nInvalid map\n", 2);
	else
		ft_putstr_fd((char *)"Error\nAn unknown error occurred\n", 2);
	clean_up(data);
}
