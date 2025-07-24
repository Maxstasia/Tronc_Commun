# CPP03 - README

---

## Description
CPP03 est le quatrième module du parcours C++ dans le cadre du cursus de l'école 42. Ce projet se concentre sur l'héritage en programmation orientée objet (OOP) sous le standard C++98. Il explore la création de classes dérivées, la gestion de l'héritage multiple, et la résolution des ambiguïtés liées à l'héritage en diamant. Les exercices impliquent la création de classes représentant des robots (`ClapTrap`, `ScavTrap`, `FragTrap`, `DiamondTrap`) avec des comportements spécifiques, tout en respectant la forme canonique de Coplien.

L'objectif est de maîtriser les concepts suivants :
- Héritage simple et multiple pour réutiliser et étendre le code.
- Gestion de la construction et de la destruction en chaîne dans les hiérarchies de classes.
- Résolution des ambiguïtés dans l'héritage en diamant.
- Implémentation de fonctions membres spécifiques pour chaque classe dérivée.
- Respect des conventions C++98, y compris la forme canonique.

## Structure du projet
Le projet est divisé en quatre exercices, chacun dans son propre dossier :

- **`ex00/`** : *Aaaaand... OPEN!* - Création de la classe de base `ClapTrap`.
  - Fichiers : `Makefile`, `main.cpp`, `ClapTrap.hpp`, `ClapTrap.cpp`.
- **`ex01/`** : *Serena, my love!* - Création de la classe dérivée `ScavTrap`.
  - Fichiers : Fichiers de l'exercice précédent + `ScavTrap.hpp`, `ScavTrap.cpp`.
- **`ex02/`** : *Repetitive work* - Création de la classe dérivée `FragTrap`.
  - Fichiers : Fichiers des exercices précédents + `FragTrap.hpp`, `FragTrap.cpp`.
- **`ex03/`** : *Now it's weird!* - Création de la classe `DiamondTrap` avec héritage multiple.
  - Fichiers : Fichiers des exercices précédents + `DiamondTrap.hpp`, `DiamondTrap.cpp`.

## Prérequis
- Un système Unix-like (Linux, macOS).
- Un compilateur C++ compatible avec le standard C++98 (ex. `g++`).
- Les bibliothèques standard C++ (`iostream`, `string`, etc.).
- Aucun accès à C++11 ou bibliothèques externes (Boost interdit).

## Compilation
Pour chaque exercice, accédez au dossier correspondant (`ex00`, `ex01`, `ex02`, `ex03`) et exécutez :
```bash
make
```
Cela génère un exécutable pour chaque exercice. Assurez-vous que les flags de compilation incluent `-Wall -Wextra -Werror -std=c++98`.

## Utilisation
### Exercice 00 : Aaaaand... OPEN!
Crée une classe `ClapTrap` avec des attributs et des fonctions pour simuler un robot de combat.

```bash
./claptrap
```
Sortie (exemple) :
```
ClapTrap Robot constructed
ClapTrap Robot attacks Target, causing 0 points of damage!
ClapTrap Robot takes 5 damage!
ClapTrap Robot repaired for 3 hit points!
ClapTrap Robot destructed
```

### Exercice 01 : Serena, my love!
Crée une classe `ScavTrap` qui hérite de `ClapTrap` avec des attributs différents et une capacité spéciale.

```bash
./scavtrap
```
Sortie (exemple) :
```
ClapTrap Serena_clap_name constructed
ScavTrap Serena constructed
ScavTrap Serena attacks Target, causing 20 points of damage!
ScavTrap Serena enters Gate keeper mode
ScavTrap Serena destructed
ClapTrap Serena_clap_name destructed
```

### Exercice 02 : Repetitive work
Crée une classe `FragTrap` qui hérite de `ClapTrap` avec des attributs différents et une capacité spéciale.

```bash
./fragtrap
```
Sortie (exemple) :
```
ClapTrap Frag_clap_name constructed
FragTrap Frag constructed
FragTrap Frag attacks Target, causing 30 points of damage!
FragTrap Frag requests a high five!
FragTrap Frag destructed
ClapTrap Frag_clap_name destructed
```

### Exercice 03 : Now it's weird!
Crée une classe `DiamondTrap` qui hérite à la fois de `ScavTrap` et `FragTrap`, gérant l'héritage en diamant.

```bash
./diamondtrap
```
Sortie (exemple) :
```
ClapTrap Diamond_clap_name constructed
ScavTrap Diamond constructed
FragTrap Diamond constructed
DiamondTrap Diamond constructed
DiamondTrap Diamond says: I am Diamond, my ClapTrap name is Diamond_clap_name
DiamondTrap Diamond attacks Target, causing 20 points of damage!
DiamondTrap Diamond enters Gate keeper mode
DiamondTrap Diamond requests a high five!
DiamondTrap Diamond destructed
FragTrap Diamond destructed
ScavTrap Diamond destructed
ClapTrap Diamond_clap_name destructed
```

## Fonctionnement détaillé
### Exercice 00 : Aaaaand... OPEN!
- **Classe `ClapTrap`** :
  - Attributs privés : `name` (string), `hitPoints` (10), `energyPoints` (10), `attackDamage` (0).
  - Fonctions publiques : `attack` (inflige des dégâts), `takeDamage` (réduit les points de vie), `beRepaired` (restaure les points de vie).
  - Respecte la forme canonique de Coplien.
- **Objectif** : Implémenter une classe de base avec des fonctionnalités de combat et des messages explicites.

### Exercice 01 : Serena, my love!
- **Classe `ScavTrap`** :
  - Hérite de `ClapTrap` avec des attributs : `hitPoints` (100), `energyPoints` (50), `attackDamage` (20).
  - Redéfinit les constructeurs, destructeur, et `attack` avec des messages spécifiques.
  - Fonction spéciale : `guardGate` (affiche un message de mode gardien).
- **Objectif** : Comprendre l'héritage simple et la chaîne de construction/destruction.

### Exercice 02 : Repetitive work
- **Classe `FragTrap`** :
  - Hérite de `ClapTrap` avec des attributs : `hitPoints` (100), `energyPoints` (100), `attackDamage` (30).
  - Redéfinit les constructeurs, destructeur, et `attack` avec des messages spécifiques.
  - Fonction spéciale : `highFivesGuys` (affiche une demande de high-five).
- **Objectif** : Renforcer la compréhension de l'héritage avec une nouvelle classe dérivée.

### Exercice 03 : Now it's weird!
- **Classe `DiamondTrap`** :
  - Hérite de `ScavTrap` et `FragTrap` (héritage multiple en diamant).
  - Attributs : `name` (propre à `DiamondTrap`), `ClapTrap::name` (suffixe `_clap_name`), `hitPoints` (de `FragTrap`), `energyPoints` (de `ScavTrap`), `attackDamage` (de `FragTrap`).
  - Utilise `attack` de `ScavTrap`.
  - Fonction spéciale : `whoAmI` (affiche son nom et son nom `ClapTrap`).
  - Résout les ambiguïtés de l'héritage en diamant (ex. en utilisant l'héritage virtuel pour `ClapTrap`).
- **Objectif** : Maîtriser l'héritage multiple et la gestion des ambiguïtés.

## Gestion des erreurs
- **Ex00** : Vérifie que `ClapTrap` ne peut pas attaquer ou se réparer sans points de vie ou d'énergie.
- **Ex01** : Gère la chaîne de construction/destruction correctement.
- **Ex02** : Assure que les messages spécifiques à `FragTrap` sont affichés.
- **Ex03** : Résout les ambiguïtés de l'héritage en diamant et gère l'instance unique de `ClapTrap`.

## Codes de sortie
- `0` : Succès.
- Pas d'erreurs spécifiques définies, mais les erreurs (ex. manque d'énergie) sont gérées en interne avec des messages.

## Limitations
- Conforme au standard C++98 uniquement.
- Pas d'utilisation de `using namespace` ni de `friend` (sinon -42).
- Pas de STL (vector, map, etc.) ni d'algorithmes (`<algorithm>` interdit).
- Pas de fonctions C comme `printf`, `malloc`, `free` (sinon 0).
- Les fuites de mémoire doivent être évitées.
- Pas de fonctions membres implémentées dans les fichiers d'en-tête (sauf templates).
- Les classes doivent respecter la forme canonique de Coplien (sauf indication contraire).

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** : Juillet 2025

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis d'approfondir ma compréhension de l'héritage simple et multiple, de la forme canonique de Coplien, et de la gestion des ambiguïtés dans l'héritage en diamant en C++98.

---

# CPP03 - README

## Description
CPP03 is the fourth module of the C++ curriculum at 42 school. This project focuses on inheritance in object-oriented programming (OOP) under the C++98 standard. It explores creating derived classes, handling multiple inheritance, and resolving ambiguities related to the diamond problem. The exercises involve creating classes representing robots (`ClapTrap`, `ScavTrap`, `FragTrap`, `DiamondTrap`) with specific behaviors while adhering to the Orthodox Canonical Form.

The goal is to master the following concepts:
- Simple and multiple inheritance for code reuse and extension.
- Managing construction and destruction chains in class hierarchies.
- Resolving ambiguities in the diamond inheritance problem.
- Implementing specific member functions for derived classes.
- Adhering to C++98 conventions, including the Orthodox Canonical Form.

## Project Structure
The project is divided into four exercises, each in its own directory:

- **`ex00/`**: *Aaaaand... OPEN!* - Creates the base `ClapTrap` class.
  - Files: `Makefile`, `main.cpp`, `ClapTrap.hpp`, `ClapTrap.cpp`.
- **`ex01/`**: *Serena, my love!* - Creates the derived `ScavTrap` class.
  - Files: Files from the previous exercise + `ScavTrap.hpp`, `ScavTrap.cpp`.
- **`ex02/`**: *Repetitive work* - Creates the derived `FragTrap` class.
  - Files: Files from previous exercises + `FragTrap.hpp`, `FragTrap.cpp`.
- **`ex03/`**: *Now it's weird!* - Creates the `DiamondTrap` class with multiple inheritance.
  - Files: Files from previous exercises + `DiamondTrap.hpp`, `DiamondTrap.cpp`.

## Prerequisites
- A Unix-like system (Linux, macOS).
- A C++ compiler compatible with C++98 (e.g., `g++`).
- Standard C++ libraries (`iostream`, `string`, etc.).
- No access to C++11 or external libraries (Boost is forbidden).

## Compilation
For each exercise, navigate to its directory (`ex00`, `ex01`, `ex02`, `ex03`) and run:
```bash
make
```
This generates an executable for each exercise. Ensure compilation flags include `-Wall -Wextra -Werror -std=c++98`.

## Usage
### Exercise 00: Aaaaand... OPEN!
Creates a `ClapTrap` class with attributes and functions to simulate a combat robot.

```bash
./claptrap
```
Output (example):
```
ClapTrap Robot constructed
ClapTrap Robot attacks Target, causing 0 points of damage!
ClapTrap Robot takes 5 damage!
ClapTrap Robot repaired for 3 hit points!
ClapTrap Robot destructed
```

### Exercise 01: Serena, my love!
Creates a `ScavTrap` class that inherits from `ClapTrap` with different attributes and a special ability.

```bash
./scavtrap
```
Output (example):
```
ClapTrap Serena_clap_name constructed
ScavTrap Serena constructed
ScavTrap Serena attacks Target, causing 20 points of damage!
ScavTrap Serena enters Gate keeper mode
ScavTrap Serena destructed
ClapTrap Serena_clap_name destructed
```

### Exercise 02: Repetitive work
Creates a `FragTrap` class that inherits from `ClapTrap` with different attributes and a special ability.

```bash
./fragtrap
```
Output (example):
```
ClapTrap Frag_clap_name constructed
FragTrap Frag constructed
FragTrap Frag attacks Target, causing 30 points of damage!
FragTrap Frag requests a high five!
FragTrap Frag destructed
ClapTrap Frag_clap_name destructed
```

### Exercise 03: Now it's weird!
Creates a `DiamondTrap` class that inherits from both `ScavTrap` and `FragTrap`, handling the diamond problem.

```bash
./diamondtrap
```
Output (example):
```
ClapTrap Diamond_clap_name constructed
ScavTrap Diamond constructed
FragTrap Diamond constructed
DiamondTrap Diamond constructed
DiamondTrap Diamond says: I am Diamond, my ClapTrap name is Diamond_clap_name
DiamondTrap Diamond attacks Target, causing 20 points of damage!
DiamondTrap Diamond enters Gate keeper mode
DiamondTrap Diamond requests a high five!
DiamondTrap Diamond destructed
FragTrap Diamond destructed
ScavTrap Diamond destructed
ClapTrap Diamond_clap_name destructed
```

## Detailed Functionality
### Exercise 00: Aaaaand... OPEN!
- **Class `ClapTrap`**:
  - Private attributes: `name` (string), `hitPoints` (10), `energyPoints` (10), `attackDamage` (0).
  - Public functions: `attack` (inflicts damage), `takeDamage` (reduces hit points), `beRepaired` (restores hit points).
  - Adheres to the Orthodox Canonical Form.
- **Objective**: Implement a base class with combat functionality and explicit messages.

### Exercise 01: Serena, my love!
- **Class `ScavTrap`**:
  - Inherits from `ClapTrap` with attributes: `hitPoints` (100), `energyPoints` (50), `attackDamage` (20).
  - Overrides constructors, destructor, and `attack` with specific messages.
  - Special function: `guardGate` (displays Gate keeper mode message).
- **Objective**: Understand simple inheritance and construction/destruction chaining.

### Exercise 02: Repetitive work
- **Class `FragTrap`**:
  - Inherits from `ClapTrap` with attributes: `hitPoints` (100), `energyPoints` (100), `attackDamage` (30).
  - Overrides constructors, destructor, and `attack` with specific messages.
  - Special function: `highFivesGuys` (displays a high-five request).
- **Objective**: Reinforce understanding of inheritance with another derived class.

### Exercise 03: Now it's weird!
- **Class `DiamondTrap`**:
  - Inherits from both `ScavTrap` and `FragTrap` (diamond inheritance).
  - Attributes: `name` (own attribute), `ClapTrap::name` (with `_clap_name` suffix), `hitPoints` (from `FragTrap`), `energyPoints` (from `ScavTrap`), `attackDamage` (from `FragTrap`).
  - Uses `attack` from `ScavTrap`.
  - Special function: `whoAmI` (displays both its name and ClapTrap name).
  - Resolves diamond problem ambiguities (e.g., using virtual inheritance for `ClapTrap`).
- **Objective**: Master multiple inheritance and ambiguity resolution.

## Error Handling
- **Ex00**: Ensures `ClapTrap` cannot attack or repair without hit points or energy.
- **Ex01**: Properly handles construction/destruction chaining.
- **Ex02**: Ensures `FragTrap`-specific messages are displayed.
- **Ex03**: Resolves diamond inheritance ambiguities and ensures a single `ClapTrap` instance.

## Exit Codes
- `0`: Success.
- No specific error codes defined, but errors (e.g., insufficient energy) are handled internally with messages.

## Limitations
- Strictly adheres to C++98.
- No `using namespace` or `friend` keywords (otherwise -42).
- No STL containers or `<algorithm>` (otherwise -42).
- No C functions like `printf`, `malloc`, `free` (otherwise 0).
- Memory leaks must be avoided.
- No member functions implemented in header files (except templates).
- Classes must adhere to the Orthodox Canonical Form (unless otherwise specified).

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**: July 2025

## Acknowledgments
Thanks to 42 school for this project, which allowed me to deepen my understanding of simple and multiple inheritance, the Orthodox Canonical Form, and handling diamond inheritance ambiguities in C++98.