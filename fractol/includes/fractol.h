/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:17:59 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/15 17:35:00 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

/*--------------------macro--------------------*/

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800

# define MLX_ERROR 1
# define MAX_ITER 250
# define MOVE_STEP 0.1

# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0x00FF00
# define BLUE_PIXEL 0x0000FF
# define WHITE_PIXEL 0xFFFFFF
# define BLACK_PIXEL 0x000000

/*--------------------bibliotheques--------------------*/

# include <fcntl.h>    // Pour open, close
# include <unistd.h>   // Pour read, write, close
# include <stdlib.h>   // Pour malloc, free, exit
# include <stdio.h>    // Pour perror
# include <string.h>   // Pour strerror
# include <math.h>

# include "ft_printf.h"
# include "libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"

/*--------------------structures--------------------*/

/**
 * struct s_complex - Structure représentant des coordonnées complexes.
 * 
 * Cette structure est utilisée pour manipuler des nombres complexes et leurs
 * propriétés dans des calculs liés aux fractales. Les champs permettent
 * de représenter :
 * - @r: Partie réelle d'un complexe.
 * - @i: Partie imaginaire d'un complexe.
 * - @z_re: Partie réelle de la variable Z dans l'itération de Julia.
 * - @z_im: Partie imaginaire de la variable Z dans l'itération de Julia.
 * - @c_re: Partie réelle du paramètre c (utilisé pour Julia).
 * - @c_im: Partie imaginaire du paramètre c (utilisé pour Julia).
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
 * struct s_move - Représente les mouvements et les animations.
 * 
 * - @range_x: Plage de mouvement sur l'axe x.
 * - @range_y: Plage de mouvement sur l'axe y.
 * - @animate: Indicateur d'activation de l'animation.
 * - @direction: Direction du mouvement.
 * - @speed: Vitesse du mouvement.
 */
typedef struct s_move
{
	double		range_x;
	double		range_y;
	int			animate;
	int			direction;
	double		speed;
}						t_move;

/**
 * struct s_data - Contient les données principales de l'application.
 * 
 * - @mlx_ptr: Pointeur vers l'instance MiniLibX.
 * - @win_ptr: Pointeur vers la fenêtre MiniLibX.
 * - @img: Structure contenant les informations de l'image affichée.
 * - @color_palette: Palette de couleurs actuelle pour les fractales.
 * - @cur_img: Type de fractale à afficher
 *   (0 pour Mandelbrot, 1 pour Julia, 2 pour Burning Ship).
 * - @min_x: Limite gauche de la fenêtre dans le plan complexe.
 * - @max_x: Limite droite de la fenêtre dans le plan complexe.
 * - @min_y: Limite inférieure de la fenêtre dans le plan complexe.
 * - @max_y: Limite supérieure de la fenêtre dans le plan complexe.
 */
typedef struct s_data
{
	t_complex	c;
	t_image		img;
	t_rect		rect;
	t_move		move;
	void		*mlx_ptr;
	void		*win_ptr;
	int			color_palette;
	int			cur_img;
	double		min_x;
	double		max_x;
	double		min_y;
	double		max_y;
}						t_data;

/*--------------------fonctions--------------------*/

/*----------fractales----------*/
/*-----burning_ship.c-----*/

/**
 * burning_ship - Cette fonction génère et affiche la fractale de Burning Ship.
 * Elle calcule chaque pixel en fonction de ses coordonnées (x, y) et met à jour
 * l'image en conséquence.
 * 
 * - @data: Structure contenant toutes les informations nécessaires
 * (coordonnées, couleur, etc.).
 */
void	burning_ship(t_data *data);

/**
 * burning_ship_calcul - Effectue les calculs pour déterminer le nombre
 * d'itérations pour un point donné dans la fractale de Burning Ship.
 * 
 * - @data: Structure contenant les coordonnées et les limites du plan.
 * - @x: Coordonnée horizontale du pixel.
 * - @y: Coordonnée verticale du pixel.
 * Return: Nombre d'itérations avant que le point diverge (ou atteigne MAX_ITER).
 */
int		burning_ship_calcul(t_data *data, int x, int y);

/**
 * burning_ship_wrapper - Prépare les paramètres nécessaires et appelle la
 * fonction principale de calcul et d'affichage de la fractale de Burning Ship.
 * 
 * - @data: Structure contenant les données globales de l'application.
 */
void	burning_ship_wrapper(t_data *data);

/*-----julia.c-----*/

/**
 * julia - Génère et affiche la fractale de Julia, basée sur des paramètres
 * complexes spécifiques.
 * 
 * - @data: Structure contenant les informations globales.
 * - @c_re: Partie réelle du paramètre complexe.
 * - @c_im: Partie imaginaire du paramètre complexe.
 */
void	julia(t_data *data);

/**
 * julia_calcul - Calcule le comportement d'un point donné dans la fractale
 * de Julia, en fonction de ses coordonnées et des paramètres complexes.
 * 
 * - @data: Données nécessaires pour les calculs.
 * - @x: Coordonnée horizontale du pixel.
 * - @y: Coordonnée verticale du pixel.
 * Return: Nombre d'itérations avant divergence ou MAX_ITER.
 */
int		julia_calcul(t_data *data, int x, int y);

/**
 * julia_wrapper - Prépare les données et appelle la fonction principale
 * pour afficher la fractale de Julia.
 * 
 * - @data: Structure contenant les informations globales.
 */
void	julia_wrapper(t_data *data);

/*-----mandelbrot.c-----*/

/**
 * mandelbrot - Génère et affiche la fractale de Mandelbrot.
 * 
 * - @data: Structure contenant toutes les informations nécessaires.
 */
void	mandelbrot(t_data *data);

/**
 * mandelbrot_calcul - Calcule le comportement d'un point donné dans la fractale
 * de Mandelbrot, en déterminant s'il appartient à l'ensemble.
 * 
 * - @data: Données pour les calculs.
 * - @x: Coordonnée horizontale du pixel.
 * - @y: Coordonnée verticale du pixel.
 * Return: Nombre d'itérations avant divergence ou MAX_ITER.
 */
int		mandelbrot_calcul(t_data *data, int x, int y);

/**
 * mandelbrot_wrapper - Prépare les données nécessaires et lance la génération
 * de la fractale de Mandelbrot.
 * 
 * - @data: Structure contenant les informations globales.
 */
void	mandelbrot_wrapper(t_data *data);

/*----------sources----------*/
/*-----colors.c-----*/

/**
 * get_color - Retourne une couleur en fonction du nombre
 * d'itérations et de la palette.
 * 
 * - @iter: Nombre d'itérations effectuées.
 * - @palette: Indice de la palette de couleurs sélectionnée.
 * Return: Couleur calculée en hexadécimal.
 */
int		get_color(int iter, int palette);

/*-----fractal_security.c-----*/

int		mandelbrot_security(char **argv, t_data *data);

int		julia_security(char **argv, t_data *data);

int		burning_ship_security(char **argv, t_data *data);

/*-----init.c-----*/

int		init_main(char **argv, t_data *data);

int		loop(t_data *data);

/*-----keyboard_events.c-----*/

/**
 * handle_keypress - Gère les événements liés aux touches du clavier.
 * 
 * - @keysym: Code de la touche pressée.
 * - @data: Pointeur vers la structure contenant les données de l'application.
 * Return: 0 en cas de succès.
 */
int		handle_keypress(int keysym, t_data *data);

void	julia_keypress(int keysym, t_data *data);

void	harrow_x_keypress(int keysym, t_data *data);

void	harrow_y_keypress(int keysym, t_data *data);

/*-----mouse_events.c-----*/

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

/*-----print_function-----*/

/**
 * print_usage - Affiche un message d'utilisation et quitte le programme.
 */
void	print_usage(void);

void	print_command(void);

/*-----screen.c-----*/

/**
 * img_pix_put - Place un pixel de couleur à une position donnée dans l'image.
 * 
 * - @img: Pointeur vers la structure contenant l'image.
 * - @x: Coordonnée x du pixel.
 * - @y: Coordonnée y du pixel.
 * - @color: Couleur du pixel en hexadécimal.
 */
void	img_pix_put(t_image *img, int x, int y, int color);

int		update_frame(t_data *data);

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

/*-----utils.c-----*/

int		ft_str_is_numeric(char *str);

int		ft_str_is_float(char *str);

void	clean_up(t_data *data);

#endif
