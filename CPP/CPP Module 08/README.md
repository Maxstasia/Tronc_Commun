# CPP08 - README

---

## Description
CPP08 est le neuvième module du parcours C++ dans le cadre du cursus de l'école 42. Ce projet se concentre sur l'utilisation des conteneurs, itérateurs et algorithmes de la bibliothèque standard STL en C++98. Les exercices impliquent la création d'une fonction pour rechercher des éléments dans un conteneur, une classe pour gérer une liste d'entiers avec calcul des écarts, et une version itérable de la pile STL (`std::stack`). L'accent est mis sur l'utilisation optimale des conteneurs STL (comme `std::vector`, `std::list`) et des algorithmes STL (comme ceux de `<algorithm>`), tout en respectant les contraintes du standard C++98.

L'objectif est de maîtriser les concepts suivants :
- Utilisation des conteneurs STL pour stocker et manipuler des données.
- Application des algorithmes STL pour effectuer des opérations sur les conteneurs.
- Création de conteneurs personnalisés avec des itérateurs compatibles STL.
- Gestion des exceptions pour les erreurs spécifiques (ex. conteneur vide, élément non trouvé).
- Respect des conventions C++98, y compris la forme canonique pour les classes.

## Structure du projet
Le projet est divisé en trois exercices, chacun dans son propre dossier :

- **`ex00/`** : *Easy find* - Implémentation de la fonction template `easyfind` pour rechercher un élément dans un conteneur.
  - Fichiers : `Makefile`, `main.cpp`, `easyfind.hpp`, `easyfind.tpp` (optionnel).
- **`ex01/`** : *Span* - Création de la classe `Span` pour gérer une liste d'entiers avec calcul des écarts.
  - Fichiers : `Makefile`, `main.cpp`, `Span.hpp`, `Span.cpp`.
- **`ex02/`** : *Mutated abomination* - Implémentation de la classe `MutantStack` pour rendre `std::stack` itérable.
  - Fichiers : `Makefile`, `main.cpp`, `MutantStack.hpp`, `MutantStack.tpp` (optionnel).

## Prérequis
- Un système Unix-like (Linux, macOS).
- Un compilateur C++ compatible avec le standard C++98 (ex. `g++`).
- Les bibliothèques standard C++ (`vector`, `list`, `algorithm`, etc.).
- Aucun accès à C++11 ou bibliothèques externes (Boost interdit).

## Compilation
Pour chaque exercice, accédez au dossier correspondant (`ex00`, `ex01`, `ex02`) et exécutez :
```bash
make
```
Cela génère un exécutable pour chaque exercice. Assurez-vous que les flags de compilation incluent `-Wall -Wextra -Werror -std=c++98`.

## Utilisation
### Exercice 00 : Easy find
Implémente une fonction template `easyfind` pour rechercher la première occurrence d'un entier dans un conteneur.

```bash
./easyfind
```
Sortie (exemple) :
```
Container: [1, 2, 3, 4, 5]
Found 3 at position: 2
Value 6 not found: exception thrown
```

### Exercice 01 : Span
Crée une classe `Span` pour stocker un maximum de `N` entiers et calculer les écarts minimum et maximum.

```bash
./span
```
Sortie (exemple) :
```
Span created with capacity: 5
Added: 6, 3, 17, 9, 11
Shortest span: 2
Longest span: 14
Error: Cannot add number, Span is full
Error: Cannot compute span, not enough numbers
```

### Exercice 02 : Mutated abomination
Crée une classe `MutantStack` qui rend `std::stack` itérable.

```bash
./mutantstack
```
Sortie (exemple) :
```
MutantStack top: 17
MutantStack size: 1
After pushing 5, 3, 7, 0: size = 4
Iterating: 5 3 7 0
After pop: size = 3
Iterating: 5 3 7
```

## Fonctionnement détaillé
### Exercice 00 : Easy find
- **Fonction template `easyfind`** :
  - Signature : `easyfind(T &container, int value)`.
  - Recherche la première occurrence de `value` dans `container` (un conteneur STL comme `std::vector` ou `std::list`).
  - Utilise un itérateur pour parcourir le conteneur, potentiellement avec `std::find` (de `<algorithm>`).
  - Lance une exception (ex. `std::exception`) si la valeur n'est pas trouvée.
- **Exigences** :
  - Fonctionne avec les conteneurs séquentiels (non associatifs).
  - Utilise les outils STL pour une implémentation efficace.
- **Objectif** : Comprendre l'utilisation des itérateurs et algorithmes STL pour la recherche.

### Exercice 01 : Span
- **Classe `Span`** :
  - Stocke un maximum de `N` entiers (fixé à la construction).
  - Attributs : Un conteneur STL (ex. `std::vector<int>`) et une capacité `N`.
  - Fonctions :
    - `addNumber(int n)` : Ajoute un entier, lance une exception si plein.
    - `shortestSpan()` : Calcule l'écart minimum entre deux nombres, lance une exception si moins de 2 nombres.
    - `longestSpan()` : Calcule l'écart maximum, lance une exception si moins de 2 nombres.
  - Respecte la forme canonique de Coplien.
- **Exigences** :
  - Utilise un conteneur STL pour stocker les entiers.
  - Testé avec au moins 10 000 nombres pour vérifier l'efficacité.
- **Objectif** : Maîtriser la gestion de conteneurs STL avec des calculs sur les données.

### Exercice 02 : Mutated abomination
- **Classe `MutantStack`** :
  - Hérite de `std::stack<T>` et ajoute des itérateurs compatibles STL.
  - Fournit toutes les fonctions de `std::stack` (ex. `push`, `pop`, `top`, `size`).
  - Ajoute `begin()` et `end()` pour permettre l'itération.
  - Implémentation typique : Utilise `std::stack::c` (le conteneur sous-jacent, souvent `std::deque`) pour fournir des itérateurs.
  - Respecte la forme canonique de Coplien.
- **Exigences** :
  - Rend la pile itérable tout en conservant son comportement standard.
  - Utilise les fonctionnalités STL pour l'itération.
- **Objectif** : Étendre un conteneur STL non itérable avec des itérateurs compatibles.

## Gestion des erreurs
- **Ex00** : Lance une exception si la valeur recherchée n'est pas trouvée.
- **Ex01** : Lance une exception si le conteneur est plein (`addNumber`) ou si le calcul d'écart est impossible (moins de 2 nombres).
- **Ex02** : Gère les erreurs liées à l'accès à une pile vide via les fonctions standard de `std::stack`.

## Codes de sortie
- `0` : Succès.
- Pas d'erreurs spécifiques définies, mais les exceptions sont capturées et affichées.

## Limitations
- Conforme au standard C++98 uniquement.
- Pas d'utilisation de `using namespace` ni de `friend` (sinon -42).
- Les conteneurs et algorithmes STL sont obligatoires dans ce module.
- Pas de fonctions C comme `printf`, `malloc`, `free` (sinon 0).
- Les fuites de mémoire doivent être évitées.
- Pas de fonctions membres implémentées dans les fichiers d'en-tête (sauf templates).
- Les classes doivent respecter la forme canonique de Coplien.

## Règles spécifiques au module
- Les conteneurs STL (ex. `std::vector`, `std::list`) et les algorithmes STL (ex. `<algorithm>`) doivent être utilisés autant que possible.
- Une note très basse sera attribuée si les outils STL ne sont pas utilisés, même si le code fonctionne.

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** :

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis d'approfondir ma compréhension des conteneurs, itérateurs et algorithmes STL en C++98.

---

# CPP08 - README

## Description
CPP08 is the ninth module of the C++ curriculum at 42 school. This project focuses on using STL containers, iterators, and algorithms in C++98. The exercises involve creating a function to search for elements in a container, a class to manage a list of integers with span calculations, and an iterable version of the STL stack (`std::stack`). Emphasis is placed on optimally using STL containers (like `std::vector`, `std::list`) and algorithms (like those in `<algorithm>`), while adhering to C++98 constraints.

The goal is to master the following concepts:
- Using STL containers to store and manipulate data.
- Applying STL algorithms for operations on containers.
- Creating custom containers with STL-compatible iterators.
- Handling exceptions for specific errors (e.g., empty container, element not found).
- Adhering to C++98 conventions, including the Orthodox Canonical Form for classes.

## Project Structure
The project is divided into three exercises, each in its own directory:

- **`ex00/`**: *Easy find* - Implements the template function `easyfind` to search for an element in a container.
  - Files: `Makefile`, `main.cpp`, `easyfind.hpp`, `easyfind.tpp` (optional).
- **`ex01/`**: *Span* - Creates the `Span` class to manage a list of integers with span calculations.
  - Files: `Makefile`, `main.cpp`, `Span.hpp`, `Span.cpp`.
- **`ex02/`**: *Mutated abomination* - Implements the `MutantStack` class to make `std::stack` iterable.
  - Files: `Makefile`, `main.cpp`, `MutantStack.hpp`, `MutantStack.tpp` (optional).

## Prerequisites
- A Unix-like system (Linux, macOS).
- A C++ compiler compatible with C++98 (e.g., `g++`).
- Standard C++ libraries (`vector`, `list`, `algorithm`, etc.).
- No access to C++11 or external libraries (Boost is forbidden).

## Compilation
For each exercise, navigate to its directory (`ex00`, `ex01`, `ex02`) and run:
```bash
make
```
This generates an executable for each exercise. Ensure compilation flags include `-Wall -Wextra -Werror -std=c++98`.

## Usage
### Exercise 00: Easy find
Implements a template function `easyfind` to find the first occurrence of an integer in a container.

```bash
./easyfind
```
Output (example):
```
Container: [1, 2, 3, 4, 5]
Found 3 at position: 2
Value 6 not found: exception thrown
```

### Exercise 01: Span
Creates a `Span` class to store up to `N` integers and compute the shortest and longest spans.

```bash
./span
```
Output (example):
```
Span created with capacity: 5
Added: 6, 3, 17, 9, 11
Shortest span: 2
Longest span: 14
Error: Cannot add number, Span is full
Error: Cannot compute span, not enough numbers
```

### Exercise 02: Mutated abomination
Creates a `MutantStack` class that makes `std::stack` iterable.

```bash
./mutantstack
```
Output (example):
```
MutantStack top: 17
MutantStack size: 1
After pushing 5, 3, 7, 0: size = 4
Iterating: 5 3 7 0
After pop: size = 3
Iterating: 5 3 7
```

## Detailed Functionality
### Exercise 00: Easy find
- **Template Function `easyfind`**:
  - Signature: `easyfind(T &container, int value)`.
  - Finds the first occurrence of `value` in `container` (an STL container like `std::vector` or `std::list`).
  - Uses an iterator to traverse the container, potentially with `std::find` (from `<algorithm>`).
  - Throws an exception (e.g., `std::exception`) if the value is not found.
- **Requirements**:
  - Works with sequential containers (not associative ones).
  - Uses STL tools for efficient implementation.
- **Objective**: Understand using STL iterators and algorithms for searching.

### Exercise 01: Span
- **Class `Span`**:
  - Stores up to `N` integers (set at construction).
  - Attributes: An STL container (e.g., `std::vector<int>`) and capacity `N`.
  - Functions:
    - `addNumber(int n)`: Adds an integer, throws an exception if full.
    - `shortestSpan()`: Computes the minimum span between two numbers, throws an exception if fewer than 2 numbers.
    - `longestSpan()`: Computes the maximum span, throws an exception if fewer than 2 numbers.
  - Adheres to the Orthodox Canonical Form.
- **Requirements**:
  - Uses an STL container to store integers.
  - Tested with at least 10,000 numbers for efficiency.
- **Objective**: Master managing STL containers with data calculations.

### Exercise 02: Mutated abomination
- **Class `MutantStack`**:
  - Inherits from `std::stack<T>` and adds STL-compatible iterators.
  - Provides all `std::stack` functions (e.g., `push`, `pop`, `top`, `size`).
  - Adds `begin()` and `end()` for iteration.
  - Typical implementation: Uses `std::stack::c` (underlying container, often `std::deque`) to provide iterators.
  - Adheres to the Orthodox Canonical Form.
- **Requirements**:
  - Makes the stack iterable while preserving standard behavior.
  - Uses STL features for iteration.
- **Objective**: Extend a non-iterable STL container with compatible iterators.

## Error Handling
- **Ex00**: Throws an exception if the searched value is not found.
- **Ex01**: Throws an exception if the container is full (`addNumber`) or if span calculation is impossible (fewer than 2 numbers).
- **Ex02**: Handles errors related to accessing an empty stack via standard `std::stack` functions.

## Exit Codes
- `0`: Success.
- No specific error codes defined, but exceptions are caught and displayed.

## Limitations
- Strictly adheres to C++98.
- No `using namespace` or `friend` keywords (otherwise -42).
- STL containers and algorithms are mandatory in this module.
- No C functions like `printf`, `malloc`, `free` (otherwise 0).
- Memory leaks must be avoided.
- No member functions implemented in header files (except templates).
- Classes must adhere to the Orthodox Canonical Form.

## Module-Specific Rules
- STL containers (e.g., `std::vector`, `std::list`) and algorithms (e.g., `<algorithm>`) must be used as much as possible.
- A very low grade will be given if STL tools are not used, even if the code works.

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**:

## Acknowledgments
Thanks to 42 school for this project, which allowed me to deepen my understanding of STL containers, iterators, and algorithms in C++98.
