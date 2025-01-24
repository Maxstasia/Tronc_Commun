/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:13:39 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/24 18:30:55 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push_swap(t_stack *a, t_stack *b)
{
	if (a->size <= 3)
		sort_small_stack(a);
	else
		sort_large_stack(a, b);
}

void	sort_small_stack(t_stack *a)
{
	int	first;
	int	second;
	int	third;
	int	temp;

	if (a->size == 2 && a->top->value > a->top->next->value)
	{
		temp = pop(a);
		push(a, pop(a));
		push(a, temp);
	}
	else if (a->size == 3)
	{
		first = a->top->value;
		second = a->top->next->value;
		third = a->top->next->next->value;
		if (first > second && second > third)
		{
			push(a, pop(a));
			push(a, pop(a));
			push(a, pop(a));
		}
		else if (second > first && first > third)
		{
			temp = pop(a);
			push(a, pop(a));
			push(a, temp);
		}
	}
}

void	sort_large_stack(t_stack *a, t_stack *b)
{
	int	pivot;
	int	temp;

	while (a->size > 3)
	{
		pivot = a->top->value;
		if (a->top->value <= pivot)
		{
			push(b, pop(a));
		}
		else
		{
			temp = pop(a);
			push(a, temp);
		}
	}
	sort_small_stack(a);
	while (!is_empty(b))
	{
		push(a, pop(b));
	}
}
