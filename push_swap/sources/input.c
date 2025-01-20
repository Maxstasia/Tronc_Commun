/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:12:52 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/20 19:13:44 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/push_swap.h"

t_stack	*parse_input(int argc, char **argv)
{
	t_stack	*stack;
	int		i;

	stack = init_stack();
	if (!stack)
		return (NULL);
	i = 0;
	while (i ++, i < argc)
	{
		if (!is_valid_number(argv[i]) || has_duplicate(argv, i))
			return (NULL);
		push(stack, ft_atoi(argv[i]));
	}
	return (stack);
}
