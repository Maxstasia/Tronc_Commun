/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:04:56 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/15 16:21:57 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*--------------------macro--------------------*/

# define MAX_PHILOS		250
# define STR_MAX_PHILOS	"250"

# define BOOL			int
# define TRUE			1
# define FALSE			0

# define INT_MAX	2147483647

# define RESET	"\e[0m"		// Reset color
# define RED	"\e[91m"	// Eating color
# define GREEN	"\e[92m"	// Sleeping color
# define PURPLE	"\e[95m"	// Fork color
# define CYAN	"\e[94m"	// Sleeping color
# define YELLOW	"\e[93m"	// Dying color

# define STR_PROG_NAME	"philo:"
# define STR_USAGE	"%s usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define STR_ERR_INPUT_DIGIT	"%s invalid input: %s: \
not a valid unsigned integer between 0 and 2147483647.\n"
# define STR_ERR_INPUT_POFLOW	"%s invalid input: \
there must be between 1 and %s philosophers.\n"
# define STR_ERR_THREAD	"%s error: Could not create thread.\n"
# define STR_ERR_MALLOC	"%s error: Could not allocate memory.\n"
# define STR_ERR_MUTEX	"%s error: Could not create mutex.\n"

/*--------------------bibliotheques--------------------*/

# include <stdio.h>		// Pour printf
# include <stdlib.h>	// Pour malloc, free
# include <string.h>	// Pour memset
# include <unistd.h>	// Pour write, usleep
# include <sys/time.h>	// Pour gettimeofday
# include <pthread.h>	// Pour pthread_create, pthread_detach, pthread_join,
						// pthread_mutex_init, pthread_mutex_destroy,
						// pthread_mutex_lock, pthread_mutex_unlock

/*--------------------structures--------------------*/

typedef struct s_philo	t_philo;

/**
 * Structure représentant la table des philosophes.
 * 
 * Contient les informations sur la simulation, y compris le nombre de
 * philosophes, les mutex pour la synchronisation, et un tableau de
 * philosophes.
 * 
 * @param start_time L'heure de début de la simulation.
 * @param nb_philos Le nombre de philosophes.
 * @param monitoring Le thread du grim reaper.
 * @param time_to_die Le temps avant de mourir.
 * @param time_to_eat Le temps pour manger.
 * @param time_to_sleep Le temps pour dormir.
 * @param must_eat_count Le nombre de repas à faire.
 * @param sim_stop Flag pour arrêter la simulation.
 * @param sim_stop_lock Mutex pour protéger l'accès à sim_stop.
 * @param write_lock Mutex pour protéger l'accès à l'écriture.
 * @param fork_locks Mutex pour protéger les fourchettes.
 * @param philos Tableau de philosophes.
 */
typedef struct s_table
{
	time_t			start_time;
	unsigned int	nb_philos;
	pthread_t		monitoring;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_count;
	BOOL			sim_stop;
	pthread_mutex_t	sim_stop_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
	t_philo			**philos;
}			t_table;

/**
 * Structure représentant un philosophe.
 * 
 * Chaque philosophe a un identifiant, un nombre de repas effectués,
 * des fourchettes associées, un mutex pour protéger l'accès à son
 * dernier repas et un pointeur vers la table.
 * 
 * @param thread Le thread du philosophe.
 * @param id L'identifiant du philosophe.
 * @param times_eat Le nombre de fois que le philosophe a mangé.
 * @param fork Les fourchettes du philosophe.
 * @param meal_time_lock Le mutex pour protéger l'accès à last_meal.
 * @param last_meal L'heure du dernier repas du philosophe.
 * @param table Le pointeur vers la table des philosophes.
 */
typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		times_eat;
	unsigned int		fork[2];
	pthread_mutex_t		meal_time_lock;
	time_t				last_meal;
	t_table				*table;
}			t_philo;

/**
 * Structure représentant un état d'un philosophe.
 * 
 * Chaque état est associé à un entier pour faciliter la gestion
 * et la comparaison des états.
 * 
 * @param died L'état où le philosophe est mort.
 * @param eating L'état où le philosophe mange.
 * @param sleeping L'état où le philosophe dort.
 * @param thinking L'état où le philosophe pense.
 * @param got_fork_1 L'état où le philosophe a pris la première fourchette.
 * @param got_fork_2 L'état où le philosophe a pris la deuxième fourchette.
 */
typedef enum e_status
{
	died,
	eating,
	sleeping,
	thinking,
	got_fork_1,
	got_fork_2,
}			t_status;

/*--------------------fonctions--------------------*/
/*----------sources----------*/
/*-----init.c-----*/

/**
 * Initialise la table des philosophes.
 * 
 * Alloue la mémoire pour la table, configure ses paramètres (nombre de
 * philosophes, temps de vie, temps de repas, temps de sommeil, etc.),
 * initialise les philosophes et les mutex globaux.
 * 
 * @param argc Nombre d'arguments passés au programme.
 * @param argv Tableau des arguments.
 * @param i Index de départ pour parser les arguments.
 * @return Un pointeur sur la table initialisée,
 * ou NULL si une erreur s'est produite.
 */
t_table			*init_table(int argc, char **argv, int i);

/*-----philosopher.c-----*/

/**
 * Routine principale d'un philosophe.
 * 
 * Cette routine gère le cycle de vie d'un philosophe : manger,
 * dormir et réfléchir. Pour éviter les conflits entre les threads,
 * les philosophes avec un identifiant pair commencent par réfléchir,
 * ce qui retarde légèrement leur repas. Cela permet aux philosophes
 * avec un identifiant impair de prendre leurs fourchettes en premier,
 * évitant ainsi les blocages (deadlocks).
 * 
 * @param data Les données du philosophe (cast en t_philo).
 * @return NULL après exécution.
 */
void			*philosopher(void *data);

/*----------utils----------*/
/*-----error.c-----*/

/**
 * Libère toute la mémoire allouée par le programme.
 * 
 * @param table La table contenant les données à libérer.
 * @return Un pointeur NULL si aucune donnée n'est à libérer ou après libération.
 */
void			*free_table(t_table *table);

/**
 * Détruit tous les mutex créés par le programme : verrous des fourchettes,
 * verrous des repas, verrou d'écriture et verrou d'arrêt de simulation.
 * 
 * @param table La table contenant les mutex à détruire.
 */
void			destroy_mutexes(t_table *table);

/**
 * Affiche un message dans la console et retourne le code de sortie fourni.
 * Utilisé pour la gestion des erreurs.
 * 
 * @param str Le format du message à afficher.
 * @param detail Les détails supplémentaires à inclure dans le message.
 * @param exit_no Le code de sortie à retourner.
 * @return Le code de sortie fourni.
 */
int				msg(char *str, char *detail, int exit_no);

/**
 * Libère la mémoire allouée, affiche un message d'erreur et retourne 0
 * pour indiquer un échec. Utilisé pour la gestion des erreurs lors de
 * l'initialisation.
 * 
 * @param str Le format du message d'erreur.
 * @param details Les détails supplémentaires de l'erreur (optionnel).
 * @param table La table à libérer (optionnel).
 * @return 0 pour indiquer un échec.
 */
int				error_failure(char *str, char *details, t_table *table);

/**
 * Libère la mémoire allouée, affiche un message d'erreur et retourne un
 * pointeur NULL. Utilisé pour la gestion des erreurs lors de l'initialisation.
 * 
 * @param str Le format du message d'erreur.
 * @param details Les détails supplémentaires de l'erreur (optionnel).
 * @param table La table à libérer (optionnel).
 * @return Un pointeur NULL.
 */
void			*error_null(char *str, char *details, t_table *table);

/*-----monitoring.c-----*/

/**
 * Vérifie si la simulation est terminée.
 * 
 * @param table La table contenant les données de la simulation.
 * @return Vrai si la simulation est arrêtée, faux sinon.
 */
BOOL			has_simulation_stopped(t_table *table);

/**
 * Routine du thread de surveillance (faucheuse).
 * 
 * Vérifie si un philosophe doit être tué ou si tous ont suffisamment mangé.
 * Si une condition de fin est atteinte, la simulation est arrêtée.
 * 
 * @param data Pointeur vers la table contenant les données de la simulation.
 * @return NULL lorsque la simulation est terminée ou en cas d'arrêt anticipé.
 */
void			*monitoring(void *data);

/*-----output.c-----*/

/**
 * Écrit l'état d'un philosophe.
 * 
 * Affiche l'état d'un philosophe tant que la simulation est active.
 * Verrouille le mutex d'écriture pour éviter l'entrelacement des messages
 * provenant de différents threads.
 * 
 * @param philo Le philosophe dont l'état doit être écrit.
 * @param reaper_report Indique si le rapport provient du faucheur.
 * @param status L'état à afficher pour le philosophe.
 */
void			write_status(t_philo *philo, BOOL reaper, t_status status);

/*-----parsing.c-----*/

/**
 * Convertit une chaîne de chiffres en entier positif.
 * 
 * @param str La chaîne à convertir.
 * @return L'entier converti entre 0 et INT_MAX,
 * ou -1 si le nombre dépasse INT_MAX.
 */
int				ft_atoi(char *str);

/**
 * Vérifie la validité des arguments d'entrée.
 * 
 * @param argc Le nombre d'arguments.
 * @param argv Le tableau des arguments.
 * @return True si tous les arguments sont valides,
 * False si l'un d'eux est invalide.
 */
BOOL			is_valid_input(int argc, char **argv);

/*-----time.c-----*/

/**
 * Récupère l'heure actuelle en millisecondes.
 * 
 * Calcule le temps écoulé depuis l'époque (1970-01-01 00:00:00)
 * en millisecondes.
 * 
 * @return La valeur du temps en millisecondes.
 */
time_t			get_time_in_ms(void);

/**
 * Met en pause le thread d'un philosophe pendant une durée donnée.
 * 
 * Suspend l'exécution du philosophe pour un temps spécifié en millisecondes.
 * Vérifie périodiquement si la simulation s'est terminée pendant la pause
 * et interrompt la pause si nécessaire.
 * 
 * @param table La table contenant les informations de la simulation.
 * @param sleep_time La durée de la pause en millisecondes.
 */
void			philo_sleep(t_table *table, time_t sleep_time);

/**
 * Synchronise le début de la simulation.
 * 
 * Introduit un léger délai au démarrage de chaque thread pour s'assurer que
 * tous les threads commencent simultanément avec la même référence temporelle.
 * Cela garantit la synchronisation entre le thread de la faucheuse et les
 * threads des philosophes.
 * 
 * @param start_time L'heure de référence pour le début de la simulation.
 */
void			sim_start_delay(time_t start_time);

#endif
