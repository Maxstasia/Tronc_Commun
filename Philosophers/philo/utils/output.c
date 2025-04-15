/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:05:56 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/15 16:11:32 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * Affiche l'état d'un philosophe.
 * 
 * Affiche l'état d'un philosophe en texte clair conformément aux exigences
 * du sujet :
 *     timestamp_in_ms X état
 * 
 * @param philo Le philosophe dont l'état doit être affiché.
 * @param str La chaîne de caractères représentant l'état.
 * @param color La couleur à utiliser pour l'affichage.
 */
static void	print_status(t_philo *philo, char *str, char *color)
{
	printf("%s%ld %d %s%s\n", color,
		get_time_in_ms() - philo->table->start_time, philo->id + 1, str, RESET);
}

void	write_status(t_philo *philo, BOOL reaper_report, t_status status)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (has_simulation_stopped(philo->table) == TRUE && reaper_report == FALSE)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	if (status == died)
		print_status(philo, "died", YELLOW);
	else if (status == eating)
		print_status(philo, "is eating", RED);
	else if (status == sleeping)
		print_status(philo, "is sleeping", CYAN);
	else if (status == thinking)
		print_status(philo, "is thinking", GREEN);
	else if (status == got_fork_1 || status == got_fork_2)
		print_status(philo, "has taken a fork", PURPLE);
	pthread_mutex_unlock(&philo->table->write_lock);
}
