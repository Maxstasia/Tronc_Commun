/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:06:09 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/15 16:11:27 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * Routine de repas et de sommeil d'un philosophe.
 * 
 * Lorsqu'un philosophe est prêt à manger, il attend que
 * les mutex des fourchettes soient déverrouillés avant de les verrouiller.
 * Ensuite, il mange pendant un certain temps. Le moment du dernier repas
 * est enregistré au début du repas, conformément aux exigences du sujet.
 * 
 * @param philo Le philosophe qui effectue la routine.
 */
static void	eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	write_status(philo, FALSE, got_fork_1);
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[1]]);
	write_status(philo, FALSE, got_fork_2);
	write_status(philo, FALSE, eating);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_time_lock);
	philo_sleep(philo->table, philo->table->time_to_eat);
	if (has_simulation_stopped(philo->table) == FALSE)
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->times_eat += 1;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	write_status(philo, FALSE, sleeping);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	philo_sleep(philo->table, philo->table->time_to_sleep);
}

/**
 * Routine de réflexion d'un philosophe.
 * 
 * Une fois que le philosophe a fini de dormir, il réfléchit pendant un certain
 * temps avant de recommencer à manger. Le temps de réflexion est calculé en
 * fonction du temps écoulé depuis le dernier repas, du temps pour manger et du
 * temps avant de mourir, afin de déterminer quand le philosophe aura de nouveau
 * faim. Cela permet d'étaler les routines de repas pour éviter qu'une fourchette
 * ne soit monopolisée par un philosophe au détriment des autres.
 * 
 * @param philo Le philosophe qui effectue la routine.
 * @param silent Indique si l'état de réflexion doit être affiché ou non.
 */
static void	think_routine(t_philo *philo, BOOL silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_to_think = (philo->table->time_to_die
			- (get_time_in_ms() - philo->last_meal)
			- philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == TRUE)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == FALSE)
		write_status(philo, FALSE, thinking);
	philo_sleep(philo->table, time_to_think);
}

/**
 * Routine pour un philosophe unique.
 * 
 * Cette routine est appelée lorsqu'il n'y a qu'un seul philosophe.
 * Un philosophe seul n'a qu'une fourchette et ne peut donc pas manger.
 * Il prend la fourchette, attend le temps de mourir (time_to_die), puis meurt.
 * Cette routine séparée garantit que le thread ne reste pas bloqué
 * en attendant une deuxième fourchette dans la routine de repas.
 * 
 * @param philo Le philosophe qui effectue la routine.
 * @return NULL après exécution.
 */
static void	*lone_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	write_status(philo, FALSE, got_fork_1);
	philo_sleep(philo->table, philo->table->time_to_die);
	write_status(philo, FALSE, died);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	return (NULL);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->must_eat_count == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	sim_start_delay(philo->table->start_time);
	if (philo->table->time_to_die == 0)
		return (NULL);
	if (philo->table->nb_philos == 1)
		return (lone_philo_routine(philo));
	else if (philo->id % 2)
		think_routine(philo, TRUE);
	while (has_simulation_stopped(philo->table) == FALSE)
	{
		eat_sleep_routine(philo);
		think_routine(philo, FALSE);
	}
	return (NULL);
}
