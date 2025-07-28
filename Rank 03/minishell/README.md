# Minishell - README

---

## Description
**Minishell** est un projet de l'école 42 visant à créer un shell simplifié en C, inspiré du comportement de **bash**. L'objectif est de reproduire les fonctionnalités de base d'un shell Unix, telles que l'exécution de commandes, la gestion des redirections, des pipes, des variables d'environnement, et l'historique des commandes. Ce projet permet de comprendre le fonctionnement interne des shells, la gestion des processus, et les interactions avec le système d'exploitation, tout en respectant la Norme de 42.

Les objectifs principaux incluent :
- Implémenter un shell capable d'exécuter des commandes simples et complexes.
- Gérer les redirections (`<`, `>`, `>>`), les pipes (`|`), et les variables d'environnement.
- Reproduire le comportement de **bash** pour certaines fonctionnalités clés (par exemple, `ctrl-C`, `ctrl-D`, `ctrl-\`).
- (Bonus) Ajouter des fonctionnalités avancées comme l'édition de lignes, la gestion des wildcards, et les opérateurs logiques (`&&`, `||`).

## Structure du projet
- **Dossier principal** : `minishell/`
- **Fichiers principaux** :
  - `Makefile`
  - `minishell.h` : Fichier d'en-tête contenant les prototypes et structures.
  - Fichiers sources (ex. `*.c`) pour la logique du shell, le parsing, et l'exécution.
- **Sortie** : Un exécutable nommé `minishell`.
- **Dossier libft** (si utilisé) : Contient les sources et le `Makefile` de la bibliothèque `libft`.

## Prérequis
- Un système Unix-like (Linux, macOS).
- Un compilateur C compatible (ex. `gcc` ou `clang`).
- Bibliothèque `termcap` pour l'historique et l'édition de lignes.
- Fonctions externes autorisées : celles de la `libc`, `termcap`, et `libft` (si incluse).
- Aucune bibliothèque externe autre que `libft` n'est autorisée.

## Compilation
Accédez au dossier du projet et exécutez :
```bash
make
```
Cela génère l'exécutable `minishell`. Le `Makefile` doit inclure les règles `$(NAME)`, `all`, `clean`, `fclean`, et `re`, et compiler avec les flags `-Wall -Wextra -Werror`. Si `libft` est utilisé, le `Makefile` doit d'abord compiler la bibliothèque `libft.a` avant de lier le projet.

Pour les bonus :
```bash
make bonus
```

## Utilisation
Exécutez le shell avec :
```bash
./minishell
```
Vous entrez dans une interface interactive où vous pouvez saisir des commandes comme dans **bash**. Exemple :
```bash
$> ls -l | grep .c
$> echo $PATH
$> export MY_VAR=hello
$> echo $MY_VAR > output.txt
```

### Fonctionnalités obligatoires
- **Interprétation des commandes** :
  - Exécute les commandes simples (ex. `ls`, `echo`, `pwd`).
  - Gère les commandes avec des arguments et les chemins relatifs/absolus.
- **Séparateurs** :
  - Le caractère `;` sépare les commandes dans la ligne de commande.
- **Redirections** :
  - `<` : Redirection d'entrée.
  - `>` : Redirection de sortie (écrase).
  - `>>` : Redirection de sortie (ajoute).
  - Pas de gestion des agrégations de descripteurs de fichiers.
- **Pipes** :
  - `|` : Redirige la sortie d'une commande vers l'entrée d'une autre.
- **Variables d'environnement** :
  - Gestion des variables (ex. `$PATH`, `$HOME`) comme dans **bash**.
  - `$?` pour le code de retour de la dernière commande.
- **Signaux** :
  - `ctrl-C` : Affiche une nouvelle ligne de prompt.
  - `ctrl-D` : Quitte le shell si aucune commande n'est en cours.
  - `ctrl-\` : Ignore (comme dans **bash**).
- **Commandes intégrées (builtins)** :
  - `echo` (avec option `-n`).
  - `cd` (gère les chemins relatifs et absolus).
  - `pwd` (affiche le répertoire courant).
  - `export` (ajoute/modifie des variables d'environnement).
  - `unset` (supprime des variables d'environnement).
  - `env` (affiche les variables d'environnement).
  - `exit` (quitte le shell avec un code de retour optionnel).
- **Historique** :
  - Utilisation de `termcap` pour naviguer dans l'historique des commandes avec les touches `haut` et `bas`.
  - Édition en ligne des commandes (sans modifier l'historique).

### Fonctionnalités bonus
- **Redirection avancée** :
  - Gestion de `<<` (heredoc) comme dans **bash**.
- **Édition de ligne avancée** (avec `termcap`) :
  - Déplacer le curseur à gauche/droite pour éditer une ligne.
  - Copier, couper, coller une partie ou toute la ligne avec des séquences de touches personnalisées.
  - Déplacement mot par mot avec `Ctrl+Left` et `Ctrl+Right`.
  - Aller au début/fin de la ligne avec `Home` et `End`.
  - Édition multiligne avec navigation via `Ctrl+Up` et `Ctrl+Down`.
- **Opérateurs logiques** :
  - `&&` : Exécute la commande suivante si la précédente réussit.
  - `||` : Exécute la commande suivante si la précédente échoue.
  - Gestion des priorités avec parenthèses `( )`.
- **Wildcards** :
  - Gestion du caractère `*` pour correspondre à des motifs dans les noms de fichiers, comme dans **bash**.

## Gestion des erreurs
- Les fonctions doivent gérer les cas limites (ex. pointeurs NULL, erreurs d'allocation, commandes invalides).
- Aucun crash inattendu (segmentation fault, bus error, double free).
- Toute mémoire allouée sur le tas doit être libérée pour éviter les fuites.
- Affichage des messages d'erreur clairs, similaires à ceux de **bash**.

## Codes de sortie
- Le shell retourne le code de sortie de la dernière commande exécutée via `$?`.
- Les builtins doivent retourner des codes appropriés (ex. 0 pour succès, 1 pour erreur générale).
- Le programme doit quitter proprement avec `exit`.

## Limitations
- Écrit en **C**, conforme à la Norme de 42.
- Fonctions autorisées : celles de la `libc`, `termcap`, et `libft` (si incluse).
- Interdiction des variables globales, sauf si justifiées (ex. variables d'environnement).
- Pas de comportements indéfinis ou de fuites de mémoire.
- Le `Makefile` ne doit pas relinker inutilement.
- Pas de gestion des agrégations de descripteurs de fichiers ou du multiligne pour les wildcards.

## Règles spécifiques
- Le programme doit être nommé `minishell`.
- Les fichiers sources doivent être à la racine du dépôt (sauf `libft/` si utilisé).
- Le `Makefile` doit inclure les règles `$(NAME)`, `all`, `clean`, `fclean`, `re`, et `bonus` (pour les bonus).
- Si `libft` est utilisé, copier ses sources et son `Makefile` dans un dossier `libft/` à la racine.
- Les bonus doivent être dans des fichiers séparés (ex. `*_bonus.c`) et compilés via `make bonus`.
- Les programmes de test sont recommandés mais non rendus.
- Le rendu doit être soumis via le dépôt git assigné.

## Bonus
- Implémentation de fonctionnalités avancées comme les heredocs, l'édition de ligne avancée, les opérateurs logiques, et les wildcards.
- Les bonus sont évalués uniquement si la partie obligatoire est parfaite.

## Exemple de commandes
```bash
$> ls -l | grep .c > output.txt
$> echo -n "Hello" && echo "World"
$> export MY_VAR=42
$> echo $MY_VAR
$> cd .. && pwd
$> *.c (affiche les fichiers .c dans le répertoire courant)
```

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** : Juillet 2025

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis d'explorer le fonctionnement des shells Unix, de maîtriser la gestion des processus, et de perfectionner mes compétences en programmation C.

---

# Minishell - README

---

## Description
**Minishell** is a project from School 42 that aims to create a simplified shell in C, inspired by the behavior of **bash**. The goal is to reproduce the basic features of a Unix shell, such as command execution, redirection management, pipes, environment variables, and command history. This project provides an understanding of the internal workings of shells, process management, and interactions with the operating system, while complying with the 42 Standard.

The main objectives include:
- Implementing a shell capable of executing simple and complex commands.
- Managing redirections (`<`, `>`, `>>`), pipes (`|`), and environment variables.
- Reproducing the behavior of **bash** for certain key features (e.g., `ctrl-C`, `ctrl-D`, `ctrl-\`).
- (Bonus) Add advanced features such as line editing, wildcard handling, and logical operators (`&&`, `||`).

## Project structure
- **Main folder**: `minishell/`
- **Main files**:
  - `Makefile`
  - `minishell.h`: Header file containing prototypes and structures.
  - Source files (e.g., `*.c`) for shell logic, parsing, and execution.
- **Output**: An executable named `minishell`.
- **libft folder** (if used): Contains the sources and `Makefile` for the `libft` library.

## Prerequisites
- A Unix-like system (Linux, macOS).
- A compatible C compiler (e.g., `gcc` or `clang`).
- `termcap` library for history and line editing.
- Allowed external functions: those from `libc`, `termcap`, and `libft` (if included).
- No external libraries other than `libft` are allowed.

## Compilation
Go to the project folder and run:
```bash
make
```
This generates the `minishell` executable. The `Makefile` must include the rules `$(NAME)`, `all`, `clean`, `fclean`, and `re`, and compile with the flags `-Wall -Wextra -Werror`. If `libft` is used, the `Makefile` must first compile the `libft.a` library before linking the project.

For bonuses:
```bash
make bonus
```

## Usage
Run the shell with:
```bash
./minishell
```
You enter an interactive interface where you can enter commands as in **bash**. Example:
```bash
$> ls -l | grep .c
$> echo $PATH
$> export MY_VAR=hello
$> echo $MY_VAR > output.txt
```

### Mandatory features
- **Command interpretation**:
  - Executes simple commands (e.g., `ls`, `echo`, `pwd`).
  - Handles commands with arguments and relative/absolute paths.
- **Separators**:
  - The `;` character separates commands in the command line.
- **Redirections**:
  - `<`: Input redirection.
  - `>`: Output redirection (overwrite).
  - `>>`: Output redirection (append).
  - No handling of file descriptor aggregation.
- **Pipes**:
  - `|`: Redirects the output of one command to the input of another.
- **Environment variables**:
  - Variable management (e.g., `$PATH`, `$HOME`) as in **bash**.
  - `$?` for the return code of the last command.
- **Signals**:
  - `ctrl-C`: Displays a new prompt line.
  - `ctrl-D`: Exits the shell if no command is in progress.
  - `ctrl-\`: Ignores (as in **bash**).
- **Built-in commands (builtins)**:
  - `echo` (with the `-n` option).
  - `cd` (handles relative and absolute paths).
  - `pwd` (displays the current directory).
  - `export` (adds/modifies environment variables).
  - `unset` (deletes environment variables).
  - `env` (displays environment variables).
  - `exit` (exits the shell with an optional return code).
- **History**:
  - Use `termcap` to navigate through the command history with the `up` and `down` keys.
  - Edit commands online (without modifying the history).

### Bonus features
- **Advanced redirection**:
  - Support for `<<` (heredoc) as in **bash**.
- **Advanced line editing** (with `termcap`):
  - Move the cursor left/right to edit a line.
  - Copy, cut, paste part or all of the line with custom key sequences.
  - Move word by word with `Ctrl+Left` and `Ctrl+Right`.
  - Go to the beginning/end of the line with `Home` and `End`.
  - Multi-line editing with navigation via `Ctrl+Up` and `Ctrl+Down`.
- **Logical operators**:
  - `&&`: Executes the next command if the previous one succeeds.
  - `||`: Executes the next command if the previous one fails.
  - Priority management with parentheses `( )`.
- **Wildcards**:
  - Management of the `*` character to match patterns in file names, as in **bash**.

## Error handling
- Functions must handle edge cases (e.g., NULL pointers, allocation errors, invalid commands).
- No unexpected crashes (segmentation fault, bus error, double free).
- All memory allocated on the heap must be freed to avoid leaks.
- Display clear error messages, similar to those in **bash**.

## Exit codes
- The shell returns the exit code of the last command executed via `$?`.
- Builtins must return appropriate codes (e.g., 0 for success, 1 for general error).
- The program must exit cleanly with `exit`.

## Limitations
- Written in **C**, compliant with the 42 Standard.
- Authorized functions: those of `libc`, `termcap`, and `libft` (if included).
- Global variables are prohibited, unless justified (e.g., environment variables).
- No undefined behavior or memory leaks.
- The `Makefile` must not relink unnecessarily.
- No handling of file descriptor aggregation or multi-line wildcards.

## Specific rules
- The program must be named `minishell`.
- Source files must be at the root of the repository (except `libft/` if used).
- The `Makefile` must include the rules `$(NAME)`, `all`, `clean`, `fclean`, `re`, and `bonus` (for bonuses).
- If `libft` is used, copy its sources and `Makefile` to a `libft/` folder at the root.
- Bonuses must be in separate files (e.g., `*_bonus.c`) and compiled via `make bonus`.
- Test programs are recommended but not graded.
- Submissions must be submitted via the assigned git repository.

## Bonus
- Implementation of advanced features such as heredocs, advanced line editing, logical operators, and wildcards.
- Bonuses are only evaluated if the mandatory part is perfect.

## Example commands
```bash
$> ls -l | grep .c > output.txt
$> echo -n “Hello” && echo “World”
$> export MY_VAR=42
$> echo $MY_VAR
$> cd .. && pwd
$> *.c (displays .c files in the current directory)
```

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**: July 2025

## Acknowledgments
Thank you to 42 School for this project, which allowed me to explore how Unix shells work, master process management, and hone my C programming skills.
