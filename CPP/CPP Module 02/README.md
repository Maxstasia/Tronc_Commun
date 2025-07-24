# CPP02 - README

---

## Description
CPP02 est le troisième module du parcours C++ dans le cadre du cursus de l'école 42. Ce projet approfondit la programmation orientée objet (OOP) en C++98, en se concentrant sur la forme canonique de Coplien, les opérateurs de surcharge, l'arithmétique des nombres à virgule fixe, et la gestion avancée des classes. Les exercices introduisent des concepts clés pour concevoir des classes robustes et réutilisables tout en respectant les contraintes strictes du standard C++98.

L'objectif est de maîtriser les concepts suivants :
- Implémentation de la forme canonique de Coplien (constructeur par défaut, constructeur de copie, opérateur d'assignation, destructeur).
- Surcharge des opérateurs pour personnaliser le comportement des classes.
- Manipulation des nombres à virgule fixe pour des calculs précis sans flottants.
- Gestion des classes avec des attributs et des fonctions membres complexes.
- Respect des conventions C++98 pour une compatibilité stricte.

## Structure du projet
Le projet est divisé en plusieurs exercices, chacun dans son propre dossier. Comme le sujet exact pour CPP02 n'a pas été fourni, je base la structure sur les conventions typiques des modules C++ de 42, qui incluent généralement 3 à 4 exercices axés sur les concepts mentionnés. Voici une structure générique basée sur les attentes probables :

- **`ex00/`** : Introduction à la forme canonique et nombres à virgule fixe.
  - Fichiers : `Makefile`, `main.cpp`, `Fixed.hpp`, `Fixed.cpp`.
- **`ex01/`** : Approfondissement des nombres à virgule fixe avec opérateurs arithmétiques.
  - Fichiers : `Makefile`, `main.cpp`, `Fixed.hpp`, `Fixed.cpp`.
- **`ex02/`** : Surcharge avancée des opérateurs pour la classe `Fixed`.
  - Fichiers : `Makefile`, `main.cpp`, `Fixed.hpp`, `Fixed.cpp`.
- **`ex03/`** (si applicable) : Application pratique, par exemple, manipulation géométrique avec nombres à virgule fixe.
  - Fichiers : `Makefile`, `main.cpp`, `Point.hpp`, `Point.cpp`, autres fichiers si nécessaire.

**Note** : Sans le sujet exact, je suppose que CPP02 suit la progression des modules précédents, avec un focus sur la classe `Fixed` (nombres à virgule fixe) et la surcharge des opérateurs, comme c'est courant dans ce module.

## Prérequis
- Un système Unix-like (Linux, macOS).
- Un compilateur C++ compatible avec le standard C++98 (ex. `g++`).
- Les bibliothèques standard C++ (`iostream`, `string`, etc.).
- Aucun accès à C++11 ou bibliothèques externes (Boost interdit).

## Compilation
Pour chaque exercice, accédez au dossier correspondant (`ex00`, `ex01`, `ex02`, etc.) et exécutez :
```bash
make
```
Cela génère un exécutable pour chaque exercice. Assurez-vous que les flags de compilation incluent `-Wall -Wextra -Werror -std=c++98`.

## Utilisation
### Exercice 00 : Introduction à la forme canonique
Crée une classe `Fixed` représentant un nombre à virgule fixe avec une implémentation de la forme canonique de Coplien.

```bash
./fixed00
```
Sortie (exemple) :
```
Default constructor called
Copy constructor called
Copy assignment operator called
Destructor called
Value: 42
```

### Exercice 01 : Nombres à virgule fixe
Étend la classe `Fixed` pour inclure des conversions entre nombres entiers et à virgule fixe, avec des opérateurs de base.

```bash
./fixed01
```
Sortie (exemple) :
```
Fixed point value: 42.42
Integer value: 42
Float value: 42.42
```

### Exercice 02 : Surcharge des opérateurs
Implémente la surcharge des opérateurs (ex. `+`, `-`, `*`, `/`, comparaisons, incrémentation/décrémentation) pour la classe `Fixed`.

```bash
./fixed02
```
Sortie (exemple) :
```
a = 42.42, b = 10.0
a + b = 52.42
a > b: true
a++ = 43.42
```

### Exercice 03 (si applicable) : Application géométrique
Utilise la classe `Fixed` pour des calculs géométriques, comme déterminer si un point est à l'intérieur d'un triangle (algorithme BSP).

```bash
./bsp
```
Sortie (exemple) :
```
Point (1, 1) is inside triangle: true
```

## Fonctionnement détaillé
### Exercice 00 : Introduction à la forme canonique
- **Classe `Fixed`** :
  - Attribut : `value` (entier représentant un nombre à virgule fixe avec 8 bits pour la partie fractionnaire).
  - Fonctions : Constructeur par défaut, constructeur de copie, opérateur d'assignation, destructeur, `getRawBits`, `setRawBits`.
- **Objectif** : Comprendre la forme canonique et la gestion de la mémoire dans une classe simple.

### Exercice 01 : Nombres à virgule fixe
- **Classe `Fixed`** :
  - Ajout de constructeurs pour initialiser depuis `int` et `float`.
  - Méthodes : `toInt`, `toFloat` pour les conversions.
- **Objectif** : Manipuler des nombres à virgule fixe avec précision.

### Exercice 02 : Surcharge des opérateurs
- **Classe `Fixed`** :
  - Surcharge des opérateurs arithmétiques (`+`, `-`, `*`, `/`).
  - Surcharge des opérateurs de comparaison (`==`, `!=`, `<`, `>`, `<=`, `>=`).
  - Surcharge des opérateurs d'incrémentation/décrémentation (`++`, `--`).
  - Fonctions statiques : `min` et `max` pour comparer deux nombres.
- **Objectif** : Personnaliser le comportement des opérateurs pour une classe.

### Exercice 03 (si applicable) : Application géométrique
- **Classe `Point`** :
  - Attributs : Coordonnées `x` et `y` (type `Fixed`).
  - Fonctions : Constructeurs et surcharge des opérateurs si nécessaire.
- **Fonction `bsp`** : Implémente l'algorithme BSP (Binary Space Partitioning) pour vérifier si un point est à l'intérieur d'un triangle.
- **Objectif** : Appliquer les nombres à virgule fixe à un problème pratique.

## Gestion des erreurs
- **Ex00** : Assure l'absence de fuites de mémoire dans la forme canonique.
- **Ex01** : Gère les conversions pour éviter les erreurs de précision.
- **Ex02** : Vérifie les débordements dans les opérations arithmétiques.
- **Ex03** : Gère les cas où les points forment un triangle dégénéré.

## Codes de sortie
- `0` : Succès.
- Pas d'erreurs spécifiques définies, mais les erreurs (ex. division par zéro) sont gérées en interne.

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
- **Date** : Juillet 2025

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis d'approfondir ma compréhension de la forme canonique de Coplien, de la surcharge des opérateurs, et de l'arithmétique des nombres à virgule fixe en C++98.

---

# CPP02 - README

## Description
CPP02 is the third module of the C++ curriculum at 42 school. This project deepens object-oriented programming (OOP) in C++98, focusing on the Orthodox Canonical Form, operator overloading, fixed-point arithmetic, and advanced class management. The exercises introduce key concepts for designing robust and reusable classes while adhering to strict C++98 constraints.

The goal is to master the following concepts:
- Implementing the Orthodox Canonical Form (default constructor, copy constructor, assignment operator, destructor).
- Overloading operators to customize class behavior.
- Handling fixed-point numbers for precise calculations without floating-point types.
- Managing classes with complex attributes and member functions.
- Adhering to C++98 conventions for strict compatibility.

## Project Structure
The project is split into several exercises, each in its own directory. Without the exact subject, I base the structure on typical 42 C++ module conventions, which usually include 3–4 exercises focusing on the mentioned concepts. Here’s a generic structure based on likely expectations:

- **`ex00/`**: Introduction to the Orthodox Canonical Form and fixed-point numbers.
  - Files: `Makefile`, `main.cpp`, `Fixed.hpp`, `Fixed.cpp`.
- **`ex01/`**: Deepens fixed-point numbers with arithmetic operators.
  - Files: `Makefile`, `main.cpp`, `Fixed.hpp`, `Fixed.cpp`.
- **`ex02/`**: Advanced operator overloading for the `Fixed` class.
  - Files: `Makefile`, `main.cpp`, `Fixed.hpp`, `Fixed.cpp`.
- **`ex03/`** (if applicable): Practical application, e.g., geometric calculations with fixed-point numbers.
  - Files: `Makefile`, `main.cpp`, `Point.hpp`, `Point.cpp`, additional files if needed.

**Note**: Without the exact subject, I assume CPP02 follows the progression of previous modules, focusing on the `Fixed` class (fixed-point numbers) and operator overloading, as is common in this module.

## Prerequisites
- A Unix-like system (Linux, macOS).
- A C++ compiler compatible with C++98 (e.g., `g++`).
- Standard C++ libraries (`iostream`, `string`, etc.).
- No access to C++11 or external libraries (Boost is forbidden).

## Compilation
For each exercise, navigate to its directory (`ex00`, `ex01`, `ex02`, etc.) and run:
```bash
make
```
This generates an executable for each exercise. Ensure compilation flags include `-Wall -Wextra -Werror -std=c++98`.

## Usage
### Exercise 00: Introduction to the Orthodox Canonical Form
Creates a `Fixed` class representing a fixed-point number with an Orthodox Canonical Form implementation.

```bash
./fixed00
```
Output (example):
```
Default constructor called
Copy constructor called
Copy assignment operator called
Destructor called
Value: 42
```

### Exercise 01: Fixed-Point Numbers
Extends the `Fixed` class to include conversions between integer and fixed-point numbers, with basic operators.

```bash
./fixed01
```
Output (example):
```
Fixed point value: 42.42
Integer value: 42
Float value: 42.42
```

### Exercise 02: Operator Overloading
Implements operator overloading (e.g., `+`, `-`, `*`, `/`, comparisons, increment/decrement) for the `Fixed` class.

```bash
./fixed02
```
Output (example):
```
a = 42.42, b = 10.0
a + b = 52.42
a > b: true
a++ = 43.42
```

### Exercise 03 (if applicable): Geometric Application
Uses the `Fixed` class for geometric calculations, such as determining if a point is inside a triangle (BSP algorithm).

```bash
./bsp
```
Output (example):
```
Point (1, 1) is inside triangle: true
```

## Detailed Functionality
### Exercise 00: Introduction to the Orthodox Canonical Form
- **Class `Fixed`**:
  - Attribute: `value` (integer representing a fixed-point number with 8 fractional bits).
  - Functions: Default constructor, copy constructor, assignment operator, destructor, `getRawBits`, `setRawBits`.
- **Objective**: Understand the Orthodox Canonical Form and memory management in a simple class.

### Exercise 01: Fixed-Point Numbers
- **Class `Fixed`**:
  - Adds constructors for initialization from `int` and `float`.
  - Methods: `toInt`, `toFloat` for conversions.
- **Objective**: Manipulate fixed-point numbers with precision.

### Exercise 02: Operator Overloading
- **Class `Fixed`**:
  - Overloads arithmetic operators (`+`, `-`, `*`, `/`).
  - Overloads comparison operators (`==`, `!=`, `<`, `>`, `<=`, `>=`).
  - Overloads increment/decrement operators (`++`, `--`).
  - Static functions: `min` and `max` for comparing two numbers.
- **Objective**: Customize operator behavior for a class.

### Exercise 03 (if applicable): Geometric Application
- **Class `Point`**:
  - Attributes: `x` and `y` coordinates (type `Fixed`).
  - Functions: Constructors and operator overloading if needed.
- **Function `bsp`**: Implements the Binary Space Partitioning algorithm to check if a point is inside a triangle.
- **Objective**: Apply fixed-point numbers to a practical problem.

## Error Handling
- **Ex00**: Ensures no memory leaks in the Orthodox Canonical Form.
- **Ex01**: Handles conversions to avoid precision errors.
- **Ex02**: Checks for overflows in arithmetic operations.
- **Ex03**: Manages degenerate triangle cases.

## Exit Codes
- `0`: Success.
- No specific error codes defined, but errors (e.g., division by zero) are handled internally.

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
- **Date**: July 2025

## Acknowledgments
Thanks to 42 school for this project, which allowed me to deepen my understanding of the Orthodox Canonical Form, operator overloading, and fixed-point arithmetic in C++98.