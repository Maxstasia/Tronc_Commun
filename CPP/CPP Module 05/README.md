# CPP05 - README

---

## Description
CPP05 est le sixième module du parcours C++ dans le cadre du cursus de l'école 42. Ce projet se concentre sur la gestion des exceptions et la répétition des concepts d'héritage et de polymorphisme en C++98. Il explore la création d'une hiérarchie de classes représentant des bureaucrates, des formulaires abstraits, et des formulaires concrets, ainsi que la gestion des erreurs via des exceptions. Les exercices impliquent des classes telles que `Bureaucrat`, `AForm`, `ShrubberyCreationForm`, `RobotomyRequestForm`, `PresidentialPardonForm`, et `Intern`, tout en respectant la forme canonique de Coplien pour toutes les classes sauf les exceptions.

L'objectif est de maîtriser les concepts suivants :
- Gestion des exceptions pour contrôler les erreurs (grades invalides, formulaires non signés, etc.).
- Utilisation de classes abstraites pour définir des comportements communs.
- Polymorphisme pour exécuter des actions spécifiques à chaque type de formulaire.
- Conception propre et évitement des solutions verbeuses (ex. structures conditionnelles excessives).
- Respect des conventions C++98, y compris la forme canonique pour les classes non-exceptionnelles.

## Structure du projet
Le projet est divisé en quatre exercices, chacun dans son propre dossier :

- **`ex00/`** : *Mommy, when I grow up, I want to be a bureaucrat!* - Création de la classe `Bureaucrat`.
  - Fichiers : `Makefile`, `main.cpp`, `Bureaucrat.hpp`, `Bureaucrat.cpp`.
- **`ex01/`** : *Form up, maggots!* - Ajout de la classe `Form`.
  - Fichiers : Fichiers de l'exercice précédent + `Form.hpp`, `Form.cpp`.
- **`ex02/`** : *No, you need form 28B, not 28C...* - Transformation de `Form` en `AForm` (abstraite) et ajout des classes concrètes `ShrubberyCreationForm`, `RobotomyRequestForm`, `PresidentialPardonForm`.
  - Fichiers : `Makefile`, `main.cpp`, `Bureaucrat.hpp`, `Bureaucrat.cpp`, `AForm.hpp`, `AForm.cpp`, `ShrubberyCreationForm.hpp`, `ShrubberyCreationForm.cpp`, `RobotomyRequestForm.hpp`, `RobotomyRequestForm.cpp`, `PresidentialPardonForm.hpp`, `PresidentialPardonForm.cpp`.
- **`ex03/`** : *At least this beats coffee-making* - Ajout de la classe `Intern` pour créer des formulaires.
  - Fichiers : Fichiers de l'exercice précédent + `Intern.hpp`, `Intern.cpp`.

## Prérequis
- Un système Unix-like (Linux, macOS).
- Un compilateur C++ compatible avec le standard C++98 (ex. `g++`).
- Les bibliothèques standard C++ (`iostream`, `string`, `fstream`, etc.).
- Aucun accès à C++11 ou bibliothèques externes (Boost interdit).

## Compilation
Pour chaque exercice, accédez au dossier correspondant (`ex00`, `ex01`, `ex02`, `ex03`) et exécutez :
```bash
make
```
Cela génère un exécutable pour chaque exercice. Assurez-vous que les flags de compilation incluent `-Wall -Wextra -Werror -std=c++98`.

## Utilisation
### Exercice 00 : Mommy, when I grow up, I want to be a bureaucrat!
Crée une classe `Bureaucrat` avec des grades et des exceptions pour gérer les erreurs.

```bash
./bureaucrat
```
Sortie (exemple) :
```
Bureaucrat Alice, grade 50 constructed
Alice, bureaucrat grade 50
Bureaucrat Alice incremented to grade 49
Bureaucrat Alice decremented to grade 50
Error: GradeTooHighException: Grade cannot be higher than 1
Bureaucrat Alice destructed
```

### Exercice 01 : Form up, maggots!
Ajoute une classe `Form` que les bureaucrates peuvent signer.

```bash
./form
```
Sortie (exemple) :
```
Bureaucrat Bob, grade 50 constructed
Form TaxForm, unsigned, sign grade 60, exec grade 40 constructed
Bob couldn't sign TaxForm because GradeTooLowException: Grade too low
Bureaucrat Bob destructed
Form TaxForm destructed
```

### Exercice 02 : No, you need form 28B, not 28C...
Transforme `Form` en une classe abstraite `AForm` et ajoute des formulaires concrets avec des actions spécifiques.

```bash
./forms
```
Sortie (exemple) :
```
Bureaucrat Charlie, grade 5 constructed
ShrubberyCreationForm Home, unsigned, sign grade 145, exec grade 137 constructed
Charlie signed Home
Charlie executed Home
RobotomyRequestForm Bender, unsigned, sign grade 72, exec grade 45 constructed
Charlie signed Bender
Charlie executed Bender: *drill noises* Bender has been robotomized successfully
PresidentialPardonForm Zaphod, unsigned, sign grade 25, exec grade 5 constructed
Charlie signed Zaphod
Charlie executed Zaphod: Zaphod Beeblebrox has been pardoned
Bureaucrat Charlie destructed
ShrubberyCreationForm Home destructed
RobotomyRequestForm Bender destructed
PresidentialPardonForm Zaphod destructed
```

### Exercice 03 : At least this beats coffee-making
Ajoute une classe `Intern` pour créer des formulaires dynamiquement.

```bash
./intern
```
Sortie (exemple) :
```
Intern constructed
Bureaucrat Dave, grade 5 constructed
Intern creates ShrubberyCreationForm
Dave signed Home
Dave executed Home
Intern creates RobotomyRequestForm
Dave signed Bender
Dave executed Bender: *drill noises* Bender has been robotomized successfully
Intern creates PresidentialPardonForm
Dave signed Zaphod
Dave executed Zaphod: Zaphod Beeblebrox has been pardoned
Error: Unknown form type: InvalidForm
Intern destructed
Bureaucrat Dave destructed
```

## Fonctionnement détaillé
### Exercice 00 : Mommy, when I grow up, I want to be a bureaucrat!
- **Classe `Bureaucrat`** :
  - Attributs : `name` (const string), `grade` (int, 1 à 150).
  - Exceptions : `GradeTooHighException` (grade < 1), `GradeTooLowException` (grade > 150).
  - Fonctions : `getName`, `getGrade`, `incrementGrade`, `decrementGrade`, surcharge de `<<`.
  - Respecte la forme canonique.
- **Objectif** : Implémenter une classe avec gestion des exceptions pour les grades.

### Exercice 01 : Form up, maggots!
- **Classe `Form`** :
  - Attributs : `name` (const string), `isSigned` (bool, initialement false), `signGrade` (const int), `execGrade` (const int).
  - Exceptions : `GradeTooHighException`, `GradeTooLowException`.
  - Fonctions : `getName`, `getIsSigned`, `getSignGrade`, `getExecGrade`, `beSigned`, surcharge de `<<`.
  - Respecte la forme canonique.
- **Classe `Bureaucrat`** : Ajout de `signForm` pour tenter de signer un formulaire.
- **Objectif** : Gérer l'interaction entre bureaucrates et formulaires avec des exceptions.

### Exercice 02 : No, you need form 28B, not 28C...
- **Classe `AForm`** :
  - Classe abstraite renommée depuis `Form`.
  - Attributs : `name`, `isSigned`, `signGrade`, `execGrade` (privés).
  - Fonction virtuelle pure : `execute(Bureaucrat const & executor) const`.
  - Exceptions : `GradeTooHighException`, `GradeTooLowException`, `FormNotSignedException`.
  - Respecte la forme canonique.
- **Classes concrètes** :
  - `ShrubberyCreationForm` : Crée un fichier `<target>_shrubbery` avec des arbres ASCII (sign 145, exec 137).
  - `RobotomyRequestForm` : Simule une robotomisation avec 50% de succès (sign 72, exec 45).
  - `PresidentialPardonForm` : Annonce un pardon présidentiel (sign 25, exec 5).
- **Classe `Bureaucrat`** : Ajout de `executeForm` pour exécuter un formulaire.
- **Objectif** : Implémenter une hiérarchie de formulaires avec des actions polymorphiques.

### Exercice 03 : At least this beats coffee-making
- **Classe `Intern`** :
  - Fonction : `makeForm(string name, string target)` pour créer des formulaires (`AForm*`).
  - Gère les types de formulaires : "shrubbery creation", "robotomy request", "presidential pardon".
  - Affiche un message de création ou une erreur si le type est inconnu.
  - Respecte la forme canonique.
- **Objectif** : Automatiser la création de formulaires avec une conception propre.

## Gestion des erreurs
- **Ex00** : Gère les grades invalides via `GradeTooHighException` et `GradeTooLowException`.
- **Ex01** : Vérifie les grades pour signer les formulaires, lance `GradeTooLowException` si nécessaire.
- **Ex02** : Vérifie si le formulaire est signé et si le grade est suffisant pour l'exécution, lance `FormNotSignedException` ou `GradeTooLowException`.
- **Ex03** : Gère les noms de formulaires inconnus avec un message d'erreur explicite.

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
- Les classes (sauf exceptions) doivent respecter la forme canonique de Coplien.

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** :

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis d'approfondir ma compréhension des exceptions, du polymorphisme, des classes abstraites, et de la conception propre en C++98.

---

# CPP05 - README

## Description
CPP05 is the sixth module of the C++ curriculum at 42 school. This project focuses on exception handling and reinforces concepts of inheritance and polymorphism in C++98. It explores creating a hierarchy of classes representing bureaucrats, abstract forms, and concrete forms, as well as managing errors through exceptions. The exercises involve classes such as `Bureaucrat`, `AForm`, `ShrubberyCreationForm`, `RobotomyRequestForm`, `PresidentialPardonForm`, and `Intern`, while adhering to the Orthodox Canonical Form for all classes except exceptions.

The goal is to master the following concepts:
- Exception handling for error control (invalid grades, unsigned forms, etc.).
- Using abstract classes to define common behaviors.
- Polymorphism for executing specific form actions.
- Clean design and avoiding verbose solutions (e.g., excessive conditional structures).
- Adhering to C++98 conventions, including the Orthodox Canonical Form for non-exception classes.

## Project Structure
The project is divided into four exercises, each in its own directory:

- **`ex00/`**: *Mommy, when I grow up, I want to be a bureaucrat!* - Creates the `Bureaucrat` class.
  - Files: `Makefile`, `main.cpp`, `Bureaucrat.hpp`, `Bureaucrat.cpp`.
- **`ex01/`**: *Form up, maggots!* - Adds the `Form` class.
  - Files: Files from previous exercise + `Form.hpp`, `Form.cpp`.
- **`ex02/`**: *No, you need form 28B, not 28C...* - Transforms `Form` into abstract `AForm` and adds concrete form classes.
  - Files: `Makefile`, `main.cpp`, `Bureaucrat.hpp`, `Bureaucrat.cpp`, `AForm.hpp`, `AForm.cpp`, `ShrubberyCreationForm.hpp`, `ShrubberyCreationForm.cpp`, `RobotomyRequestForm.hpp`, `RobotomyRequestForm.cpp`, `PresidentialPardonForm.hpp`, `PresidentialPardonForm.cpp`.
- **`ex03/`**: *At least this beats coffee-making* - Adds the `Intern` class for form creation.
  - Files: Files from previous exercise + `Intern.hpp`, `Intern.cpp`.

## Prerequisites
- A Unix-like system (Linux, macOS).
- A C++ compiler compatible with C++98 (e.g., `g++`).
- Standard C++ libraries (`iostream`, `string`, `fstream`, etc.).
- No access to C++11 or external libraries (Boost is forbidden).

## Compilation
For each exercise, navigate to its directory (`ex00`, `ex01`, `ex02`, `ex03`) and run:
```bash
make
```
This generates an executable for each exercise. Ensure compilation flags include `-Wall -Wextra -Werror -std=c++98`.

## Usage
### Exercise 00: Mommy, when I grow up, I want to be a bureaucrat!
Creates a `Bureaucrat` class with grades and exceptions for error handling.

```bash
./bureaucrat
```
Output (example):
```
Bureaucrat Alice, grade 50 constructed
Alice, bureaucrat grade 50
Bureaucrat Alice incremented to grade 49
Bureaucrat Alice decremented to grade 50
Error: GradeTooHighException: Grade cannot be higher than 1
Bureaucrat Alice destructed
```

### Exercise 01: Form up, maggots!
Adds a `Form` class that bureaucrats can sign.

```bash
./form
```
Output (example):
```
Bureaucrat Bob, grade 50 constructed
Form TaxForm, unsigned, sign grade 60, exec grade 40 constructed
Bob couldn't sign TaxForm because GradeTooLowException: Grade too low
Bureaucrat Bob destructed
Form TaxForm destructed
```

### Exercise 02: No, you need form 28B, not 28C...
Transforms `Form` into an abstract `AForm` class and adds concrete form classes with specific actions.

```bash
./forms
```
Output (example):
```
Bureaucrat Charlie, grade 5 constructed
ShrubberyCreationForm Home, unsigned, sign grade 145, exec grade 137 constructed
Charlie signed Home
Charlie executed Home
RobotomyRequestForm Bender, unsigned, sign grade 72, exec grade 45 constructed
Charlie signed Bender
Charlie executed Bender: *drill noises* Bender has been robotomized successfully
PresidentialPardonForm Zaphod, unsigned, sign grade 25, exec grade 5 constructed
Charlie signed Zaphod
Charlie executed Zaphod: Zaphod Beeblebrox has been pardoned
Bureaucrat Charlie destructed
ShrubberyCreationForm Home destructed
RobotomyRequestForm Bender destructed
PresidentialPardonForm Zaphod destructed
```

### Exercise 03: At least this beats coffee-making
Adds an `Intern` class to dynamically create forms.

```bash
./intern
```
Output (example):
```
Intern constructed
Bureaucrat Dave, grade 5 constructed
Intern creates ShrubberyCreationForm
Dave signed Home
Dave executed Home
Intern creates RobotomyRequestForm
Dave signed Bender
Dave executed Bender: *drill noises* Bender has been robotomized successfully
Intern creates PresidentialPardonForm
Dave signed Zaphod
Dave executed Zaphod: Zaphod Beeblebrox has been pardoned
Error: Unknown form type: InvalidForm
Intern destructed
Bureaucrat Dave destructed
```

## Detailed Functionality
### Exercise 00: Mommy, when I grow up, I want to be a bureaucrat!
- **Class `Bureaucrat`**:
  - Attributes: `name` (const string), `grade` (int, 1 to 150).
  - Exceptions: `GradeTooHighException` (grade < 1), `GradeTooLowException` (grade > 150).
  - Functions: `getName`, `getGrade`, `incrementGrade`, `decrementGrade`, `<<` operator overload.
  - Adheres to the Orthodox Canonical Form.
- **Objective**: Implement a class with exception handling for grades.

### Exercise 01: Form up, maggots!
- **Class `Form`**:
  - Attributes: `name` (const string), `isSigned` (bool, initially false), `signGrade` (const int), `execGrade` (const int).
  - Exceptions: `GradeTooHighException`, `GradeTooLowException`.
  - Functions: `getName`, `getIsSigned`, `getSignGrade`, `getExecGrade`, `beSigned`, `<<` operator overload.
  - Adheres to the Orthodox Canonical Form.
- **Class `Bureaucrat`**: Adds `signForm` to attempt signing a form.
- **Objective**: Manage interactions between bureaucrats and forms with exceptions.

### Exercise 02: No, you need form 28B, not 28C...
- **Class `AForm`**:
  - Abstract class renamed from `Form`.
  - Attributes: `name`, `isSigned`, `signGrade`, `execGrade` (private).
  - Pure virtual function: `execute(Bureaucrat const & executor) const`.
  - Exceptions: `GradeTooHighException`, `GradeTooLowException`, `FormNotSignedException`.
  - Adheres to the Orthodox Canonical Form.
- **Concrete Classes**:
  - `ShrubberyCreationForm`: Creates a `<target>_shrubbery` file with ASCII trees (sign 145, exec 137).
  - `RobotomyRequestForm`: Simulates robotomization with 50% success (sign 72, exec 45).
  - `PresidentialPardonForm`: Announces a presidential pardon (sign 25, exec 5).
- **Class `Bureaucrat`**: Adds `executeForm` to execute a form.
- **Objective**: Implement a form hierarchy with polymorphic actions.

### Exercise 03: At least this beats coffee-making
- **Class `Intern`**:
  - Function: `makeForm(string name, string target)` to create forms (`AForm*`).
  - Handles form types: "shrubbery creation", "robotomy request", "presidential pardon".
  - Prints creation message or error for unknown form types.
  - Adheres to the Orthodox Canonical Form.
- **Objective**: Automate form creation with clean design.

## Error Handling
- **Ex00**: Handles invalid grades via `GradeTooHighException` and `GradeTooLowException`.
- **Ex01**: Checks grades for signing forms, throws `GradeTooLowException` if needed.
- **Ex02**: Verifies form signing and sufficient grade for execution, throws `FormNotSignedException` or `GradeTooLowException`.
- **Ex03**: Handles unknown form names with an explicit error message.

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
- Classes (except exceptions) must adhere to the Orthodox Canonical Form.

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**:

## Acknowledgments
Thanks to 42 school for this project, which allowed me to deepen my understanding of exception handling, polymorphism, abstract classes, and clean design in C++98.
