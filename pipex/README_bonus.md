Français

---

# Pipex Bonus - README

---

## Description
Pipex Bonus est une version avancée du projet Pipex réalisé dans le cadre du cursus de l'école 42. Ce programme simule un pipeline Unix avec la prise en charge de multiples commandes et du mode `here_doc`. Il peut reproduire des comportements comme :
```bash
< file1 cmd1 | cmd2 | cmd3 > file2
```
ou avec `here_doc` :
```bash
here_doc LIMITER cmd1 cmd2 file
```
Le programme lit une entrée (fichier ou saisie utilisateur avec `here_doc`), exécute une série de commandes en les reliant par des pipes, et écrit le résultat final dans un fichier de sortie.

Les objectifs principaux sont :
- Gestion avancée des processus avec `fork`.
- Utilisation de multiples pipes pour connecter plusieurs commandes.
- Support du mode `here_doc` pour une entrée dynamique.
- Redirection des entrées/sorties avec `dup2`.
- Exécution des commandes avec `execve`.
- Gestion robuste des erreurs.

## Structure du projet
Le projet est organisé en plusieurs fichiers pour une modularité optimale :
- **`main_bonus.c`** : Logique principale (initialisation, lancement des processus).
- **`pipex_bonus.c`** : Gestion des processus enfants, pipes et `here_doc`.
- **`utils_bonus.c`** : Fonctions utilitaires pour trouver et exécuter les commandes.
- **`ft_split_advanced_bonus.c`** : Séparation des arguments avec prise en charge des guillemets.
- **`error_bonus.c`** : Gestion des erreurs et messages.
- **`pipex_bonus.h`** : Définitions des structures et prototypes.
- **`Libft/`** : Bibliothèque personnelle pour les fonctions utilitaires.

## Prérequis
- Un système Unix-like (Linux, macOS).
- Un compilateur C (ex. `gcc`).
- Bibliothèques standard (`unistd.h`, `fcntl.h`, etc.).
- Les bibliothèques `Libft` et `get_next_line` (incluses dans le projet).

## Compilation
Pour compiler, exécutez cette commande dans le répertoire racine :
```bash
make bonus
```
Cela génère l'exécutable `pipex_bonus`. Assurez-vous que `Libft` et `get_next_line` sont compilés.

## Utilisation
Le programme accepte un nombre variable d'arguments selon le mode :
1. **Mode standard** (minimum 5 arguments) :
```bash
./pipex_bonus file1 cmd1 cmd2 ... cmdN file2
```
- `file1` : Fichier d'entrée.
- `cmd1` à `cmdN` : Commandes à exécuter en séquence.
- `file2` : Fichier de sortie.

2. **Mode `here_doc`** (minimum 6 arguments) :
```bash
./pipex_bonus here_doc LIMITER cmd1 cmd2 ... cmdN file
```
- `here_doc` : Mot-clé pour activer ce mode.
- `LIMITER` : Délimiteur pour arrêter la saisie.
- `cmd1` à `cmdN` : Commandes à exécuter.
- `file` : Fichier de sortie.

### Exemples
1. Pipeline avec plusieurs commandes :
```bash
./pipex_bonus infile "cat" "grep error" "wc -l" outfile
```
- Lit `infile`, filtre les lignes avec "error", compte les lignes, et écrit dans `outfile`.

2. Mode `here_doc` :
```bash
./pipex_bonus here_doc END "cat" "wc -w" outfile
```
- Lit l'entrée utilisateur jusqu'à "END", compte les mots, et écrit dans `outfile`.

3. Fichier d'entrée inexistant :
```bash
./pipex_bonus inexistant "ls -l" "wc -l" outfile
```
- Si `inexistant` n'existe pas, affiche une erreur et quitte.

## Fonctionnement détaillé
### Structures
- **`t_pipex`** : Contient les données principales (arguments, fichiers, pipes, flags).
```c
typedef struct s_pipex
{
    char    **argv;
    char    **envp;
    char    *filein;
    char    *fileout;
    int     fd[2];
    int     prev_fd;
    int     is_first;
    int     is_last;
    int     here_doc;
}           t_pipex;
```
- **`t_temp`** : Stocke des données temporaires (PID, statut).
```c
typedef struct s_temp
{
    pid_t   last_pid;
    int     cmd_count;
    int     last_status;
    int     status;
}           t_temp;
```

### Étapes principales
1. **Initialisation (`init_pipex`)** :
   - Vérifie les arguments et configure `t_pipex`, incluant le mode `here_doc`.

2. **Gestion de `here_doc` (`handle_here_doc`)** :
   - Crée un pipe temporaire et lit l'entrée utilisateur jusqu'au délimiteur.

3. **Lancement des processus (`launch_processes`)** :
   - Crée un processus pour chaque commande avec `fork_process`.
   - Attend la fin de tous les processus et récupère le statut du dernier.

4. **Processus enfant (`child_process`)** :
   - Redirige l'entrée depuis le fichier ou le pipe précédent.
   - Redirige la sortie vers le pipe suivant ou le fichier final.
   - Exécute la commande avec `execute`.

5. **Gestion des pipes** :
   - Chaque processus utilise un nouveau pipe, et le précédent est fermé.

### Cas particuliers
- **Mode `here_doc`** : Utilise `get_next_line` pour lire l'entrée jusqu'au délimiteur.
- **Fichier d'entrée absent** : Quitte avec une erreur si le fichier n'existe pas (sauf en mode `here_doc`).
- **Commandes avec guillemets** : Gérées par `ft_split_advanced`.

## Fonctions principales
- **`main`** : Point d'entrée, initialise et coordonne tout.
- **`fork_process`** : Crée un processus enfant avec un pipe.
- **`child_process`** : Configure les redirections et exécute une commande.
- **`handle_here_doc`** : Gère l'entrée dynamique.
- **`execute`** : Lance une commande avec `execve`.
- **`find_path`** : Trouve le chemin d'une commande dans `PATH`.

## Gestion des erreurs
- **`usage`** : Affiche un message si les arguments sont incorrects.
- **`error`** : Gère les erreurs système (ex. échec de `pipe`).
- **`error_127`** : Gère les commandes introuvables (code 127).

## Codes de sortie
- `0` : Succès.
- `1` : Erreur générale.
- `126` : Permission refusée.
- `127` : Commande non trouvée.

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** : Mars 2025

## Remerciements
Merci à l'école 42 pour ce projet enrichissant sur les pipes et les processus multiples.

---

English

---

# Pipex Bonus - README

## Description
Pipex Bonus is an advanced version of the Pipex project from the 42 school curriculum. It simulates a Unix pipeline with support for multiple commands and the `here_doc` mode. It can replicate behaviors like:
```bash
< file1 cmd1 | cmd2 | cmd3 > file2
```
or with `here_doc`:
```bash
here_doc LIMITER cmd1 cmd2 file
```
The program reads an input (file or user input with `here_doc`), executes a series of commands connected by pipes, and writes the final result to an output file.

The main goals are:
- Advanced process management with `fork`.
- Use of multiple pipes to link several commands.
- Support for `here_doc` for dynamic input.
- Input/output redirection with `dup2`.
- Command execution with `execve`.
- Robust error handling.

## Project Structure
The project is organized into several files for optimal modularity:
- **`main_bonus.c`**: Main logic (initialization, process launching).
- **`pipex_bonus.c`**: Child process management, pipes, and `here_doc`.
- **`utils_bonus.c`**: Utility functions for finding and executing commands.
- **`ft_split_advanced_bonus.c`**: Argument splitting with quote support.
- **`error_bonus.c`**: Error handling and messages.
- **`pipex_bonus.h`**: Structure definitions and prototypes.
- **`Libft/`**: Personal library for utility functions.

## Prerequisites
- A Unix-like system (Linux, macOS).
- A C compiler (e.g., `gcc`).
- Standard libraries (`unistd.h`, `fcntl.h`, etc.).
- `Libft` and `get_next_line` libraries (included in the project).

## Compilation
To compile, run this command in the root directory:
```bash
make bonus
```
This generates the `pipex_bonus` executable. Ensure `Libft` and `get_next_line` are compiled.

## Usage
The program accepts a variable number of arguments depending on the mode:
1. **Standard Mode** (minimum 5 arguments):
```bash
./pipex_bonus file1 cmd1 cmd2 ... cmdN file2
```
- `file1`: Input file.
- `cmd1` to `cmdN`: Commands to execute sequentially.
- `file2`: Output file.

2. **Here_doc Mode** (minimum 6 arguments):
```bash
./pipex_bonus here_doc LIMITER cmd1 cmd2 ... cmdN file
```
- `here_doc`: Keyword to enable this mode.
- `LIMITER`: Delimiter to stop input.
- `cmd1` to `cmdN`: Commands to execute.
- `file`: Output file.

### Examples
1. Multi-command pipeline:
```bash
./pipex_bonus infile "cat" "grep error" "wc -l" outfile
```
- Reads `infile`, filters lines with "error", counts them, and writes to `outfile`.

2. Here_doc mode:
```bash
./pipex_bonus here_doc END "cat" "wc -w" outfile
```
- Reads user input until "END", counts words, and writes to `outfile`.

3. Non-existent input file:
```bash
./pipex_bonus nonexistent "ls -l" "wc -l" outfile
```
- If `nonexistent` doesn’t exist, exits with an error.

## Detailed Functionality
### Structures
- **`t_pipex`**: Holds core data (arguments, files, pipes, flags).
```c
typedef struct s_pipex
{
    char    **argv;
    char    **envp;
    char    *filein;
    char    *fileout;
    int     fd[2];
    int     prev_fd;
    int     is_first;
    int     is_last;
    int     here_doc;
}           t_pipex;
```
- **`t_temp`**: Stores temporary data (PID, status).
```c
typedef struct s_temp
{
    pid_t   last_pid;
    int     cmd_count;
    int     last_status;
    int     status;
}           t_temp;
```

### Main Steps
1. **Initialization (`init_pipex`)**:
   - Checks arguments and sets up `t_pipex`, including `here_doc` mode.

2. **Here_doc Handling (`handle_here_doc`)**:
   - Creates a temporary pipe and reads user input until the delimiter.

3. **Process Launching (`launch_processes`)**:
   - Creates a process for each command via `fork_process`.
   - Waits for all processes to finish and retrieves the last status.

4. **Child Process (`child_process`)**:
   - Redirects input from the file or previous pipe.
   - Redirects output to the next pipe or final file.
   - Executes the command with `execute`.

5. **Pipe Management**:
   - Each process uses a new pipe, closing the previous one.

### Special Cases
- **Here_doc Mode**: Uses `get_next_line` to read input until the delimiter.
- **Missing Input File**: Exits with an error if the file doesn’t exist (except in `here_doc`).
- **Quoted Commands**: Handled by `ft_split_advanced`.

## Key Functions
- **`main`**: Entry point, initializes and coordinates everything.
- **`fork_process`**: Creates a child process with a pipe.
- **`child_process`**: Sets up redirections and executes a command.
- **`handle_here_doc`**: Manages dynamic input.
- **`execute`**: Runs a command with `execve`.
- **`find_path`**: Finds a command’s path in `PATH`.

## Error Handling
- **`usage`**: Displays a message for incorrect arguments.
- **`error`**: Handles system errors (e.g., pipe failure).
- **`error_127`**: Manages "command not found" errors (code 127).

## Exit Codes
- `0`: Success.
- `1`: General error.
- `126`: Permission denied.
- `127`: Command not found.

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**: March 2025

## Acknowledgments
Thanks to 42 school for this enriching project on pipes and multi-process management.
