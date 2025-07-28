/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:05:51 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/15 16:44:06 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

/**
 * Commence la simulation en créant les threads pour chaque philosophe.
 * Si le nombre de philosophes est supérieur à 1, crée également
 * le thread de surveillance.
 * 
 * @param table La table à utiliser.
 * @return true si la simulation a démarré avec succès, false sinon.
 */
static BOOL	start(t_table *table)
{
	unsigned int	i;

	table->start_time = get_time_in_ms() + (table->nb_philos * 10 * 2);
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL,
				&philosopher, table->philos[i]) != 0)
			return (error_failure(STR_ERR_THREAD, NULL, table));
		i++;
	}
	if (table->nb_philos > 1)
	{
		if (pthread_create(&table->monitoring, NULL,
				&monitoring, table) != 0)
			return (error_failure(STR_ERR_THREAD, NULL, table));
	}
	return (TRUE);
}

/**
 * Arrête la simulation en rejoignant tous les threads des philosophes
 * et le thread de surveillance.
 * 
 * @param table La table à utiliser.
 */
static void	stop(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	if (table->nb_philos > 1)
		pthread_join(table->monitoring, NULL);
	destroy_mutexes(table);
	free_table(table);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (argc - 1 < 4 || argc - 1 > 5)
		return (msg(STR_USAGE, NULL, EXIT_FAILURE));
	if (!is_valid_input(argc, argv))
		return (EXIT_FAILURE);
	table = init_table(argc, argv, 1);
	if (!table)
		return (EXIT_FAILURE);
	if (!start(table))
		return (EXIT_FAILURE);
	stop(table);
	return (EXIT_SUCCESS);
}
