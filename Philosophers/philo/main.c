/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:40:07 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/09 17:29:34 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

#include "philo.h"

static int	ft_check_args(int ac)
{
	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd(ERR_ARGS, 2);
		return (1);
	}
	return (0);
}

int main(int ac, char **av)
{
    t_data  data;

    if (ft_check_args(ac))
        return (1);
    if (ft_init_data(&data, ac, av))
        return (1);
    if (ft_init_philos(&data))
        return (1);
    if (ft_start_simulation(&data))
    {
        ft_cleanup(&data);
        return (1);
    }
    ft_cleanup(&data);  // Appelé après que tous les threads sont joints
    return (0);
}
