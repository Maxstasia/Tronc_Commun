/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:13:04 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/20 18:56:27 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/push_swap.h"

t_stack	*init_swap(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->top = NULL;
	stack->size = 0;
	return (stack);
}

void	push(t_stack *stack, int value)
{
	t_node	*new_node;
	
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node->value = value;
	new_node->next = stack->top;
	stack->top = new_node;
	stack->size ++;
}

int	pop(t_stack *stack)
{
	t_node	*temp;
	int		value;

	if (!stack || stack->size == 0)
		return (0);
	temp = stack->top;
	value = temp->value;
	stack->top = temp->next;
	stack->size --;
	return (free(temp), value);
}

int	is_empty(t_stack *stack)
{
	return (stack->size == 0);
}
