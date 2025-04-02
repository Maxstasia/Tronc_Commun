/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:48:45 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/02 16:41:04 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void cleanup(t_data *data)
{
    int i = 0;

    while (i < data->nb_philo)
        pthread_mutex_destroy(&data->forks[i++]);
    pthread_mutex_destroy(&data->print_mutex);
    free(data->philos);
    free(data->forks);
}
