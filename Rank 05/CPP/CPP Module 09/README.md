# CPP09 - README

---

## Description
CPP09 est le dixième et dernier module du parcours C++ dans le cadre du cursus de l'école 42. Ce projet se concentre sur l'utilisation avancée de la bibliothèque standard STL en C++98, en mettant l'accent sur les conteneurs, les algorithmes et la gestion des données. Les exercices incluent un programme pour calculer la valeur des bitcoins à partir d'une base de données CSV, un programme pour évaluer des expressions en notation polonaise inversée (RPN), et un programme pour trier une séquence d'entiers en utilisant l'algorithme Ford-Johnson avec deux conteneurs différents. Chaque exercice impose l'utilisation d'un conteneur STL unique par exercice (sauf pour le dernier, qui en nécessite deux), tout en respectant les contraintes du standard C++98.

L'objectif est de maîtriser les concepts suivants :
- Utilisation des conteneurs STL (`std::map`, `std::stack`, `std::vector`, `std::deque`, etc.) pour gérer des données complexes.
- Application des algorithmes STL pour le traitement et le tri des données.
- Gestion des erreurs avec des exceptions ou des messages d'erreur appropriés.
- Comparaison des performances entre différents conteneurs STL.
- Respect des conventions C++98, y compris la forme canonique de Coplien pour les classes.

## Structure du projet
Le projet est divisé en trois exercices, chacun dans son propre dossier :

- **`ex00/`** : *Bitcoin Exchange* - Programme pour calculer la valeur des bitcoins à partir d'une base de données CSV.
  - Fichiers : `Makefile`, `main.cpp`, `BitcoinExchange.hpp`, `BitcoinExchange.cpp`.
- **`ex01/`** : *Reverse Polish Notation* - Programme pour évaluer des expressions mathématiques en notation polonaise inversée.
  - Fichiers : `Makefile`, `main.cpp`, `RPN.hpp`, `RPN.cpp`.
- **`ex02/`** : *PmergeMe* - Programme pour trier une séquence d'entiers en utilisant l'algorithme Ford-Johnson avec deux conteneurs.
  - Fichiers : `Makefile`, `main.cpp`, `PmergeMe.hpp`, `PmergeMe.cpp`.

## Prérequis
- Un système Unix-like (Linux, macOS).
- Un compilateur C++ compatible avec le standard C++98 (ex. `g++`).
- Les bibliothèques standard C++ (`map`, `stack`, `vector`, `deque`, `algorithm`, etc.).
- Aucun accès à C++11 ou bibliothèques externes (Boost interdit).

## Compilation
Pour chaque exercice, accédez au dossier correspondant (`ex00`, `ex01`, `ex02`) et exécutez :
```bash
make
```
Cela génère un exécutable pour chaque exercice (`btc`, `RPN`, `PmergeMe`). Assurez-vous que les flags de compilation incluent `-Wall -Wextra -Werror -std=c++98`. Le `Makefile` doit inclure les règles `$(NAME)`, `all`, `clean`, `fclean`, et `re`, et ne pas relinker inutilement.

## Utilisation
### Exercice 00 : Bitcoin Exchange
Calcule la valeur des bitcoins pour des dates et quantités données à partir d'un fichier CSV.

```bash
./btc input.txt
```
Sortie (exemple) :
```
2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
2011-01-09 => 1.2 = 0.36
Error: bad input => 2011-01-03 | -1
Error: value out of range => 2011-01-03 | 1001
```

### Exercice 01 : Reverse Polish Notation
Évalue des expressions mathématiques en notation polonaise inversée (RPN).

```bash
./RPN "8 9 * 9 - 9 - 9 - 9 - 9 -"
./RPN "5 1 2 + 4 * + 3 -"
```
Sortie (exemple) :
```
42
14
Error
```

### Exercice 02 : PmergeMe
Trie une séquence d'entiers positifs en utilisant l'algorithme Ford-Johnson avec deux conteneurs différents.

```bash
./PmergeMe 3 5 9 7 4
```
Sortie (exemple) :
```
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::vector: 0.00014 us
Time to process a range of 5 elements with std::deque: 0.00016 us
```

## Fonctionnement détaillé
### Exercice 00 : Bitcoin Exchange
- **Programme `btc`** :
  - Lit une base de données CSV (ex. `data.csv`) contenant les prix des bitcoins par date.
  - Prend un fichier d'entrée (ex. `input.txt`) avec des lignes au format `date | valeur`.
  - Valide les dates (format `YYYY-MM-DD`) et les valeurs (float ou entier entre 0 et 1000).
  - Utilise un conteneur STL (ex. `std::map<std::string, float>`) pour stocker la base de données.
  - Pour chaque ligne du fichier d'entrée, calcule `valeur * prix_bitcoin` pour la date correspondante (ou la date antérieure la plus proche).
  - Gère les erreurs : format de date invalide, valeur hors limites, fichier introuvable.
- **Exigences** :
  - Utilise un conteneur STL (non réutilisable dans les autres exercices).
  - Gère les erreurs avec des messages clairs.
- **Objectif** : Maîtriser la gestion des données avec un conteneur associatif et le traitement de fichiers.

### Exercice 01 : Reverse Polish Notation
- **Programme `RPN`** :
  - Prend une expression en notation polonaise inversée (ex. `"8 9 * 9 - 9 - 9 - 9 -"`) comme argument.
  - Utilise un conteneur STL (ex. `std::stack<int>`) pour évaluer l'expression.
  - Supporte les opérateurs `+`, `-`, `*`, `/`.
  - Les opérandes sont des entiers < 10, mais le résultat peut être quelconque.
  - Gère les erreurs : expression mal formée, division par zéro, pile insuffisante.
- **Exigences** :
  - Utilise un conteneur STL différent de celui utilisé dans `ex00`.
  - Affiche un message d'erreur sur `std::cerr` en cas de problème.
- **Objectif** : Comprendre l'évaluation d'expressions avec une pile STL.

### Exercice 02 : PmergeMe
- **Programme `PmergeMe`** :
  - Prend une séquence d'entiers positifs comme arguments.
  - Trie la séquence en utilisant l'algorithme Ford-Johnson (merge-insert sort) avec deux conteneurs différents (ex. `std::vector` et `std::deque`).
  - Affiche la séquence avant et après le tri, ainsi que le temps d'exécution pour chaque conteneur.
  - Gère au moins 3000 entiers différents.
  - Gère les erreurs : arguments non valides, doublons (à votre discrétion).
- **Exigences** :
  - Utilise deux conteneurs STL différents, non utilisés dans `ex00` ou `ex01`.
  - Implémente l'algorithme Ford-Johnson séparément pour chaque conteneur (pas de fonction générique).
  - Mesure et affiche le temps d'exécution avec une précision suffisante (ex. microsecondes).
- **Objectif** : Comparer les performances de différents conteneurs STL avec un algorithme de tri complexe.

## Gestion des erreurs
- **Ex00** : Erreurs pour fichier introuvable, format de date invalide, valeur hors limites (< 0 ou > 1000).
- **Ex01** : Erreurs pour expression mal formée, division par zéro, opérandes insuffisants.
- **Ex02** : Erreurs pour arguments non valides (non-entiers, négatifs), séquence vide.

## Codes de sortie
- `0` : Succès.
- Pas de codes d'erreur spécifiques définis, mais les exceptions ou messages d'erreur sont affichés sur `std::cerr`.

## Limitations
- Conforme au standard C++98 uniquement.
- Pas d'utilisation de `using namespace` ni de `friend` (sinon -42).
- Les conteneurs STL sont obligatoires, mais chaque conteneur ne peut être utilisé que dans un seul exercice (sauf `ex02`, qui en utilise deux).
- Pas de fonctions C comme `printf`, `malloc`, `free` (sinon 0).
- Les fuites de mémoire doivent être évitées.
- Pas de fonctions membres implémentées dans les fichiers d'en-tête (sauf templates).
- Les classes doivent respecter la forme canonique de Coplien.

## Règles spécifiques au module
- Les conteneurs STL doivent être utilisés dans chaque exercice.
- Un conteneur utilisé dans un exercice ne peut pas être réutilisé dans un autre (sauf `ex02`, qui utilise deux conteneurs distincts).
- ` Makefile` obligatoire avec les règles standard et compilation sans relink.
- `ex02` nécessite des implémentations séparées de l'algorithme Ford-Johnson pour chaque conteneur.

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** :

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis d'approfondir ma compréhension des conteneurs STL, des algorithmes, et de la gestion des performances en C++98.

---

# CPP09 - README

## Description
CPP09 is the tenth and final module of the C++ curriculum at 42 school. This project focuses on advanced use of the STL in C++98, emphasizing containers, algorithms, and data management. The exercises include a program to calculate bitcoin values from a CSV database, a program to evaluate reverse Polish notation (RPN) expressions, and a program to sort a sequence of integers using the Ford-Johnson algorithm with two different containers. Each exercise requires using a unique STL container (except for the last, which requires two), while adhering to C++98 constraints.

The goal is to master the following concepts:
- Using STL containers (`std::map`, `std::stack`, `std::vector`, `std::deque`, etc.) for complex data management.
- Applying STL algorithms for data processing and sorting.
- Handling errors with exceptions or appropriate error messages.
- Comparing performance between different STL containers.
- Adhering to C++98 conventions, including the Orthodox Canonical Form for classes.

## Project Structure
The project is divided into three exercises, each in its own directory:

- **`ex00/`**: *Bitcoin Exchange* - Program to calculate bitcoin values from a CSV database.
  - Files: `Makefile`, `main.cpp`, `BitcoinExchange.hpp`, `BitcoinExchange.cpp`.
- **`ex01/`**: *Reverse Polish Notation* - Program to evaluate mathematical expressions in reverse Polish notation.
  - Files: `Makefile`, `main.cpp`, `RPN.hpp`, `RPN.cpp`.
- **`ex02/`**: *PmergeMe* - Program to sort a sequence of positive integers using the Ford-Johnson algorithm with two containers.
  - Files: `Makefile`, `main.cpp`, `PmergeMe.hpp`, `PmergeMe.cpp`.

## Prerequisites
- A Unix-like system (Linux, macOS).
- A C++ compiler compatible with C++98 (e.g., `g++`).
- Standard C++ libraries (`map`, `stack`, `vector`, `deque`, `algorithm`, etc.).
- No access to C++11 or external libraries (Boost is forbidden).

## Compilation
For each exercise, navigate to its directory (`ex00`, `ex01`, `ex02`) and run:
```bash
make
```
This generates an executable for each exercise (`btc`, `RPN`, `PmergeMe`). Ensure compilation flags include `-Wall -Wextra -Werror -std=c++98`. The `Makefile` must include the rules `$(NAME)`, `all`, `clean`, `fclean`, and `re`, and avoid unnecessary relinking.

## Usage
### Exercise 00: Bitcoin Exchange
Calculates bitcoin values for given dates and amounts from a CSV database.

```bash
./btc input.txt
```
Output (example):
```
2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
2011-01-09 => 1.2 = 0.36
Error: bad input => 2011-01-03 | -1
Error: value out of range => 2011-01-03 | 1001
```

### Exercise 01: Reverse Polish Notation
Evaluates mathematical expressions in reverse Polish notation (RPN).

```bash
./RPN "8 9 * 9 - 9 - 9 - 9 -"
./RPN "5 1 2 + 4 * + 3 -"
```
Output (example):
```
42
14
Error
```

### Exercise 02: PmergeMe
Sorts a sequence of positive integers using the Ford-Johnson algorithm with two different containers.

```bash
./PmergeMe 3 5 9 7 4
```
Output (example):
```
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::vector: 0.00014 us
Time to process a range of 5 elements with std::deque: 0.00016 us
```

## Detailed Functionality
### Exercise 00: Bitcoin Exchange
- **Program `btc`**:
  - Reads a CSV database (e.g., `data.csv`) containing bitcoin prices by date.
  - Takes an input file (e.g., `input.txt`) with lines in the format `date | value`.
  - Validates dates (format `YYYY-MM-DD`) and values (float or integer between 0 and 1000).
  - Uses an STL container (e.g., `std::map<std::string, float>`) to store the database.
  - For each input line, calculates `value * bitcoin_price` for the corresponding date (or the closest prior date).
  - Handles errors: invalid date format, value out of bounds, file not found.
- **Requirements**:
  - Uses an STL container (not reusable in other exercises).
  - Handles errors with clear messages.
- **Objective**: Master data management with an associative container and file processing.

### Exercise 01: Reverse Polish Notation
- **Program `RPN`**:
  - Takes a reverse Polish notation expression (e.g., `"8 9 * 9 - 9 - 9 - 9 -"`) as an argument.
  - Uses an STL container (e.g., `std::stack<int>`) to evaluate the expression.
  - Supports operators `+`, `-`, `*`, `/`.
  - Operands are integers < 10, but the result can be any integer.
  - Handles errors: malformed expression, division by zero, insufficient operands.
- **Requirements**:
  - Uses an STL container different from the one used in `ex00`.
  - Outputs an error message to `std::cerr` on failure.
- **Objective**: Understand expression evaluation using an STL stack.

### Exercise 02: PmergeMe
- **Program `PmergeMe`**:
  - Takes a sequence of positive integers as arguments.
  - Sorts the sequence using the Ford-Johnson (merge-insert) algorithm with two different containers (e.g., `std::vector` and `std::deque`).
  - Displays the sequence before and after sorting, plus the execution time for each container.
  - Handles at least 3000 distinct integers.
  - Handles errors: invalid arguments (non-integers, negative), empty sequence.
- **Requirements**:
  - Uses two distinct STL containers, not used in `ex00` or `ex01`.
  - Implements the Ford-Johnson algorithm separately for each container (no generic function).
  - Measures and displays execution time with sufficient precision (e.g., microseconds).
- **Objective**: Compare performance of different STL containers with a complex sorting algorithm.

## Error Handling
- **Ex00**: Errors for missing file, invalid date format, value out of bounds (< 0 or > 1000).
- **Ex01**: Errors for malformed expression, division by zero, insufficient operands.
- **Ex02**: Errors for invalid arguments (non-integers, negative), empty sequence.

## Exit Codes
- `0`: Success.
- No specific error codes defined, but exceptions or error messages are output to `std::cerr`.

## Limitations
- Strictly adheres to C++98.
- No `using namespace` or `friend` keywords (otherwise -42).
- STL containers are mandatory, but each container can only be used in one exercise (except `ex02`, which uses two).
- No C functions like `printf`, `malloc`, `free` (otherwise 0).
- Memory leaks must be avoided.
- No member functions implemented in header files (except templates).
- Classes must adhere to the Orthodox Canonical Form.

## Module-Specific Rules
- STL containers are mandatory for each exercise.
- A container used in one exercise cannot be reused in another (except `ex02`, which uses two distinct containers).
- `Makefile` is required with standard rules and no unnecessary relinking.
- `ex02` requires separate Ford-Johnson algorithm implementations for each container.

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**:

## Acknowledgments
Thanks to 42 school for this project, which allowed me to deepen my understanding of STL containers, algorithms, and performance management in C++98.
