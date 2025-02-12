/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_stack.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:25:24 by mstasiak          #+#    #+#             */
/*   Updated: 2025/02/12 15:51:58 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

// Creates new node and returns the pointer of it
t_stack	*ft_lstnew(int value)
{
	t_stack	*new;

	new = (t_stack *) malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->value = value;
	new->index = -1;
	new->next = NULL;
	return (new);
}

// Adds the specified node to a stack (list) making it the head
void	ft_lstadd_front(t_stack **stack, t_stack *new_stack)
{
	new_stack->next = *stack;
	*stack = new_stack;
}

// Returns the last node of a list 
t_stack	*ft_lstlast(t_stack *head)
{
	t_stack	*tmp;

	tmp = head;
	while (tmp->next)
	{
		tmp = tmp->next;
		if (tmp->next == NULL)
			return (tmp);
	}
	return (tmp);
}

// Adds the specified node to a stack (list) making it the last node
void	ft_lstadd_back(t_stack **stack, t_stack *new_stack)
{
	t_stack	*n;

	if (*stack)
	{
		n = ft_lstlast(*stack);
		n->next = new_stack;
		new_stack->next = NULL;
	}
	else
	{
		*stack = new_stack;
		(*stack)->next = NULL;
	}
}

// Returns the size of the Linked List
int	ft_lstsize(t_stack *head)
{
	size_t	i;
	t_stack	*tmp;

	tmp = head;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
