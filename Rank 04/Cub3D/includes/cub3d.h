/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:21:57 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/11 17:28:46 by mstasiak         ###   ########.fr       */
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
# include <stdbool.h>

// Custom libraries
# include "Libft/libft.h"
# include "get_next_line/get_next_line.h"
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
/* ------------------------------ parsing ------------------------------ */
/* ------- parser.c ------- */
int			parse_file(t_data *data);
int			parse_textures(t_data *data, char *line);
int			parse_colors(t_data *data, char *line);
int			validate_map(t_data *data);

/* ------------------------------ sources ------------------------------ */
/* --------------- init --------------- */
/* ------- init_data.c ------- */
int			init_data(t_data *data, t_image *img, t_map *map);

/* ------- init_main.c ------- */
int			init_all(t_data *data, t_image *img, t_map *map);

/* ------- init_map.c ------- */
void		init_map(t_data *data);

/* ------- init_mlx.c ------- */
void		init_mlx(t_data *data);
int			setup_mlx(t_data *data);
int			loop(t_data *data);

/* ------------------------------ sources ------------------------------ */
/* ------- error.c ------- */
void		print_error(int error_code, t_data *data);

/* ------- keyboard_event.c ------- */
int			handle_keypress(int keysym, t_data *data);

/* ------- mouse_event.c ------- */
int			handle_destroy(t_data *data);

/* ------------------------------ utils ------------------------------ */
/* ------- clean_up -------*/
void		clean_up(t_data *data);
void		free_split(char **split);

#endif