Français

---

# Pipex - README

---

## Description
Pipex est un projet réalisé dans le cadre du cursus de l'école 42. Il simule le comportement d'un pipeline dans un shell Unix, comme la commande suivante :
```bash
< file1 cmd1 | cmd2 > file2
```
Le programme prend en entrée un fichier (`file1`), exécute une première commande (`cmd1`) avec ce contenu, passe la sortie de cette commande à une seconde commande (`cmd2`) via un pipe, puis écrit le résultat final dans un fichier de sortie (`file2`).

L'objectif est de maîtriser les concepts suivants :
- Gestion des processus avec `fork`.
- Utilisation des pipes pour la communication inter-processus.
- Redirection des entrées/sorties avec `dup2`.
- Exécution de commandes avec `execve`.
- Gestion des erreurs et des variables d'environnement.

## Structure du projet
Le projet est organisé en plusieurs fichiers pour une meilleure lisibilité et modularité :
- **`main.c`** : Contient la logique principale (initialisation, création des processus, gestion des pipes).
- **`utils.c`** : Fonctions utilitaires pour trouver les chemins des commandes et les exécuter.
- **`ft_split_advanced.c`** : Fonction pour séparer les arguments des commandes en respectant les guillemets.
- **`error.c`** : Gestion des erreurs et affichage des messages.
- **`pipex.h`** : Fichier d'en-tête avec les prototypes et la structure `t_pipex`.
- **`Libft/`** : Bibliothèque personnelle utilisée pour les fonctions comme `ft_split`, `ft_strjoin`, etc.

## Prérequis
- Un système Unix-like (Linux, macOS).
- Un compilateur compatible avec le standard C (ex. `gcc`).
- Les bibliothèques standard (`unistd.h`, `fcntl.h`, etc.).
- La bibliothèque `Libft` (incluse dans le projet).

## Compilation
Pour compiler le projet, exécutez la commande suivante dans le répertoire racine :
```bash
make
```
Cela générera un exécutable nommé `pipex`. Assurez-vous que la bibliothèque `Libft` est correctement compilée (elle est incluse dans le Makefile).

## Utilisation
Le programme prend exactement 5 arguments dans l'ordre suivant :
```bash
./pipex file1 cmd1 cmd2 file2
```
- `file1` : Fichier d'entrée contenant les données à traiter.
- `cmd1` : Première commande à exécuter (ex. `ls -l`, `cat`).
- `cmd2` : Seconde commande à exécuter (ex. `wc -l`, `grep "mot"`).
- `file2` : Fichier de sortie où le résultat sera écrit.

### Exemples
1. Compter les lignes d'un fichier :
```bash
./pipex infile "cat" "wc -l" outfile
```
- `cat` lit `infile` et passe son contenu à `wc -l`.
- `wc -l` compte les lignes et écrit le résultat dans `outfile`.

2. Filtrer des lignes contenant "error" :
```bash
./pipex infile "cat" "grep error" outfile
```
- `cat` lit `infile` et passe son contenu à `grep error`.
- `grep error` filtre les lignes contenant "error" et les écrit dans `outfile`.

3. Gestion d'un fichier d'entrée inexistant :
```bash
./pipex inexistant "ls -l" "wc -l" outfile
```
- Si `inexistant` n'existe pas, le programme utilise `/dev/null` comme entrée par défaut.

## Fonctionnement détaillé
### Structure `t_pipex`
La structure `t_pipex` contient toutes les données nécessaires au programme :
```c
typedef struct s_pipex
{
    char    **argv;     // Arguments passés au programme
    char    **envp;     // Variables d'environnement
    char    *filein;    // Fichier d'entrée
    char    *fileout;   // Fichier de sortie
    int     fd[2];      // Descripteurs de fichier pour le pipe
    int     is_first;   // Drapeau pour le premier processus
    int     is_last;    // Drapeau pour le dernier processus
}               t_pipex;
```

### Étapes principales
1. **Initialisation (`init_pipex`)** :
   - Vérifie que le nombre d'arguments est correct (5).
   - Configure la structure `t_pipex` avec les fichiers d'entrée/sortie et crée un pipe avec `pipe`.

2. **Création des processus (`fork_process`)** :
   - Deux processus enfants sont créés avec `fork` :
     - Le premier exécute `cmd1`.
     - Le second exécute `cmd2`.

3. **Redirection des entrées/sorties (`child_process`)** :
   - **Premier processus** :
     - Ouvre `file1` et redirige son contenu vers `STDIN`.
     - Redirige `STDOUT` vers l'extrémité d'écriture du pipe (`fd[1]`).
   - **Second processus** :
     - Lit depuis l'extrémité de lecture du pipe (`fd[0]`) via `STDIN`.
     - Redirige `STDOUT` vers `file2`.

4. **Exécution des commandes (`execute`)** :
   - Utilise `ft_split_advanced` pour séparer les arguments.
   - Recherche le chemin de la commande dans `PATH` avec `find_path`.
   - Exécute la commande avec `execve`.

5. **Gestion des erreurs** :
   - Si une commande n'est pas trouvée, le programme retourne le code 127.
   - Si une permission est refusée, il retourne 126.
   - Les erreurs système (ex. échec de `open`) sont affichées avec `perror`.

### Gestion des cas particuliers
- **Fichier d'entrée inexistant** : Si `file1` ne peut pas être ouvert, le programme utilise `/dev/null` comme entrée par défaut.
- **Commandes avec guillemets** : La fonction `ft_split_advanced` gère les arguments entourés de guillemets (ex. `"ls -l"`).
- **PATH absent** : Si la variable d'environnement `PATH` n'est pas définie, une liste par défaut (`/bin:/usr/bin:/usr/local/bin`) est utilisée.

## Fonctions principales
- **`main`** : Point d'entrée, initialise le programme et coordonne les processus.
- **`child_process`** : Gère les redirections et exécute les commandes dans les processus enfants.
- **`fork_process`** : Crée les processus enfants avec `fork`.
- **`execute`** : Prépare et exécute une commande avec `execve`.
- **`find_path`** : Recherche le chemin d'une commande dans `PATH`.
- **`ft_split_advanced`** : Sépare une chaîne en arguments en respectant les guillemets.

## Gestion des erreurs
- **`usage`** : Affiche un message si le nombre d'arguments est incorrect.
- **`error`** : Affiche une erreur système et quitte.
- **`error_127`** : Gère les erreurs "commande non trouvée" (code 127).

## Codes de sortie
- `0` : Succès.
- `1` : Erreur générale (ex. échec d'ouverture d'un fichier).
- `126` : Permission refusée pour exécuter une commande.
- `127` : Commande non trouvée.

## Limitations
- Le programme ne gère qu'un seul pipe (deux commandes). Pour plusieurs pipes, une version bonus serait nécessaire.
- Les commandes doivent être des exécutables valides ou des chemins absolus/relatifs.

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** : Mars 2025

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis de mieux comprendre les pipes, les processus et la gestion des entrées/sorties en C.

---

English

---

# Pipex - README

## Description
Pipex is a project developed as part of the 42 school curriculum. It simulates the behavior of a pipeline in a Unix shell, such as the following command:
```bash
< file1 cmd1 | cmd2 > file2
```
The program takes an input file (`file1`), executes a first command (`cmd1`) with its content, passes the output of that command to a second command (`cmd2`) through a pipe, and writes the final result to an output file (`file2`).

The goal is to master the following concepts:
- Process management with `fork`.
- Use of pipes for inter-process communication.
- Input/output redirection with `dup2`.
- Command execution with `execve`.
- Error handling and environment variable management.

## Project Structure
The project is organized into multiple files for better readability and modularity:
- **`main.c`**: Contains the main logic (initialization, process creation, pipe management).
- **`utils.c`**: Utility functions to find command paths and execute them.
- **`ft_split_advanced.c`**: Function to split command arguments while respecting quotes.
- **`error.c`**: Error handling and message display.
- **`pipex.h`**: Header file with function prototypes and the `t_pipex` structure.
- **`Libft/`**: Personal library used for functions like `ft_split`, `ft_strjoin`, etc.

## Prerequisites
- A Unix-like system (Linux, macOS).
- A C standard-compliant compiler (e.g., `gcc`).
- Standard libraries (`unistd.h`, `fcntl Godcha-style (`fcntl.h`, etc.).
- The `Libft` library (included in the project).

## Compilation
To compile the project, run the following command in the root directory:
```bash
make
```
This will generate an executable named `pipex`. Ensure the `Libft` library is properly compiled (included in the Makefile).

## Usage
The program requires exactly 5 arguments in the following order:
```bash
./pipex file1 cmd1 cmd2 file2
```
- `file1`: Input file containing the data to process.
- `cmd1`: First command to execute (e.g., `ls -l`, `cat`).
- `cmd2`: Second command to execute (e.g., `wc -l`, `grep "word"`).
- `file2`: Output file where the result will be written.

### Examples
1. Counting lines in a file:
```bash
./pipex infile "cat" "wc -l" outfile
```
- `cat` reads `infile` and passes its content to `wc -l`.
- `wc -l` counts the lines and writes the result to `outfile`.

2. Filtering lines containing "error":
```bash
./pipex infile "cat" "grep error" outfile
```
- `cat` reads `infile` and passes its content to `grep error`.
- `grep error` filters lines containing "error" and writes them to `outfile`.

3. Handling a non-existent input file:
```bash
./pipex nonexistent "ls -l" "wc -l" outfile
```
- If `nonexistent` doesn’t exist, the program uses `/dev/null` as a default input.

## Detailed Functionality
### `t_pipex` Structure
The `t_pipex` structure holds all necessary data for the program:
```c
typedef struct s_pipex
{
    char    **argv;     // Program arguments
    char    **envp;     // Environment variables
    char    *filein;    // Input file
    char    *fileout;   // Output file
    int     fd[2];      // File descriptors for the pipe
    int     is_first;   // Flag for the first process
    int     is_last;    // Flag for the last process
}               t_pipex;
```

### Main Steps
1. **Initialization (`init_pipex`)**:
   - Verifies the correct number of arguments (5).
   - Sets up the `t_pipex` structure with input/output files and creates a pipe using `pipe`.

2. **Process Creation (`fork_process`)**:
   - Two child processes are created with `fork`:
     - The first executes `cmd1`.
     - The second executes `cmd2`.

3. **Input/Output Redirection (`child_process`)**:
   - **First process**:
     - Opens `file1` and redirects its content to `STDIN`.
     - Redirects `STDOUT` to the pipe’s write end (`fd[1]`).
   - **Second process**:
     - Reads from the pipe’s read end (`fd[0]`) via `STDIN`.
     - Redirects `STDOUT` to `file2`.

4. **Command Execution (`execute`)**:
   - Uses `ft_split_advanced` to split arguments.
   - Finds the command path in `PATH` using `find_path`.
   - Executes the command with `execve`.

5. **Error Handling**:
   - Returns code 127 if a command is not found.
   - Returns code 126 if permission is denied.
   - System errors (e.g., `open` failure) are displayed with `perror`.

### Special Cases
- **Non-existent Input File**: If `file1` cannot be opened, `/dev/null` is used as a fallback input.
- **Quoted Commands**: `ft_split_advanced` handles arguments within quotes (e.g., `"ls -l"`).
- **Missing PATH**: If the `PATH` environment variable is undefined, a default list (`/bin:/usr/bin:/usr/local/bin`) is used.

## Key Functions
- **`main`**: Entry point, initializes the program and coordinates processes.
- **`child_process`**: Manages redirections and executes commands in child processes.
- **`fork_process`**: Creates child processes with `fork`.
- **`execute`**: Prepares and executes a command with `execve`.
- **`find_path`**: Searches for a command’s path in `PATH`.
- **`ft_split_advanced`**: Splits a string into arguments while respecting quotes.

## Error Handling
- **`usage`**: Displays a message if the argument count is incorrect.
- **`error`**: Displays a system error and exits.
- **`error_127`**: Handles "command not found" errors (code 127).

## Exit Codes
- `0`: Success.
- `1`: General error (e.g., file opening failure).
- `126`: Permission denied for command execution.
- `127`: Command not found.

## Limitations
- The program handles only one pipe (two commands). Multiple pipes require a bonus version.
- Commands must be valid executables or absolute/relative paths.

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**: March 2025

## Acknowledgments
Thanks to 42 school for this project, which helped me deepen my understanding of pipes, processes, and I/O management in C.
