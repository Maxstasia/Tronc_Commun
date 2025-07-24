# ft_printf - README

---

## Description
**ft_printf** est un projet de l'école 42 qui consiste à recoder la fonction `printf()` de la bibliothèque standard C. L'objectif est de créer une bibliothèque statique, `libftprintf.a`, contenant une fonction `ft_printf()` capable de gérer un nombre variable d'arguments à l'aide des fonctions variadiques en C. Ce projet permet de maîtriser les fonctions variadiques (`va_start`, `va_arg`, `va_copy`, `va_end`), la gestion des formats d'affichage, et la création d'une bibliothèque statique. Une fois validé, `ft_printf()` peut être intégré à la bibliothèque `libft` pour une utilisation dans d'autres projets du cursus.

Les objectifs principaux incluent :
- Comprendre et utiliser les fonctions variadiques en C.
- Implémenter une version simplifiée de `printf()` avec des conversions spécifiques.
- Produire une bibliothèque statique bien structurée et extensible.
- Gérer les erreurs et éviter les fuites de mémoire.

## Structure du projet
- **Dossier principal** : `ft_printf/`
- **Fichiers obligatoires** :
  - `Makefile`
  - Fichiers sources en C (ex. `ft_printf.c`, fichiers pour gérer les conversions).
  - Fichiers d'en-tête (ex. `ft_printf.h`).
- **Sortie** : Une bibliothèque statique nommée `libftprintf.a`.

## Prérequis
- Un système Unix-like (Linux, macOS).
- Un compilateur C compatible (ex. `gcc` ou `clang`).
- Les fonctions autorisées : `malloc`, `free`, `write`, `va_start`, `va_arg`, `va_copy`, `va_end`.
- Aucune bibliothèque externe n'est autorisée, sauf `libft` si utilisée (doit être incluse dans un dossier `libft/` à la racine).

## Compilation
Accédez au dossier du projet et exécutez :
```bash
make
```
Cela génère la bibliothèque `libftprintf.a` à la racine du dépôt. Le `Makefile` doit inclure les règles `$(NAME)`, `all`, `clean`, `fclean`, et `re`, et compiler avec les flags `-Wall -Wextra -Werror`. La commande `ar` doit être utilisée pour créer la bibliothèque (l'utilisation de `libtool` est interdite). Si `libft` est utilisée, son `Makefile` doit être appelé pour compiler la bibliothèque avant le projet.

## Utilisation
La fonction `ft_printf` a le prototype suivant :
```c
int ft_printf(const char *format, ...);
```
Elle retourne le nombre de caractères affichés (comme `printf`) ou une valeur négative en cas d'erreur.

Exemple d'utilisation :
```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello, %s! You are %d years old.\n", "Alice", 25);
    ft_printf("Hex: %x, Pointer: %p\n", 42, (void *)0x12345678);
    return 0;
}
```

### Conversions obligatoires
La fonction doit gérer les conversions suivantes :
- `%c` : Affiche un seul caractère.
- `%s` : Affiche une chaîne de caractères (convention C).
- `%p` : Affiche une adresse de pointeur en hexadécimal (base 16).
- `%d` : Affiche un nombre décimal (base 10).
- `%i` : Affiche un entier en base 10 (identique à `%d`).
- `%u` : Affiche un nombre décimal non signé (base 10).
- `%x` : Affiche un nombre en hexadécimal (base 16, lettres minuscules).
- `%X` : Affiche un nombre en hexadécimal (base 16, lettres majuscules).
- `%%` : Affiche un signe pourcentage.

### Exemple de sortie
```c
ft_printf("Char: %c, String: %s, Hex: %x, Pointer: %p\n", 'A', "test", 42, (void *)0x12345678);
```
Sortie :
```
Char: A, String: test, Hex: 2a, Pointer: 0x12345678
```

## Fonctionnement détaillé
### Partie obligatoire
- **Prototype** : `int ft_printf(const char *format, ...);`
- **Fonctionnement** :
  - Parcourt la chaîne `format` pour identifier les spécificateurs de format (ex. `%c`, `%s`).
  - Utilise les fonctions variadiques (`va_start`, `va_arg`, `va_end`) pour récupérer les arguments correspondants.
  - Gère chaque conversion en affichant les données via `write` sur la sortie standard.
  - Retourne le nombre total de caractères affichés (excluant le caractère nul).
- **Contraintes** :
  - Ne gère pas la gestion de buffer (contrairement à `printf`).
  - Utilise `ar` pour créer `libftprintf.a`.
  - Doit être robuste : pas de segmentation fault, bus error, ou double free.
  - Toute mémoire allouée sur le tas (heap) doit être libérée.

### Partie bonus
- Gestion des drapeaux : `-`, `0`, `.` (précision), et la largeur minimale du champ pour toutes les conversions.
- Gestion du drapeau `#` (ex. ajout de `0x` pour `%x` et `%X`) et du drapeau espace.
- Les bonus doivent être implémentés dans des fichiers séparés (ex. `bonus.c`, `bonus.h`) et compilés via une règle `bonus` dans le `Makefile`.

## Gestion des erreurs
- **Comportement indéfini** : La fonction doit gérer les erreurs sans provoquer de crash (ex. pointeur NULL pour `%s`).
- **Mémoire** : Toute allocation doit être libérée pour éviter les fuites.
- **Sortie** : En cas d'erreur (ex. échec de `write`), retourne une valeur négative.

## Codes de sortie
- La fonction `ft_printf` retourne :
  - Nombre de caractères affichés en cas de succès.
  - Valeur négative en cas d'erreur.
- Le programme de test (si créé) doit quitter proprement.

## Limitations
- Écrit en **C** uniquement, conforme à **la Norme** de l'école 42.
- Pas de gestion de buffer (contrairement à `printf`).
- Fonctions autorisées : `malloc`, `free`, `write`, `va_start`, `va_arg`, `va_copy`, `va_end`.
- Utilisation de `ar` obligatoire pour la bibliothèque (pas de `libtool`).
- Le `Makefile` ne doit pas relinker inutilement.
- Pas de crashes inattendus (segmentation fault, bus error, double free).

## Règles spécifiques
- La bibliothèque doit être nommée `libftprintf.a` et créée à la racine du dépôt.
- Les conversions `%c`, `%s`, `%p`, `%d`, `%i`, `%u`, `%x`, `%X`, et `%%` sont obligatoires.
- Le `Makefile` doit inclure les règles standard (`$(NAME)`, `all`, `clean`, `fclean`, `re`).
- Les bonus doivent être séparés et compilés via une règle `bonus`.
- Si `libft` est utilisée, elle doit être compilée via son propre `Makefile` dans un dossier `libft/`.

## Bonus
- Gestion des drapeaux : `-` (alignement à gauche), `0` (remplissage avec zéros), `.` (précision), et largeur minimale.
- Gestion du drapeau `#` (ex. `0x` pour hexadécimal) et du drapeau espace.
- Planification dès le départ recommandée pour intégrer les bonus sans restructurer le code.

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** :

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis de maîtriser les fonctions variadiques en C et de développer une bibliothèque statique robuste et réutilisable.

---

# ft_printf - README

## Description
**ft_printf** is a project from 42 school that involves recreating the `printf()` function from the C standard library. The goal is to create a static library, `libftprintf.a`, containing a `ft_printf()` function capable of handling variable arguments using variadic functions in C. This project teaches the use of variadic functions (`va_start`, `va_arg`, `va_copy`, `va_end`), format specifiers, and static library creation. Once validated, `ft_printf()` can be integrated into the `libft` library for use in other curriculum projects.

Key objectives include:
- Understanding and using variadic functions in C.
- Implementing a simplified version of `printf()` with specific conversions.
- Producing a well-structured and extensible static library.
- Handling errors and preventing memory leaks.

## Project Structure
- **Main directory**: `ft_printf/`
- **Mandatory files**:
  - `Makefile`
  - C source files (e.g., `ft_printf.c`, files for conversion handling).
  - Header files (e.g., `ft_printf.h`).
- **Output**: A static library named `libftprintf.a`.

## Prerequisites
- A Unix-like system (Linux, macOS).
- A compatible C compiler (e.g., `gcc` or `clang`).
- Allowed functions: `malloc`, `free`, `write`, `va_start`, `va_arg`, `va_copy`, `va_end`.
- No external libraries are allowed, except `libft` if used (must be included in a `libft/` directory at the root).

## Compilation
Navigate to the project directory and run:
```bash
make
```
This generates the `libftprintf.a` library at the root of the repository. The `Makefile` must include the rules `$(NAME)`, `all`, `clean`, `fclean`, and `re`, and compile with the flags `-Wall -Wextra -Werror`. The `ar` command must be used to create the library (`libtool` is forbidden). If `libft` is used, its `Makefile` must be called to compile the library before the project.

## Usage
The `ft_printf` function has the following prototype:
```c
int ft_printf(const char *format, ...);
```
It returns the number of characters printed (like `printf`) or a negative value on error.

Example usage:
```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello, %s! You are %d years old.\n", "Alice", 25);
    ft_printf("Hex: %x, Pointer: %p\n", 42, (void *)0x12345678);
    return 0;
}
```

### Mandatory Conversions
The function must handle the following conversions:
- `%c`: Prints a single character.
- `%s`: Prints a string (per C convention).
- `%p`: Prints a void pointer address in hexadecimal (base 16).
- `%d`: Prints a decimal number (base 10).
- `%i`: Prints an integer in base 10 (same as `%d`).
- `%u`: Prints an unsigned decimal number (base 10).
- `%x`: Prints a number in hexadecimal (base 16, lowercase).
- `%X`: Prints a number in hexadecimal (base 16, uppercase).
- `%%`: Prints a percent sign.

### Example Output
```c
ft_printf("Char: %c, String: %s, Hex: %x, Pointer: %p\n", 'A', "test", 42, (void *)0x12345678);
```
Output:
```
Char: A, String: test, Hex: 2a, Pointer: 0x12345678
```

## Detailed Functionality
### Mandatory Part
- **Prototype**: `int ft_printf(const char *format, ...);`
- **Functionality**:
  - Parses the `format` string to identify format specifiers (e.g., `%c`, `%s`).
  - Uses variadic functions (`va_start`, `va_arg`, `va_end`) to retrieve corresponding arguments.
  - Handles each conversion by printing data via `write` to standard output.
  - Returns the total number of characters printed (excluding the null character).
- **Constraints**:
  - No buffer management (unlike original `printf`).
  - Uses `ar` to create `libftprintf.a`.
  - Must be robust: no segmentation faults, bus errors, or double frees.
  - All heap-allocated memory must be freed.

### Bonus Part
- Handle flags: `-` (left-align), `0` (zero-padding), `.` (precision), and minimum field width for all conversions.
- Handle the `#` flag (e.g., adding `0x` for `%x` and `%X`) and the space flag.
- Bonuses must be implemented in separate files (e.g., `bonus.c`, `bonus.h`) and compiled via a `bonus` rule in the `Makefile`.

## Error Handling
- **Undefined Behavior**: The function must handle errors without crashing (e.g., NULL pointer for `%s`).
- **Memory**: All allocations must be freed to prevent leaks.
- **Output**: On error (e.g., `write` failure), returns a negative value.

## Exit Codes
- The `ft_printf` function returns:
  - Number of characters printed on success.
  - Negative value on error.
- Test programs (if created) must exit cleanly.

## Limitations
- Written in **C** only, adhering to 42’s **Norme**.
- No buffer management (unlike `printf`).
- Allowed functions: `malloc`, `free`, `write`, `va_start`, `va_arg`, `va_copy`, `va_end`.
- Uses `ar` for library creation (`libtool` is forbidden).
- The `Makefile` must not relink unnecessarily.
- No unexpected crashes (segmentation fault, bus error, double free).

## Specific Rules
- The library must be named `libftprintf.a` and created at the repository root.
- Conversions `%c`, `%s`, `%p`, `%d`, `%i`, `%u`, `%x`, `%X`, and `%%` are mandatory.
- The `Makefile` must include standard rules (`$(NAME)`, `all`, `clean`, `fclean`, `re`).
- Bonuses must be separate and compiled via a `bonus` rule.
- If `libft` is used, it must be compiled via its own `Makefile` in a `libft/` directory.

## Bonuses
- Handle flags: `-` (left-align), `0` (zero-padding), `.` (precision), and minimum field width.
- Handle the `#` flag (e.g., `0x` for hexadecimal) and the space flag.
- Plan bonus implementation early to avoid restructuring the code.

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**:

## Acknowledgments
Thanks to 42 school for this project, which allowed me to master variadic functions in C and develop a robust, reusable static library.
