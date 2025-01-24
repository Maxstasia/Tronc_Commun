/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:13:39 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/22 16:17:56 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/push_swap.h"

void push_swap(t_stack *a, t_stack *b)
{
	if (a->size <= 3)
		sort_small_stack(a);
	else
		sort_large_stack(a, b);
}

void	sort_small_stack(t_stack *a)
{
	
}

void	sort_large_stack(t_stack *a, t_stack *b)
{
	
}
