Français

---

# **Pipex Bonus - Exécution de Commandes Unix en (multiple) Pipeline**

Ce projet **Pipex Bonus** est une extension du projet **Pipex** de l'école 42. Il permet de reproduire le comportement de la commande shell suivante en manipulant les pipes et la redirection des fichiers en C :

```sh
< file1 cmd1 | cmd2 | ... | cmdn > file2
```

Il gère également le mode **here_doc**, qui permet d'utiliser un "limiteur" comme entrée standard au lieu d'un fichier.

---

## 📌 **1. Fonctionnement global du programme (`main_bonus.c`)**
Le programme suit ces étapes :

1. **Vérification des arguments et initialisation**
   - Il vérifie que le nombre d'arguments passés est correct.
   - Si `argv[1]` est `"here_doc"`, il active le mode here_doc.
   
2. **Ouverture des fichiers**
   - `filein` (fichier d'entrée) est ouvert en mode lecture (sauf pour `here_doc`).
   - `fileout` (fichier de sortie) est ouvert en mode écriture ou ajout.
   
3. **Création des processus enfants**
   - Chaque commande intermédiaire est exécutée dans un processus enfant.
   - Chaque processus redirige sa sortie standard vers un pipe pour transmettre les données à la commande suivante.
   
4. **Gestion du mode here_doc** (`here_doc()`)
   - Lit l'entrée standard jusqu'à ce que l'utilisateur entre la chaîne `LIMITER`.
   - Envoie les lignes reçues à la commande suivante via un pipe.
   
5. **Exécution de la dernière commande et fermeture des fichiers**
   - La dernière commande est exécutée avec `execve()` et sa sortie est redirigée vers `fileout`.
   
6. **Gestion des erreurs et libération de la mémoire**
   - Toute erreur d'exécution (mauvaise commande, fichier introuvable) affiche un message approprié.

---

## 📌 **2. Fonctions principales et fichiers**
### **`main_bonus.c`**
- Initialise le programme et gère l'exécution des commandes en créant des processus enfants.

### **`utils_bonus.c`**
- `find_path()` : Recherche le chemin d'exécution d'une commande dans `$PATH`.
- `execute()` : Exécute une commande avec `execve()`.
- `open_file()` : Ouvre un fichier avec les bons flags.
- `get_next_line()` : Lit l'entrée utilisateur ligne par ligne.

### **`error_bonus.c`**
- `usage()` : Affiche un message d'erreur si les arguments sont incorrects.
- `error()` : Affiche un message d'erreur général et quitte le programme.

---

## 📌 **3. Compilation et exécution**
### **Compilation**
Le projet doit être compilé avec un `Makefile`.

```sh
make bonus
```

### **Exécution**
#### **Mode standard**
```sh
./pipex file1 "cmd1" "cmd2" "..." "cmdn" file2
```
Exemple :
```sh
./pipex input.txt "grep error" "sort" "uniq" output.txt
```

#### **Mode here_doc**
```sh
./pipex here_doc LIMITER "cmd1" "cmd2" "..." file
```
Exemple :
```sh
./pipex here_doc EOF "cat" "wc -l" output.txt
```
L'entrée sera lue jusqu'à ce que l'utilisateur entre `EOF`.

---

## 📌 **4. Gestion des erreurs**
Le programme gère les erreurs courantes :
- **Fichiers introuvables** : Affiche un message d'erreur.
- **Mauvaises commandes** : Indique que la commande est introuvable.
- **Mauvais arguments** : Indique la bonne syntaxe d'utilisation.

---

## 📌 **5. Améliorations possibles**
- Gérer les permissions des fichiers de sortie.
- Ajouter la gestion des options comme `-v` pour le mode verbeux.
- Optimiser la gestion des processus pour une meilleure efficacité.

---

## 📌 **6. Auteur**
- **mstasiak** (*mstasiak@student.42.fr*)

---

English

---

# **Pipex Bonus - Executing Unix Commands in (Multiple) Pipeline**

This **Pipex Bonus** project is an extension of the **Pipex** project at 42 school. It mimics the behavior of the following shell command by manipulating pipes and file redirection in C:

```sh
< file1 cmd1 | cmd2 | ... | cmdn > file2
```

It also handles the **here_doc** mode, which allows using a "limiter" as standard input instead of a file.

---

## 📌 **1. Overall Functionality of the Program (`main_bonus.c`)**
The program follows these steps:

1. **Argument Verification and Initialization**
   - It checks that the correct number of arguments are passed.
   - If `argv[1]` is `"here_doc"`, it activates the here_doc mode.

2. **File Opening**
   - `filein` (input file) is opened in read mode (except for `here_doc`).
   - `fileout` (output file) is opened in write or append mode.

3. **Child Process Creation**
   - Each intermediate command is executed in a child process.
   - Each process redirects its standard output to a pipe to pass data to the next command.

4. **Here_doc Mode Handling** (`here_doc()`)
   - Reads standard input until the user enters the `LIMITER` string.
   - Sends the received lines to the next command via a pipe.

5. **Executing the Last Command and Closing Files**
   - The last command is executed with `execve()` and its output is redirected to `fileout`.

6. **Error Handling and Memory Cleanup**
   - Any execution error (wrong command, file not found) displays an appropriate message.

---

## 📌 **2. Main Functions and Files**
### **`main_bonus.c`**
- Initializes the program and manages the execution of commands by creating child processes.

### **`utils_bonus.c`**
- `find_path()` : Searches for the execution path of a command in `$PATH`.
- `execute()` : Executes a command with `execve()`.
- `open_file()` : Opens a file with the correct flags.
- `get_next_line()` : Reads user input line by line.

### **`error_bonus.c`**
- `usage()` : Displays an error message if the arguments are incorrect.
- `error()` : Displays a general error message and exits the program.

---

## 📌 **3. Compilation and Execution**
### **Compilation**
The project must be compiled with a `Makefile`.

```sh
make bonus
```

### **Execution**
#### **Standard Mode**
```sh
./pipex file1 "cmd1" "cmd2" "..." "cmdn" file2
```
Example:
```sh
./pipex input.txt "grep error" "sort" "uniq" output.txt
```

#### **Here_doc Mode**
```sh
./pipex here_doc LIMITER "cmd1" "cmd2" "..." file
```
Example:
```sh
./pipex here_doc EOF "cat" "wc -l" output.txt
```
The input will be read until the user enters `EOF`.

---

## 📌 **4. Error Handling**
The program handles common errors:
- **File Not Found**: Displays an error message.
- **Wrong Commands**: Indicates that the command is not found.
- **Incorrect Arguments**: Shows the correct usage syntax.

---

## 📌 **5. Possible Improvements**
- Manage output file permissions.
- Add option handling like `-v` for verbose mode.
- Optimize process management for better efficiency.

---

## 📌 **6. Author**
- **mstasiak** (*mstasiak@student.42.fr*)
