/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:13:54 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/29 15:32:09 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	has_duplicate(char **argv, int index)
{
	int	i;

	i = 1;
	while (i < index)
	{
		if (ft_atoi(argv[i]) == ft_atoi(argv[index]))
			return (1);
		i++;
	}
	return (0);
}

void	rotate(t_stack *stack)
{
	t_node	*first;
	t_node	*last;

	if (stack->size <= 1)
		return ;
	first = stack->top;
	stack->top = first->next;
	last = stack->top;
	while (last->next)
		last = last->next;
	last->next = first;
	first->next = NULL;
}

void	reverse_rotate(t_stack *stack)
{
	t_node	*second_last;
	t_node	*last;

	if (!stack || stack->size <= 1 || !stack->top || !stack->top->next)
		return ;
	second_last = stack->top;
	while (second_last->next && second_last->next->next)
		second_last = second_last->next;
	last = second_last->next;
	if (!last)
		return ;
	second_last->next = NULL;
	last->next = stack->top;
	stack->top = last;
}
