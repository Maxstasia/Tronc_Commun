/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:28:48 by mstasiak          #+#    #+#             */
/*   Updated: 2025/02/14 14:56:40 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/*--------------------bibliotheques--------------------*/

# include <unistd.h>   // Pour read, write
# include <stdlib.h>   // Pour malloc, free, exit

# include "ft_printf/ft_printf.h"

/*--------------------structures--------------------*/

/**
 * struct s_stack - Structure représentant une pile.
 * 
 * Cette structure est utilisée comme pile.
 * Les champs permettent de représenter :
 * - @value:	La valeur entière stockée dans le chaînon.
 * - @index:	Index actuelle de la pile.
 * - @next:		Pointeur vers le chaînon suivant dans la pile.
 */
typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}							t_stack;

/*--------------------fonctions--------------------*/
/*-----main.c-----*/

/*----------sources----------*/
/*-----instructions.c-----*/

// Util functions
t_stack	*ft_lstnew(int value);
t_stack	*ft_lstlast(t_stack *head);
void	ft_lstadd_front(t_stack **stack, t_stack *new_stack);
void	ft_lstadd_back(t_stack **stack, t_stack *new_stack);
int		ft_lstsize(t_stack *head);

void	ft_error(char *msg);
void	ft_check_args(int argc, char **argv);
int		is_sorted(t_stack **stack);
int		get_distance(t_stack **stack, int index);
void	make_top(t_stack **stack, int distance);
void	free_stack(t_stack **stack);
void	*ft_free_tab(char **str, int len);
void	ft_error_with_free(char *msg, int argc, char **args, int i);

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(const char *str, int fd);
void	ft_putendl_fd(char *str, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
int		ft_isdigit(const char c);
int		ft_countword(const char *s, char c);

// Algorithm utils
void	radix_sort(t_stack **stack_a, t_stack **stack_b);
void	simple_sort(t_stack **stack_a, t_stack **stack_b);
void	index_stack(t_stack **stack);
void	sort_5(t_stack **stack_a, t_stack **stack_b);

/**
 * sa - Échange les deux premiers éléments de la pile a.
 * @stack_a: Pile A.
 */
int		sa(t_stack **stack_a);

/**
 * sb - Échange les deux premiers éléments de la pile b.
 * @stack_b: Pile B.
 */
int		sb(t_stack **stack_b);

/**
 * Swap des piles a et b.
 * @stack_a: Pile A.
 * @stack_b: Pile B.
 */
int		ss(t_stack **stack_a, t_stack **stack_b);

/**
 * pa - Déplace le premier élément de b vers le haut de a.
 * @stack_a: Pile A.
 * @stack_b: Pile B.
 */
int		pa(t_stack **stack_a, t_stack **stack_b);

/**
 * pb - Déplace le premier élément de a vers le haut de b.
 * @a: Pile A.
 * @b: Pile B.
 */
int		pb(t_stack **stack_b, t_stack **stack_a);

/**
 * ra - Rotation de A vers le haut.
 * @a: Pile A.
 */
int		ra(t_stack **stack_a);

/**
 * rb - Rotation de B vers le haut.
 * @b: Pile B.
 */
int		rb(t_stack **stack_b);

/* Rotate des piles a et b */
int		rr(t_stack **stack_a, t_stack **stack_b);

/**
 * rra - Rotation inverse de A.
 * @a: Pile A.
 */
int		rra(t_stack **stack_a);

/**
 * rrb - Rotation inverse de B.
 * @b: Pile B.
 */
int		rrb(t_stack **stack_b);

/* Reverse rotate des piles a et b */
int		rrr(t_stack **stack_a, t_stack **stack_b);

#endif
