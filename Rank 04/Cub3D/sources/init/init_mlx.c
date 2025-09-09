/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:22:01 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/09 15:34:11 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
	{
		ft_putstr_fd((char *)"Error\nFailed to initialize MLX\n", 2);
		return (1);
	}
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	if (mlx->win == NULL)
	{
		ft_putstr_fd((char *)"Error\nFailed to create window\n", 2);
		return (1);
	}
	return (0);
}