# CPP01 - README

---

## Description
CPP01 est le deuxième module du parcours C++ dans le cadre du cursus de l'école 42. Ce projet approfondit les concepts de la programmation orientée objet (OOP) en C++98, en se concentrant sur la gestion de la mémoire, les pointeurs vers les membres, les références, et l'utilisation de l'instruction `switch`. Il comprend six exercices qui explorent ces notions à travers des scénarios variés : gestion de zombies, manipulation de chaînes, et filtrage de messages.

L'objectif est de maîtriser les concepts suivants :
- Allocation et désallocation de mémoire avec `new` et `delete`.
- Utilisation des pointeurs vers les membres pour appeler des fonctions dynamiquement.
- Manipulation des références pour comprendre la gestion des adresses.
- Utilisation de l'instruction `switch` pour gérer des cas multiples.
- Gestion des flux d'entrée/sortie et des fichiers en C++.
- Conception de classes respectant les conventions C++98.

## Structure du projet
Le projet est divisé en six exercices, chacun dans son propre dossier :
- **`ex00/`** : *BraiiiiiiinnnzzzZ* - Création d'une classe `Zombie` avec allocation sur pile et tas.
  - Fichiers : `Makefile`, `main.cpp`, `Zombie.hpp`, `Zombie.cpp`, `newZombie.cpp`, `randomChump.cpp`.
- **`ex01/`** : *Moar brainz!* - Création d'une horde de zombies avec allocation unique.
  - Fichiers : `Makefile`, `main.cpp`, `Zombie.hpp`, `Zombie.cpp`, `zombieHorde.cpp`.
- **`ex02/`** : *HI THIS IS BRAIN* - Manipulation de pointeurs et références sur une chaîne.
  - Fichiers : `Makefile`, `main.cpp`.
- **`ex03/`** : *Unnecessary violence* - Classes `Weapon`, `HumanA`, et `HumanB` pour gérer des attaques.
  - Fichiers : `Makefile`, `main.cpp`, `Weapon.hpp`, `Weapon.cpp`, `HumanA.hpp`, `HumanA.cpp`, `HumanB.hpp`, `HumanB.cpp`.
- **`ex04/`** : *Sed is for losers* - Remplacement de chaînes dans un fichier sans `std::string::replace`.
  - Fichiers : `Makefile`, `main.cpp`, fichiers supplémentaires si nécessaire.
- **`ex05/`** : *Harl 2.0* - Classe `Harl` avec pointeurs vers fonctions membres pour différents niveaux de logs.
  - Fichiers : `Makefile`, `main.cpp`, `Harl.hpp`, `Harl.cpp`.
- **`ex06/`** : *Harl filter* - Filtrage des messages de `Harl` avec une instruction `switch`.
  - Fichiers : `Makefile`, `main.cpp`, `Harl.hpp`, `Harl.cpp`.

## Prérequis
- Un système Unix-like (Linux, macOS).
- Un compilateur C++ compatible avec le standard C++98 (ex. `g++`).
- Les bibliothèques standard C++ (`iostream`, `string`, `fstream`, etc.).
- Aucun accès à C++11 ou bibliothèques externes (Boost interdit).

## Compilation
Pour chaque exercice, accédez au dossier correspondant (`ex00`, `ex01`, ..., `ex06`) et exécutez :
```bash
make
```
Cela génère un exécutable pour chaque exercice. Assurez-vous que les flags de compilation incluent `-Wall -Wextra -Werror -std=c++98`.

## Utilisation
### Exercice 00 : BraiiiiiiinnnzzzZ
Crée une classe `Zombie` avec un nom et une fonction `announce`. Inclut des fonctions pour créer des zombies sur le tas (`newZombie`) ou la pile (`randomChump`).

```bash
./zombie
```
Sortie (exemple) :
```
Foo: BraiiiiiiinnnzzzZ...
```

### Exercice 01 : Moar brainz!
Crée une horde de `N` zombies avec une allocation unique via `zombieHorde`.

```bash
./zombieHorde
```
Sortie (exemple pour `N=3`, nom=`Zombie`) :
```
Zombie: BraiiiiiiinnnzzzZ...
Zombie: BraiiiiiiinnnzzzZ...
Zombie: BraiiiiiiinnnzzzZ...
```

### Exercice 02 : HI THIS IS BRAIN
Affiche les adresses et valeurs d'une chaîne via une variable, un pointeur, et une référence.

```bash
./hiThisIsBrain
```
Sortie (exemple) :
```
String address: 0x7ffee4b0b4a0
Pointer address: 0x7ffee4b0b4a0
Reference address: 0x7ffee4b0b4a0
String value: HI THIS IS BRAIN
Pointer value: HI THIS IS BRAIN
Reference value: HI THIS IS BRAIN
```

### Exercice 03 : Unnecessary violence
Gère des classes `Weapon`, `HumanA`, et `HumanB` pour afficher des attaques.

```bash
./violence
```
Sortie (exemple) :
```
Bob attacks with their crude spiked club
Bob attacks with their some other type of club
Jim attacks with their crude spiked club
Jim attacks with their some other type of club
```

### Exercice 04 : Sed is for losers
Remplace toutes les occurrences de `s1` par `s2` dans un fichier, créant `<filename>.replace`.

```bash
./sedlosers input.txt "hello" "world"
```
Sortie : Crée `input.txt.replace` avec `hello` remplacé par `world`.

### Exercice 05 : Harl 2.0
Classe `Harl` avec une fonction `complain` utilisant des pointeurs vers fonctions membres pour afficher des messages de niveaux `DEBUG`, `INFO`, `WARNING`, `ERROR`.

```bash
./harl2
```
Sortie (exemple) :
```
[DEBUG] I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!
[INFO] I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!
[WARNING] I think I deserve to have some extra bacon for free. I've been coming for years, whereas you started working here just last month.
[ERROR] This is unacceptable! I want to speak to the manager now.
```

### Exercice 06 : Harl filter
Filtre les messages de `Harl` en fonction d'un niveau de log spécifié, utilisant un `switch`.

```bash
./harlFilter WARNING
```
Sortie (exemple) :
```
[WARNING] I think I deserve to have some extra bacon for free. I've been coming for years, whereas you started working here just last month.
[ERROR] This is unacceptable! I want to speak to the manager now.
```

## Fonctionnement détaillé
### Exercice 00 : BraiiiiiiinnnzzzZ
- **Classe `Zombie`** : Attribut privé `name` et fonction membre `announce` affichant `<name>: BraiiiiiiinnnzzzZ...`.
- **Fonctions** :
  - `newZombie` : Alloue un zombie sur le tas avec `new`.
  - `randomChump` : Crée un zombie sur la pile qui s'annonce immédiatement.
- **Objectif** : Comprendre l'allocation sur pile vs tas et la gestion des destructeurs.

### Exercice 01 : Moar brainz!
- **Fonction `zombieHorde`** : Alloue `N` zombies en une seule allocation avec `new[]`, initialise leurs noms, et retourne un pointeur vers le premier.
- **Tests** : Appeler `announce` pour chaque zombie et désallouer avec `delete[]`.
- **Objectif** : Gérer une allocation groupée et éviter les fuites de mémoire.

### Exercice 02 : HI THIS IS BRAIN
- Crée une chaîne, un pointeur, et une référence.
- Affiche leurs adresses mémoire et valeurs.
- **Objectif** : Comprendre les références comme une syntaxe alternative pour la manipulation d'adresses.

### Exercice 03 : Unnecessary violence
- **Classe `Weapon`** : Attribut `type` (string), fonctions `getType` (retourne une référence constante) et `setType`.
- **Classe `HumanA`** : Toujours armé, prend une référence à `Weapon` dans son constructeur.
- **Classe `HumanB`** : Peut être sans arme, utilise un pointeur à `Weapon`.
- **Fonction `attack`** : Affiche `<name> attacks with their <weapon type>`.
- **Objectif** : Comprendre les différences entre références et pointeurs dans les classes.

### Exercice 04 : Sed is for losers
- Lit un fichier avec `std::ifstream`, remplace `s1` par `s2` dans son contenu, et écrit dans `<filename>.replace` avec `std::ofstream`.
- **Interdiction** : Ne pas utiliser `std::string::replace`.
- **Objectif** : Manipuler des fichiers et des chaînes en C++ sans fonctions interdites.

### Exercice 05 : Harl 2.0
- **Classe `Harl`** : Fonctions privées `debug`, `info`, `warning`, `error` affichant des messages prédéfinis.
- **Fonction `complain`** : Utilise des pointeurs vers fonctions membres pour appeler la fonction correspondant au niveau.
- **Objectif** : Maîtriser les pointeurs vers fonctions membres sans `if/else`.

### Exercice 06 : Harl filter
- Réutilise la classe `Harl` de l'exercice 05.
- Utilise un `switch` pour afficher les messages à partir du niveau spécifié (ex. `WARNING` affiche `WARNING` et `ERROR`).
- **Exécutable** : Nommé `harlFilter`.
- **Objectif** : Apprendre à utiliser `switch` pour filtrer des niveaux de log.

## Gestion des erreurs
- **Ex00** : Gère la désallocation des zombies alloués dynamiquement.
- **Ex01** : Vérifie que `N` est valide pour l'allocation de la horde.
- **Ex02** : Pas d'erreurs spécifiques, affiche simplement les adresses et valeurs.
- **Ex03** : Gère le cas où `HumanB` n'a pas d'arme.
- **Ex04** : Gère les erreurs d'ouverture/lecture de fichiers et les entrées invalides.
- **Ex05** : Ignore les niveaux de log invalides.
- **Ex06** : Affiche un message par défaut pour les niveaux invalides.

## Codes de sortie
- `0` : Succès.
- Pas d'erreurs spécifiques définies, mais les erreurs (ex. fichiers non ouverts) sont gérées en interne.

## Limitations
- Conforme au standard C++98 uniquement.
- Pas d'utilisation de `using namespace` ni de `friend` (sinon -42).
- Pas de STL (vector, map, etc.) ni d'algorithmes (`<algorithm>` interdit).
- Pas de fonctions C comme `printf`, `malloc`, `free` (sinon 0).
- Les fuites de mémoire doivent être évitées.
- Pas de fonctions membres implémentées dans les fichiers d'en-tête (sauf templates).

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** : Juillet 2025

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis d'approfondir ma compréhension de la gestion de la mémoire, des pointeurs vers fonctions membres, des références, et des instructions `switch` en C++98.

---

# CPP01 - README

## Description
CPP01 is the second module of the C++ curriculum at 42 school. This project deepens the understanding of object-oriented programming (OOP) in C++98, focusing on memory management, pointers to member functions, references, and the `switch` statement. It includes six exercises exploring these concepts through various scenarios: zombie management, string manipulation, and log filtering.

The goal is to master the following concepts:
- Memory allocation and deallocation with `new` and `delete`.
- Using pointers to member functions for dynamic function calls.
- Handling references to understand address manipulation.
- Using the `switch` statement for multiple cases.
- Managing input/output streams and file operations in C++.
- Designing classes adhering to C++98 conventions.

## Project Structure
The project is split into six exercises, each in its own directory:
- **`ex00/`**: *BraiiiiiiinnnzzzZ* - Creates a `Zombie` class with stack and heap allocation.
  - Files: `Makefile`, `main.cpp`, `Zombie.hpp`, `Zombie.cpp`, `newZombie.cpp`, `randomChump.cpp`.
- **`ex01/`**: *Moar brainz!* - Creates a horde of zombies with a single allocation.
  - Files: `Makefile`, `main.cpp`, `Zombie.hpp`, `Zombie.cpp`, `zombieHorde.cpp`.
- **`ex02/`**: *HI THIS IS BRAIN* - Manipulates pointers and references on a string.
  - Files: `Makefile`, `main.cpp`.
- **`ex03/`**: *Unnecessary violence* - Manages `Weapon`, `HumanA`, and `HumanB` classes for attacks.
  - Files: `Makefile`, `main.cpp`, `Weapon.hpp`, `Weapon.cpp`, `HumanA.hpp`, `HumanA.cpp`, `HumanB.hpp`, `HumanB.cpp`.
- **`ex04/`**: *Sed is for losers* - Replaces strings in a file without `std::string::replace`.
  - Files: `Makefile`, `main.cpp`, additional files if needed.
- **`ex05/`**: *Harl 2.0* - `Harl` class with pointers to member functions for log levels.
  - Files: `Makefile`, `main.cpp`, `Harl.hpp`, `Harl.cpp`.
- **`ex06/`**: *Harl filter* - Filters `Harl` messages using a `switch` statement.
  - Files: `Makefile`, `main.cpp`, `Harl.hpp`, `Harl.cpp`.

## Prerequisites
- A Unix-like system (Linux, macOS).
- A C++ compiler compatible with C++98 (e.g., `g++`).
- Standard C++ libraries (`iostream`, `string`, `fstream`, etc.).
- No access to C++11 or external libraries (Boost is forbidden).

## Compilation
For each exercise, navigate to its directory (`ex00`, `ex01`, ..., `ex06`) and run:
```bash
make
```
This generates an executable for each exercise. Ensure compilation flags include `-Wall -Wextra -Werror -std=c++98`.

## Usage
### Exercise 00: BraiiiiiiinnnzzzZ
Creates a `Zombie` class with a name and an `announce` function. Includes functions to create zombies on the heap (`newZombie`) or stack (`randomChump`).

```bash
./zombie
```
Output (example):
```
Foo: BraiiiiiiinnnzzzZ...
```

### Exercise 01: Moar brainz!
Creates a horde of `N` zombies with a single allocation via `zombieHorde`.

```bash
./zombieHorde
```
Output (example for `N=3`, name=`Zombie`):
```
Zombie: BraiiiiiiinnnzzzZ...
Zombie: BraiiiiiiinnnzzzZ...
Zombie: BraiiiiiiinnnzzzZ...
```

### Exercise 02: HI THIS IS BRAIN
Displays addresses and values of a string via a variable, pointer, and reference.

```bash
./hiThisIsBrain
```
Output (example):
```
String address: 0x7ffee4b0b4a0
Pointer address: 0x7ffee4b0b4a0
Reference address: 0x7ffee4b0b4a0
String value: HI THIS IS BRAIN
Pointer value: HI THIS IS BRAIN
Reference value: HI THIS IS BRAIN
```

### Exercise 03: Unnecessary violence
Manages `Weapon`, `HumanA`, and `HumanB` classes to display attacks.

```bash
./violence
```
Output (example):
```
Bob attacks with their crude spiked club
Bob attacks with their some other type of club
Jim attacks with their crude spiked club
Jim attacks with their some other type of club
```

### Exercise 04: Sed is for losers
Replaces all occurrences of `s1` with `s2` in a file, creating `<filename>.replace`.

```bash
./sedlosers input.txt "hello" "world"
```
Output: Creates `input.txt.replace` with `hello` replaced by `world`.

### Exercise 05: Harl 2.0
`Harl` class with a `complain` function using pointers to member functions to display `DEBUG`, `INFO`, `WARNING`, `ERROR` messages.

```bash
./harl2
```
Output (example):
```
[DEBUG] I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!
[INFO] I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!
[WARNING] I think I deserve to have some extra bacon for free. I've been coming for years, whereas you started working here just last month.
[ERROR] This is unacceptable! I want to speak to the manager now.
```

### Exercise 06: Harl filter
Filters `Harl` messages based on a specified log level, using a `switch`.

```bash
./harlFilter WARNING
```
Output (example):
```
[WARNING] I think I deserve to have some extra bacon for free. I've been coming for years, whereas you started working here just last month.
[ERROR] This is unacceptable! I want to speak to the manager now.
```

## Detailed Functionality
### Exercise 00: BraiiiiiiinnnzzzZ
- **Class `Zombie`**: Private `name` attribute and `announce` function displaying `<name>: BraiiiiiiinnnzzzZ...`.
- **Functions**:
  - `newZombie`: Allocates a zombie on the heap with `new`.
  - `randomChump`: Creates a stack-allocated zombie that announces itself.
- **Objective**: Understand stack vs. heap allocation and destructor management.

### Exercise 01: Moar brainz!
- **Function `zombieHorde`**: Allocates `N` zombies in a single `new[]` allocation, initializes their names, and returns a pointer to the first.
- **Tests**: Call `announce` for each zombie and deallocate with `delete[]`.
- **Objective**: Manage bulk allocation and prevent memory leaks.

### Exercise 02: HI THIS IS BRAIN
- Creates a string, pointer, and reference.
- Displays their memory addresses and values.
- **Objective**: Understand references as an alternative syntax for address manipulation.

### Exercise 03: Unnecessary violence
- **Class `Weapon`**: `type` attribute (string), `getType` (returns const reference), and `setType` functions.
- **Class `HumanA`**: Always armed, takes a `Weapon` reference in its constructor.
- **Class `HumanB`**: May lack a weapon, uses a `Weapon` pointer.
- **Function `attack`**: Displays `<name> attacks with their <weapon type>`.
- **Objective**: Understand differences between references and pointers in classes.

### Exercise 04: Sed is for losers
- Reads a file with `std::ifstream`, replaces `s1` with `s2`, and writes to `<filename>.replace` with `std::ofstream`.
- **Forbidden**: Using `std::string::replace`.
- **Objective**: Manipulate files and strings in C++ without forbidden functions.

### Exercise 05: Harl 2.0
- **Class `Harl`**: Private functions `debug`, `info`, `warning`, `error` displaying predefined messages.
- **Function `complain`**: Uses pointers to member functions to call the appropriate function based on the level.
- **Objective**: Master pointers to member functions without `if/else`.

### Exercise 06: Harl filter
- Reuses the `Harl` class from exercise 05.
- Uses a `switch` to display messages from the specified level and above.
- **Executable**: Named `harlFilter`.
- **Objective**: Learn to use `switch` for log level filtering.

## Error Handling
- **Ex00**: Manages deallocation of dynamically allocated zombies.
- **Ex01**: Validates `N` for horde allocation.
- **Ex02**: No specific errors, simply displays addresses and values.
- **Ex03**: Handles cases where `HumanB` has no weapon.
- **Ex04**: Manages file opening/reading errors and invalid inputs.
- **Ex05**: Ignores invalid log levels.
- **Ex06**: Displays a default message for invalid levels.

## Exit Codes
- `0`: Success.
- No specific error codes defined, but errors (e.g., file not opened) are handled internally.

## Limitations
- Strictly adheres to C++98.
- No `using namespace` or `friend` keywords (otherwise -42).
- No STL containers or `<algorithm>` (otherwise -42).
- No C functions like `printf`, `malloc`, `free` (otherwise 0).
- Memory leaks must be avoided.
- No member functions implemented in header files (except templates).

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**: July 2025

## Acknowledgments
Thanks to 42 school for this project, which allowed me to deepen my understanding of memory management, pointers to member functions, references, and `switch` statements in C++98.