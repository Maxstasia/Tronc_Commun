/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:59:22 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/10 16:19:03 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*--------------------macro--------------------*/

# define ERR_ARGS "Error: Invalid number of arguments\n"
# define ERR_USAGE "./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define ERR_INPUT "Error: Invalid input\n"
# define ERR_MEM "Error: Memory allocation failed\n"
# define ERR_THREAD "Error: Thread creation failed\n"

# define RESET "\033[0m"
# define FORK "\033[95m"		// Violet clair
# define EATING "\033[91m"		// Rouge clair
# define SLEEPING "\033[94m"	// Bleu clair
# define THINKING "\033[92m"	// Vert clair

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
	pthread_mutex_t	meal_mutex;		// Mutex pour protéger l'accès à last_meal
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
	pthread_mutex_t stop_mutex;		// Nouveau mutex pour stop
	long			start_time;		// Timestamp de départ
	int				stop;			// Flag pour arrêter la simulation
}				t_data;

/*--------------------fonctions--------------------*/
/*----------sources----------*/
/*-----error.c-----*/

void	ft_cleanup(t_data *data);

/*-----init.c-----*/

int		ft_init_data(t_data *data, int ac, char **av);
int		ft_init_philos(t_data *data);

/*----------utils----------*/
/*-----utils.c-----*/

long	ft_get_time(void);
void	ft_print_state(t_philo *philo, char *state);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);

/*-----action.c-----*/

void	*ft_philo_routine(void *arg);
void	*ft_monitor(void *arg);
int		ft_start_simulation(t_data *data);

#endif
