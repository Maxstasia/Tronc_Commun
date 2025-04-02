/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:48:56 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/02 16:46:43 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 == 0) // Éviter les deadlocks : philos pairs attendent un peu
        usleep(1000);
    while (philo->data->stop == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        print_state(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_state(philo, "has taken a fork");

        philo->last_meal = get_time();
        print_state(philo, "is eating");
        usleep(philo->data->time_to_eat * 1000);
        philo->meals_eaten++;

        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        if (philo->data->must_eat > 0 && philo->meals_eaten >= philo->data->must_eat)
            break;

        print_state(philo, "is sleeping");
        usleep(philo->data->time_to_sleep * 1000);

        print_state(philo, "is thinking");
    }
    return (NULL);
}

void *monitor(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    while (data->stop == 0)
    {
        i = 0;
        while (i < data->nb_philo)
        {
            if (get_time() - data->philos[i].last_meal > data->time_to_die)
            {
                pthread_mutex_lock(&data->print_mutex);
                printf("%ld %d died\n", get_time() - data->start_time, data->philos[i].id);
                data->stop = 1;
                pthread_mutex_unlock(&data->print_mutex);
                return (NULL);
            }
            if (data->must_eat > 0)
            {
                int all_ate = 1;
                for (int j = 0; j < data->nb_philo; j++)
                {
                    if (data->philos[j].meals_eaten < data->must_eat)
                        all_ate = 0;
                }
                if (all_ate)
                {
                    data->stop = 1;
                    return (NULL);
                }
            }
            i++;
        }
        usleep(1000); // Vérification toutes les 1ms
    }
    return (NULL);
}

int start_simulation(t_data *data)
{
    pthread_t monitor_thread;
    int i = 0;

    while (i < data->nb_philo)
    {
        if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]) != 0)
            return (1);
        i++;
    }
    if (pthread_create(&monitor_thread, NULL, monitor, data) != 0)
        return (1);

    i = 0;
    while (i < data->nb_philo)
        pthread_join(data->philos[i++].thread, NULL);
    pthread_join(monitor_thread, NULL);
    return (0);
}
