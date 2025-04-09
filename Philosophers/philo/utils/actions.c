/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:10:36 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/09 17:54:58 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void ft_eat(t_philo *philo)
{
    pthread_mutex_t *first;
    pthread_mutex_t *second;

    if (philo->data->nb_philo == 1)  // Cas spécial : 1 philosophe
    {
        pthread_mutex_lock(philo->left_fork);
        ft_print_state(philo, "has taken a fork");
        usleep(philo->data->time_to_die * 1000);  // Attend time_to_die
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    // Ordre strict pour plusieurs philosophes
    if (philo->left_fork < philo->right_fork)
    {
        first = philo->left_fork;
        second = philo->right_fork;
    }
    else
    {
        first = philo->right_fork;
        second = philo->left_fork;
    }
    pthread_mutex_lock(first);
    ft_print_state(philo, "has taken a fork");
    pthread_mutex_lock(&philo->data->stop_mutex);
    if (philo->data->stop)  // Vérifie si mort pendant l'attente
    {
        pthread_mutex_unlock(first);
        pthread_mutex_unlock(&philo->data->stop_mutex);
        return;
    }
    pthread_mutex_unlock(&philo->data->stop_mutex);
    pthread_mutex_lock(second);
    ft_print_state(philo, "has taken a fork");
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal = ft_get_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->meal_mutex);
    ft_print_state(philo, "is eating");
    usleep(philo->data->time_to_eat * 1000);
    pthread_mutex_unlock(second);
    pthread_mutex_unlock(first);
}

void *ft_philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        usleep(1000);
    while (1)
    {
        pthread_mutex_lock(&philo->data->stop_mutex);
        if (philo->data->stop)
        {
            pthread_mutex_unlock(&philo->data->stop_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->stop_mutex);
        ft_eat(philo);
        if (philo->data->nb_philo == 1)  // Sortie pour 1 philosophe
            break;
        if (philo->data->must_eat > 0 && philo->meals_eaten >= philo->data->must_eat)
            break;
        ft_print_state(philo, "is sleeping");
        usleep(philo->data->time_to_sleep * 1000);
        ft_print_state(philo, "is thinking");
    }
    return (NULL);
}

static int ft_check_death(t_data *data, int i)
{
    long last_meal;

    pthread_mutex_lock(&data->philos[i].meal_mutex);
    last_meal = data->philos[i].last_meal;
    pthread_mutex_unlock(&data->philos[i].meal_mutex);
    if (ft_get_time() - last_meal > data->time_to_die)
    {
        pthread_mutex_lock(&data->print_mutex);
        printf("%ld %d died\n", ft_get_time() - data->start_time, data->philos[i].id);
        pthread_mutex_lock(&data->stop_mutex);
        data->stop = 1;
        pthread_mutex_unlock(&data->stop_mutex);
        pthread_mutex_unlock(&data->print_mutex);
        return (1);
    }
    return (0);
}

void *ft_monitor(void *arg)
{
    t_data  *data;
    int     i;
    int     j;

    data = (t_data *)arg;
    while (1)
    {
        pthread_mutex_lock(&data->stop_mutex);
        if (data->stop)
        {
            pthread_mutex_unlock(&data->stop_mutex);
            break;
        }
        pthread_mutex_unlock(&data->stop_mutex);
        i = 0;
        while (i < data->nb_philo)
        {
            if (ft_check_death(data, i))
                return (NULL);
            if (data->must_eat > 0)
            {
                j = 0;
                while (j < data->nb_philo)
                {
                    pthread_mutex_lock(&data->philos[j].meal_mutex);
                    if (data->philos[j].meals_eaten < data->must_eat)
                    {
                        pthread_mutex_unlock(&data->philos[j].meal_mutex);
                        break;
                    }
                    pthread_mutex_unlock(&data->philos[j].meal_mutex);
                    j++;
                }
                if (j == data->nb_philo)
                {
                    pthread_mutex_lock(&data->stop_mutex);
                    data->stop = 1;
                    pthread_mutex_unlock(&data->stop_mutex);
                }
            }
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}

int ft_start_simulation(t_data *data)
{
    pthread_t   monitor_thread;
    int         i;

    i = 0;
    while (i < data->nb_philo)
    {
        if (pthread_create(&data->philos[i].thread, NULL, ft_philo_routine, &data->philos[i]))
        {
            ft_putstr_fd(ERR_THREAD, 2);
            return (1);
        }
        i++;
    }
    if (pthread_create(&monitor_thread, NULL, ft_monitor, data))
    {
        ft_putstr_fd(ERR_THREAD, 2);
        return (1);
    }
    i = 0;
    while (i < data->nb_philo)
        pthread_join(data->philos[i++].thread, NULL);
    pthread_join(monitor_thread, NULL);
    return (0);
}
