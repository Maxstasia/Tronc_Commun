/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:24:58 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/11 14:17:17 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>

# include "Libft/libft.h"
# include "minilibx-linux/mlx.h"

# include "cub3d.h"

typedef enum e_error
{
	MLX_INIT_ERROR = 1,
	WINDOW_ERROR,
	IMAGE_ERROR,
	IMAGE_ADDR_ERROR,
	USAGE_ERROR,
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

typedef struct s_data
{
	t_image	*img;
	int		argc;
	char	**argv;
	void	*mlx_ptr;
	void	*win_ptr;
}				t_data;

typedef struct s_parsing
{
	char	*texture_north;
	char	*texture_south;
	char	*texture_west;
	char	*texture_east;
	char	*color_floor;
	char	*color_ceiling;
	char	**map;
}				t_parsing;

#endif