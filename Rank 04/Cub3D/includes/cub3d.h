/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:21:57 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/09 15:18:26 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// Standard libraries
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <limits.h>

// Custom libraries
# include "Libft/libft.h"
# include "minilibx-linux/mlx.h"

# include "struct.h"



// Macros
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define TILE_WIDTH 64
# define TILE_HEIGHT 64
# define FOV_ANGLE (60 * (M_PI / 180))



// Function prototypes
int						init_all(int argc, char **argv, t_data *data, t_mlx *mlx);
int						init_data(int argc, char **argv, t_data *data, t_mlx *mlx);
int 					init_mlx(t_mlx *mlx);

#endif