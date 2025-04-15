/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:05:41 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/15 16:11:24 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * Initialise les fourchettes de la table.
 * 
 * @param table La table à initialiser.
 * @return Un pointeur sur le tableau de fourchettes,
 * ou NULL si une erreur s'est produite.
 */
static pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (!forks)
		return (error_null(STR_ERR_MALLOC, NULL, 0));
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (error_null(STR_ERR_MUTEX, NULL, 0));
		i++;
	}
	return (forks);
}

/**
 * Attribue les fourchettes aux philosophes.
 * 
 * Chaque philosophe reçoit deux identifiants de fourchettes. Les philosophes
 * avec un identifiant pair inversent l'ordre des fourchettes pour éviter les
 * interblocages.
 * 
 * Par exemple, pour 3 philosophes :
 * 
 * - Philo #1 (id: 0) prend fourchette 1 puis 0.
 * 
 * - Philo #2 (id: 1) prend fourchette 1 puis 2.
 * 
 * - Philo #3 (id: 2) prend fourchette 0 puis 2.
 * 
 * Cela permet d'éviter qu'un philosophe attende indéfiniment une fourchette
 * déjà utilisée.
 * 
 * @param philo Le philosophe à qui attribuer les fourchettes.
 */
static void	assign_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->table->nb_philos;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->table->nb_philos;
		philo->fork[1] = philo->id;
	}
}

/**
 * Initialise les philosophes de la table.
 * 
 * Alloue la mémoire pour chaque philosophe et initialise leurs valeurs,
 * y compris leur identifiant, leur table et leurs fourchettes. Les mutex
 * pour gérer le temps des repas sont également initialisés.
 * 
 * @param table La table contenant les informations des philosophes.
 * @return Un pointeur sur le tableau de philosophes,
 * ou NULL si une erreur s'est produite.
 */
static t_philo	**init_philosophers(t_table *table)
{
	t_philo			**philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (!philos)
		return (error_null(STR_ERR_MALLOC, NULL, 0));
	i = 0;
	while (i < table->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (error_null(STR_ERR_MALLOC, NULL, 0));
		if (pthread_mutex_init(&philos[i]->meal_time_lock, 0) != 0)
			return (error_null(STR_ERR_MUTEX, NULL, 0));
		philos[i]->table = table;
		philos[i]->id = i;
		philos[i]->times_eat = 0;
		assign_forks(philos[i]);
		i++;
	}
	return (philos);
}

/**
 * Initialise les mutex globaux.
 * 
 * Crée les verrous pour les fourchettes, l'écriture et l'arrêt de la simulation.
 * 
 * @param table La table à initialiser.
 * @return true si l'initialisation a réussi, false sinon.
 */
static BOOL	init_global_mutexes(t_table *table)
{
	table->fork_locks = init_forks(table);
	if (!table->fork_locks)
		return (FALSE);
	if (pthread_mutex_init(&table->sim_stop_lock, 0) != 0)
		return (error_failure(STR_ERR_MUTEX, NULL, table));
	if (pthread_mutex_init(&table->write_lock, 0) != 0)
		return (error_failure(STR_ERR_MUTEX, NULL, table));
	return (TRUE);
}

t_table	*init_table(int argc, char **argv, int i)
{
	t_table	*table;

	table = malloc(sizeof(t_table) * 1);
	if (!table)
		return (error_null(STR_ERR_MALLOC, NULL, 0));
	table->nb_philos = ft_atoi(argv[i++]);
	table->time_to_die = ft_atoi(argv[i++]);
	table->time_to_eat = ft_atoi(argv[i++]);
	table->time_to_sleep = ft_atoi(argv[i++]);
	table->must_eat_count = -1;
	if (argc - 1 == 5)
		table->must_eat_count = ft_atoi(argv[i]);
	table->philos = init_philosophers(table);
	if (!table->philos)
		return (NULL);
	if (!init_global_mutexes(table))
		return (NULL);
	table->sim_stop = FALSE;
	return (table);
}
