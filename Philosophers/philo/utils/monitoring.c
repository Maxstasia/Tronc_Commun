/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:05:17 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/15 11:54:05 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * Définit l'état du drapeau d'arrêt de la simulation.
 * 
 * @param table La table contenant les données de la simulation.
 * @param state L'état à attribuer au drapeau (vrai pour arrêter, faux sinon).
 */
static void	set_sim_stop_flag(t_table *table, BOOL state)
{
	pthread_mutex_lock(&table->sim_stop_lock);
		table->sim_stop = state;
	pthread_mutex_unlock(&table->sim_stop_lock);
}

BOOL	has_simulation_stopped(t_table *table)
{
	BOOL	r;

	r = FALSE;
	pthread_mutex_lock(&table->sim_stop_lock);
	if (table->sim_stop == TRUE)
		r = TRUE;
	pthread_mutex_unlock(&table->sim_stop_lock);
	return (r);
}

/**
 * Vérifie si un philosophe doit être tué.
 * 
 * Compare le temps écoulé depuis le dernier repas du philosophe avec
 * le paramètre time_to_die. Si le temps est écoulé, définit le drapeau
 * d'arrêt de la simulation et affiche l'état de décès.
 * 
 * @param philo Le philosophe à vérifier.
 * @return Vrai si le philosophe est tué, faux sinon.
 */
static BOOL	kill_philo(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal) >= philo->table->time_to_die)
	{
		set_sim_stop_flag(philo->table, TRUE);
		write_status(philo, TRUE, died);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (TRUE);
	}
	return (FALSE);
}

/**
 * Vérifie si une condition de fin de simulation est atteinte.
 * 
 * Parcourt chaque philosophe pour vérifier si un philosophe doit être tué
 * ou si tous ont suffisamment mangé. Arrête la simulation si une condition
 * de fin est atteinte.
 * 
 * @param table La table contenant les données de la simulation.
 * @return Vrai si une condition de fin est atteinte, faux sinon.
 */
static BOOL	end_condition_reached(t_table *table)
{
	unsigned int	i;
	BOOL			all_ate_enough;

	all_ate_enough = TRUE;
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philos[i]->meal_time_lock);
		if (kill_philo(table->philos[i]))
			return (TRUE);
		if (table->must_eat_count != -1)
			if (table->philos[i]->times_eat
				< (unsigned int)table->must_eat_count)
				all_ate_enough = FALSE;
		pthread_mutex_unlock(&table->philos[i]->meal_time_lock);
		i++;
	}
	if (table->must_eat_count != -1 && all_ate_enough == TRUE)
	{
		set_sim_stop_flag(table, TRUE);
		return (TRUE);
	}
	return (FALSE);
}

void	*monitoring(void *data)
{
	t_table			*table;

	table = (t_table *)data;
	if (table->must_eat_count == 0)
		return (NULL);
	set_sim_stop_flag(table, FALSE);
	sim_start_delay(table->start_time);
	while (TRUE)
	{
		if (end_condition_reached(table) == TRUE)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
