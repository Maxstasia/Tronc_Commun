/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:12:52 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/29 17:41:51 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_stack	*parse_input(int argc, char **argv)
{
	t_stack	*stack;
	char	**numbers;
	int		i;
	int		num;

	stack = init_stack();
	if (!stack)
		return (NULL);
	if (argc == 2)
		numbers = ft_split(argv[1], ' ');
	else
		numbers = argv + 1;
	i = -1;
	while (numbers[++i])
	{
		if (!is_valid_number(numbers[i]))
			return (free_stack(stack), ft_putstr_fd("Error\n", 2), exit(ERROR), NULL);
		num = ft_atoi(numbers[i]);
		if (num == 0 && numbers[i][0] != '0')
			return (free_stack(stack), ft_putstr_fd("Error\n", 2), exit(ERROR), NULL);
		if (has_duplicate(numbers, i))
			return (free_stack(stack), ft_putstr_fd("Error\n", 2), exit(ERROR), NULL);
		push(stack, num);
	}
	if (argc == 2)
		free_split(numbers);
	return (stack);
}
