/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:17:59 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/01 17:48:07 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
}	t_data;

/*--bibliotheques--*/

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

# include "ft_printf.h"
# include "libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"

/*--fonctions--*/

#endif
