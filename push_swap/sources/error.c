/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:14:11 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/24 18:30:42 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	error_exit(t_stack *a, t_stack *b)
{
	if (a)
		free_stack(a);
	if (b)
		free_stack(b);
	ft_putstr_fd("Error\n", 2);
	exit(ERROR);
}

void	free_stack(t_stack *stack)
{
	t_node	*current;
	t_node	*next;

	if (!stack)
		return ;
	current = stack->top;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(stack);
}
