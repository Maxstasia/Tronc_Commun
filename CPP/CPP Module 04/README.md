# CPP04 - README

---

## Description
CPP04 est le cinquième module du parcours C++ dans le cadre du cursus de l'école 42. Ce projet se concentre sur le polymorphisme par sous-typage, les classes abstraites et les interfaces en C++98. Il explore la création de classes dérivées avec des comportements polymorphiques, la gestion des classes abstraites pour empêcher l'instanciation, et l'implémentation d'interfaces pour standardiser les comportements. Les exercices impliquent des classes représentant des animaux (`Animal`, `Dog`, `Cat`), des cerveaux (`Brain`), des matérias (`AMateria`, `Ice`, `Cure`), des personnages (`Character`), et des sources de matérias (`MateriaSource`), tout en respectant la forme canonique de Coplien.

L'objectif est de maîtriser les concepts suivants :
- Polymorphisme par sous-typage via des fonctions virtuelles.
- Création de classes abstraites avec des fonctions purement virtuelles.
- Implémentation d'interfaces pour standardiser les comportements.
- Gestion des copies profondes pour éviter les fuites de mémoire.
- Respect des conventions C++98, y compris la forme canonique.

## Structure du projet
Le projet est divisé en quatre exercices, chacun dans son propre dossier :

- **`ex00/`** : *Polymorphisme* - Création des classes `Animal`, `Dog`, `Cat`, `WrongAnimal`, `WrongCat`.
  - Fichiers : `Makefile`, `main.cpp`, `Animal.hpp`, `Animal.cpp`, `Dog.hpp`, `Dog.cpp`, `Cat.hpp`, `Cat.cpp`, `WrongAnimal.hpp`, `WrongAnimal.cpp`, `WrongCat.hpp`, `WrongCat.cpp`.
- **`ex01/`** : *Je ne veux pas brûler le monde* - Ajout de la classe `Brain` et gestion des copies profondes.
  - Fichiers : Fichiers de l'exercice précédent + `Brain.hpp`, `Brain.cpp`, fichiers modifiés pour `Dog` et `Cat`.
- **`ex02/`** : *Classe abstraite* - Transformation de `Animal` en classe abstraite.
  - Fichiers : Fichiers de l'exercice précédent, avec `Animal.hpp` et `Animal.cpp` modifiés.
- **`ex03/`** : *Interface & recap* - Création des interfaces `AMateria`, `ICharacter`, `IMateriaSource` et des classes concrètes `Ice`, `Cure`, `Character`, `MateriaSource`.
  - Fichiers : Fichiers des exercices précédents + `AMateria.hpp`, `AMateria.cpp`, `Ice.hpp`, `Ice.cpp`, `Cure.hpp`, `Cure.cpp`, `ICharacter.hpp`, `Character.hpp`, `Character.cpp`, `IMateriaSource.hpp`, `MateriaSource.hpp`, `MateriaSource.cpp`.

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
### Exercice 00 : Polymorphisme
Crée des classes `Animal`, `Dog`, `Cat`, `WrongAnimal`, `WrongCat` pour démontrer le polymorphisme.

```bash
./polymorphism
```
Sortie (exemple) :
```
Animal constructed
Dog constructed
Cat constructed
Dog barks: Woof!
Cat meows: Meow!
WrongAnimal constructed
WrongCat constructed
WrongAnimal makes sound: Generic animal sound
Animal destructed
Dog destructed
Cat destructed
WrongAnimal destructed
WrongCat destructed
```

### Exercice 01 : Je ne veux pas brûler le monde
Ajoute la classe `Brain` et intègre des copies profondes pour `Dog` et `Cat`.

```bash
./brain
```
Sortie (exemple) :
```
Dog constructed
Brain constructed
Cat constructed
Brain constructed
Dog barks: Woof!
Cat meows: Meow!
Dog destructed
Brain destructed
Cat destructed
Brain destructed
```

### Exercice 02 : Classe abstraite
Transforme `Animal` en classe abstraite en rendant `makeSound` purement virtuelle.

```bash
./abstract
```
Sortie (exemple) :
```
Dog constructed
Brain constructed
Cat constructed
Brain constructed
Dog barks: Woof!
Cat meows: Meow!
Dog destructed
Brain destructed
Cat destructed
Brain destructed
```

### Exercice 03 : Interface & recap
Implémente des interfaces (`AMateria`, `ICharacter`, `IMateriaSource`) et des classes concrètes pour gérer des matérias et des personnages.

```bash
./interface
```
Sortie (exemple) :
```
MateriaSource constructed
Ice Materia constructed
MateriaSource learned Ice
Cure Materia constructed
MateriaSource learned Cure
Character Ash constructed
Ash equipped Ice at slot 0
Ash equipped Cure at slot 1
Ash uses Ice on Bob: * shoots an ice bolt at Bob *
Ash uses Cure on Bob: * heals Bob's wounds *
Character Ash destructed
Ice Materia destructed
Cure Materia destructed
MateriaSource destructed
```

## Fonctionnement détaillé
### Exercice 00 : Polymorphisme
- **Classe `Animal`** :
  - Attribut protégé : `type` (string).
  - Fonction virtuelle : `makeSound` (implémentation générique).
  - Respecte la forme canonique.
- **Classes `Dog` et `Cat`** :
  - Héritent de `Animal`, initialisent `type` à "Dog" ou "Cat".
  - Redéfinissent `makeSound` pour émettre des sons spécifiques ("Woof!" pour `Dog`, "Meow!" pour `Cat").
- **Classes `WrongAnimal` et `WrongCat`** :
  - Simulent un polymorphisme incorrect (sans fonction virtuelle).
  - `WrongCat` hérite de `WrongAnimal`, mais `makeSound` n'est pas virtuel, donc le son de `WrongAnimal` est utilisé.
- **Objectif** : Comprendre le polymorphisme via des fonctions virtuelles.

### Exercice 01 : Je ne veux pas brûler le monde
- **Classe `Brain`** :
  - Attribut : tableau de 100 `std::string` nommé `ideas`.
  - Respecte la forme canonique pour la copie profonde.
- **Classes `Dog` et `Cat`** :
  - Ajout d’un attribut privé `Brain*`.
  - Allocation de `Brain` avec `new` dans le constructeur, désallocation dans le destructeur.
  - Implémentation de la copie profonde pour éviter les fuites de mémoire.
- **Tests** : Création d’un tableau d’objets `Animal` (moitié `Dog`, moitié `Cat`), suppression correcte avec destructeurs en chaîne.
- **Objectif** : Gérer les copies profondes et la destruction appropriée.

### Exercice 02 : Classe abstraite
- **Classe `Animal`** :
  - Transformée en classe abstraite en rendant `makeSound` purement virtuelle (`virtual void makeSound() const = 0;`).
  - Ne peut plus être instanciée directement.
- **Classes `Dog` et `Cat`** : Inchangées, mais héritent de la classe abstraite `Animal`.
- **Objectif** : Comprendre les classes abstraites et leur rôle dans le polymorphisme.

### Exercice 03 : Interface & recap
- **Classe `AMateria`** :
  - Classe abstraite avec attribut `type` (string).
  - Fonctions : `getType`, `clone` (pure virtuelle), `use` (virtuelle).
- **Classes `Ice` et `Cure`** :
  - Héritent de `AMateria`, initialisent `type` à "ice" ou "cure".
  - Redéfinissent `clone` pour retourner une nouvelle instance du même type.
  - Redéfinissent `use` pour afficher des messages spécifiques.
- **Interface `ICharacter`** :
  - Fonctions purement virtuelles : `getName`, `equip`, `unequip`, `use`.
- **Classe `Character`** :
  - Implémente `ICharacter` avec un inventaire de 4 `AMateria*`.
  - Gère la copie profonde et la destruction des matérias.
- **Interface `IMateriaSource`** :
  - Fonctions purement virtuelles : `learnMateria`, `createMateria`.
- **Classe `MateriaSource`** :
  - Implémente `IMateriaSource` avec un inventaire de 4 `AMateria*`.
  - Gère la copie et la création de matérias.
- **Objectif** : Maîtriser les interfaces et le polymorphisme dans un système complexe.

## Gestion des erreurs
- **Ex00** : Assure que le polymorphisme fonctionne correctement via des fonctions virtuelles.
- **Ex01** : Vérifie les copies profondes et l'absence de fuites de mémoire.
- **Ex02** : Empêche l'instanciation de `Animal`.
- **Ex03** : Gère les cas d'inventaire plein, d'indices invalides, et de matérias non équipées.

## Codes de sortie
- `0` : Succès.
- Pas d'erreurs spécifiques définies, mais les erreurs (ex. inventaire plein) sont gérées en interne.

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
Merci à l'école 42 pour ce projet qui m'a permis d'approfondir ma compréhension du polymorphisme par sous-typage, des classes abstraites, des interfaces, et de la gestion des copies profondes en C++98.

---

# CPP04 - README

## Description
CPP04 is the fifth module of the C++ curriculum at 42 school. This project focuses on subtype polymorphism, abstract classes, and interfaces in C++98. It explores creating derived classes with polymorphic behaviors, managing abstract classes to prevent instantiation, and implementing interfaces to standardize behaviors. The exercises involve classes representing animals (`Animal`, `Dog`, `Cat`), brains (`Brain`), materias (`AMateria`, `Ice`, `Cure`), characters (`Character`), and materia sources (`MateriaSource`), while adhering to the Orthodox Canonical Form.

The goal is to master the following concepts:
- Subtype polymorphism via virtual functions.
- Creating abstract classes with pure virtual functions.
- Implementing interfaces to standardize behaviors.
- Managing deep copies to avoid memory leaks.
- Adhering to C++98 conventions, including the Orthodox Canonical Form.

## Project Structure
The project is divided into four exercises, each in its own directory:

- **`ex00/`**: *Polymorphism* - Creates `Animal`, `Dog`, `Cat`, `WrongAnimal`, `WrongCat` classes.
  - Files: `Makefile`, `main.cpp`, `Animal.hpp`, `Animal.cpp`, `Dog.hpp`, `Dog.cpp`, `Cat.hpp`, `Cat.cpp`, `WrongAnimal.hpp`, `WrongAnimal.cpp`, `WrongCat.hpp`, `WrongCat.cpp`.
- **`ex01/`**: *I don’t want to set the world on fire* - Adds `Brain` class and deep copy management.
  - Files: Files from previous exercise + `Brain.hpp`, `Brain.cpp`, modified `Dog` and `Cat` files.
- **`ex02/`**: *Abstract class* - Transforms `Animal` into an abstract class.
  - Files: Files from previous exercise, with modified `Animal.hpp` and `Animal.cpp`.
- **`ex03/`**: *Interface & recap* - Creates `AMateria`, `ICharacter`, `IMateriaSource` interfaces and concrete classes.
  - Files: Files from previous exercises + `AMateria.hpp`, `AMateria.cpp`, `Ice.hpp`, `Ice.cpp`, `Cure.hpp`, `Cure.cpp`, `ICharacter.hpp`, `Character.hpp`, `Character.cpp`, `IMateriaSource.hpp`, `MateriaSource.hpp`, `MateriaSource.cpp`.

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
### Exercise 00: Polymorphism
Creates `Animal`, `Dog`, `Cat`, `WrongAnimal`, `WrongCat` classes to demonstrate polymorphism.

```bash
./polymorphism
```
Output (example):
```
Animal constructed
Dog constructed
Cat constructed
Dog barks: Woof!
Cat meows: Meow!
WrongAnimal constructed
WrongCat constructed
WrongAnimal makes sound: Generic animal sound
Animal destructed
Dog destructed
Cat destructed
WrongAnimal destructed
WrongCat destructed
```

### Exercise 01: I don’t want to set the world on fire
Adds the `Brain` class and integrates deep copies for `Dog` and `Cat`.

```bash
./brain
```
Output (example):
```
Dog constructed
Brain constructed
Cat constructed
Brain constructed
Dog barks: Woof!
Cat meows: Meow!
Dog destructed
Brain destructed
Cat destructed
Brain destructed
```

### Exercise 02: Abstract class
Transforms `Animal` into an abstract class by making `makeSound` pure virtual.

```bash
./abstract
```
Output (example):
```
Dog constructed
Brain constructed
Cat constructed
Brain constructed
Dog barks: Woof!
Cat meows: Meow!
Dog destructed
Brain destructed
Cat destructed
Brain destructed
```

### Exercise 03: Interface & recap
Implements `AMateria`, `ICharacter`, `IMateriaSource` interfaces and concrete classes for managing materias and characters.

```bash
./interface
```
Output (example):
```
MateriaSource constructed
Ice Materia constructed
MateriaSource learned Ice
Cure Materia constructed
MateriaSource learned Cure
Character Ash constructed
Ash equipped Ice at slot 0
Ash equipped Cure at slot 1
Ash uses Ice on Bob: * shoots an ice bolt at Bob *
Ash uses Cure on Bob: * heals Bob's wounds *
Character Ash destructed
Ice Materia destructed
Cure Materia destructed
MateriaSource destructed
```

## Detailed Functionality
### Exercise 00: Polymorphism
- **Class `Animal`**:
  - Protected attribute: `type` (string).
  - Virtual function: `makeSound` (generic implementation).
  - Adheres to the Orthodox Canonical Form.
- **Classes `Dog` and `Cat`**:
  - Inherit from `Animal`, set `type` to "Dog" or "Cat".
  - Override `makeSound` to emit specific sounds ("Woof!" for `Dog`, "Meow!" for `Cat").
- **Classes `WrongAnimal` and `WrongCat`**:
  - Simulate incorrect polymorphism (without virtual functions).
  - `WrongCat` inherits from `WrongAnimal`, but `makeSound` is not virtual, so `WrongAnimal`’s sound is used.
- **Objective**: Understand polymorphism via virtual functions.

### Exercise 01: I don’t want to set the world on fire
- **Class `Brain`**:
  - Attribute: Array of 100 `std::string` named `ideas`.
  - Adheres to the Orthodox Canonical Form for deep copying.
- **Classes `Dog` and `Cat`**:
  - Add private `Brain*` attribute.
  - Allocate `Brain` with `new` in constructor, deallocate in destructor.
  - Implement deep copying to avoid memory leaks.
- **Tests**: Create an array of `Animal` objects (half `Dog`, half `Cat`), delete correctly with chained destructors.
- **Objective**: Manage deep copies and proper destruction.

### Exercise 02: Abstract class
- **Class `Animal`**:
  - Transformed into an abstract class by making `makeSound` pure virtual (`virtual void makeSound() const = 0;`).
  - Cannot be instantiated directly.
- **Classes `Dog` and `Cat`**: Unchanged, but inherit from the abstract `Animal`.
- **Objective**: Understand abstract classes and their role in polymorphism.

### Exercise 03: Interface & recap
- **Class `AMateria`**:
  - Abstract class with `type` attribute (string).
  - Functions: `getType`, `clone` (pure virtual), `use` (virtual).
- **Classes `Ice` and `Cure`**:
  - Inherit from `AMateria`, set `type` to "ice" or "cure".
  - Override `clone` to return a new instance of the same type.
  - Override `use` to display specific messages.
- **Interface `ICharacter`**:
  - Pure virtual functions: `getName`, `equip`, `unequip`, `use`.
- **Class `Character`**:
  - Implements `ICharacter` with a 4-slot `AMateria*` inventory.
  - Manages deep copying and materia destruction.
- **Interface `IMateriaSource`**:
  - Pure virtual functions: `learnMateria`, `createMateria`.
- **Class `MateriaSource`**:
  - Implements `IMateriaSource` with a 4-slot `AMateria*` inventory.
  - Manages copying and creating materias.
- **Objective**: Master interfaces and polymorphism in a complex system.

## Error Handling
- **Ex00**: Ensures polymorphism works correctly via virtual functions.
- **Ex01**: Verifies deep copies and no memory leaks.
- **Ex02**: Prevents instantiation of `Animal`.
- **Ex03**: Handles full inventory, invalid indices, and unequipped materias.

## Exit Codes
- `0`: Success.
- No specific error codes defined, but errors (e.g., full inventory) are handled internally.

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
Thanks to 42 school for this project, which allowed me to deepen my understanding of subtype polymorphism, abstract classes, interfaces, and deep copy management in C++98.