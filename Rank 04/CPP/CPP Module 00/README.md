# CPP00 - README

---

## Description
CPP00 est le premier module du parcours C++ dans le cadre du cursus de l'école 42. Ce projet introduit les bases de la programmation orientée objet (OOP) en C++98, en mettant l'accent sur des concepts fondamentaux tels que les namespaces, les classes, les fonctions membres, les flux d'entrée/sortie (stdio streams), les listes d'initialisation, ainsi que les mots-clés `static` et `const`. Il comprend trois exercices : Mégaphone (conversion de texte en majuscules), My Awesome PhoneBook (gestion d'un répertoire de contacts), et L'emploi de vos rêves (reconstruction d'une classe bancaire).

L'objectif est de maîtriser les concepts suivants :
- Syntaxe et conventions de base du C++98.
- Création et utilisation de classes avec attributs et fonctions membres.
- Gestion des entrées/sorties avec les flux C++ (`iostream`).
- Encapsulation avec des membres publics et privés.
- Gestion de la mémoire sans fuites (via `new` et `delete`).
- Compréhension des concepts `static` et `const` dans les classes.

## Structure du projet
Le projet est divisé en trois exercices, chacun dans son propre dossier :
- **`ex00/`** : Contient l'exercice *Mégaphone*.
  - `Makefile` : Compilation du programme.
  - `megaphone.cpp` : Programme convertissant les arguments en majuscules.
- **`ex01/`** : Contient l'exercice *My Awesome PhoneBook*.
  - `Makefile` : Compilation du programme.
  - `utils/phonebook.cpp`, `include/phonebook.hpp`, `utils/contact.cpp`, `include/contact.hpp`, `main` : Classes pour gérer un répertoire de contacts.
- **`ex02/`** : Contient l'exercice *L'emploi de vos rêves*.
  - `Makefile` : Compilation du programme.
  - `Account.cpp`, `Account.hpp`, `tests.cpp` : Reconstruction d'une classe bancaire à partir d'un fichier de log.

## Prérequis
- Un système Unix-like (Linux, macOS).
- Un compilateur C++ compatible avec le standard C++98 (ex. `g++`).
- Les bibliothèques standard C++ (`iostream`, `string`, `iomanip`, etc.).
- Aucun accès à C++11 ou bibliothèques externes (Boost interdit).

## Compilation
Pour chaque exercice, accédez au dossier correspondant (`ex00`, `ex01`, `ex02`) et exécutez :
```bash
make
```
Cela génère un exécutable pour chaque exercice. Assurez-vous que les flags de compilation incluent `-Wall -Wextra -Werror -std=c++98`.

## Utilisation
### Exercice 00 : Mégaphone
Le programme convertit les arguments en majuscules. S'il n'y a pas d'arguments, il affiche un message par défaut.

```bash
./megaphone "hello world"
```
Sortie : `HELLO WORLD`

```bash
./megaphone
```
Sortie : `* LOUD AND UNBEARABLE FEEDBACK NOISE *`

### Exercice 01 : My Awesome PhoneBook
Le programme simule un répertoire de contacts avec trois commandes : `ADD`, `SEARCH`, et `EXIT`.

```bash
./phonebook
```
- **ADD** : Ajoute un contact (prénom, nom, surnom, numéro, secret). Maximum 8 contacts, le plus ancien est remplacé si nécessaire.
- **SEARCH** : Affiche une liste de contacts (index, prénom, nom, surnom) avec des colonnes de 10 caractères, alignées à droite, tronquées si nécessaire. Demande un index pour afficher les détails d'un contact.
- **EXIT** : Quitte le programme, perdant tous les contacts.

Exemple :
```bash
ADD
First name: John
Last name: Doe
Nickname: Johnny
Phone number: 1234567890
Darkest secret: Loves pizza
SEARCH
|     index|first name| last name|  nickname|
|         1|      John|       Doe|    Johnny|
Enter index: 1
First name: John
Last name: Doe
Nickname: Johnny
Phone number: 1234567890
Darkest secret: Loves pizza
EXIT
```

### Exercice 02 : L'emploi de vos rêves
Le programme reconstruit la classe `Account` pour passer les tests fournis dans `tests.cpp`, en s'appuyant sur `Account.hpp` et un fichier de log.

```bash
./account
```
Sortie : Correspond aux tests du fichier de log (horodatage excepté).

## Fonctionnement détaillé
### Exercice 00 : Mégaphone
- Lit les arguments de la ligne de commande (`argc`, `argv`).
- Convertit chaque caractère en majuscule avec `std::toupper`.
- Si aucun argument n'est fourni, affiche `* LOUD AND UNBEARABLE FEEDBACK NOISE *`.

### Exercice 01 : My Awesome PhoneBook
#### Structure des classes
- **`PhoneBook`** :
  - Contient un tableau statique de 8 objets `Contact`.
  - Méthodes : `addContact` (ajoute un contact), `searchContact` (affiche la liste et les détails).
- **`Contact`** :
  - Attributs : `firstName`, `lastName`, `nickname`, `phoneNumber`, `darkestSecret` (tous `std::string`).
  - Méthodes : Setters/getters pour chaque attribut.

#### Étapes principales
1. **Initialisation** : Le répertoire est vide au démarrage.
2. **Commande ADD** :
   - Demande les 5 champs du contact via `std::cin`.
   - Vérifie que les champs ne sont pas vides.
   - Ajoute le contact au tableau, remplaçant le plus ancien si plein.
3. **Commande SEARCH** :
   - Affiche une table formatée avec `std::setw(10)` et `std::right`.
   - Tronque les champs trop longs avec un point (`.`).
   - Demande un index valide et affiche les détails du contact.
4. **Commande EXIT** : Termine le programme.
5. **Gestion des erreurs** : Ignore les entrées invalides, gère les index incorrects.

### Exercice 02 : L'emploi de vos rêves
#### Structure de la classe
- **`Account`** :
  - Attributs : `accountIndex`, `amount`, `nbDeposits`, `nbWithdrawals` (attributs d'instance), `nbAccounts`, `totalAmount`, `nbDeposits`, `nbWithdrawals` (attributs statiques).
  - Méthodes : Constructeur, destructeur, `makeDeposit`, `makeWithdrawal`, `displayStatus`, `displayAccountsInfos` (statique).
- **`tests.cpp`** : Contient les tests pour valider l'implémentation.

#### Étapes principales
1. **Reconstruction** : Implémentez `Account.cpp` en suivant `Account.hpp` et le fichier de log.
2. **Gestion des comptes** :
   - Suivi des dépôts/retraits et du solde.
   - Affichage formaté des informations avec `std::cout`.
3. **Validation** : La sortie doit correspondre au log (sauf horodatage).
4. **Gestion des erreurs** : Pas de fuites de mémoire, respect des conventions C++98.

## Gestion des erreurs
- **Ex00** : Gère l'absence d'arguments avec un message par défaut.
- **Ex01** :
  - Vérifie les champs non vides pour les contacts.
  - Gère les index invalides dans `SEARCH`.
  - Ignore les commandes inconnues.
- **Ex02** : Assure l'absence de fuites de mémoire et la conformité des sorties avec le log.

## Codes de sortie
- `0` : Succès.
- Pas d'erreurs spécifiques définies, mais les erreurs d'exécution (ex. index invalide) sont gérées en interne.

## Limitations
- Conforme au standard C++98 uniquement.
- Pas d'utilisation de `using namespace` ni de `friend` (sinon -42).
- Pas de STL (vector, map, etc.) ni d'algorithmes (`<algorithm>` interdit).
- Pas de fonctions C comme `printf`, `malloc`, `free` (sinon 0).
- Les fuites de mémoire doivent être évitées.

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** : Juillet 2025

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis de découvrir les bases de la programmation orientée objet en C++ et de m'initier aux concepts de classes, d'encapsulation et de gestion des flux.

---

# CPP00 - README

## Description
CPP00 is the first module of the C++ curriculum at 42 school. This project introduces the fundamentals of object-oriented programming (OOP) in C++98, focusing on key concepts such as namespaces, classes, member functions, stdio streams, initialization lists, and the `static` and `const` keywords. It consists of three exercises: Mégaphone (text to uppercase conversion), My Awesome PhoneBook (contact management), and L'emploi de vos rêves (rebuilding a banking class).

The goal is to master the following concepts:
- Basic C++98 syntax and conventions.
- Creating and using classes with attributes and member functions.
- Handling input/output with C++ streams (`iostream`).
- Encapsulation with public and private members.
- Memory management without leaks (using `new` and `delete`).
- Understanding `static` and `const` in classes.

## Project Structure
The project is split into three exercises, each in its own directory:
- **`ex00/`**: Contains the *Mégaphone* exercise.
  - `Makefile`: Compiles the program.
  - `megaphone.cpp`: Converts command-line arguments to uppercase.
- **`ex01/`**: Contains the *My Awesome PhoneBook* exercise.
  - `Makefile`: Compiles the program.
  - `utils/phonebook.cpp`, `include/phonebook.hpp`, `utils/contact.cpp`, `include/contact.hpp`, `main`: Classes for managing a contact directory.
- **`ex02/`**: Contains the *L'emploi de vos rêves* exercise.
  - `Makefile`: Compiles the program.
  - `Account.cpp`, `Account.hpp`, `tests.cpp`: Rebuilds a banking class based on a log file.

## Prerequisites
- A Unix-like system (Linux, macOS).
- A C++ compiler compatible with C++98 (e.g., `g++`).
- Standard C++ libraries (`iostream`, `string`, `iomanip`, etc.).
- No access to C++11 or external libraries (Boost is forbidden).

## Compilation
For each exercise, navigate to its directory (`ex00`, `ex01`, `ex02`) and run:
```bash
make
```
This generates an executable for each exercise. Ensure compilation flags include `-Wall -Wextra -Werror -std=c++98`.

## Usage
### Exercise 00: Mégaphone
The program converts command-line arguments to uppercase. If no arguments are provided, it displays a default message.

```bash
./megaphone "hello world"
```
Output: `HELLO WORLD`

```bash
./megaphone
```
Output: `* LOUD AND UNBEARABLE FEEDBACK NOISE *`

### Exercise 01: My Awesome PhoneBook
The program simulates a contact directory with three commands: `ADD`, `SEARCH`, and `EXIT`.

```bash
./phonebook
```
- **ADD**: Adds a contact (first name, last name, nickname, phone number, darkest secret). Maximum 8 contacts, replacing the oldest if full.
- **SEARCH**: Displays a list of contacts (index, first name, last name, nickname) in 10-character columns, right-aligned, truncated if needed. Prompts for an index to display contact details.
- **EXIT**: Quits the program, losing all contacts.

Example:
```bash
ADD
First name: John
Last name: Doe
Nickname: Johnny
Phone number: 1234567890
Darkest secret: Loves pizza
SEARCH
|     index|first name| last name|  nickname|
|         1|      John|       Doe|    Johnny|
Enter index: 1
First name: John
Last name: Doe
Nickname: Johnny
Phone number: 1234567890
Darkest secret: Loves pizza
EXIT
```

### Exercise 02: L'emploi de vos rêves
The program rebuilds the `Account` class to pass tests in `tests.cpp`, using `Account.hpp` and a log file.

```bash
./account
```
Output: Matches the log file (except for timestamps).

## Detailed Functionality
### Exercise 00: Mégaphone
- Reads command-line arguments (`argc`, `argv`).
- Converts each character to uppercase using `std::toupper`.
- Outputs a default message if no arguments are provided.

### Exercise 01: My Awesome PhoneBook
#### Class Structure
- **`PhoneBook`**:
  - Contains a static array of 8 `Contact` objects.
  - Methods: `addContact` (adds a contact), `searchContact` (displays the list and details).
- **`Contact`**:
  - Attributes: `firstName`, `lastName`, `nickname`, `phoneNumber`, `darkestSecret` (all `std::string`).
  - Methods: Setters/getters for each attribute.

#### Main Steps
1. **Initialization**: The directory is empty at startup.
2. **ADD Command**:
   - Prompts for 5 contact fields via `std::cin`.
   - Ensures fields are not empty.
   - Adds the contact to the array, replacing the oldest if full.
3. **SEARCH Command**:
   - Displays a formatted table using `std::setw(10)` and `std::right`.
   - Truncates fields longer than 10 characters with a dot (`.`).
   - Prompts for a valid index and displays contact details.
4. **EXIT Command**: Terminates the program.
5. **Error Handling**: Ignores invalid inputs, handles incorrect indices.

### Exercise 02: L'emploi de vos rêves
#### Class Structure
- **`Account`**:
  - Attributes: `accountIndex`, `amount`, `nbDeposits`, `nbWithdrawals` (instance), `nbAccounts`, `totalAmount`, `nbDeposits`, `nbWithdrawals` (static).
  - Methods: Constructor, destructor, `makeDeposit`, `makeWithdrawal`, `displayStatus`, `displayAccountsInfos` (static).
- **`tests.cpp`**: Contains tests to validate the implementation.

#### Main Steps
1. **Reconstruction**: Implement `Account.cpp` based on `Account.hpp` and the log file.
2. **Account Management**:
   - Tracks deposits, withdrawals, and balances.
   - Formats output using `std::cout`.
3. **Validation**: Output must match the log (except timestamps).
4. **Error Handling**: Ensures no memory leaks and compliance with C++98.

## Error Handling
- **Ex00**: Handles missing arguments with a default message.
- **Ex01**:
  - Ensures non-empty contact fields.
  - Manages invalid indices in `SEARCH`.
  - Ignores unknown commands.
- **Ex02**: Prevents memory leaks and ensures output matches the log.

## Exit Codes
- `0`: Success.
- No specific error codes defined, but runtime errors (e.g., invalid index) are handled internally.

## Limitations
- Strictly adheres to C++98.
- No `using namespace` or `friend` keywords (otherwise -42).
- No STL containers or `<algorithm>` (otherwise -42).
- No C functions like `printf`, `malloc`, `free` (otherwise 0).
- Memory leaks must be avoided.

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**: July 2025

## Acknowledgments
Thanks to 42 school for this project, which helped me understand the basics of object-oriented programming in C++ and introduced me to classes, encapsulation, and stream management.