# get_next_line - README

---

## Description
**get_next_line** est un projet de l'école 42 qui consiste à développer une fonction en C, `get_next_line()`, capable de lire une ligne à la fois depuis un descripteur de fichier (file descriptor, fd). Ce projet vise à approfondir la compréhension des variables statiques, de la gestion de la mémoire dynamique, et de la lecture de fichiers ou de l'entrée standard. La fonction doit être robuste, gérer différentes tailles de buffer via la macro `BUFFER_SIZE`, et éviter les fuites de mémoire. Une fois validée, `get_next_line()` peut être intégrée à la bibliothèque `libft` pour une utilisation dans d'autres projets du cursus.

Les objectifs principaux incluent :
- Maîtriser les variables statiques pour conserver l'état entre les appels.
- Gérer la lecture efficace d'un descripteur de fichier, ligne par ligne.
- Assurer une gestion rigoureuse de la mémoire allouée dynamiquement.
- Comprendre l'impact de la taille du buffer sur les performances.

## Structure du projet
- **Dossier principal** : `get_next_line/`
- **Fichiers obligatoires** :
  - `get_next_line.c` : Contient l'implémentation de la fonction principale.
  - `get_next_line.h` : Contient le prototype de la fonction et les définitions nécessaires.
  - `get_next_line_utils.c` : Contient les fonctions utilitaires nécessaires.
- **Fichiers bonus (si implémentés)** :
  - `get_next_line_bonus.c`
  - `get_next_line_bonus.h`
  - `get_next_line_utils_bonus.c`
- **Sortie** : Un programme de test ou une bibliothèque intégrable à `libft`.

## Prérequis
- Un système Unix-like (Linux, macOS).
- Un compilateur C compatible (ex. `gcc` ou `clang`).
- Fonctions autorisées : `read`, `malloc`, `free`.
- La macro `BUFFER_SIZE` définit la taille du buffer pour `read()` (modifiable lors de la compilation).
- La bibliothèque `libft` **n'est pas autorisée** pour ce projet.

## Compilation
Accédez au dossier du projet et exécutez :
```bash
make
```
Le `Makefile` doit compiler les fichiers sources avec les flags `-Wall -Wextra -Werror` et inclure la macro `-D BUFFER_SIZE=<n>` (ex. `-D BUFFER_SIZE=42`). Les règles obligatoires sont `$(NAME)`, `all`, `clean`, `fclean`, et `re`. Pour les bonus, une règle `bonus` doit compiler les fichiers bonus séparément.

Exemple de compilation :
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o test_gnl
```

## Utilisation
La fonction `get_next_line` a le prototype suivant :
```c
char *get_next_line(int fd);
```

Elle retourne :
- Une chaîne de caractères contenant la ligne lue (incluant `\n` sauf à la fin du fichier).
- `NULL` si plus rien à lire ou en cas d'erreur.

Exemple d'utilisation :
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

### Exemple de fichier `test.txt` :
```
Hello, world!
This is a test.
Last line.
```

### Sortie :
```
Hello, world!
This is a test.
Last line.
```

## Fonctionnement détaillé
### Partie obligatoire
- **Prototype** : `char *get_next_line(int fd);`
- **Fonctionnement** :
  - Lit une ligne depuis le descripteur de fichier `fd` (fichier, entrée standard, etc.).
  - Utilise une variable statique pour stocker le contenu résiduel entre les appels.
  - Retourne la ligne lue (incluant `\n` sauf si la fin du fichier ne contient pas de `\n`).
  - Retourne `NULL` en cas d'erreur ou si plus rien à lire.
  - Gère la lecture avec un buffer de taille `BUFFER_SIZE`, qui peut être 1, 9999, ou 10000000.
- **Contraintes** :
  - Fonctions autorisées : `read`, `malloc`, `free`.
  - Doit fonctionner pour les fichiers et l'entrée standard (`fd = 0`).
  - Doit gérer correctement la fin de fichier (EOF) et les erreurs de lecture.
  - La lecture doit être minimale : ne lire que ce qui est nécessaire pour retourner une ligne.
  - Comportement indéfini si :
    - Le descripteur de fichier change entre deux appels avant que le fichier ne soit lu entièrement.
    - Le fichier est binaire (optionnel : rendre le comportement cohérent).
- **Interdictions** :
  - Utilisation de `libft`.
  - Utilisation de `lseek()`.
  - Variables globales.

### Partie bonus
- **Objectifs** :
  - Utiliser **une seule variable statique** pour gérer plusieurs descripteurs de fichier.
  - Permettre la lecture alternée de plusieurs `fd` (ex. `fd 3`, `fd 4`, `fd 5`) sans perdre le contenu ou mélanger les lignes.
- **Fichiers** :
  - `get_next_line_bonus.c`
  - `get_next_line_bonus.h`
  - `get_next_line_utils_bonus.c`
- **Exemple** :
  - Appeler `get_next_line(3)`, puis `get_next_line(4)`, puis `get_next_line(3)` doit retourner les bonnes lignes pour chaque `fd`.
- Les bonus ne sont évalués que si la partie obligatoire est parfaite (aucun dysfonctionnement).

## Gestion des erreurs
- Retourne `NULL` pour :
  - Erreurs de lecture (ex. `read` échoue).
  - Descripteur de fichier invalide (`fd < 0`).
  - Fin de fichier atteinte (EOF).
- Toute mémoire allouée doit être libérée pour éviter les fuites.
- Pas de segmentation fault, bus error, ou double free.

## Codes de sortie
- La fonction `get_next_line` retourne :
  - Une chaîne (succès, ligne lue).
  - `NULL` (erreur ou EOF).
- Les programmes de test doivent quitter proprement.

## Limitations
- Écrit en **C** uniquement, conforme à **la Norme** de l'école 42.
- Fonctions autorisées : `read`, `malloc`, `free`.
- Pas de `libft`, `lseek()`, ou variables globales.
- Doit gérer différentes tailles de `BUFFER_SIZE` (1, 9999, 10000000, etc.).
- Le `Makefile` ne doit pas relinker inutilement.
- Pas de crashes inattendus (segmentation fault, bus error, double free).

## Règles spécifiques
- La fonction doit être nommée `get_next_line`.
- Les fichiers obligatoires sont `get_next_line.c`, `get_next_line.h`, `get_next_line_utils.c`.
- Les fichiers bonus doivent avoir le suffixe `_bonus` (ex. `get_next_line_bonus.c`).
- Le `Makefile` doit inclure les règles `$(NAME)`, `all`, `clean`, `fclean`, `re`, et `bonus` pour les bonus.
- La compilation doit supporter la macro `-D BUFFER_SIZE=<n>`.

## Bonus
- Gérer plusieurs descripteurs de fichier avec une seule variable statique.
- Lire alternativement plusieurs `fd` sans perte de données ou confusion des lignes.

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** : Juillet 2025

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis de maîtriser les variables statiques, la gestion de la mémoire, et la lecture efficace de fichiers en C.

---

# get_next_line - README

## Description
**get_next_line** is a project from 42 school that involves developing a C function, `get_next_line()`, capable of reading a line at a time from a file descriptor (fd). The project aims to deepen understanding of static variables, dynamic memory management, and file reading. The function must be robust, handle different buffer sizes via the `BUFFER_SIZE` macro, and avoid memory leaks. Once validated, `get_next_line()` can be integrated into the `libft` library for use in other curriculum projects.

Key objectives include:
- Mastering static variables to maintain state between calls.
- Efficiently reading a file descriptor line by line.
- Ensuring rigorous dynamic memory management.
- Understanding the impact of buffer size on performance.

## Project Structure
- **Main directory**: `get_next_line/`
- **Mandatory files**:
  - `get_next_line.c`: Contains the main function implementation.
  - `get_next_line.h`: Contains the function prototype and necessary definitions.
  - `get_next_line_utils.c`: Contains required utility functions.
- **Bonus files (if implemented)**:
  - `get_next_line_bonus.c`
  - `get_next_line_bonus.h`
  - `get_next_line_utils_bonus.c`
- **Output**: A test program or a library integrable into `libft`.

## Prerequisites
- A Unix-like system (Linux, macOS).
- A compatible C compiler (e.g., `gcc` or `clang`).
- Allowed functions: `read`, `malloc`, `free`.
- The `BUFFER_SIZE` macro defines the buffer size for `read()` (modifiable at compile time).
- The `libft` library **is not allowed** for this project.

## Compilation
Navigate to the project directory and run:
```bash
make
```
The `Makefile` must compile source files with the flags `-Wall -Wextra -Werror` and include the macro `-D BUFFER_SIZE=<n>` (e.g., `-D BUFFER_SIZE=42`). Mandatory rules are `$(NAME)`, `all`, `clean`, `fclean`, and `re`. For bonuses, a `bonus` rule must compile the bonus files separately.

Example compilation:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o test_gnl
```

## Usage
The `get_next_line` function has the following prototype:
```c
char *get_next_line(int fd);
```

It returns:
- A string containing the read line (including `\n` unless the file ends without one).
- `NULL` if nothing remains to read or an error occurs.

Example usage:
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

### Example file `test.txt`:
```
Hello, world!
This is a test.
Last line.
```

### Output:
```
Hello, world!
This is a test.
Last line.
```

## Detailed Functionality
### Mandatory Part
- **Prototype**: `char *get_next_line(int fd);`
- **Functionality**:
  - Reads a line from the file descriptor `fd` (file, standard input, etc.).
  - Uses a static variable to store residual content between calls.
  - Returns the read line (including `\n` unless the file ends without one).
  - Returns `NULL` on error or if nothing remains to read.
  - Handles reading with a buffer of size `BUFFER_SIZE`, which can be 1, 9999, or 10000000.
- **Constraints**:
  - Allowed functions: `read`, `malloc`, `free`.
  - Must work for files and standard input (`fd = 0`).
  - Must properly handle end-of-file (EOF) and read errors.
  - Reading must be minimal: only read what is needed to return a line.
  - Undefined behavior if:
    - The file descriptor changes between calls before the file is fully read.
    - The file is binary (optional: make the behavior consistent).
- **Prohibitions**:
  - Use of `libft`.
  - Use of `lseek()`.
  - Global variables.

### Bonus Part
- **Objectives**:
  - Use **a single static variable** to handle multiple file descriptors.
  - Allow alternating reads from multiple `fd`s (e.g., `fd 3`, `fd 4`, `fd 5`) without losing content or mixing lines.
- **Files**:
  - `get_next_line_bonus.c`
  - `get_next_line_bonus.h`
  - `get_next_line_utils_bonus.c`
- **Example**:
  - Calling `get_next_line(3)`, then `get_next_line(4)`, then `get_next_line(3)` must return the correct lines for each `fd`.
- Bonuses are only evaluated if the mandatory part is perfect (no issues).

## Error Handling
- Returns `NULL` for:
  - Read errors (e.g., `read` fails).
  - Invalid file descriptor (`fd < 0`).
  - End-of-file (EOF).
- All allocated memory must be freed to prevent leaks.
- No segmentation faults, bus errors, or double frees.

## Exit Codes
- The `get_next_line` function returns:
  - A string (success, line read).
  - `NULL` (error or EOF).
- Test programs must exit cleanly.

## Limitations
- Written in **C** only, adhering to 42’s **Norme**.
- Allowed functions: `read`, `malloc`, `free`.
- No `libft`, `lseek()`, or global variables.
- Must handle various `BUFFER_SIZE` values (1, 9999, 10000000, etc.).
- The `Makefile` must not relink unnecessarily.
- No unexpected crashes (segmentation fault, bus error, double free).

## Specific Rules
- The function must be named `get_next_line`.
- Mandatory files are `get_next_line.c`, `get_next_line.h`, `get_next_line_utils.c`.
- Bonus files must have the `_bonus` suffix (e.g., `get_next_line_bonus.c`).
- The `Makefile` must include the rules `$(NAME)`, `all`, `clean`, `fclean`, `re`, and `bonus` for bonuses.
- Compilation must support the `-D BUFFER_SIZE=<n>` macro.

## Bonuses
- Handle multiple file descriptors with a single static variable.
- Read alternately from multiple `fd`s without data loss or line confusion.

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**: July 2025

## Acknowledgments
Thanks to 42 school for this project, which allowed me to master static variables, memory management, and efficient file reading in C.