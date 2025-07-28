# Philosophers - README

---

## Description
Philosophers est un projet réalisé dans le cadre du cursus de l'école 42. Il vise à initier les étudiants aux concepts de programmation concurrente et de gestion des threads en C, à travers la simulation du problème classique des "philosophes dinant". Ce projet explore les mécanismes de synchronisation (mutex, threads) pour éviter les problèmes comme les deadlocks et les conditions de course, tout en respectant des contraintes strictes.

L'objectif est de maîtriser les concepts suivants :
- Programmation en C avec gestion des threads et des mutex.
- Compréhension des problématiques de concurrence (deadlocks, starvation).
- Gestion des ressources partagées (fourchettes) entre plusieurs processus/threads.
- Affichage des états des philosophes (manger, dormir, penser, mourir) avec des timestamps précis.
- Implémentation d'une simulation qui s'arrête correctement (mort d'un philosophe ou nombre de repas atteint).
- Gestion des bonus (utilisation de processus au lieu de threads).

## Structure du projet
Le projet est structuré en deux parties principales :
- **Partie obligatoire** : Dossier `philo/` contenant le programme principal utilisant des threads et des mutex.
- **Partie bonus** : Dossier `philo_bonus/` utilisant des processus et des sémaphores (optionnel).
- Les fichiers clés incluent :
  - **Sources C** : Fichiers contenant le code de la simulation.
  - **Makefile** : Pour compiler les programmes avec les flags `-Wall`, `-Wextra`, `-Werror`.

## Prérequis
- Un environnement Linux/Unix pour compiler et exécuter le programme.
- Connaissances de base en programmation C (threads, mutex, sémaphores pour la partie bonus).
- Compilateur compatible avec C99 (gcc, clang).
- Connaissance des concepts de concurrence et de synchronisation.

## Installation
1. **Cloner le dépôt Git** :
   ```bash
   git clone <votre-dépôt-git>
   cd philosophers
   ```
2. **Compiler la partie obligatoire** :
   ```bash
   make -C philo
   ```
   Produit l'exécutable `philo`.
3. **Compiler la partie bonus (si applicable)** :
   ```bash
   make -C philo_bonus
   ```
   Produit l'exécutable `philo_bonus`.
4. **Nettoyer les fichiers objets** :
   ```bash
   make clean -C philo
   make clean -C philo_bonus
   ```
5. **Recompiler tout** :
   ```bash
   make re -C philo
   make re -C philo_bonus
   ```

## Utilisation
### Commandes principales
1. **Lancer le programme obligatoire** :
   ```bash
   ./philo/philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
   ```
   Exemple :
   ```bash
   ./philo/philo 5 800 200 200 7
   ```
   - `number_of_philosophers` : Nombre de philosophes (et fourchettes).
   - `time_to_die` : Temps en ms avant qu’un philosophe ne meure s’il n’a pas mangé.
   - `time_to_eat` : Temps en ms pour manger (en tenant deux fourchettes).
   - `time_to_sleep` : Temps en ms pour dormir.
   - `[number_of_times_each_philosopher_must_eat]` : Nombre de repas par philosophe (optionnel).

2. **Lancer le programme bonus (si implémenté)** :
   ```bash
   ./philo_bonus/philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
   ```

### Exemple de sortie
Les changements d’état des philosophes sont affichés avec des timestamps en millisecondes :
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
800 2 died
```

### Règles du programme
- Chaque philosophe est un thread (partie obligatoire) ou un processus (partie bonus).
- Les fourchettes sont des ressources partagées (mutex pour la partie obligatoire, sémaphores pour la partie bonus).
- Les états des philosophes doivent être affichés sans chevauchement.
- La mort d’un philosophe doit être signalée dans les 10 ms.
- Les philosophes doivent éviter de mourir (gestion des deadlocks et starvation).
- La simulation s’arrête si un philosophe meurt ou si tous ont mangé le nombre de repas requis (si spécifié).

## Fonctionnement détaillé
### Partie obligatoire
- Le programme simule `number_of_philosophers` philosophes assis autour d’une table avec autant de fourchettes.
- Chaque philosophe suit un cycle : manger (prend deux fourchettes), dormir, penser.
- Les fourchettes sont protégées par des mutex pour éviter les conflits.
- Les logs doivent respecter le format suivant :
  ```
  timestamp_in_ms X has taken a fork
  timestamp_in_ms X is eating
  timestamp_in_ms X is sleeping
  timestamp_in_ms X is thinking
  timestamp_in_ms X died
  ```
- Les variables globales sont interdites.
- La mémoire allouée doit être libérée correctement.

### Partie bonus
- Utilise des processus et des sémaphores au lieu de threads et de mutex.
- Même comportement que la partie obligatoire, mais avec une gestion différente des ressources partagées.
- Les bonus sont évalués séparément et doivent être compilés via une règle `bonus` dans le Makefile.

### Makefile
Le Makefile doit inclure les règles suivantes :
- `all` : Compile le programme principal.
- `clean` : Supprime les fichiers objets.
- `fclean` : Supprime les fichiers objets et l’exécutable.
- `re` : Recompile tout.
- `bonus` : Compile le programme bonus (si implémenté).

## Gestion des erreurs
- Vérifiez que le programme ne provoque pas de segmentation faults, bus errors, ou fuites de mémoire.
- Assurez-vous que le code respecte la Norme 42 (vérifié par `norminette`).
- Testez avec différents nombres de philosophes et paramètres pour éviter les deadlocks ou starvation.
- Les messages de logs doivent être synchronisés pour éviter tout chevauchement.
- Pendant l’évaluation, Deepthought peut tester des cas extrêmes (ex. : 1 philosophe, temps très courts).

## Limitations
- Les variables globales sont interdites.
- Les erreurs non gérées (segmentation fault, double free, etc.) entraînent une note de 0.
- Le programme doit être conforme à la Norme 42, sinon la note est 0.
- Aucun outil externe autre que le compilateur et `norminette` n’est autorisé pour le développement.

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** : Avril 2025 - Avril 2025

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis de découvrir la programmation concurrente et la gestion des threads en C, tout en explorant le problème classique des philosophes dinant.

---

# Philosophers - README

## Description
Philosophers is a project developed as part of the 42 school curriculum. It introduces students to concurrent programming and thread management in C through the simulation of the classic "dining philosophers" problem. The project focuses on synchronization mechanisms (mutex, threads) to avoid issues like deadlocks and race conditions while adhering to strict constraints.

The goal is to master the following concepts:
- Programming in C with thread and mutex management.
- Understanding concurrency issues (deadlocks, starvation).
- Managing shared resources (forks) among multiple processes/threads.
- Displaying philosophers' states (eating, sleeping, thinking, dying) with precise timestamps.
- Implementing a simulation that stops correctly (philosopher death or required meals completed).
- Handling bonuses (using processes instead of threads).

## Project Structure
The project is divided into two main parts:
- **Mandatory Part**: Directory `philo/` containing the main program using threads and mutexes.
- **Bonus Part**: Directory `philo_bonus/` using processes and semaphores (optional).
- Key files include:
  - **C Source Files**: Files containing the simulation code.
  - **Makefile**: To compile the programs with `-Wall`, `-Wextra`, `-Werror` flags.

## Prerequisites
- A Linux/Unix environment to compile and run the program.
- Basic knowledge of C programming (threads, mutexes, semaphores for the bonus part).
- A C99-compatible compiler (gcc, clang).
- Understanding of concurrency and synchronization concepts.

## Installation
1. **Clone the Git repository**:
   ```bash
   git clone <your-git-repository>
   cd philosophers
   ```
2. **Compile the mandatory part**:
   ```bash
   make -C philo
   ```
   Produces the `philo` executable.
3. **Compile the bonus part (if applicable)**:
   ```bash
   make -C philo_bonus
   ```
   Produces the `philo_bonus` executable.
4. **Clean object files**:
   ```bash
   make clean -C philo
   make clean -C philo_bonus
   ```
5. **Recompile everything**:
   ```bash
   make re -C philo
   make re -C philo_bonus
   ```

## Usage
### Key Commands
1. **Run the mandatory program**:
   ```bash
   ./philo/philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
   ```
   Example:
   ```bash
   ./philo/philo 5 800 200 200 7
   ```
   - `number_of_philosophers`: Number of philosophers (and forks).
   - `time_to_die`: Time in ms before a philosopher dies if they haven’t eaten.
   - `time_to_eat`: Time in ms to eat (holding two forks).
   - `time_to_sleep`: Time in ms to sleep.
   - `[number_of_times_each_philosopher_must_eat]`: Number of meals per philosopher (optional).

2. **Run the bonus program (if implemented)**:
   ```bash
   ./philo_bonus/philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
   ```

### Example Output
Philosophers’ state changes are displayed with millisecond timestamps:
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
800 2 died
```

### Program Rules
- Each philosopher is a thread (mandatory part) or a process (bonus part).
- Forks are shared resources (mutexes for mandatory, semaphores for bonus).
- State logs must be displayed without overlap.
- A philosopher’s death must be logged within 10 ms.
- Philosophers must avoid dying (handle deadlocks and starvation).
- The simulation stops if a philosopher dies or all have eaten the required number of meals (if specified).

## Detailed Functionality
### Mandatory Part
- The program simulates `number_of_philosophers` philosophers around a table with an equal number of forks.
- Each philosopher cycles through eating (taking two forks), sleeping, and thinking.
- Forks are protected by mutexes to prevent conflicts.
- Logs must follow this format:
  ```
  timestamp_in_ms X has taken a fork
  timestamp_in_ms X is eating
  timestamp_in_ms X is sleeping
  timestamp_in_ms X is thinking
  timestamp_in_ms X died
  ```
- Global variables are forbidden.
- Allocated memory must be freed properly.

### Bonus Part
- Uses processes and semaphores instead of threads and mutexes.
- Same behavior as the mandatory part but with different resource management.
- Bonuses are evaluated separately and compiled via a `bonus` rule in the Makefile.

### Makefile
The Makefile must include:
- `all`: Compiles the main program.
- `clean`: Removes object files.
- `fclean`: Removes object files and the executable.
- `re`: Recompiles everything.
- `bonus`: Compiles the bonus program (if implemented).

## Error Handling
- Ensure the program avoids segmentation faults, bus errors, or memory leaks.
- Verify code compliance with the 42 Norm (checked by `norminette`).
- Test with various philosopher counts and parameters to prevent deadlocks or starvation.
- Logs must be synchronized to avoid overlap.
- During evaluation, Deepthought may test edge cases (e.g., 1 philosopher, very short times).

## Limitations
- Global variables are forbidden.
- Unhandled errors (segmentation fault, double free, etc.) result in a grade of 0.
- The program must comply with the 42 Norm, or the grade is 0.
- No external tools other than the compiler and `norminette` are allowed for development.

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**: April 2025 - April 2025

## Acknowledgments
Thanks to 42 school for this project, which allowed me to explore concurrent programming and thread management in C while tackling the classic dining philosophers problem.