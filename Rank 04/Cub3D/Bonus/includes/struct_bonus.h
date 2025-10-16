/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:24:58 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/16 13:55:18 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_BONUS_H
# define STRUCT_BONUS_H

# include "cub3d_bonus.h"

typedef enum e_error
{
	MLX_INIT_ERROR = 1,
	WINDOW_ERROR,
	IMAGE_ERROR,
	IMAGE_ADDR_ERROR,
	USAGE_ERROR,
	MALLOC_ERROR,
	FILE_OPEN_ERROR,
	TEXTURE_ERROR,
	COLOR_ERROR,
	MAP_ERROR,
	TOO_MANY_TELEPORTERS_ERROR,
	UNKNOWN_ERROR
}				t_error;

/**
 * struct s_image - Contient les informations nécessaires pour
 * manipuler une image.
 * 
 * - @mlx_img: Pointeur vers l'image créée par la bibliothèque MiniLibX.
 * - @addr: Adresse de départ des pixels dans l'image.
 * - @bpp: Bits par pixel de l'image.
 * - @l_len: Longueur d'une ligne de l'image en octets.
 * - @endian: Ordre des octets de l'image.
 *   (0 pour little-endian, 1 pour big-endian).
 */
typedef struct s_image
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		l_len;
	int		endian;
}				t_image;

typedef struct s_anim
{
	void	**frames;
	int		frame_count;
	int		current_frame;
	int		is_animated;
}				t_anim;

typedef struct s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct s_teleporter
{
	int			numbers;
	t_vector	pos;
}				t_teleporter;

typedef struct s_map
{
	t_anim			anim_north;
	t_anim			anim_south;
	t_anim			anim_west;
	t_anim			anim_east;
	t_anim			anim_door;
	t_anim			anim_teleport;
	t_teleporter	*teleporter_3;
	t_teleporter	*teleporter_4;
	t_teleporter	*teleporter_5;
	t_teleporter	*teleporter_6;
	char			*texture_north;
	char			*texture_south;
	char			*texture_west;
	char			*texture_east;
	char			*texture_door;
	char			*texture_teleport;
	void			*img_north;
	void			*img_south;
	void			*img_west;
	void			*img_east;
	void			*img_door;
	void			*img_teleport;
	int				tex_width;
	int				tex_height;
	char			*color_floor;
	char			*color_ceiling;
	char			**map;
	char			player_direction;
}				t_map;

typedef struct s_parser
{
	int		fd;
	char	*line;
	char	*first_line;
	char	**map;
	char	**floor_split;
	char	**ceiling_split;
	int		count;
	int		len;
	int		i;
	int		j;
}				t_parser;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir_p;
	t_vector	fov;
	double		move_speed;
}				t_player;

typedef struct s_keys
{
	int			w;
	int			s;
	int			a;
	int			d;
	int			left;
	int			right;
	int			shift;
}				t_keys;

typedef struct s_ray {
	t_vector	dir;
	double		perp_dist;
	int			map_x;
	int			map_y;
	int			side;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	bool		is_door;
	bool		is_tp;
}				t_ray;

typedef struct s_texture
{
	int		bpp;
	int		l_len;
	int		endian;
}				t_texture;

typedef struct s_minimap
{
	int		map_height;
	int		map_width;
	int		size;
	int		tile_size;
	int		offset_x;
	int		offset_y;
	int		wall_color;
	int		door_color;
	int		door_open_color;
	int		teleport_color_3;
	int		teleport_color_4;
	int		teleport_color_5;
	int		teleport_color_6;
	int		floor_color;
	int		player_color;
	int		border_color;
}				t_minimap;

typedef struct s_data
{
	t_image		*img;
	t_map		*map;
	t_parser	*parser;
	t_player	*player;
	t_ray		*ray;
	t_keys		*keys;
	t_texture	*texture;
	t_minimap	*minimap;
	int			argc;
	char		**argv;
	void		*mlx_ptr;
	void		*win_ptr;
	bool		nothing_after_map;
	int			floor_color;
	int			ceiling_color;
	int			anim_counter;
	int			anim_speed;
	int			last_mouse_x;
	double		mouse_sensitivity;
}				t_data;

#endif