# Libft - README

---

## Description
**Libft** est un projet de l'école 42 qui consiste à créer une bibliothèque statique en C, nommée `libft.a`, regroupant des fonctions usuelles pour les projets futurs du cursus. Ce projet permet de recoder des fonctions standard de la bibliothèque C (`libc`), d'implémenter des fonctions supplémentaires utiles, et d'ajouter des fonctions bonus pour la gestion de listes chaînées. L'objectif est de construire une bibliothèque robuste, conforme à la Norme de 42, et réutilisable, tout en maîtrisant la gestion de la mémoire et les bonnes pratiques de programmation en C.

Les objectifs principaux incluent :
- Recoder des fonctions de la `libc` avec le préfixe `ft_`.
- Implémenter des fonctions utilitaires absentes de la `libc`.
- Apprendre à manipuler des listes chaînées (bonus).
- Produire une bibliothèque statique bien structurée et sans fuites de mémoire.

## Structure du projet
- **Dossier principal** : `libft/`
- **Fichiers obligatoires** :
  - `Makefile`
  - `libft.h` : Fichier d'en-tête contenant les prototypes et définitions.
  - Fichiers sources (ex. `ft_*.c`) pour chaque fonction.
- **Fichiers bonus (si implémentés)** :
  - Fichiers sources pour les fonctions de liste (ex. `ft_lst*.c`).
- **Sortie** : Une bibliothèque statique nommée `libft.a`.

## Prérequis
- Un système Unix-like (Linux, macOS).
- Un compilateur C compatible (ex. `gcc` ou `clang`).
- Fonctions externes autorisées : dépendent des fonctions implémentées (ex. `malloc`, `free`, `write` pour certaines).
- Interdiction d'utiliser le qualificateur `restrict` ou le flag `-std=c99`.
- Aucune bibliothèque externe n'est autorisée, sauf `libft` elle-même.

## Compilation
Accédez au dossier du projet et exécutez :
```bash
make
```
Cela génère la bibliothèque `libft.a` à la racine du dépôt. Le `Makefile` doit inclure les règles `$(NAME)`, `all`, `clean`, `fclean`, et `re`, et compiler avec les flags `-Wall -Wextra -Werror`. Une règle `bonus` doit être incluse pour compiler les fonctions bonus. La commande `ar` est utilisée pour créer la bibliothèque.

Pour les bonus :
```bash
make bonus
```

## Utilisation
La bibliothèque `libft.a` peut être incluse dans d'autres projets en ajoutant l'en-tête `libft.h` et en liant la bibliothèque lors de la compilation.

Exemple d'utilisation :
```c
#include "libft.h"
#include <stdio.h>

int main(void)
{
    char *str = ft_strdup("Hello, world!");
    ft_putstr_fd(str, 1);
    ft_putchar_fd('\n', 1);
    free(str);
    return 0;
}
```

Compilation avec `libft.a` :
```bash
gcc -Wall -Wextra -Werror main.c -L. -lft -o program
```

### Fonctions obligatoires
#### Partie 1 - Fonctions de la `libc`
Ces fonctions doivent reproduire exactement le comportement des originales, avec le préfixe `ft_`. Aucune fonction externe n'est requise sauf indication contraire.

- `ft_isalpha` : Vérifie si un caractère est alphabétique.
- `ft_isdigit` : Vérifie si un caractère est un chiffre.
- `ft_isalnum` : Vérifie si un caractère est alphanumérique.
- `ft_isascii` : Vérifie si un caractère appartient à l'ASCII.
- `ft_isprint` : Vérifie si un caractère est imprimable.
- `ft_strlen` : Calcule la longueur d'une chaîne.
- `ft_memset` : Remplit une zone mémoire avec un octet.
- `ft_bzero` : Met une zone mémoire à zéro.
- `ft_memcpy` : Copie une zone mémoire.
- `ft_memmove` : Copie une zone mémoire avec gestion des chevauchements.
- `ft_strlcpy` : Copie une chaîne avec limite de taille.
- `ft_strlcat` : Concatène une chaîne avec limite de taille.
- `ft_toupper` : Convertit un caractère en majuscule.
- `ft_tolower` : Convertit un caractère en minuscule.
- `ft_strchr` : Recherche un caractère dans une chaîne.
- `ft_strrchr` : Recherche un caractère dans une chaîne (depuis la fin).
- `ft_strncmp` : Compare un nombre limité de caractères de deux chaînes.
- `ft_memchr` : Recherche un octet dans une zone mémoire.
- `ft_memcmp` : Compare deux zones mémoire.
- `ft_strnstr` : Recherche une sous-chaîne dans une chaîne avec limite.
- `ft_atoi` : Convertit une chaîne en entier.
- `ft_calloc` : Alloue et initialise une zone mémoire à zéro (utilise `malloc`).
- `ft_strdup` : Duplique une chaîne (utilise `malloc`).

#### Partie 2 - Fonctions supplémentaires
Ces fonctions sont absentes de la `libc` ou diffèrent dans leur implémentation.

- `ft_substr` : Extrait une sous-chaîne (utilise `malloc`).
- `ft_strjoin` : Concatène deux chaînes (utilise `malloc`).
- `ft_strtrim` : Supprime des caractères spécifiques au début et à la fin d'une chaîne (utilise `malloc`).
- `ft_split` : Divise une chaîne en tableau de sous-chaînes (utilise `malloc`).
- `ft_itoa` : Convertit un entier en chaîne (utilise `malloc`).
- `ft_strmapi` : Applique une fonction à chaque caractère d'une chaîne avec index (utilise `malloc`).
- `ft_striteri` : Applique une fonction à chaque caractère d'une chaîne avec index (sans allocation).
- `ft_putchar_fd` : Écrit un caractère sur un descripteur de fichier (utilise `write`).
- `ft_putstr_fd` : Écrit une chaîne sur un descripteur de fichier (utilise `write`).
- `ft_putendl_fd` : Écrit une chaîne suivie d'un `\n` sur un descripteur de fichier (utilise `write`).
- `ft_putnbr_fd` : Écrit un entier sur un descripteur de fichier (utilise `write`).

### Fonctions bonus
Ces fonctions manipulent des listes chaînées définies par la structure :
```c
typedef struct s_list
{
    void *content;
    struct s_list *next;
} t_list;
```

- `ft_lstnew` : Crée un nouvel élément de liste (utilise `malloc`).
- `ft_lstadd_front` : Ajoute un élément au début d'une liste.
- `ft_lstadd_back` : Ajoute un élément à la fin d'une liste.
- `ft_lstsize` : Calcule la taille d'une liste.
- `ft_lstlast` : Retourne le dernier élément d'une liste.
- `ft_lstdelone` : Supprime un élément de liste (utilise `free` et une fonction de suppression).
- `ft_lstclear` : Supprime tous les éléments d'une liste (utilise `free` et une fonction de suppression).
- `ft_lstiter` : Applique une fonction à chaque élément d'une liste.
- `ft_lstmap` : Crée une nouvelle liste en appliquant une fonction à chaque élément (utilise `malloc` et une fonction de suppression).

## Fonctionnement détaillé
### Partie obligatoire
- **Nom de la bibliothèque** : `libft.a`
- **Fonctionnement** :
  - **Partie 1** : Recoder les fonctions de la `libc` avec le même comportement et prototype, préfixées par `ft_`.
  - **Partie 2** : Implémenter des fonctions utilitaires pour manipuler des chaînes, des entiers, et écrire sur des descripteurs de fichier.
  - Toutes les fonctions doivent respecter la Norme de 42.
  - Les fonctions utilisant `malloc` doivent gérer les erreurs d'allocation.
- **Contraintes** :
  - Interdiction des variables globales.
  - Les fonctions auxiliaires doivent être `static` pour limiter leur portée au fichier.
  - Pas de fichiers inutilisés dans le rendu.
  - Compilation avec `-Wall -Wextra -Werror`.
  - Pas de segmentation fault, bus error, ou double free.
  - Toute mémoire allouée doit être libérée.

### Partie bonus
- **Structure** : Utilisation de la structure `t_list` pour les listes chaînées.
- **Fonctionnement** :
  - Implémenter des fonctions pour créer, manipuler, et supprimer des listes chaînées.
  - Les fonctions bonus doivent être compilées via la règle `bonus` du `Makefile`.
- **Contraintes** :
  - Les fichiers bonus ne doivent pas avoir le suffixe `_bonus` sauf s'ils sont exclusifs aux bonus.
  - Les bonus ne sont évalués que si la partie obligatoire est parfaite.

## Gestion des erreurs
- Les fonctions doivent gérer les cas limites (ex. pointeurs NULL, allocations échouées).
- Retourner `NULL` pour les fonctions allouant de la mémoire en cas d'échec.
- Pas de fuites de mémoire, de crashes, ou de comportements indéfinis (sauf spécifié).

## Codes de sortie
- Les fonctions retournent :
  - Une valeur appropriée (ex. pointeur, entier, ou rien) en cas de succès.
  - `NULL` ou une valeur spécifique en cas d'erreur (ex. allocation échouée).
- Les programmes de test doivent quitter proprement.

## Limitations
- Écrit en **C** uniquement, conforme à **la Norme** de 42.
- Fonctions autorisées : `malloc`, `free`, `write` (selon les fonctions).
- Interdiction du qualificateur `restrict` et du flag `-std=c99`.
- Pas de variables globales.
- Le `Makefile` ne doit pas relinker inutilement.
- Pas de crashes inattendus (segmentation fault, bus error, double free).

## Règles spécifiques
- La bibliothèque doit être nommée `libft.a` et créée à la racine du dépôt.
- Tous les fichiers doivent être à la racine (pas de sous-dossiers sauf pour les tests).
- Le `Makefile` doit inclure les règles `$(NAME)`, `all`, `clean`, `fclean`, `re`, et `bonus` pour les bonus.
- Les fonctions bonus doivent être compilées séparément via `make bonus`.
- Les fichiers inutilisés sont interdits dans le rendu.

## Bonus
- Implémentation de fonctions pour manipuler des listes chaînées avec la structure `t_list`.
- Les fonctions bonus facilitent la gestion de données dynamiques dans les projets futurs.

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** :

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis de construire une bibliothèque robuste et réutilisable, tout en approfondissant mes compétences en programmation C et en gestion de la mémoire.

---

# Libft - README

## Description
**Libft** is a project from 42 school that involves creating a static C library, named `libft.a`, containing useful functions for future curriculum projects. The project requires recoding standard C library (`libc`) functions, implementing additional utility functions, and adding bonus functions for linked list management. The goal is to build a robust, 42 Norm-compliant, reusable library while mastering memory management and C programming best practices.

Key objectives include:
- Recoding `libc` functions with the `ft_` prefix.
- Implementing additional utility functions absent from `libc`.
- Learning to manipulate linked lists (bonus).
- Producing a well-structured static library with no memory leaks.

## Project Structure
- **Main directory**: `libft/`
- **Mandatory files**:
  - `Makefile`
  - `libft.h`: Header file with prototypes and definitions.
  - Source files (e.g., `ft_*.c`) for each function.
- **Bonus files (if implemented)**:
  - Source files for list functions (e.g., `ft_lst*.c`).
- **Output**: A static library named `libft.a`.

## Prerequisites
- A Unix-like system (Linux, macOS).
- A compatible C compiler (e.g., `gcc` or `clang`).
- Allowed external functions: depend on the implemented functions (e.g., `malloc`, `free`, `write` for some).
- Prohibition of the `restrict` qualifier or the `-std=c99` flag.
- No external libraries are allowed, except `libft` itself.

## Compilation
Navigate to the project directory and run:
```bash
make
```
This generates the `libft.a` library at the repository root. The `Makefile` must include the rules `$(NAME)`, `all`, `clean`, `fclean`, and `re`, and compile with the flags `-Wall -Wextra -Werror`. A `bonus` rule must be included to compile bonus functions. The `ar` command is used to create the library.

For bonuses:
```bash
make bonus
```

## Usage
The `libft.a` library can be included in other projects by adding the `libft.h` header and linking the library during compilation.

Example usage:
```c
#include "libft.h"
#include <stdio.h>

int main(void)
{
    char *str = ft_strdup("Hello, world!");
    ft_putstr_fd(str, 1);
    ft_putchar_fd('\n', 1);
    free(str);
    return 0;
}
```

Compilation with `libft.a`:
```bash
gcc -Wall -Wextra -Werror main.c -L. -lft -o program
```

### Mandatory Functions
#### Part 1 - `libc` Functions
These functions must replicate the exact behavior of their `libc` counterparts, prefixed with `ft_`. No external functions are required unless specified.

- `ft_isalpha`: Checks if a character is alphabetic.
- `ft_isdigit`: Checks if a character is a digit.
- `ft_isalnum`: Checks if a character is alphanumeric.
- `ft_isascii`: Checks if a character is ASCII.
- `ft_isprint`: Checks if a character is printable.
- `ft_strlen`: Calculates the length of a string.
- `ft_memset`: Fills a memory area with a byte.
- `ft_bzero`: Sets a memory area to zero.
- `ft_memcpy`: Copies a memory area.
- `ft_memmove`: Copies a memory area with overlap handling.
- `ft_strlcpy`: Copies a string with size limit.
- `ft_strlcat`: Concatenates a string with size limit.
- `ft_toupper`: Converts a character to uppercase.
- `ft_tolower`: Converts a character to lowercase.
- `ft_strchr`: Searches for a character in a string.
- `ft_strrchr`: Searches for a character in a string (from the end).
- `ft_strncmp`: Compares a limited number of characters from two strings.
- `ft_memchr`: Searches for a byte in a memory area.
- `ft_memcmp`: Compares two memory areas.
- `ft_strnstr`: Searches for a substring in a string with a limit.
- `ft_atoi`: Converts a string to an integer.
- `ft_calloc`: Allocates and zeros memory (uses `malloc`).
- `ft_strdup`: Duplicates a string (uses `malloc`).

#### Part 2 - Additional Functions
These functions are absent from `libc` or differ in implementation.

- `ft_substr`: Extracts a substring (uses `malloc`).
- `ft_strjoin`: Concatenates two strings (uses `malloc`).
- `ft_strtrim`: Trims specified characters from the start and end of a string (uses `malloc`).
- `ft_split`: Splits a string into an array of substrings (uses `malloc`).
- `ft_itoa`: Converts an integer to a string (uses `malloc`).
- `ft_strmapi`: Applies a function to each character of a string with its index (uses `malloc`).
- `ft_striteri`: Applies a function to each character of a string with its index (no allocation).
- `ft_putchar_fd`: Writes a character to a file descriptor (uses `write`).
- `ft_putstr_fd`: Writes a string to a file descriptor (uses `write`).
- `ft_putendl_fd`: Writes a string followed by a newline to a file descriptor (uses `write`).
- `ft_putnbr_fd`: Writes an integer to a file descriptor (uses `write`).

### Bonus Functions
These functions manipulate linked lists defined by the structure:
```c
typedef struct s_list
{
    void *content;
    struct s_list *next;
} t_list;
```

- `ft_lstnew`: Creates a new list element (uses `malloc`).
- `ft_lstadd_front`: Adds an element to the front of a list.
- `ft_lstadd_back`: Adds an element to the end of a list.
- `ft_lstsize`: Calculates the size of a list.
- `ft_lstlast`: Returns the last element of a list.
- `ft_lstdelone`: Deletes a single list element (uses `free` and a deletion function).
- `ft_lstclear`: Deletes all elements of a list (uses `free` and a deletion function).
- `ft_lstiter`: Applies a function to each element of a list.
- `ft_lstmap`: Creates a new list by applying a function to each element (uses `malloc` and a deletion function).

## Detailed Functionality
### Mandatory Part
- **Library Name**: `libft.a`
- **Functionality**:
  - **Part 1**: Recode `libc` functions with identical behavior and prototypes, prefixed with `ft_`.
  - **Part 2**: Implement utility functions for string manipulation, integer conversion, and file descriptor output.
  - All functions must comply with 42’s Norme.
  - Functions using `malloc` must handle allocation failures.
- **Constraints**:
  - No global variables.
  - Auxiliary functions must be `static` to limit scope to their file.
  - No unused files in the submission.
  - Compilation with `-Wall -Wextra -Werror`.
  - No segmentation faults, bus errors, or double frees.
  - All allocated memory must be freed.

### Bonus Part
- **Structure**: Uses the `t_list` structure for linked lists.
- **Functionality**:
  - Implement functions to create, manipulate, and delete linked lists.
  - Bonus functions must be compiled via the `bonus` rule in the `Makefile`.
- **Constraints**:
  - Bonus files must not have the `_bonus` suffix unless exclusive to bonuses.
  - Bonuses are only evaluated if the mandatory part is perfect.

## Error Handling
- Functions must handle edge cases (e.g., NULL pointers, allocation failures).
- Return `NULL` for functions allocating memory if allocation fails.
- No memory leaks, crashes, or undefined behavior (unless specified).

## Exit Codes
- Functions return:
  - Appropriate values (e.g., pointer, integer, or void) on success.
  - `NULL` or a specific value on error (e.g., allocation failure).
- Test programs must exit cleanly.

## Limitations
- Written in **C** only, adhering to 42’s **Norme**.
- Allowed functions: `malloc`, `free`, `write` (depending on the function).
- No `restrict` qualifier or `-std=c99` flag.
- No global variables.
- The `Makefile` must not relink unnecessarily.
- No unexpected crashes (segmentation fault, bus error, double free).

## Specific Rules
- The library must be named `libft.a` and created at the repository root.
- All files must be at the root (no subdirectories except for tests).
- The `Makefile` must include the rules `$(NAME)`, `all`, `clean`, `fclean`, `re`, and `bonus` for bonuses.
- Bonus functions must be compiled separately via `make bonus`.
- No unused files in the submission.

## Bonuses
- Implementation of functions to manipulate linked lists using the `t_list` structure.
- Bonus functions facilitate dynamic data management in future projects.

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**:

## Acknowledgments
Thanks to 42 school for this project, which allowed me to build a robust, reusable library while deepening my skills in C programming and memory management.