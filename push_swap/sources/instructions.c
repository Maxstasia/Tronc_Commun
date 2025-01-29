/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:13:22 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/29 15:25:08 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/* Swap de la pile a */
void	sa(t_stack *a)
{
	int	temp;

	if (a && a->size > 1)
	{
		temp = a->top->value;
		a->top->value = a->top->next->value;
		a->top->next->value = temp;
	}
	ft_putstr_fd("sa\n", 1);
}

/* Swap de la pile b */
void	sb(t_stack *b)
{
	int	temp;

	if (b && b->size > 1)
	{
		temp = b->top->value;
		b->top->value = b->top->next->value;
		b->top->next->value = temp;
	}
	ft_putstr_fd("sb\n", 1);
}

/* Swap des piles a et b */
void	ss(t_stack *a, t_stack *b)
{
	sa(a);
	sb(b);
	ft_putstr_fd("ss\n", 1);
}

/* Push d'un élément de b vers a */
void	pa(t_stack *a, t_stack *b)
{
	if (b && !is_empty(b))
		push(a, pop(b));
	ft_putstr_fd("pa\n", 1);
}

/* Push d'un élément de a vers b */
void	pb(t_stack *a, t_stack *b)
{
	if (a && !is_empty(a))
		push(b, pop(a));
	ft_putstr_fd("pb\n", 1);
}

/* Rotate la pile a */
void	ra(t_stack *a)
{
	if (a && a->size > 1)
		rotate(a);
	ft_putstr_fd("ra\n", 1);
}

/* Rotate la pile b */
void	rb(t_stack *b)
{
	if (b && b->size > 1)
		rotate(b);
	ft_putstr_fd("rb\n", 1);
}

/* Rotate des piles a et b */
void	rr(t_stack *a, t_stack *b)
{
	ra(a);
	rb(b);
	ft_putstr_fd("rr\n", 1);
}

/* Reverse rotate la pile a */
void	rra(t_stack *a)
{
	if (a && a->size > 1)
		reverse_rotate(a);
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
