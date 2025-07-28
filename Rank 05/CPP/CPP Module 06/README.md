# CPP06 - README

---

## Description
CPP06 est le septième module du parcours C++ dans le cadre du cursus de l'école 42. Ce projet se concentre sur les conversions de types (casts) en C++98, en explorant les mécanismes de conversion de types scalaires, la sérialisation/désérialisation, et l'identification dynamique de types sans utiliser `std::typeinfo`. Les exercices impliquent la création de classes et de fonctions pour gérer les conversions de types, la sérialisation de pointeurs, et l'identification du type réel d'objets polymorphiques, tout en respectant les contraintes du standard C++98.

L'objectif est de maîtriser les concepts suivants :
- Conversion explicite entre types scalaires (char, int, float, double) avec gestion des cas spéciaux (inf, nan).
- Sérialisation et désérialisation de pointeurs en utilisant `uintptr_t`.
- Identification dynamique du type réel d'objets via des pointeurs et des références dans un contexte polymorphique.
- Utilisation appropriée des casts C++ (`static_cast`, `dynamic_cast`, etc.) selon les besoins de chaque exercice.
- Respect des conventions C++98, y compris la forme canonique pour les classes lorsque requis.

## Structure du projet
Le projet est divisé en trois exercices, chacun dans son propre dossier :

- **`ex00/`** : *Conversion of scalar types* - Création de la classe `ScalarConverter` pour convertir des littéraux scalaires.
  - Fichiers : `Makefile`, `main.cpp`, `ScalarConverter.hpp`, `ScalarConverter.cpp`.
- **`ex01/`** : *Serialization* - Implémentation de la classe `Breadizer` pour la sérialisation/désérialisation de pointeurs.
  - Fichiers : `Makefile`, `main.cpp`, `Breadizer.hpp`, `Breadizer.cpp`, `Data.hpp`, `Data.cpp`.
- **`ex02/`** : *Identify real type* - Création d'une hiérarchie de classes (`Base`, `A`, `B`, `C`) pour identifier dynamiquement les types.
  - Fichiers : `Makefile`, `main.cpp`, `Base.hpp`, `Base.cpp`, `A.hpp`, `B.hpp`, `C.hpp`.

## Prérequis
- Un système Unix-like (Linux, macOS).
- Un compilateur C++ compatible avec le standard C++98 (ex. `g++`).
- Les bibliothèques standard C++ (`iostream`, `string`, `limits`, etc.).
- Aucun accès à C++11 ou bibliothèques externes (Boost interdit).

## Compilation
Pour chaque exercice, accédez au dossier correspondant (`ex00`, `ex01`, `ex02`) et exécutez :
```bash
make
```
Cela génère un exécutable pour chaque exercice. Assurez-vous que les flags de compilation incluent `-Wall -Wextra -Werror -std=c++98`.

## Utilisation
### Exercice 00 : Conversion of scalar types
Crée une classe `ScalarConverter` pour convertir une chaîne représentant un littéral en char, int, float, et double.

```bash
./scalar_converter 42.0f
```
Sortie (exemple) :
```
char: '*'
int: 42
float: 42.0f
double: 42.0
```

```bash
./scalar_converter nan
```
Sortie (exemple) :
```
char: impossible
int: impossible
float: nanf
double: nan
```

### Exercice 01 : Serialization
Implémente une classe `Breadizer` pour sérialiser/désérialiser des pointeurs vers une structure `Data`.

```bash
./serializer
```
Sortie (exemple) :
```
Data created with value: 42
Serialized pointer: <some_uintptr_t_value>
Deserialized pointer matches original: true
Data destructed
```

### Exercice 02 : Identify real type
Crée une hiérarchie de classes (`Base`, `A`, `B`, `C`) et identifie le type réel des objets via des pointeurs et des références.

```bash
./identify
```
Sortie (exemple) :
```
Generated object type (via pointer): A
Generated object type (via reference): A
Generated object type (via pointer): B
Generated object type (via reference): B
Generated object type (via pointer): C
Generated object type (via reference): C
```

## Fonctionnement détaillé
### Exercice 00 : Conversion of scalar types
- **Classe `ScalarConverter`** :
  - Non instanciable (constructeurs privés ou protégés).
  - Méthode statique : `convert(std::string const &literal)` qui détecte le type du littéral (char, int, float, double) et effectue les conversions explicites vers les autres types.
  - Gère les pseudo-littéraux : `-inf`, `+inf`, `nan` (pour double), `-inff`, `+inff`, `nanf` (pour float).
  - Gère les cas d'erreur : caractères non affichables, conversions impossibles, débordements.
  - Utilise des casts explicites (ex. `static_cast`) pour les conversions.
- **Objectif** : Comprendre la détection de type et la conversion explicite entre types scalaires.

### Exercice 01 : Serialization
- **Classe `Breadizer`** :
  - Non instanciable (constructeurs privés ou protégés).
  - Méthodes statiques :
    - `serialize(Data* ptr)` : Convertit un pointeur `Data*` en `uintptr_t`.
    - `deserialize(uintptr_t raw)` : Convertit un `uintptr_t` en `Data*`.
  - Respecte la forme canonique si implémentée comme classe.
- **Structure `Data`** :
  - Contient au moins un membre de données (ex. `int value`).
  - Respecte la forme canonique.
- **Tests** : Vérifie que le pointeur désérialisé correspond au pointeur original.
- **Objectif** : Maîtriser la sérialisation/désérialisation de pointeurs avec `uintptr_t`.

### Exercice 02 : Identify real type
- **Classe `Base`** :
  - Contient uniquement un destructeur virtuel public (`virtual ~Base() {}`).
  - Non conforme à la forme canonique (non requis).
- **Classes `A`, `B`, `C`** :
  - Héritent publiquement de `Base`.
  - Classes vides, utilisées pour le polymorphisme.
  - Non conformes à la forme canonique (non requis).
- **Fonctions** :
  - `Base* generate(void)` : Crée aléatoirement une instance de `A`, `B`, ou `C` et retourne un pointeur `Base*`.
  - `void identify(Base* p)` : Identifie le type réel (`A`, `B`, `C`) via un pointeur en utilisant `dynamic_cast`.
  - `void identify(Base& p)` : Identifie le type réel via une référence en utilisant `dynamic_cast`, sans utiliser de pointeur internement.
- **Objectif** : Comprendre l'identification dynamique des types dans un contexte polymorphique sans `std::typeinfo`.

## Gestion des erreurs
- **Ex00** : Gère les conversions impossibles (ex. caractères non affichables, débordements) et les pseudo-littéraux (inf, nan).
- **Ex01** : Assure que la sérialisation/désérialisation conserve l'intégrité du pointeur.
- **Ex02** : Gère correctement l'identification des types sans provoquer d'erreurs d'exécution.

## Codes de sortie
- `0` : Succès.
- Pas d'erreurs spécifiques définies, mais les erreurs de conversion ou d'identification sont affichées.

## Limitations
- Conforme au standard C++98 uniquement.
- Pas d'utilisation de `using namespace` ni de `friend` (sinon -42).
- Pas de STL (vector, map, etc.) ni d'algorithmes (`<algorithm>` interdit).
- Pas de fonctions C comme `printf`, `malloc`, `free` (sinon 0).
- Pas de `std::typeinfo` pour l'exercice 02 (sinon non valide).
- Les fuites de mémoire doivent être évitées.
- Pas de fonctions membres implémentées dans les fichiers d'en-tête (sauf templates).
- Les classes doivent respecter la forme canonique de Coplien, sauf pour `Base`, `A`, `B`, `C` dans l'exercice 02.

## Règle supplémentaire
- Chaque exercice doit utiliser un type de cast spécifique (`static_cast`, `dynamic_cast`, `const_cast`, ou `reinterpret_cast`), et le choix sera évalué lors de la soutenance.

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** :

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis d'approfondir ma compréhension des conversions de types, de la sérialisation, et de l'identification dynamique des types en C++98.

---

# CPP06 - README

## Description
CPP06 is the seventh module of the C++ curriculum at 42 school. This project focuses on type casting in C++98, exploring scalar type conversions, pointer serialization/deserialization, and dynamic type identification without using `std::typeinfo`. The exercises involve creating classes and functions to handle type conversions, pointer serialization, and identifying the real type of polymorphic objects, all while adhering to C++98 constraints.

The goal is to master the following concepts:
- Explicit conversion between scalar types (char, int, float, double) with handling of special cases (inf, nan).
- Pointer serialization and deserialization using `uintptr_t`.
- Dynamic identification of object types via pointers and references in a polymorphic context.
- Appropriate use of C++ casts (`static_cast`, `dynamic_cast`, etc.) based on exercise requirements.
- Adhering to C++98 conventions, including the Orthodox Canonical Form when required.

## Project Structure
The project is divided into three exercises, each in its own directory:

- **`ex00/`**: *Conversion of scalar types* - Creates the `ScalarConverter` class for converting scalar literals.
  - Files: `Makefile`, `main.cpp`, `ScalarConverter.hpp`, `ScalarConverter.cpp`.
- **`ex01/`**: *Serialization* - Implements the `Breadizer` class for pointer serialization/deserialization.
  - Files: `Makefile`, `main.cpp`, `Breadizer.hpp`, `Breadizer.cpp`, `Data.hpp`, `Data.cpp`.
- **`ex02/`**: *Identify real type* - Creates a class hierarchy (`Base`, `A`, `B`, `C`) for dynamic type identification.
  - Files: `Makefile`, `main.cpp`, `Base.hpp`, `Base.cpp`, `A.hpp`, `B.hpp`, `C.hpp`.

## Prerequisites
- A Unix-like system (Linux, macOS).
- A C++ compiler compatible with C++98 (e.g., `g++`).
- Standard C++ libraries (`iostream`, `string`, `limits`, etc.).
- No access to C++11 or external libraries (Boost is forbidden).

## Compilation
For each exercise, navigate to its directory (`ex00`, `ex01`, `ex02`) and run:
```bash
make
```
This generates an executable for each exercise. Ensure compilation flags include `-Wall -Wextra -Werror -std=c++98`.

## Usage
### Exercise 00: Conversion of scalar types
Creates a `ScalarConverter` class to convert a string literal into char, int, float, and double.

```bash
./scalar_converter 42.0f
```
Output (example):
```
char: '*'
int: 42
float: 42.0f
double: 42.0
```

```bash
./scalar_converter nan
```
Output (example):
```
char: impossible
int: impossible
float: nanf
double: nan
```

### Exercise 01: Serialization
Implements a `Breadizer` class for serializing/deserializing pointers to a `Data` structure.

```bash
./serializer
```
Output (example):
```
Data created with value: 42
Serialized pointer: <some_uintptr_t_value>
Deserialized pointer matches original: true
Data destructed
```

### Exercise 02: Identify real type
Creates a class hierarchy (`Base`, `A`, `B`, `C`) and identifies the real type of objects via pointers and references.

```bash
./identify
```
Output (example):
```
Generated object type (via pointer): A
Generated object type (via reference): A
Generated object type (via pointer): B
Generated object type (via reference): B
Generated object type (via pointer): C
Generated object type (via reference): C
```

## Detailed Functionality
### Exercise 00: Conversion of scalar types
- **Class `ScalarConverter`**:
  - Non-instantiable (private or protected constructors).
  - Static method: `convert(std::string const &literal)` detects the literal’s type (char, int, float, double) and explicitly converts to other types.
  - Handles pseudo-literals: `-inf`, `+inf`, `nan` (for double), `-inff`, `+inff`, `nanf` (for float).
  - Manages errors: non-displayable characters, impossible conversions, overflows.
  - Uses explicit casts (e.g., `static_cast`) for conversions.
- **Objective**: Understand type detection and explicit conversion between scalar types.

### Exercise 01: Serialization
- **Class `Breadizer`**:
  - Non-instantiable (private or protected constructors).
  - Static methods:
    - `serialize(Data* ptr)`: Converts a `Data*` pointer to `uintptr_t`.
    - `deserialize(uintptr_t raw)`: Converts a `uintptr_t` to a `Data*` pointer.
  - Adheres to the Orthodox Canonical Form if implemented as a class.
- **Structure `Data`**:
  - Contains at least one data member (e.g., `int value`).
  - Adheres to the Orthodox Canonical Form.
- **Tests**: Verifies that the deserialized pointer matches the original.
- **Objective**: Master pointer serialization/deserialization with `uintptr_t`.

### Exercise 02: Identify real type
- **Class `Base`**:
  - Contains only a public virtual destructor (`virtual ~Base() {}`).
  - Not required to follow the Orthodox Canonical Form.
- **Classes `A`, `B`, `C`**:
  - Publicly inherit from `Base`.
  - Empty classes used for polymorphism.
  - Not required to follow the Orthodox Canonical Form.
- **Functions**:
  - `Base* generate(void)`: Randomly creates an instance of `A`, `B`, or `C`, returning a `Base*` pointer.
  - `void identify(Base* p)`: Identifies the real type (`A`, `B`, `C`) using `dynamic_cast` via a pointer.
  - `void identify(Base& p)`: Identifies the real type using `dynamic_cast` via a reference, without using pointers internally.
- **Objective**: Understand dynamic type identification in a polymorphic context without `std::typeinfo`.

## Error Handling
- **Ex00**: Handles impossible conversions (e.g., non-displayable chars, overflows) and pseudo-literals (inf, nan).
- **Ex01**: Ensures serialization/deserialization maintains pointer integrity.
- **Ex02**: Correctly identifies types without runtime errors.

## Exit Codes
- `0`: Success.
- No specific error codes defined, but conversion or identification errors are displayed.

## Limitations
- Strictly adheres to C++98.
- No `using namespace` or `friend` keywords (otherwise -42).
- No STL containers or `<algorithm>` (otherwise -42).
- No C functions like `printf`, `malloc`, `free` (otherwise 0).
- No `std::typeinfo` for exercise 02 (otherwise invalid).
- Memory leaks must be avoided.
- No member functions implemented in header files (except templates).
- Classes must adhere to the Orthodox Canonical Form, except for `Base`, `A`, `B`, `C` in exercise 02.

## Additional Rule
- Each exercise must use a specific type of cast (`static_cast`, `dynamic_cast`, `const_cast`, or `reinterpret_cast`), and the choice will be evaluated during the defense.

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**:

## Acknowledgments
Thanks to 42 school for this project, which allowed me to deepen my understanding of type conversions, serialization, and dynamic type identification in C++98.
