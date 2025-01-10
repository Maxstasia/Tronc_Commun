/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:17:59 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/10 18:05:10 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

/*----------variables globales----------*/

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800

# define MLX_ERROR 1
# define MAX_ITER 250

# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0x00FF00
# define BLUE_PIXEL 0x0000FF
# define WHITE_PIXEL 0xFFFFFF
# define BLACK_PIXEL 0x000000

/*----------bibliotheques----------*/

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

/*----------structures----------*/

/**
 * struct s_complex - Structure représentant des coordonnées complexes.
 * 
 * Cette structure est utilisée pour manipuler des nombres complexes et leurs
 * propriétés dans des calculs liés aux fractale. Les champs permettent
 * de représenter :
 * - @r: Partie réelle d'un complexe.
 * - @i: Partie imaginaire d'un complexe.
 * - @z_re: Partie réelle de la variable Z dans l'itération de Julia.
 * - @z_im: Partie imaginaire de la variable Z dans l'itération de Julia.
 * - @c_re: Partie réelle du paramètre constant C dans l'ensemble de Julia.
 * - @c_im: Partie imaginaire du paramètre constant C dans l'ensemble de Julia.
 */
typedef struct s_complex
{
	double	r;
	double	i;
	double	z_re;
	double	z_im;
	double	c_re;
	double	c_im;
}						t_complex;

/**
 * struct s_image - Contient les informations nécessaires pour
 * manipuler une image.
 * 
 * - @mlx_img: Pointeur vers l'image créée par la bibliothèque MiniLibX.
 * - @addr: Adresse de départ des pixels dans l'image.
 * - @bpp: Bits par pixel de l'image. (Bit by Pixel Picture).
 * - @l_len: Longueur d'une ligne de l'image en octets.
 * - @endian: Ordre des octets de l'image.
 * (0 pour little-endian, 1 pour big-endian).
 */
typedef struct s_image
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		l_len;
	int		endian;
}						t_image;

/**
 * struct s_rect - Définit un rectangle pour le rendu graphique.
 * 
 * - @x: Coordonnée x du coin supérieur gauche.
 * - @y: Coordonnée y du coin supérieur gauche.
 * - @width: Largeur du rectangle.
 * - @height: Hauteur du rectangle.
 * - @color: Couleur du rectangle en hexadécimal.
 */
typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}						t_rect;

/**
 * struct s_data - Contient les données principales de l'application.
 * 
 * - @mlx_ptr: Pointeur vers l'instance MiniLibX.
 * - @win_ptr: Pointeur vers la fenêtre MiniLibX.
 * - @img: Structure contenant les informations de l'image affichée.
 * - @color_palette: Palette de couleurs actuelle pour les fractales.
 * - @cur_img: Type de fractale à afficher (0 pour Mandelbrot, 1 pour Julia).
 * - @min_x: Limite gauche de la fenêtre dans le plan complexe.
 * - @max_x: Limite droite de la fenêtre dans le plan complexe.
 * - @min_y: Limite inférieure de la fenêtre dans le plan complexe.
 * - @max_y: Limite supérieure de la fenêtre dans le plan complexe.
 * - @c_re: Partie réelle du paramètre c (utilisé pour Julia).
 * - @c_im: Partie imaginaire du paramètre c (utilisé pour Julia).
 * - @time: Temps écoulé (peut être utilisé pour des animations ou des effets).
 */
typedef struct s_data
{
	t_complex	complex;
	t_image		img;
	t_rect		rect;
	void		*mlx_ptr;
	void		*win_ptr;
	int			color_palette;
	int			cur_img;
	double		min_x;
	double		max_x;
	double		min_y;
	double		max_y;
	double		c_re;
	double		c_im;
	double		time;
	int			animate;
	int			direction;
	double		speed;
}						t_data;

/*----------fonctions----------*/

/*----fractales----*/
/*--julia.c--*/

/**
 * julia - Calcule et affiche la fractale de Julia.
 * 
 * - @data: Pointeur vers la structure contenant les données de l'application.
 * - @c_re: Partie réelle du paramètre c.
 * - @c_im: Partie imaginaire du paramètre c.
 */
void	julia(t_data *data);

/**
 * julia_wrapper - Prépare les paramètres et appelle la fonction Julia.
 * 
 * - @data: Pointeur vers la structure contenant les données de l'application.
 * - @c_re: Partie réelle du paramètre c.
 * - @c_im: Partie imaginaire du paramètre c.
 */
void	julia_wrapper(t_data *data);

/*--mandelbrot.c--*/

/**
 * mandelbrot - Calcule et affiche la fractale de Mandelbrot.
 * 
 * - @data: Pointeur vers la structure contenant les données de l'application.
 */
void	mandelbrot(t_data *data);

/**
 * mandelbrot_wrapper - Prépare les paramètres et appelle la fonction Mandelbrot.
 * 
 * - @data: Pointeur vers la structure contenant les données de l'application.
 */
void	mandelbrot_wrapper(t_data *data);

/*----sources----*/
/*--colors.c--*/

/**
 * get_color - Retourne une couleur en fonction du nombre
 * d'itérations et de la palette.
 * 
 * - @iter: Nombre d'itérations effectuées.
 * - @palette: Indice de la palette de couleurs sélectionnée.
 * Return: Couleur calculée en hexadécimal.
 */
int		get_color(int iter, int palette);

/*--events.c--*/

/**
 * handle_keypress - Gère les événements liés aux touches du clavier.
 * 
 * - @keysym: Code de la touche pressée.
 * - @data: Pointeur vers la structure contenant les données de l'application.
 * Return: 0 en cas de succès.
 */
int		handle_keypress(int keysym, t_data *data);

/**
 * handle_destroy - Gère la fermeture de la fenêtre.
 * 
 * - @data: Pointeur vers la structure contenant les données de l'application.
 * Return: 0 en cas de succès.
 */
int		handle_destroy(t_data *data);

/**
 * handle_scroll - Gère le zoom avant et arrière avec la molette de la souris.
 * 
 * - @button: Bouton de la souris pressé
 * (4 pour zoom avant, 5 pour zoom arrière).
 * - @x: Position x du curseur de la souris.
 * - @y: Position y du curseur de la souris.
 * - @data: Pointeur vers la structure contenant les données de l'application.
 * Return: 0 en cas de succès.
 */
int		handle_scroll(int button, int x, int y, t_data *data);

int		update_frame(t_data *data);

void	print_command(void);

/*--screen.c--*/

/**
 * img_pix_put - Place un pixel de couleur à une position donnée dans l'image.
 * 
 * - @img: Pointeur vers la structure contenant l'image.
 * - @x: Coordonnée x du pixel.
 * - @y: Coordonnée y du pixel.
 * - @color: Couleur du pixel en hexadécimal.
 */
void	img_pix_put(t_image *img, int x, int y, int color);

/**
 * render_rect - Dessine un rectangle de couleur sur l'image.
 * 
 * - @img: Pointeur vers la structure contenant l'image.
 * - @rect: Structure définissant les propriétés du rectangle
 * (position, dimensions, couleur).
 * Return: 0 en cas de succès.
 */
int		render_rect(t_image *img, t_rect rect);

/**
 * render_background - Remplit l'image avec une couleur unie.
 * 
 * - @img: Pointeur vers la structure contenant l'image.
 * - @color: Couleur de fond en hexadécimal.
 */
void	render_background(t_image *img, int color);

/**
 * render - Affiche la fractale actuelle dans la fenêtre graphique.
 * 
 * - @data: Pointeur vers la structure contenant les données de l'application.
 * Return: 0 en cas de succès, 1 si la fenêtre n'est pas initialisée.
 */
int		render(t_data *data);

/*--utils.c--*/

/**
 * ft_atof - Convertit une chaîne de caractères en double.
 * 
 * - @str: Chaîne de caractères à convertir.
 * Return: Valeur en double correspondant à la chaîne.
 */
double	ft_atof(const char *str);

/**
 * print_usage - Affiche un message d'utilisation et quitte le programme.
 */
void	print_usage(void);

int		is_end(t_data *data);

// void	error(void);
void	clean_up(t_data *data);

#endif
