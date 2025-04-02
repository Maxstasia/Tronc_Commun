/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:59:22 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/02 16:46:31 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*--------------------macro--------------------*/

/*--------------------bibliotheques--------------------*/

# include <stdio.h>      // Pour printf
# include <stdlib.h>     // Pour malloc, free
# include <string.h>     // Pour memset
# include <unistd.h>     // Pour write, usleep
# include <sys/time.h>   // Pour gettimeofday
# include <pthread.h>    // Pour pthread_create, pthread_detach, pthread_join,
                         // pthread_mutex_init, pthread_mutex_destroy,
                         // pthread_mutex_lock, pthread_mutex_unlock

/*--------------------structures--------------------*/

typedef struct s_philo
{
	int				id;				// Numéro du philosophe (1 à n)
	pthread_t		thread;			// Thread du philosophe
	pthread_mutex_t	*left_fork;		// Fourchette à gauche
	pthread_mutex_t	*right_fork;	// Fourchette à droite
	long			last_meal;		// Timestamp du dernier repas
	int				meals_eaten;	// Nombre de repas mangés
	struct s_data	*data;			// Pointeur vers les données globales
}				t_philo;

typedef struct s_data
{
	int				nb_philo;		// Nombre de philosophes
	long			time_to_die;	// Temps avant de mourir (ms)
	long			time_to_eat;	// Temps pour manger (ms)
	long			time_to_sleep;	// Temps pour dormir (ms)
	int				must_eat;		// Nombre de repas requis (optionnel)
	t_philo			*philos;		// Tableau de philosophes
	pthread_mutex_t	*forks;			// Tableau de mutex pour les fourchettes
	pthread_mutex_t	print_mutex;	// Mutex pour l’affichage
	long			start_time;		// Timestamp de départ
	int				stop;			// Flag pour arrêter la simulation
}				t_data;

/*--------------------fonctions--------------------*/
/*----------sources----------*/
/*-----error.c-----*/



/*-----philo.c-----*/



/*----------utils----------*/
/*-----utils.c-----*/


// int     init_data(t_data *data, int ac, char **av);
// void    init_philos(t_data *data);
long    get_time(void);
void    print_state(t_philo *philo, char *state);
void    *philo_routine(void *arg);
int     start_simulation(t_data *data);
void    cleanup(t_data *data);
void    *monitor(void *arg);
int ft_atoi(const char *str);

#endif
