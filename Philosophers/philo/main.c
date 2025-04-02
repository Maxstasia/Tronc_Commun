/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:40:07 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/02 16:43:39 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static int init_data(t_data *data, int ac, char **av)
{
    data->nb_philo = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    data->must_eat = (ac == 6) ? ft_atoi(av[5]) : -1;
    data->stop = 0;

    if (data->nb_philo < 1 || data->time_to_die < 0 || data->time_to_eat < 0 || 
        data->time_to_sleep < 0 || (ac == 6 && data->must_eat < 0))
    {
        printf("Invalid arguments\n");
        return (1);
    }

    data->philos = malloc(sizeof(t_philo) * data->nb_philo);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
    if (!data->philos || !data->forks)
        return (1);

    pthread_mutex_init(&data->print_mutex, NULL);
    data->start_time = get_time();
    return (0);
}

static void init_philos(t_data *data)
{
    int i = 0;

    while (i < data->nb_philo)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        data->philos[i].id = i + 1;
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
        data->philos[i].last_meal = data->start_time;
        data->philos[i].meals_eaten = 0;
        data->philos[i].data = data;
        i++;
    }
}

int main(int ac, char **av)
{
    t_data  data;

    if (ac < 5 || ac > 6)
    {
        printf("Usage: ./philo nb_philo time_to_die time_to_eat time_to_sleep [must_eat]\n");
        return (1);
    }
    if (init_data(&data, ac, av) != 0)
        return (1);
    init_philos(&data);
    if (start_simulation(&data) != 0)
        return (cleanup(&data), 1);
    return (cleanup(&data), 0);
}
