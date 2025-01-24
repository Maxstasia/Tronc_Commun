/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:12:52 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/24 18:44:13 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_stack	*parse_input(int argc, char **argv)
{
	t_stack	*stack;
	int		i;
	int		num;

	stack = init_stack();
	if (!stack)
		return (NULL);
	i = 0;
	while (++i < argc)
	{
		if (!is_valid_number(argv[i]))
			return (free_stack(stack), ft_putstr_fd("Error\n", 2), NULL);
		num = ft_atoi(argv[i]);
		if (num == 0 && argv[i][0] != '0') // Vérifie les dépassements
			return (free_stack(stack), ft_putstr_fd("Error\n", 2), NULL);
		if (has_duplicate(argv, i))
			return (free_stack(stack), ft_putstr_fd("Error\n", 2), NULL);
		push(stack, num);
	}
	return (stack);
}
