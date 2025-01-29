/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:12:39 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/29 17:51:45 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

void	print_stack(t_stack *stack, char *name)
{
	t_node	*tmp = stack->top;
	ft_printf("Stack %s:", name);
	while (tmp)
	{
		ft_printf(" %d", tmp->value);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc < 2)
		return (0);
	a = parse_input(argc, argv);
	if (!a)
		return (free_stack(a), ft_putstr_fd("Error\n", 2), 1);
	print_stack(a, "A avant tri");
	b = init_stack();
	if (!b)
		return (error_exit(a, b), 1);
	push_swap(a, b);
	print_stack(a, "A après tri");
	return (free_stack(a), free_stack(b), 0);
}
