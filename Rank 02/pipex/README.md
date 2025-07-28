# Pipex - README

---

## Description
Pipex est un projet réalisé dans le cadre du cursus de l'école 42. Il vise à initier les étudiants aux mécanismes UNIX de gestion des pipes en recréant le comportement de la redirection de flux dans un shell. Le programme `pipex` simule l'exécution de commandes shell avec des pipes, en prenant en entrée un fichier, une ou plusieurs commandes, et en redirigeant la sortie vers un fichier de destination. Ce projet explore les concepts de gestion des processus, des descripteurs de fichiers, et des pipes en C.

L'objectif est de maîtriser les concepts suivants :
- Programmation en C avec manipulation des pipes et des processus (fork, execve).
- Gestion des descripteurs de fichiers (dup, dup2).
- Gestion des erreurs et des fuites de mémoire.
- Compréhension des mécanismes UNIX de redirection de flux.
- Implémentation des bonus pour gérer plusieurs pipes et le mode `here_doc`.

## Structure du projet
Le projet est organisé comme suit :
- **Dossier principal** : Contient les fichiers sources (*.c, *.h) et le Makefile pour le programme `pipex`.
- **Dossier bonus (optionnel)** : Contient les fichiers pour les fonctionnalités bonus (multi-pipes et `here_doc`).
- **Dossier libft** : Contient la bibliothèque libft pour les fonctions utilitaires (ex. : `ft_printf`).

Les fichiers clés incluent :
- **Sources C** : Fichiers pour la gestion des pipes, l'exécution des commandes, et la redirection des flux.
- **Makefile** : Pour compiler les programmes avec les flags `-Wall`, `-Wextra`, `-Werror`.
- **Libft** : Bibliothèque personnalisée pour les fonctions utilitaires.

## Prérequis
- Un environnement Linux/Unix pour compiler et exécuter le programme.
- Connaissances de base en programmation C (gestion des processus, des pipes, et des descripteurs de fichiers).
- Compilateur compatible avec C99 (gcc, clang).
- Connaissance des mécanismes UNIX (pipes, redirections, fork, execve).

## Installation
1. **Cloner le dépôt Git** :
   ```bash
   git clone <votre-dépôt-git>
   cd pipex
   ```
2. **Compiler la partie obligatoire** :
   ```bash
   make
   ```
   Produit l'exécutable `pipex`.
3. **Compiler la partie bonus (si implémentée)** :
   ```bash
   make bonus
   ```
   Produit l'exécutable `pipex` avec les fonctionnalités bonus.
4. **Nettoyer les fichiers objets** :
   ```bash
   make clean
   ```
5. **Recompiler tout** :
   ```bash
   make re
   ```

## Utilisation
### Commandes principales
1. **Lancer le programme pipex (partie obligatoire)** :
   ```bash
   ./pipex file1 cmd1 cmd2 file2
   ```
   Exemple :
   ```bash
   ./pipex infile "ls -l" "wc -l" outfile
   ```
   - `file1` : Fichier d'entrée.
   - `cmd1` : Première commande avec ses paramètres.
   - `cmd2` : Deuxième commande avec ses paramètres.
   - `file2` : Fichier de sortie.
   - Comportement équivalent à la commande shell : `< infile cmd1 | cmd2 > outfile`.

2. **Lancer le programme avec bonus (si implémenté)** :
   - **Multi-pipes** :
     ```bash
     ./pipex file1 cmd1 cmd2 ... cmdN file2
     ```
     Exemple :
     ```bash
     ./pipex infile "ls -l" "grep .txt" "wc -l" outfile
     ```
     - Comportement équivalent à : `< infile cmd1 | cmd2 | ... | cmdN > outfile`.
   - **Mode here_doc** :
     ```bash
     ./pipex here_doc LIMITER cmd1 cmd2 file
     ```
     Exemple :
     ```bash
     ./pipex here_doc EOF "cat" "wc -l" outfile
     ```
     - Lit l'entrée standard jusqu'à `LIMITER`, puis applique : `cmd1 | cmd2 > file`.

### Exemple de sortie
Pour `./pipex infile "ls -l" "wc -l" outfile` :
- Le contenu de `outfile` sera identique à celui produit par `< infile ls -l | wc -l > outfile`.

Pour `./pipex here_doc EOF "cat" "wc -l" outfile` :
- Lit l'entrée jusqu'à `EOF`, puis écrit le résultat de `cat | wc -l` dans `outfile`.

## Fonctionnement détaillé
### Partie obligatoire
- Le programme simule une pipeline à deux commandes : `< file1 cmd1 | cmd2 > file2`.
- **Étapes principales** :
  - Ouvre le fichier d'entrée (`file1`) en lecture.
  - Crée un pipe pour connecter la sortie de `cmd1` à l'entrée de `cmd2`.
  - Utilise `fork` pour créer deux processus :
    - Le processus enfant exécute `cmd1` (via `execve`), avec la sortie redirigée vers le pipe.
    - Le processus parent exécute `cmd2`, avec l'entrée lue depuis le pipe et la sortie redirigée vers `file2`.
  - Utilise `dup2` pour rediriger les descripteurs de fichiers (stdin, stdout).
  - Gère les erreurs (fichiers inaccessibles, commandes invalides) avec des messages via `perror` ou `strerror`.

### Partie bonus
- **Multi-pipes** :
  - Gère plusieurs commandes en chaîne (ex. : `cmd1 | cmd2 | cmd3`).
  - Crée un pipe pour chaque paire de commandes consécutives.
  - Utilise plusieurs processus (via `fork`) pour exécuter chaque commande.
  - Redirige correctement les entrées/sorties entre les pipes et vers le fichier de sortie.
- **Mode here_doc** :
  - Lit l'entrée standard jusqu'à ce que la ligne corresponde à `LIMITER`.
  - Stocke l'entrée dans un fichier temporaire ou un pipe.
  - Applique les commandes en chaîne, avec la sortie finale redirigée vers le fichier spécifié.
  - Comportement équivalent à : `cmd1 < LIMITER | cmd2 > file`.

### Makefile
Le Makefile inclut les règles suivantes :
- `all` : Compile le programme `pipex`.
- `clean` : Supprime les fichiers objets.
- `fclean` : Supprime les fichiers objets et l'exécutable.
- `re` : Recompile tout.
- `bonus` : Compile le programme avec les fonctionnalités bonus.

## Gestion des erreurs
- Vérifiez que le programme gère correctement les erreurs : fichiers inaccessibles, commandes introuvables, permissions refusées.
- Assurez-vous que le code respecte la Norme 42 (vérifié par `norminette`).
- Testez avec des cas limites : fichiers vides, commandes invalides, permissions restreintes.
- Les fuites de mémoire doivent être éliminées (vérifié avec `valgrind` ou équivalent).
- Les descripteurs de fichiers (pipes, fichiers) doivent être fermés correctement.

## Limitations
- Les variables globales sont interdites.
- Les erreurs non gérées (segmentation fault, double free, etc.) entraînent une note de 0.
- Le programme doit respecter la Norme 42, sinon la note est 0.
- Les fonctions autorisées sont limitées à : `open`, `close`, `read`, `write`, `malloc`, `free`, `perror`, `strerror`, `access`, `dup`, `dup2`, `execve`, `exit`, `fork`, `pipe`, `unlink`, `wait`, `waitpid`, et les fonctions de `libft` (ex. : `ft_printf`).

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** : Février 2025 - Février 2025

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis d'explorer les mécanismes UNIX de gestion des pipes et des processus, tout en approfondissant mes compétences en programmation C et en gestion des descripteurs de fichiers.

---

# Pipex - README

## Description
Pipex is a project developed as part of the 42 school curriculum. It introduces students to UNIX mechanisms for handling pipes by recreating the behavior of shell command redirection. The `pipex` program simulates the execution of shell commands with pipes, taking an input file, one or more commands, and redirecting the output to a destination file. This project explores process management, file descriptors, and pipes in C.

The goal is to master the following concepts:
- Programming in C with pipe and process management (fork, execve).
- Managing file descriptors (dup, dup2).
- Handling errors and memory leaks.
- Understanding UNIX mechanisms for stream redirection.
- Implementing bonuses for multiple pipes and `here_doc` mode.

## Project Structure
The project is organized as follows:
- **Main Directory**: Contains source files (*.c, *.h) and the Makefile for the `pipex` program.
- **Bonus Directory (optional)**: Contains files for bonus features (multi-pipes and `here_doc`).
- **Libft Directory**: Contains the libft library for utility functions (e.g., `ft_printf`).

Key files include:
- **C Source Files**: Files for pipe management, command execution, and stream redirection.
- **Makefile**: To compile programs with `-Wall`, `-Wextra`, `-Werror` flags.
- **Libft**: Custom library for utility functions.

## Prerequisites
- A Linux/Unix environment to compile and run the program.
- Basic knowledge of C programming (process management, pipes, file descriptors).
- A C99-compatible compiler (gcc, clang).
- Understanding of UNIX mechanisms (pipes, redirections, fork, execve).

## Installation
1. **Clone the Git repository**:
   ```bash
   git clone <your-git-repository>
   cd pipex
   ```
2. **Compile the mandatory part**:
   ```bash
   make
   ```
   Produces the `pipex` executable.
3. **Compile the bonus part (if implemented)**:
   ```bash
   make bonus
   ```
   Produces the `pipex` executable with bonus features.
4. **Clean object files**:
   ```bash
   make clean
   ```
5. **Recompile everything**:
   ```bash
   make re
   ```

## Usage
### Key Commands
1. **Run the pipex program (mandatory part)**:
   ```bash
   ./pipex file1 cmd1 cmd2 file2
   ```
   Example:
   ```bash
   ./pipex infile "ls -l" "wc -l" outfile
   ```
   - `file1`: Input file.
   - `cmd1`: First command with its parameters.
   - `cmd2`: Second command with its parameters.
   - `file2`: Output file.
   - Equivalent to the shell command: `< infile cmd1 | cmd2 > outfile`.

2. **Run the program with bonuses (if implemented)**:
   - **Multi-pipes**:
     ```bash
     ./pipex file1 cmd1 cmd2 ... cmdN file2
     ```
     Example:
     ```bash
     ./pipex infile "ls -l" "grep .txt" "wc -l" outfile
     ```
     - Equivalent to: `< infile cmd1 | cmd2 | ... | cmdN > outfile`.
   - **Here_doc mode**:
     ```bash
     ./pipex here_doc LIMITER cmd1 cmd2 file
     ```
     Example:
     ```bash
     ./pipex here_doc EOF "cat" "wc -l" outfile
     ```
     - Reads stdin until `LIMITER`, then applies: `cmd1 | cmd2 > file`.

### Example Output
For `./pipex infile "ls -l" "wc -l" outfile`:
- The content of `outfile` will match the output of `< infile ls -l | wc -l > outfile`.

For `./pipex here_doc EOF "cat" "wc -l" outfile`:
- Reads input until `EOF`, then writes the result of `cat | wc -l` to `outfile`.

## Detailed Functionality
### Mandatory Part
- The program simulates a two-command pipeline: `< file1 cmd1 | cmd2 > file2`.
- **Key Steps**:
  - Opens the input file (`file1`) for reading.
  - Creates a pipe to connect the output of `cmd1` to the input of `cmd2`.
  - Uses `fork` to create two processes:
    - The child process executes `cmd1` (via `execve`), with output redirected to the pipe.
    - The parent process executes `cmd2`, with input read from the pipe and output redirected to `file2`.
  - Uses `dup2` to redirect file descriptors (stdin, stdout).
  - Handles errors (inaccessible files, invalid commands) using `perror` or `strerror`.

### Bonus Part
- **Multi-pipes**:
  - Handles multiple commands in a chain (e.g., `cmd1 | cmd2 | cmd3`).
  - Creates a pipe for each pair of consecutive commands.
  - Uses multiple processes (via `fork`) to execute each command.
  - Correctly redirects inputs/outputs between pipes and to the output file.
- **Here_doc mode**:
  - Reads stdin until the line matches `LIMITER`.
  - Stores input in a temporary file or pipe.
  - Applies commands in a chain, with the final output redirected to the specified file.
  - Equivalent to: `cmd1 < LIMITER | cmd2 > file`.

### Makefile
The Makefile includes:
- `all`: Compiles the `pipex` program.
- `clean`: Removes object files.
- `fclean`: Removes object files and the executable.
- `re`: Recompiles everything.
- `bonus`: Compiles the program with bonus features.

## Error Handling
- Ensure the program handles errors correctly: inaccessible files, invalid commands, permission denied.
- Verify code compliance with the 42 Norm (checked by `norminette`).
- Test with edge cases: empty files, invalid commands, restricted permissions.
- Eliminate memory leaks (checked with `valgrind` or equivalent).
- Properly close file descriptors (pipes, files).

## Limitations
- Global variables are forbidden.
- Unhandled errors (segmentation fault, double free, etc.) result in a grade of 0.
- The program must comply with the 42 Norm, or the grade is 0.
- Authorized functions are limited to: `open`, `close`, `read`, `write`, `malloc`, `free`, `perror`, `strerror`, `access`, `dup`, `dup2`, `execve`, `exit`, `fork`, `pipe`, `unlink`, `wait`, `waitpid`, and `libft` functions (e.g., `ft_printf`).

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**: February 2025 - February 2025

## Acknowledgments
Thanks to 42 school for this project, which allowed me to explore UNIX mechanisms for pipe and process management while deepening my skills in C programming and file descriptor handling.