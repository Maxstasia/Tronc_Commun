/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:24:58 by mstasiak          #+#    #+#             */
/*   Updated: 2025/10/09 19:11:53 by mstasiak         ###   ########.fr       */
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

typedef struct s_map
{
	char	*texture_north;
	char	*texture_south;
	char	*texture_west;
	char	*texture_east;
	void	*img_north;
	void	*img_south;
	void	*img_west;
	void	*img_east;
	int		tex_width;
	int		tex_height;
	char	*color_floor;
	char	*color_ceiling;
	char	**map;
	char	player_direction;
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

typedef struct s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir_p;
	t_vector	fov;
}				t_player;

typedef struct s_keys
{
	int			w;
	int			s;
	int			a;
	int			d;
	int			left;
	int			right;
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
}				t_ray;

typedef struct s_texture
{
	int		bpp;
	int		l_len;
	int		endian;
}				t_texture;

typedef struct s_data
{
	t_image		*img;
	t_map		*map;
	t_parser	*parser;
	t_player	*player;
	t_ray		*ray;
	t_keys		*keys;
	t_texture	*texture;
	int			argc;
	char		**argv;
	void		*mlx_ptr;
	void		*win_ptr;
	bool		nothing_after_map;
	int			floor_color;
	int			ceiling_color;
}				t_data;

#endif