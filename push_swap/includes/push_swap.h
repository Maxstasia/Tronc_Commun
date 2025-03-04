/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:28:48 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/04 15:05:58 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/*--------------------bibliotheques--------------------*/

# include <unistd.h>				// Pour read, write
# include <stdlib.h>				// Pour malloc, free, exit

# include "ft_printf/ft_printf.h"	// Pour l'affichage formaté

/*--------------------structures--------------------*/

/**
 * struct s_stack - Structure représentant une pile (stack).
 * 
 * Cette structure est utilisée pour représenter une pile chaînée.
 * - @value: Valeur stockée dans le nœud.
 * - @index: Index de l'élément dans la pile.
 * - @next: Pointeur vers l'élément suivant.
 */
typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}							t_stack;

/*--------------------fonctions--------------------*/
/*----------sources----------*/
/*-----instructions_push.c-----*/

/**
 * pa - Déplace le premier élément de la pile B vers le haut de A.
 * 
 * - @stack_a: Pointeur vers la pile A.
 * - @stack_b: Pointeur vers la pile B.
 * Return: 0 si l'opération est réussie, sinon -1.
 */
int		pa(t_stack **stack_a, t_stack **stack_b);

/**
 * pb - Déplace le premier élément de la pile A vers le haut de B.
 * 
 * - @stack_a: Pointeur vers la pile A.
 * - @stack_b: Pointeur vers la pile B.
 * Return: 0 si l'opération est réussie, sinon -1.
 */
int		pb(t_stack **stack_b, t_stack **stack_a);

/*-----instructions_reverse_rotate.c-----*/

/**
 * rra - Effectue une rotation inverse sur la pile A
 * (le dernier élément devient le premier).
 * 
 * - @stack_a: Pointeur vers la pile A.
 * Return: 0 si l'opération est réussie, sinon -1.
 */
int		rra(t_stack **stack_a);

/**
 * rrb - Effectue une rotation inverse sur la pile B.
 * 
 * - @stack_b: Pointeur vers la pile B.
 * Return: 0 si l'opération est réussie, sinon -1.
 */
int		rrb(t_stack **stack_b);

/**
 * rrr - Effectue une rotation inverse sur les piles A et B simultanément.
 * 
 * - @stack_a: Pointeur vers la pile A.
 * - @stack_b: Pointeur vers la pile B.
 * Return: 0 si l'opération est réussie, sinon -1.
 */
int		rrr(t_stack **stack_a, t_stack **stack_b);

/*-----instructions_rotate.c-----*/

/**
 * ra - Fait tourner la pile A vers le haut
 * (le premier élément devient le dernier).
 * 
 * - @stack_a: Pointeur vers la pile A.
 * Return: 0 si l'opération est réussie, sinon -1.
 */
int		ra(t_stack **stack_a);

/**
 * rb - Fait tourner la pile B vers le haut.
 * 
 * - @stack_b: Pointeur vers la pile B.
 * Return: 0 si l'opération est réussie, sinon -1.
 */
int		rb(t_stack **stack_b);

/**
 * rr - Fait tourner les piles A et B simultanément.
 * 
 * - @stack_a: Pointeur vers la pile A.
 * - @stack_b: Pointeur vers la pile B.
 * Return: 0 si l'opération est réussie, sinon -1.
 */
int		rr(t_stack **stack_a, t_stack **stack_b);

/*-----instructions_swap.c-----*/

/**
 * sa - Échange les deux premiers éléments de la pile A.
 * 
 * - @stack_a: Pointeur vers la pile A.
 * Return: 0 si l'opération est réussie, sinon -1.
 */
int		sa(t_stack **stack_a);

/**
 * sb - Échange les deux premiers éléments de la pile B.
 * 
 * - @stack_b: Pointeur vers la pile B.
 * Return: 0 si l'opération est réussie, sinon -1.
 */
int		sb(t_stack **stack_b);

/**
 * ss - Échange les deux premiers éléments des piles A et B simultanément.
 * 
 * - @stack_a: Pointeur vers la pile A.
 * - @stack_b: Pointeur vers la pile B.
 * Return: 0 si l'opération est réussie, sinon -1.
 */
int		ss(t_stack **stack_a, t_stack **stack_b);

/*-----radix.c-----*/

/**
 * radix_sort - Trie la pile en utilisant l'algorithme du tri par base
 * (radix sort).
 * 
 * - @stack_a: Pointeur vers la pile A.
 * - @stack_b: Pointeur vers la pile B (utilisée comme pile auxiliaire).
 */
void	radix_sort(t_stack **stack_a, t_stack **stack_b);

/*-----simple.c-----*/

/**
 * simple_sort - Trie une petite pile avec une méthode simple et efficace.
 * 
 * - @stack_a: Pointeur vers la pile A.
 * - @stack_b: Pointeur vers la pile B.
 */
void	simple_sort(t_stack **stack_a, t_stack **stack_b);

/*----------utils----------*/
/*-----check_args.c-----*/

/**
 * ft_check_args - Vérifie la validité des arguments passés au programme.
 * 
 * - @argc: Nombre d'arguments.
 * - @argv: Tableau des arguments.
 */
void	ft_check_args(int argc, char **argv);

/*-----error.c-----*/

/**
 * ft_error - Affiche un message d'erreur et quitte le programme.
 * 
 * - @msg: Message d'erreur à afficher.
 */
void	ft_error(char *msg);

/**
 * ft_error_with_free - Affiche un message d'erreur, libère la mémoire et quitte.
 * 
 * - @msg: Message d'erreur.
 * - @argc: Nombre d'arguments.
 * - @args: Tableau des arguments.
 * - @i: Index courant pour la libération de mémoire.
 */
void	ft_error_with_free(char *msg, int argc, char **args, int i);

/**
 * ft_free_tab - Libère un tableau de chaînes de caractères.
 * 
 * - @str: Tableau à libérer.
 * - @len: Taille du tableau.
 */
void	*ft_free_tab(char **str, int len);

/**
 * free_stack - Libère toute la mémoire d'une pile.
 * 
 * - @stack: Pointeur vers la pile.
 */
void	free_stack(t_stack **stack);

/*-----ft_split.c-----*/

/**
 * ft_split - Sépare une chaîne de caractères en un tableau de mots.
 * 
 * - @s: La chaîne à découper.
 * - @c: Le caractère délimitant les mots.
 * Return: Un tableau de chaînes de caractères ou NULL en cas d'échec.
 */
char	**ft_split(char const *s, char c);

/*-----function_Libft.c-----*/

/**
 * ft_putnbr_fd - Affiche un nombre entier sur un descripteur de fichier.
 * 
 * - @n: Le nombre entier à afficher.
 * - @fd: Le descripteur de fichier sur lequel écrire.
 */
void	ft_putnbr_fd(int n, int fd);

/**
 * ft_atoi - Convertit une chaîne de caractères en entier.
 * 
 * - @str: La chaîne de caractères à convertir.
 * Return: La valeur entière convertie.
 */
long	ft_atoi(const char *str);

/**
 * ft_isdigit - Vérifie si un caractère est un chiffre (0-9).
 * 
 * - @c: Le caractère à tester.
 * Return: 1 si c'est un chiffre, 0 sinon.
 */
int		ft_isdigit(const char c);

/*-----function_put.c-----*/

/**
 * ft_putchar_fd - Écrit un caractère sur un descripteur de fichier.
 * 
 * - @c: Le caractère à écrire.
 * - @fd: Le descripteur de fichier.
 */
void	ft_putchar_fd(char c, int fd);

/**
 * ft_putstr_fd - Affiche une chaîne de caractères sur un descripteur de fichier.
 * 
 * - @str: La chaîne à afficher.
 * - @fd: Le descripteur de fichier.
 */
void	ft_putstr_fd(const char *str, int fd);

/**
 * ft_putendl_fd - Affiche une chaîne suivie d'un retour à la ligne
 * sur un descripteur.
 * 
 * - @str: La chaîne à afficher.
 * - @fd: Le descripteur de fichier.
 */
void	ft_putendl_fd(char *str, int fd);

/*-----index.c-----*/

/**
 * index_stack - Associe un index à chaque élément de la pile.
 * 
 * - @stack: La pile à indexer.
 */
void	index_stack(t_stack **stack);

/*-----t_stack.c-----*/

/**
 * ft_lstnew - Crée un nouveau nœud pour une liste chaînée.
 * 
 * - @value: La valeur du nouveau nœud.
 * Return: Un pointeur vers le nœud créé ou NULL en cas d'échec.
 */
t_stack	*ft_lstnew(int value);

/**
 * ft_lstlast - Retourne le dernier nœud d'une liste chaînée.
 * 
 * - @head: Le premier nœud de la liste.
 * Return: Un pointeur vers le dernier nœud de la liste.
 */
t_stack	*ft_lstlast(t_stack *head);

/**
 * ft_lstadd_back - Ajoute un nœud à la fin de la liste chaînée.
 * 
 * - @stack: Pointeur vers la liste chaînée.
 * - @new_stack: Le nœud à ajouter.
 */
void	ft_lstadd_back(t_stack **stack, t_stack *new_stack);

/**
 * ft_lstsize - Retourne le nombre de nœuds dans une liste chaînée.
 * 
 * - @head: Le premier nœud de la liste.
 * Return: La taille de la liste chaînée.
 */
int		ft_lstsize(t_stack *head);

/*-----utils.c-----*/

/**
 * is_sorted - Vérifie si une pile est triée en ordre croissant.
 * 
 * - @stack: La pile à vérifier.
 * Return: 1 si la pile est triée, 0 sinon.
 */
int		is_sorted(t_stack **stack);

/**
 * get_distance - Calcule la distance d'un index par rapport au début de la pile.
 * 
 * - @stack: La pile où chercher.
 * - @index: L'index à rechercher.
 * Return: La distance de l'élément trouvé, ou -1 si l'index est absent.
 */
int		get_distance(t_stack **stack, int index);

/**
 * ft_countword - Compte le nombre de mots dans une chaîne
 * en fonction d'un séparateur.
 * 
 * - @s: La chaîne de caractères à analyser.
 * - @c: Le caractère délimitant les mots.
 * Return: Le nombre de mots trouvés.
 */
int		ft_countword(const char *s, char c);

#endif
