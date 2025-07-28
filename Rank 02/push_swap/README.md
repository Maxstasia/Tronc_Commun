# Push_Swap - README

---

## Description
Push_Swap est un projet réalisé dans le cadre du cursus de l'école 42. Il vise à développer un algorithme de tri efficace pour ordonner une pile d'entiers en utilisant un ensemble limité d'opérations et une pile auxiliaire. Le programme `push_swap` prend en entrée une liste d'entiers et génère la séquence d'instructions la plus courte possible pour trier la pile en ordre croissant, avec le plus petit nombre au sommet. Ce projet met l'accent sur l'optimisation algorithmique et la compréhension des complexités des algorithmes de tri.

L'objectif est de maîtriser les concepts suivants :
- Programmation en C avec manipulation de piles.
- Conception et implémentation d'algorithmes de tri optimisés.
- Gestion de la mémoire dynamique sans fuites.
- Respect des contraintes de performance (nombre maximal d'opérations).
- Implémentation optionnelle d'un programme `checker` pour valider les instructions (bonus).

Pour ce projet, j'ai implémenté un **algorithme de tri radix** pour optimiser le tri des entiers, en particulier pour les grandes listes (jusqu'à 500 nombres), tout en respectant les exigences de performance.

## Structure du projet
Le projet est organisé comme suit :
- **Dossier principal** : Contient les fichiers sources (*.c, *.h) et le Makefile pour le programme `push_swap`.
- **Dossier bonus (optionnel)** : Contient les fichiers pour le programme `checker`.
- **Dossier libft** : Contient la bibliothèque libft pour les fonctions utilitaires (ex. : `ft_printf`).

Les fichiers clés incluent :
- **Sources C** : Fichiers pour la logique de tri, la gestion des piles, et les opérations.
- **Makefile** : Pour compiler les programmes avec les flags `-Wall`, `-Wextra`, `-Werror`.
- **Libft** : Bibliothèque personnalisée pour les fonctions utilitaires.

## Prérequis
- Un environnement Linux/Unix pour compiler et exécuter le programme.
- Connaissances de base en programmation C (gestion de la mémoire, structures de données).
- Compilateur compatible avec C99 (gcc, clang).
- Connaissance des algorithmes de tri et de leur complexité.

## Installation
1. **Cloner le dépôt Git** :
   ```bash
   git clone <votre-dépôt-git>
   cd push_swap
   ```
2. **Compiler la partie obligatoire** :
   ```bash
   make
   ```
   Produit l'exécutable `push_swap`.
3. **Compiler la partie bonus (si implémentée)** :
   ```bash
   make bonus
   ```
   Produit l'exécutable `checker`.
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
1. **Lancer le programme push_swap** :
   ```bash
   ./push_swap <liste_d_entiers>
   ```
   Exemple :
   ```bash
   ./push_swap 2 1 3 6 5 8
   ```
   Affiche une séquence d'instructions comme :
   ```
   pb
   sa
   pa
   ```
   - Les entiers sont fournis en arguments, le premier étant au sommet de la pile a.
   - Les instructions possibles sont : `sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`.
   - Si aucun argument n’est fourni, le programme ne produit aucune sortie.
   - En cas d’erreur (ex. : non-entiers, doublons, dépassement d’int), affiche `Error` sur la sortie d’erreur.

2. **Lancer le programme checker (bonus, si implémenté)** :
   ```bash
   ./checker <liste_d_entiers>
   ```
   Exemple :
   ```bash
   ./checker 2 1 3 6 5 8
   ```
   - Lit les instructions sur l’entrée standard (ex. : via un pipe depuis `push_swap`).
   - Affiche `OK` si la pile a est triée et la pile b est vide, sinon `KO`.
   - Exemple d’utilisation avec pipe :
     ```bash
     ./push_swap 2 1 3 6 5 8 | ./checker 2 1 3 6 5 8
     ```

### Exemple de sortie
Pour `./push_swap 2 1 3` :
```
pb
sa
pa
```
Pour `./checker 2 1 3` avec les instructions ci-dessus en entrée :
```
OK
```

## Fonctionnement détaillé
### Algorithme de tri radix
L’algorithme de tri radix a été choisi pour sa performance linéaire en temps pour de grandes listes, avec une complexité de **O(n log n)** dans le pire des cas. Voici une explication de son fonctionnement dans ce projet :
- **Prétraitement des entiers** :
  - Les entiers en entrée sont convertis en leurs indices dans une liste triée pour simplifier le tri (ex. : [5, 2, 8] devient [1, 0, 2]).
  - Cela garantit que les nombres négatifs et positifs sont gérés uniformément.
- **Tri binaire** :
  - Le tri radix examine les bits des indices un par un, du bit le moins significatif (LSB) au bit le plus significatif (MSB).
  - Pour chaque bit, les nombres sont partitionnés entre la pile a (bit = 0) et la pile b (bit = 1) à l’aide de l’opération `pb`.
  - Après chaque itération, les nombres de la pile b sont ramenés dans la pile a avec `pa`.
- **Optimisation** :
  - Le nombre de bits à examiner est limité au minimum requis pour représenter le plus grand indice (log₂(n)).
  - Les rotations (`ra`, `rra`) sont optimisées pour minimiser les mouvements en fonction de la position des éléments.
- **Avantages** :
  - Performant pour 100 et 500 nombres (respecte les limites de 700 et 5500 opérations).
  - Stable pour différentes tailles de liste.
  - Évite les cas pathologiques des algorithmes comme le tri rapide.

### Instructions disponibles
- `sa` : Intervertit les deux premiers éléments de la pile a.
- `sb` : Intervertit les deux premiers éléments de la pile b.
- `ss` : Exécute `sa` et `sb` simultanément.
- `pa` : Déplace le premier élément de la pile b vers la pile a.
- `pb` : Déplace le premier élément de la pile a vers la pile b.
- `ra` : Décale tous les éléments de la pile a vers le haut (le premier devient le dernier).
- `rb` : Décale tous les éléments de la pile b vers le haut.
- `rr` : Exécute `ra` et `rb` simultanément.
- `rra` : Décale tous les éléments de la pile a vers le bas (le dernier devient le premier).
- `rrb` : Décale tous les éléments de la pile b vers le bas.
- `rrr` : Exécute `rra` et `rrb` simultanément.

### Partie bonus (checker)
- Le programme `checker` lit une liste d’instructions depuis l’entrée standard et les applique à la pile a.
- Il vérifie si la pile a est triée (en ordre croissant) et si la pile b est vide après exécution.
- Sortie : `OK` pour un tri correct, `KO` sinon, ou `Error` en cas d’instructions invalides.

### Makefile
Le Makefile inclut les règles suivantes :
- `all` : Compile le programme `push_swap`.
- `clean` : Supprime les fichiers objets.
- `fclean` : Supprime les fichiers objets et les exécutables.
- `re` : Recompile tout.
- `bonus` : Compile le programme `checker`.

## Gestion des erreurs
- Vérifiez que le programme gère correctement les erreurs : non-entiers, doublons, dépassement d’int.
- Assurez-vous que le code respecte la Norme 42 (vérifié par `norminette`).
- Testez avec des listes de différentes tailles (3, 5, 100, 500 nombres) pour valider les performances.
- Les fuites de mémoire doivent être éliminées (vérifié avec `valgrind` ou équivalent).
- Pendant l’évaluation, Deepthought teste les performances et la correction du tri.

## Limitations
- Les variables globales sont interdites.
- Les erreurs non gérées (segmentation fault, double free, etc.) entraînent une note de 0.
- Le programme doit respecter la Norme 42, sinon la note est 0.
- Les performances doivent respecter les seuils : < 700 opérations pour 100 nombres, < 5500 pour 500 nombres.

## Performances
- **100 nombres** : Moins de 700 opérations en moyenne pour une note de 80/100.
- **500 nombres** : Moins de 5500 opérations pour une note maximale et l’accès à l’évaluation des bonus.
- L’algorithme radix garantit des performances stables, souvent bien en-dessous des seuils requis.

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** : Mars 2025 - Mars 2025

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis de plonger dans les algorithmes de tri, en particulier le tri radix, et de développer des compétences en optimisation et en gestion de structures de données en C.

---

# Push_Swap - README

## Description
Push_Swap is a project developed as part of the 42 school curriculum. It involves developing an efficient sorting algorithm to order a stack of integers using a limited set of operations and an auxiliary stack. The `push_swap` program takes a list of integers as input and outputs the shortest sequence of instructions to sort the stack in ascending order, with the smallest number at the top. The project emphasizes algorithmic optimization and understanding sorting complexities.

The goal is to master the following concepts:
- Programming in C with stack manipulation.
- Designing and implementing optimized sorting algorithms.
- Managing dynamic memory without leaks.
- Meeting performance constraints (maximum number of operations).
- Implementing an optional `checker` program to validate instructions (bonus).

For this project, I implemented a **radix sort algorithm** to optimize sorting for large lists (up to 500 numbers) while meeting performance requirements.

## Project Structure
The project is organized as follows:
- **Main Directory**: Contains source files (*.c, *.h) and the Makefile for the `push_swap` program.
- **Bonus Directory (optional)**: Contains files for the `checker` program.
- **Libft Directory**: Contains the libft library for utility functions (e.g., `ft_printf`).

Key files include:
- **C Source Files**: Files for sorting logic, stack management, and operations.
- **Makefile**: To compile programs with `-Wall`, `-Wextra`, `-Werror` flags.
- **Libft**: Custom library for utility functions.

## Prerequisites
- A Linux/Unix environment to compile and run the program.
- Basic knowledge of C programming (memory management, data structures).
- A C99-compatible compiler (gcc, clang).
- Understanding of sorting algorithms and their complexity.

## Installation
1. **Clone the Git repository**:
   ```bash
   git clone <your-git-repository>
   cd push_swap
   ```
2. **Compile the mandatory part**:
   ```bash
   make
   ```
   Produces the `push_swap` executable.
3. **Compile the bonus part (if implemented)**:
   ```bash
   make bonus
   ```
   Produces the `checker` executable.
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
1. **Run the push_swap program**:
   ```bash
   ./push_swap <list_of_integers>
   ```
   Example:
   ```bash
   ./push_swap 2 1 3 6 5 8
   ```
   Outputs a sequence of instructions like:
   ```
   pb
   sa
   pa
   ```
   - Integers are provided as arguments, the first being at the top of stack a.
   - Available instructions: `sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`.
   - If no arguments are provided, the program outputs nothing.
   - In case of errors (e.g., non-integers, duplicates, int overflow), outputs `Error` to stderr.

2. **Run the checker program (bonus, if implemented)**:
   ```bash
   ./checker <list_of_integers>
   ```
   Example:
   ```bash
   ./checker 2 1 3 6 5 8
   ```
   - Reads instructions from stdin (e.g., piped from `push_swap`).
   - Outputs `OK` if stack a is sorted and stack b is empty, otherwise `KO`.
   - Example with pipe:
     ```bash
     ./push_swap 2 1 3 6 5 8 | ./checker 2 1 3 6 5 8
     ```

### Example Output
For `./push_swap 2 1 3`:
```
pb
sa
pa
```
For `./checker 2 1 3` with the above instructions as input:
```
OK
```

## Detailed Functionality
### Radix Sort Algorithm
The radix sort algorithm was chosen for its linear time performance on large lists, with a worst-case complexity of **O(n log n)**. Here’s how it works in this project:
- **Integer Preprocessing**:
  - Input integers are converted to their indices in a sorted list to simplify sorting (e.g., [5, 2, 8] becomes [1, 0, 2]).
  - This ensures uniform handling of negative and positive numbers.
- **Binary Sorting**:
  - Radix sort examines the bits of the indices one by one, from least significant bit (LSB) to most significant bit (MSB).
  - For each bit, numbers are partitioned between stack a (bit = 0) and stack b (bit = 1) using the `pb` operation.
  - After each iteration, numbers from stack b are moved back to stack a with `pa`.
- **Optimization**:
  - The number of bits to check is limited to the minimum required to represent the largest index (log₂(n)).
  - Rotations (`ra`, `rra`) are optimized to minimize movements based on element positions.
- **Advantages**:
  - Efficient for 100 and 500 numbers (meets thresholds of 700 and 5500 operations).
  - Stable across different list sizes.
  - Avoids worst-case scenarios of algorithms like quicksort.

### Available Instructions
- `sa`: Swaps the top two elements of stack a.
- `sb`: Swaps the top two elements of stack b.
- `ss`: Performs `sa` and `sb` simultaneously.
- `pa`: Moves the top element from stack b to stack a.
- `pb`: Moves the top element from stack a to stack b.
- `ra`: Rotates all elements of stack a upward (first becomes last).
- `rb`: Rotates all elements of stack b upward.
- `rr`: Performs `ra` and `rb` simultaneously.
- `rra`: Rotates all elements of stack a downward (last becomes first).
- `rrb`: Rotates all elements of stack b downward.
- `rrr`: Performs `rra` and `rrb` simultaneously.

### Bonus Part (checker)
- The `checker` program reads a list of instructions from stdin and applies them to stack a.
- It checks if stack a is sorted (in ascending order) and stack b is empty after execution.
- Output: `OK` for a correct sort, `KO` otherwise, or `Error` for invalid instructions.

### Makefile
The Makefile includes:
- `all`: Compiles the `push_swap` program.
- `clean`: Removes object files.
- `fclean`: Removes object files and executables.
- `re`: Recompiles everything.
- `bonus`: Compiles the `checker` program.

## Error Handling
- Ensure the program handles errors correctly: non-integers, duplicates, int overflow.
- Verify code compliance with the 42 Norm (checked by `norminette`).
- Test with various list sizes (3, 5, 100, 500 numbers) to validate performance.
- Eliminate memory leaks (checked with `valgrind` or equivalent).
- During evaluation, Deepthought tests performance and sorting correctness.

## Limitations
- Global variables are forbidden.
- Unhandled errors (segmentation fault, double free, etc.) result in a grade of 0.
- The program must comply with the 42 Norm, or the grade is 0.
- Performance must meet thresholds: < 700 operations for 100 numbers, < 5500 for 500 numbers.

## Performance
- **100 numbers**: Less than 700 operations on average for a grade of 80/100.
- **500 numbers**: Less than 5500 operations for a maximum grade and bonus evaluation access.
- The radix sort ensures stable performance, often well below the required thresholds.

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**: March 2025 - March 2025

## Acknowledgments
Thanks to 42 school for this project, which allowed me to dive into sorting algorithms, particularly radix sort, and develop skills in optimization and data structure management in C.