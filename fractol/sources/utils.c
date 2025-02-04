/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:39:20 by mstasiak          #+#    #+#             */
/*   Updated: 2025/02/04 14:30:13 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	ft_str_is_numeric(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_str_is_float(char *str)
{
	int	i;
	int	has_dot;

	if (!str || !*str)
		return (0);
	i = 0;
	has_dot = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (has_dot)
				return (0);
			has_dot = 1;
		}
		else if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	clean_up(t_data *data)
{
	print_usage();
	if (data != NULL)
	{
		if (data->img.mlx_img && data->mlx_ptr)
			mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		if (data->win_ptr && data->mlx_ptr)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		if (data->mlx_ptr)
		{
			mlx_destroy_display(data->mlx_ptr);
			data->win_ptr = NULL;
			free(data->mlx_ptr);
		}
	}
	return ;
}
