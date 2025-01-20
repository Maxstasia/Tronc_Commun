/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:12:39 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/20 19:13:45 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc < 2)
		return (0);
	a = parse_input(argc, argv);
	if (!a)
		return(free_stack(a), ft_printf("Error\n"), 1);
	b = init_stack();
	if (!b)
		return (free_stack(a), free_stack(b), ft_printf("Error\n"), 1);
	push_swap(a, b);
	return (free_stack(a), free_stack(b), 0);
}
