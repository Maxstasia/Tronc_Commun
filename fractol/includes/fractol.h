/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:17:59 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/24 16:45:32 by mstasiak         ###   ########.fr       */
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

// # include <fcntl.h>    // Pour open, close
// # include <unistd.h>   // Pour read, write, close
// # include <stdio.h>    // Pour perror
// # include <string.h>   // Pour strerror
# include <stdlib.h>   // Pour malloc, free, exit
# include <math.h>

# include "ft_printf/ft_printf.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"

/*--------------------structures--------------------*/

/**
 * struct s_complex - Structure représentant des coordonnées complexes.
 * 
 * Cette structure est utilisée pour manipuler des nombres complexes et leurs
 * propriétés dans des calculs liés aux fractales. Les champs permettent
 * de représenter :
 * - @z_re: Partie réelle de la variable Z dans l'itération de Julia.
 * - @z_im: Partie imaginaire de la variable Z dans l'itération de Julia.
 * - @c_re: Partie réelle du paramètre c (utilisé pour Julia).
 * - @c_im: Partie imaginaire du paramètre c (utilisé pour Julia).
 */
typedef struct s_complex
{
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
/*-----julia.c-----*/

/**
 * julia - Génère et affiche la fractale de Julia, basée sur des paramètres
 * complexes spécifiques.
 * 
 * - @data: Structure contenant les informations globales.
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
 * d'itérations et de la palette sélectionnée.
 * 
 * - @iter: Nombre d'itérations effectuées pour un point donné.
 * - @palette: Indice de la palette de couleurs utilisée.
 * Return: Couleur calculée en hexadécimal selon la palette choisie.
 */
int		get_color(int iter, int palette);

/*-----fractal_security.c-----*/

/**
 * mandelbrot_security - Vérifie les arguments nécessaires à l'affichage
 * de la fractale de Mandelbrot.
 * 
 * - @argv: Tableau contenant les arguments passés en ligne de commande.
 * - @data: Structure contenant les paramètres et les données de l'application.
 * Return: 1 si les arguments sont valides, sinon 0.
 */
int		mandelbrot_security(char **argv, t_data *data);

/**
 * julia_security - Vérifie les arguments nécessaires à l'affichage
 * de la fractale de Julia.
 * 
 * - @argv: Tableau contenant les arguments passés en ligne de commande.
 * - @data: Structure contenant les paramètres et les données de l'application.
 * Return: 1 si les arguments sont valides, sinon 0.
 */
int		julia_security(char **argv, t_data *data);

/*-----ft_atof.c-----*/

/**
 * ft_atof - Convertit une chaîne de caractères en nombre flottant.
 * 
 * - @str: Chaîne de caractères à convertir en nombre flottant.
 * Return: Le nombre flottant résultant de la conversion. La fonction gère
 * également les décimales et les signes (positif ou négatif).
 */
double	ft_atof(const char *str);

/*-----function_Libft.c-----*/

/**
 * ft_strcmp - Compare deux chaînes de caractères lexicographiquement.
 * 
 * - @s1: Première chaîne de caractères à comparer.
 * - @s2: Deuxième chaîne de caractères à comparer.
 * Return: 
 * - Un entier négatif si la première chaîne est lexicographiquement
 * inférieure à la deuxième chaîne.
 * - Zéro si les deux chaînes sont identiques.
 * - Un entier positif si la première chaîne est lexicographiquement
 * supérieure à la deuxième chaîne.
 */
int		ft_strcmp(char *s1, char *s2);

/**
 * ft_atoi - Convertit une chaîne de caractères en entier.
 * 
 * - @str: Chaîne de caractères à convertir en entier.
 * Return: L'entier résultant de la conversion. Si la chaîne
 * contient des caractères non numériques, le comportement
 * peut être indéfini, mais généralement la conversion
 * s'arrête au premier caractère non numérique.
 */
int		ft_atoi(const char *str);

/*-----init.c-----*/

/**
 * init_main - Initialise les paramètres et les données principales
 * de l'application en fonction des arguments fournis.
 * 
 * - @argv: Tableau contenant les arguments passés en ligne de commande.
 * - @data: Structure contenant les paramètres et les données de l'application.
 * Return: 0 si l'initialisation est réussie, sinon 1.
 */
int		init_main(char **argv, t_data *data);

/**
 * loop - Démarre la boucle principale de rendu de l'application.
 * 
 * - @data: Structure contenant les paramètres et les données de l'application.
 * Return: 0 si la boucle se termine correctement.
 */
int		loop(t_data *data);

/*-----keyboard_events.c-----*/

/**
 * handle_keypress - Gère les événements liés aux touches du clavier.
 * 
 * - @keysym: Code de la touche pressée (ex : flèches, touches numériques).
 * - @data: Structure contenant les paramètres et les données de l'application.
 * Return: 0 en cas de succès.
 */
int		handle_keypress(int keysym, t_data *data);

/**
 * julia_keypress - Gère les touches spécifiques pour manipuler la fractale
 * de Julia (ex : modifier les paramètres complexes).
 * 
 * - @keysym: Code de la touche pressée.
 * - @data: Structure contenant les paramètres et les données de l'application.
 */
void	julia_keypress(int keysym, t_data *data);

/*-----mouse_events.c-----*/

/**
 * handle_destroy - Gère la fermeture de la fenêtre et libère
 * les ressources utilisées par l'application.
 * 
 * - @data: Structure contenant les paramètres et les données de l'application.
 * Return: 0 en cas de succès.
 */
int		handle_destroy(t_data *data);

/**
 * handle_scroll - Gère le zoom avant et arrière avec la molette de la souris.
 * 
 * - @button: Bouton de la souris utilisé pour le zoom (4 ou 5).
 * - @data: Structure contenant les paramètres et les données de l'application.
 * Return: 0 en cas de succès.
 */
int		handle_scroll(int button, int x, int y, t_data *data);

/*-----print_function-----*/

/**
 * print_usage - Affiche un message d'aide expliquant comment utiliser
 * le programme, puis termine son exécution.
 */
int		print_usage(void);

/**
 * print_command - Affiche une liste des commandes disponibles pour manipuler
 * les fractales et l'application.
 */
void	print_command(void);

/*-----screen.c-----*/

/**
 * img_pix_put - Dessine un pixel de couleur dans l'image aux coordonnées citées.
 * 
 * - @data: Structure contenant les paramètres et les données de l'application.
 * - @x: Coordonnée x où dessiner le pixel.
 * - @y: Coordonnée y où dessiner le pixel.
 * - @color: Couleur du pixel en hexadécimal.
 */
void	img_pix_put(t_data *data, int x, int y, int color);

/**
 * render_background - Remplit l'image avec une couleur unie.
 * 
 * - @data: Structure contenant les paramètres et les données de l'application.
 * - @color: Couleur de fond utilisée.
 */
void	render_background(t_data *data, int color);

/**
 * render - Génère et affiche la fractale dans la fenêtre.
 * 
 * - @data: Structure contenant les paramètres et les données de l'application.
 * Return: 0 si la fractale est affichée correctement, 1 sinon.
 */
int		render(t_data *data);

/**
 * update_frame - Met à jour l'affichage de la fenêtre après calcul
 * ou modification des paramètres.
 * 
 * - @data: Structure contenant les paramètres et les données de l'application.
 * Return: 0 si l'affichage est mis à jour correctement.
 */
int		update_frame(t_data *data);

/*-----utils.c-----*/

/**
 * ft_str_is_numeric - Vérifie si une chaîne de caractères contient
 * uniquement des chiffres.
 * 
 * - @str: Chaîne de caractères à vérifier.
 * Return: 1 si la chaîne est numérique, sinon 0.
 */
int		ft_str_is_numeric(char *str);

/**
 * ft_str_is_float - Vérifie si une chaîne de caractères représente
 * un nombre décimal valide.
 * 
 * - @str: Chaîne de caractères à vérifier.
 * Return: 1 si la chaîne est un nombre flottant valide, sinon 0.
 */
int		ft_str_is_float(char *str);

/**
 * clean_up - Libère les ressources et nettoie les données avant de
 * fermer l'application.
 * 
 * - @data: Structure contenant les paramètres et les données de l'application.
 */
void	clean_up(t_data *data);

#endif
