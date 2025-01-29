/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:28:48 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/29 18:05:06 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/*--------------------macro--------------------*/

# define ERROR 1

/*--------------------bibliotheques--------------------*/

# include <unistd.h>   // Pour read, write
# include <stdlib.h>   // Pour malloc, free, exit

# include "ft_printf/ft_printf.h"

/*--------------------structures--------------------*/

/**
 * struct s_node - Structure chaînon de la pile.
 * 
 * Cette structure est utilisée pour manipuler les données liés aux piles.
 * Les champs permettent de représenter :
 * - @next: Pointeur vers le chaînon suivant dans la pile.
 * - @value: La valeur entière stockée dans le chaînon.
 */
typedef struct s_node
{
	struct s_node	*next;
	int				value;
}							t_node;

/**
 * struct s_stack - Structure représentant une pile.
 * 
 * Cette structure est utilisée comme pile.
 * Les champs permettent de représenter :
 * - @top: Tableau d'entiers.
 * - @size: Taille actuelle de la pile (nb d'éléments).
 */
typedef struct s_stack
{
	t_node	*top;
	int		size;
}							t_stack;

/*--------------------fonctions--------------------*/

void	print_stack(t_stack *stack, char *name);

/*----------sources----------*/
/*-----error.c-----*/

void	error_exit(t_stack *a, t_stack *b);

void	free_stack(t_stack *stack);

/*-----ft_split.c-----*/

char	**ft_split(char const *s, char c);

void	free_split(char **strs);

/*-----function_Libft.c-----*/

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

int		ft_isdigit(const char c);

/**
 * is_valid_number - Vérifie si une chaîne représente un entier valide.
 * 
 * - @str: Chaîne à valider.
 * Return: 1 si la chaîne est un entier valide, sinon 0.
 */
int		is_valid_number(const char *str);

/**
 * ft_putstr_fd - Écrit une chaîne de caractères dans un descripteur de fichier.
 * 
 * - @str: Chaîne à écrire.
 * - @fd: Descripteur de fichier (1 pour stdout, 2 pour stderr, etc.).
 */
void	ft_putstr_fd(const char *str, int fd);

/*-----input.c-----*/

/**
 * parse_input - Analyse et valide les arguments pour créer une pile.
 * 
 * - @argc: Nombre d'arguments passés au programme.
 * - @argv: Tableau des arguments.
 * Return: Pointeur vers la pile construite ou NULL en cas d'erreur.
 */
t_stack	*parse_input(int argc, char **argv);

/*-----instructions.c-----*/

void	sa(t_stack *a);

void	sb(t_stack *b);

void	ss(t_stack *a, t_stack *b);

void	pa(t_stack *a, t_stack *b);

void	pb(t_stack *a, t_stack *b);

void	ra(t_stack *a);

void	rb(t_stack *b);

void	rr(t_stack *a, t_stack *b);

void	rra(t_stack *a);

void	rrb(t_stack *b);

void	rrr(t_stack *a, t_stack *b);

/*-----sort.c-----*/

/**
 * push_swap - Implémente l'algorithme de tri principal.
 * 
 * - @a: Pile contenant les éléments à trier.
 * - @b: Pile auxiliaire utilisée pour le tri.
 */
void	push_swap(t_stack *a, t_stack *b);

/**
 * sort_small_stack - Trie une petite pile (3 éléments maximum).
 * 
 * - @a: Pile principale.
 */
void	sort_small_stack(t_stack *a);

/**
 * sort_large_stack - Trie une pile de grande taille en utilisant
 * un tri optimisé.
 * 
 * - @a: Pile principale.
 * - @b: Pile auxiliaire.
 */
void	sort_large_stack(t_stack *a, t_stack *b);

int		find_median(t_stack *stack);

void	sort_array(int *arr, int size);

/*-----stack.c-----*/

t_stack	*init_stack(void);

t_stack	*init_swap(void);

/**
 * push - Ajoute une valeur en haut de la pile.
 * 
 * - @stack: Pile où ajouter la valeur.
 * - @value: Valeur entière à ajouter.
 */
void	push(t_stack *stack, int value);

/**
 * pop - Supprime et retourne la valeur en haut de la pile.
 * 
 * - @stack: Pile dont on souhaite retirer l'élément.
 * Return: Valeur retirée ou 0 si la pile est vide.
 */
int		pop(t_stack *stack);

/**
 * is_empty - Vérifie si une pile est vide.
 * 
 * - @stack: Pile à vérifier.
 * Return: 1 si la pile est vide, sinon 0.
 */
int		is_empty(t_stack *stack);

/*-----utils.c-----*/

/**
 * has_duplicate - Vérifie si un argument est en double.
 * 
 * - @argv: Tableau des arguments passés au programme.
 * - @index: Index actuel dans le tableau argv.
 * Return: 1 s'il y a un doublon, sinon 0.
 */
int		has_duplicate(char **argv, int index);

void	rotate(t_stack *stack);

void	reverse_rotate(t_stack *stack);

#endif
