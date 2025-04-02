/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:49:37 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/02 16:37:10 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000); // Temps en millisecondes
}

void print_state(t_philo *philo, char *state)
{
    long timestamp;

    pthread_mutex_lock(&philo->data->print_mutex);
    if (philo->data->stop == 0) // Vérifier si la simulation continue
    {
        timestamp = get_time() - philo->data->start_time;
        printf("%ld %d %s\n", timestamp, philo->id, state);
    }
    pthread_mutex_unlock(&philo->data->print_mutex);
}

int ft_atoi(const char *str)
{
    int res;

	res = 0;
    while (*str >= '0' && *str <= '9')
    {
        res = res * 10 + (*str - '0');
        str++;
    }
    return (res);
}
