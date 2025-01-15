/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:43:46 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/15 16:10:05 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	print_usage(void)
{
	ft_printf("Usage: ./fractol <fractal> [options]\n");
	ft_printf("Available fractals:\n");
	ft_printf("- mandelbrot [palette: 0-9]\n");
	ft_printf("- julia {Re} {Im} [palette: 0-9]\n");
	ft_printf("- burning_ship [palette: 0-9]\n");
	exit(MLX_ERROR);
}

void	print_command(void)
{
	ft_printf("Command :\n");
	ft_printf("	For All :\n");
	ft_printf("\n");
	ft_printf("	- Button 5 (mouse scroll) : zoom;\n");
	ft_printf("	- Button 4 (mouse scroll) : unzoom;\n");
	ft_printf("	- Space, Enter and Return : change color;\n");
	ft_printf("	- Arrow keys : move the view;\n");
	ft_printf("	- Esc, Backspace and Delete: quit;\n");
	ft_printf("\n");
	ft_printf("	For Julia :\n");
	ft_printf("	- Keybord 'e' or 'q': change value/parameter;\n");
	ft_printf("	- Keybord 'a' : change value/parameter automatically;\n");
}
