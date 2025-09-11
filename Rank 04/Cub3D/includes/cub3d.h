/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:21:57 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/11 15:09:38 by mstasiak         ###   ########.fr       */
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
# include "minilibx-linux/mlx_int.h"

# include "struct.h"

// Macros
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define TILE_WIDTH 64
# define TILE_HEIGHT 64

# define MLX_ERROR 1

// Function prototypes
int			init_data(t_data *data, t_image *img, t_map *map);

int			init_all(t_data *data, t_image *img, t_map *map);

int			init_map(t_data *data);

int			init_mlx(t_data *data);
int			loop(t_data *data);

void		print_error(int error_code, t_data *data);

int			handle_keypress(int keysym, t_data *data);

int			handle_destroy(t_data *data);

void		clean_up(t_data *data);

#endif