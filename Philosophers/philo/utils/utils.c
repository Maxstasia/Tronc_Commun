/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:49:37 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/10 16:16:43 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long ft_get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void ft_print_state(t_philo *philo, char *state)
{
    long    timestamp;
    char    *color;

    if (!philo || !philo->data)
    {
        ft_putstr_fd("Error: Invalid philo or data pointer\n", 2);
        return;
    }
    // Sélection de la couleur en fonction de l'état
    if (strcmp(state, "is eating") == 0)
        color = EATING;
    else if (strcmp(state, "is sleeping") == 0)
        color = SLEEPING;
    else if (strcmp(state, "is thinking") == 0)
        color = THINKING;
    else if (strcmp(state, "has taken a fork") == 0)
        color = FORK;
    else
        color = RESET;
    pthread_mutex_lock(&philo->data->print_mutex);
    if (!philo->data->stop || strcmp(state, "died") == 0)
    {
        timestamp = ft_get_time() - philo->data->start_time;
        printf("%s%ld %d %s%s\n", color, timestamp, philo->id, state, RESET);
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

void ft_putstr_fd(char *s, int fd)
{
    while (*s)
        write(fd, s++, 1);
}
