/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:13:22 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/30 13:30:44 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/**
 * sa - Échange les deux premiers éléments de la pile a.
 * @a: Pile A.
 */
void	sa(t_stack *a)
{
	t_node	*first;
	t_node	*second;

	if (!a || a->size < 2)
		return;
	first = a->top;
	second = first->next;
	first->next = second->next;
	second->next = first;
	a->top = second;
	ft_putstr_fd("sa\n", 1);
}

/**
 * sb - Échange les deux premiers éléments de la pile b.
 * @b: Pile B.
 */
void	sb(t_stack *b)
{
	sa(b);
	ft_putstr_fd("sb\n", 1);
}

/* Swap des piles a et b */
void	ss(t_stack *a, t_stack *b)
{
	sa(a);
	sb(b);
	ft_putstr_fd("ss\n", 1);
}

/**
 * pa - Déplace le premier élément de b vers le haut de a.
 * @a: Pile A.
 * @b: Pile B.
 */
void	pa(t_stack *a, t_stack *b)
{
	t_node	*tmp;

	if (!b || !b->top)
		return;
	tmp = b->top;
	b->top = tmp->next;
	tmp->next = a->top;
	a->top = tmp;
	a->size++;
	b->size--;
	ft_putstr_fd("pa\n", 1);
}

/**
 * pb - Déplace le premier élément de a vers le haut de b.
 * @a: Pile A.
 * @b: Pile B.
 */
void	pb(t_stack *a, t_stack *b)
{
	t_node	*tmp;

	if (!a || !a->top)
		return;
	tmp = a->top;
	a->top = tmp->next;
	tmp->next = b->top;
	b->top = tmp;
	a->size--;
	b->size++;
	ft_putstr_fd("pb\n", 1);
}

/**
 * ra - Rotation de A vers le haut.
 * @a: Pile A.
 */
void	ra(t_stack *a)
{
	t_node	*tmp;
	t_node	*last;

	if (!a || a->size < 2)
		return;
	tmp = a->top;
	a->top = tmp->next;
	tmp->next = NULL;
	last = a->top;
	while (last->next)
		last = last->next;
	last->next = tmp;
	ft_putstr_fd("ra\n", 1);
}

/**
 * rb - Rotation de B vers le haut.
 * @b: Pile B.
 */
void	rb(t_stack *b)
{
	ra(b);
	ft_putstr_fd("rb\n", 1);
}

/* Rotate des piles a et b */
void	rr(t_stack *a, t_stack *b)
{
	ra(a);
	rb(b);
	ft_putstr_fd("rr\n", 1);
}

/**
 * rra - Rotation inverse de A.
 * @a: Pile A.
 */
void	rra(t_stack *a)
{
	t_node	*prev;
	t_node	*last;

	if (!a || a->size < 2)
		return;
	prev = NULL;
	last = a->top;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = a->top;
	a->top = last;
	ft_putstr_fd("rra\n", 1);
}

/* Reverse rotate la pile b */
void	rrb(t_stack *b)
{
	if (b && b->size > 1)
		reverse_rotate(b);
	ft_putstr_fd("rrb\n", 1);
}

/* Reverse rotate des piles a et b */
void	rrr(t_stack *a, t_stack *b)
{
	rra(a);
	rrb(b);
	ft_putstr_fd("rrr\n", 1);
}
