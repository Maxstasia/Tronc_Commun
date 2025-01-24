/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:13:54 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/24 18:30:49 by mstasiak         ###   ########.fr       */
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
