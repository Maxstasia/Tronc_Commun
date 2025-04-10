/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:04:44 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/10 17:03:50 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int ft_parse_args(t_data *data, int ac, char **av)
{
    data->nb_philo = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    data->must_eat = (ac == 6) ? ft_atoi(av[5]) : -1;
    if (data->nb_philo <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
        || data->time_to_sleep <= 0 || (ac == 6 && data->must_eat <= 0))
    {
        ft_putstr_fd(ERR_INPUT, 2);
        return (1);
    }
    return (0);
}

int ft_init_data(t_data *data, int ac, char **av)
{
    memset(data, 0, sizeof(t_data));
    if (ft_parse_args(data, ac, av))
        return (1);
    data->philos = malloc(sizeof(t_philo) * data->nb_philo);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
    if (!data->philos || !data->forks)
    {
        ft_putstr_fd(ERR_MEM, 2);
        free(data->philos);
        free(data->forks);
        return (1);
    }
    pthread_mutex_init(&data->print_mutex, NULL);
    pthread_mutex_init(&data->stop_mutex, NULL);
    data->start_time = ft_get_time();
    return (0);
}

int ft_init_philos(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nb_philo)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
        data->philos[i].id = i + 1;
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
        data->philos[i].last_meal = data->start_time;
        data->philos[i].meals_eaten = 0;
        data->philos[i].data = data;
        i++;
    }
    return (0);
}
