/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:21:57 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/09 15:57:40 by mstasiak         ###   ########.fr       */
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

// Math constants
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

// Macros
//# define WIN_WIDTH 800
//# define WIN_HEIGHT 600
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define MOV_SPEED 0.1
# define ROT_SPEED 0.05
# define FOV 90

# define MLX_ERROR 1

// Function prototypes
/* ------------------------------ parsing ------------------------------ */
/* ------- check_map.c ------- */
int			validate_map(t_data *data, t_map *map);

/* ------- parse_colors.c ------- */
int			parse_colors(t_data *data, char *line);
int			validate_colors(t_data *data);

/* ------- parse_map_lines.c ------- */
int			parse_map_lines(t_data *data, t_parser *parser);

/* -------  parse_textures.c ------- */
int			parse_textures(t_data *data, t_parser *parser);

/* ------- parser.c ------- */
int			parse_file(t_data *data, t_parser *parser);
int			count_map_lines(char **map);

/* ------------------------------ ray_casting ------------------------------ */
/* ------- ray_casting.c ------- */
int			ray_casting(t_data *data);

/* ------- ray_casting_norm.c ------- */
void		draw_wall_slice_helper(t_data *data, int x,
				int wall_height, int tex_x);

/* ------- render.c ------- */
void		img_pix_put(t_image *img, int x, int y, int color);
int			render_frame(t_data *data);
void		precalculate_colors(t_data *data);

/* ------------------------------ sources ------------------------------ */
/* --------------- events --------------- */
/* ------- keyboard_event.c ------- */
int			handle_keypress(int keysym, t_data *data);
int			handle_keyrelease(int keysym, t_data *data);
void		update_player(t_data *data);

/* ------- mouse_event.c ------- */
int			handle_destroy(t_data *data);

/* ------- movement.c ------- */
void		move_forward(t_data *data);
void		move_backward(t_data *data);
void		move_left(t_data *data);
void		move_right(t_data *data);

/* ------------------------------ sources ------------------------------ */
/* --------------- init --------------- */
/* ------- init_data.c ------- */
int			init_data(t_data *data);

/* ------- init_main.c ------- */
int			init_all(t_data *data);

/* ------- init_map.c ------- */
void		init_map(t_data *data);

/* ------- init_mlx.c ------- */
void		init_mlx(t_data *data);
int			setup_mlx(t_data *data);
int			load_textures(t_data *data);
int			loop(t_data *data);

/* ------- init_paser.c ------- */
int			init_parser(t_data *data);

/* ------- init_player.c ------- */
void		init_player(t_data *data);
void		find_player_position(t_data *data);

/* ------- init_ray.c ------- */
void		init_ray(t_data *data);

/* ------------------------------ sources ------------------------------ */
/* ------- error.c ------- */
void		print_error(int error_code, t_data *data);

/* ------------------------------ utils ------------------------------ */
/* ------- clean_up.c ------- */
void		clean_up(t_data *data);
void		free_tab(char **map);
void		destroy_sprites(t_data *data);

/* ------- free_all.c ------- */
void		free_split(char **split);
void		free_all(t_data *data);

/* ------- free_data.c ------- */
void		free_map(t_map *map);
void		free_img(t_data *data);
void		free_parser(t_parser *parser);
void		free_data(t_data *data);

#endif