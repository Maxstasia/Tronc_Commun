/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:13:22 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/20 19:13:43 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/push_swap.h"

void	sa(t_stack *a)
{
	int	temp;

	if (a && a->size > 1)
	{
		temp = a->top->value;
		a->top->value = a->top->next->value;
		a->top->next->value = temp;
	}
}

void	sb(t_stack *b)
{
	int	temp;

	if (b && b->size > 1)
	{
		temp = b->top->value;
		b->top->value = b->top->next->value;
		b->top->next->value = temp;
	}
}

void	pa(t_stack *a, t_stack *b)
{
	if (b && !is_empty(b))
		push(a, pop(b));	
}

void	pb(t_stack *a, t_stack *b)
{
	if (a && !is_empty(a))
		push(b, pop(a));	
}

