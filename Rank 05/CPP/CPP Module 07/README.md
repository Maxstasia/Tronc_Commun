# CPP07 - README

---

## Description
CPP07 est le huitième module du parcours C++ dans le cadre du cursus de l'école 42. Ce projet se concentre sur les templates en C++98, en explorant les fonctions templates, l'itération sur des tableaux génériques, et la création d'une classe template pour gérer des tableaux dynamiques. Les exercices impliquent l'implémentation de fonctions génériques (`swap`, `min`, `max`), une fonction d'itération (`iter`), et une classe `Array` pour manipuler des tableaux de tout type, tout en respectant les contraintes du standard C++98.

L'objectif est de maîtriser les concepts suivants :
- Création et utilisation de fonctions templates pour des opérations génériques.
- Itération sur des tableaux de tout type avec une fonction template.
- Conception d'une classe template pour gérer des tableaux dynamiques avec gestion sécurisée de la mémoire.
- Respect des conventions C++98, y compris la forme canonique pour les classes.

## Structure du projet
Le projet est divisé en trois exercices, chacun dans son propre dossier :

- **`ex00/`** : *Start with a few functions* - Implémentation des fonctions templates `swap`, `min`, et `max`.
  - Fichiers : `Makefile`, `main.cpp`, `whatever.hpp`.
- **`ex01/`** : *Iter* - Implémentation de la fonction template `iter` pour itérer sur des tableaux.
  - Fichiers : `Makefile`, `main.cpp`, `iter.hpp`.
- **`ex02/`** : *Array* - Création d'une classe template `Array` pour gérer des tableaux dynamiques.
  - Fichiers : `Makefile`, `main.cpp`, `Array.hpp`, `Array.tpp` (optionnel).

## Prérequis
- Un système Unix-like (Linux, macOS).
- Un compilateur C++ compatible avec le standard C++98 (ex. `g++`).
- Les bibliothèques standard C++ (`iostream`, `string`, etc.).
- Aucun accès à C++11 ou bibliothèques externes (Boost interdit).

## Compilation
Pour chaque exercice, accédez au dossier correspondant (`ex00`, `ex01`, `ex02`) et exécutez :
```bash
make
```
Cela génère un exécutable pour chaque exercice. Assurez-vous que les flags de compilation incluent `-Wall -Wextra -Werror -std=c++98`.

## Utilisation
### Exercice 00 : Start with a few functions
Implémente les fonctions templates `swap`, `min`, et `max` pour manipuler des valeurs de tout type comparable.

```bash
./template_functions
```
Sortie (exemple) :
```
a = 3, b = 2
min(a, b) = 2
max(a, b) = 3
c = chaine2, d = chaine1
min(c, d) = chaine1
max(c, d) = chaine2
```

### Exercice 01 : Iter
Implémente une fonction template `iter` pour appliquer une fonction à chaque élément d'un tableau.

```bash
./iter
```
Sortie (exemple) :
```
Array: [1, 2, 3, 4, 5]
After applying print: 1 2 3 4 5
After applying increment: [2, 3, 4, 5, 6]
```

### Exercice 02 : Array
Crée une classe template `Array` pour gérer des tableaux dynamiques avec accès sécurisé.

```bash
./array
```
Sortie (exemple) :
```
Array created with size: 5
Array: [0, 0, 0, 0, 0]
Array[2] = 42
Array: [0, 0, 42, 0, 0]
Size: 5
Error: Index out of bounds
Array copy created: [0, 0, 42, 0, 0]
Array copy modified: [0, 0, 99, 0, 0]
Original array unchanged: [0, 0, 42, 0, 0]
```

## Fonctionnement détaillé
### Exercice 00 : Start with a few functions
- **Fonctions templates** :
  - `swap(T &a, T &b)` : Échange les valeurs de deux paramètres.
  - `min(T const &a, T const &b)` : Retourne la plus petite valeur (ou `b` si égaux).
  - `max(T const &a, T const &b)` : Retourne la plus grande valeur (ou `b` si égaux).
- **Exigences** :
  - Les types doivent supporter les opérateurs de comparaison (`<`, `>`, `==`).
  - Définies dans un fichier d'en-tête (`whatever.hpp`).
- **Objectif** : Comprendre la création et l'utilisation de fonctions templates génériques.

### Exercice 01 : Iter
- **Fonction template `iter`** :
  - Signature : `iter(T *array, size_t length, void (*func)(T &))`.
  - Applique la fonction `func` à chaque élément du tableau `array` de taille `length`.
  - Supporte les éléments const et non-const via une surcharge ou une conception générique.
- **Exigences** :
  - Fonctionne avec tout type de tableau.
  - La fonction passée peut prendre des arguments par référence const ou non-const.
- **Objectif** : Maîtriser l'itération sur des tableaux génériques avec des fonctions templates.

### Exercice 02 : Array
- **Classe template `Array`** :
  - Contient un tableau dynamique d'éléments de type `T`.
  - Constructeurs :
    - Par défaut : Crée un tableau vide.
    - Avec taille : Crée un tableau de `n` éléments initialisés par défaut.
    - Par copie : Copie profonde pour éviter les modifications croisées.
  - Opérateurs :
    - `operator[]` : Accès aux éléments avec vérification des bornes (lance `std::exception` si hors limites).
    - Opérateur d'affectation : Copie profonde.
  - Fonction : `size()` retourne la taille du tableau (const).
  - Utilise `new[]` pour l'allocation, évite les allocations préventives.
- **Exigences** :
  - Respecte la forme canonique de Coplien.
  - Gère la mémoire proprement pour éviter les fuites.
- **Objectif** : Concevoir une classe template pour gérer des tableaux dynamiques sécurisés.

## Gestion des erreurs
- **Ex00** : Vérifie que les types utilisés supportent les opérateurs de comparaison.
- **Ex01** : Gère les tableaux nuls ou de taille zéro en évitant les erreurs d'accès.
- **Ex02** : Lance une `std::exception` pour les indices hors limites.

## Codes de sortie
- `0` : Succès.
- Pas d'erreurs spécifiques définies, mais les exceptions sont capturées et affichées.

## Limitations
- Conforme au standard C++98 uniquement.
- Pas d'utilisation de `using namespace` ni de `friend` (sinon -42).
- Pas de STL (vector, map, etc.) ni d'algorithmes (`<algorithm>` interdit).
- Pas de fonctions C comme `printf`, `malloc`, `free` (sinon 0).
- Les fuites de mémoire doivent être évitées.
- Pas de fonctions membres implémentées dans les fichiers d'en-tête (sauf templates).
- Les classes doivent respecter la forme canonique de Coplien.

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** :

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis d'approfondir ma compréhension des templates, de l'itération générique, et de la gestion de tableaux dynamiques en C++98.

---

# CPP07 - README

## Description
CPP07 is the eighth module of the C++ curriculum at 42 school. This project focuses on templates in C++98, exploring generic functions, iteration over generic arrays, and creating a template class for managing dynamic arrays. The exercises involve implementing generic functions (`swap`, `min`, `max`), an iteration function (`iter`), and an `Array` class to handle arrays of any type, all while adhering to C++98 constraints.

The goal is to master the following concepts:
- Creating and using template functions for generic operations.
- Iterating over arrays of any type with a template function.
- Designing a template class for managing dynamic arrays with safe memory handling.
- Adhering to C++98 conventions, including the Orthodox Canonical Form for classes.

## Project Structure
The project is divided into three exercises, each in its own directory:

- **`ex00/`**: *Start with a few functions* - Implements template functions `swap`, `min`, and `max`.
  - Files: `Makefile`, `main.cpp`, `whatever.hpp`.
- **`ex01/`**: *Iter* - Implements the template function `iter` for array iteration.
  - Files: `Makefile`, `main.cpp`, `iter.hpp`.
- **`ex02/`**: *Array* - Creates a template class `Array` for managing dynamic arrays.
  - Files: `Makefile`, `main.cpp`, `Array.hpp`, `Array.tpp` (optional).

## Prerequisites
- A Unix-like system (Linux, macOS).
- A C++ compiler compatible with C++98 (e.g., `g++`).
- Standard C++ libraries (`iostream`, `string`, etc.).
- No access to C++11 or external libraries (Boost is forbidden).

## Compilation
For each exercise, navigate to its directory (`ex00`, `ex01`, `ex02`) and run:
```bash
make
```
This generates an executable for each exercise. Ensure compilation flags include `-Wall -Wextra -Werror -std=c++98`.

## Usage
### Exercise 00: Start with a few functions
Implements template functions `swap`, `min`, and `max` to manipulate values of any comparable type.

```bash
./template_functions
```
Output (example):
```
a = 3, b = 2
min(a, b) = 2
max(a, b) = 3
c = chaine2, d = chaine1
min(c, d) = chaine1
max(c, d) = chaine2
```

### Exercise 01: Iter
Implements a template function `iter` to apply a function to each element of an array.

```bash
./iter
```
Output (example):
```
Array: [1, 2, 3, 4, 5]
After applying print: 1 2 3 4 5
After applying increment: [2, 3, 4, 5, 6]
```

### Exercise 02: Array
Creates a template class `Array` to manage dynamic arrays with safe access.

```bash
./array
```
Output (example):
```
Array created with size: 5
Array: [0, 0, 0, 0, 0]
Array[2] = 42
Array: [0, 0, 42, 0, 0]
Size: 5
Error: Index out of bounds
Array copy created: [0, 0, 42, 0, 0]
Array copy modified: [0, 0, 99, 0, 0]
Original array unchanged: [0, 0, 42, 0, 0]
```

## Detailed Functionality
### Exercise 00: Start with a few functions
- **Template Functions**:
  - `swap(T &a, T &b)`: Swaps the values of two parameters.
  - `min(T const &a, T const &b)`: Returns the smallest value (or `b` if equal).
  - `max(T const &a, T const &b)`: Returns the largest value (or `b` if equal).
- **Requirements**:
  - Types must support comparison operators (`<`, `>`, `==`).
  - Defined in a header file (`whatever.hpp`).
- **Objective**: Understand creating and using generic template functions.

### Exercise 01: Iter
- **Template Function `iter`**:
  - Signature: `iter(T *array, size_t length, void (*func)(T &))`.
  - Applies `func` to each element of the array `array` of size `length`.
  - Supports const and non-const elements via overloading or generic design.
- **Requirements**:
  - Works with any array type.
  - The function passed can take arguments by const or non-const reference.
- **Objective**: Master iteration over generic arrays with template functions.

### Exercise 02: Array
- **Template Class `Array`**:
  - Contains a dynamic array of type `T` elements.
  - Constructors:
    - Default: Creates an empty array.
    - With size: Creates an array of `n` default-initialized elements.
    - Copy: Deep copy to avoid cross-modification.
  - Operators:
    - `operator[]`: Accesses elements with bounds checking (throws `std::exception` if out of bounds).
    - Assignment operator: Deep copy.
  - Function: `size()` returns the array size (const).
  - Uses `new[]` for allocation, avoids preventive allocation.
- **Requirements**:
  - Adheres to the Orthodox Canonical Form.
  - Manages memory properly to avoid leaks.
- **Objective**: Design a template class for managing safe dynamic arrays.

## Error Handling
- **Ex00**: Ensures types support comparison operators.
- **Ex01**: Handles null arrays or zero size to avoid access errors.
- **Ex02**: Throws `std::exception` for out-of-bounds indices.

## Exit Codes
- `0`: Success.
- No specific error codes defined, but exceptions are caught and displayed.

## Limitations
- Strictly adheres to C++98.
- No `using namespace` or `friend` keywords (otherwise -42).
- No STL containers or `<algorithm>` (otherwise -42).
- No C functions like `printf`, `malloc`, `free` (otherwise 0).
- Memory leaks must be avoided.
- No member functions implemented in header files (except templates).
- Classes must adhere to the Orthodox Canonical Form.

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**:

## Acknowledgments
Thanks to 42 school for this project, which allowed me to deepen my understanding of templates, generic iteration, and dynamic array management in C++98.
