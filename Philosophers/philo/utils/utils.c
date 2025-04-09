/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:49:37 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/09 17:29:03 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void ft_print_state(t_philo *philo, char *state)
{
    long    timestamp;

    if (!philo || !philo->data)
    {
        write(2, "Error: Invalid philo or data pointer\n", 37);
        return;
    }
    pthread_mutex_lock(&philo->data->print_mutex);
    if (!philo->data->stop)
    {
        timestamp = ft_get_time() - philo->data->start_time;
        printf("%ld %d %s\n", timestamp, philo->id, state);
    }
    pthread_mutex_unlock(&philo->data->print_mutex);
}

int	ft_atoi(const char *str)
{
	int	res;

	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
}
