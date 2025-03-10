Français

---

# **Pipex - Exécution de Commandes Unix en Pipeline**

Ce projet réimplémente le fonctionnement de la redirection de pipe (`|`) en Shell, permettant d'exécuter deux commandes en chaîne avec un fichier d'entrée et un fichier de sortie.

---

## 📌 **1. Fonctionnement global du programme (`main.c`)**
Le programme suit ces étapes :

1. **Vérification des arguments**
   - Le programme attend exactement **quatre arguments** sous la forme :
     ```sh
     ./pipex <file1> <cmd1> <cmd2> <file2>
     ```
   - Si le nombre d'arguments est incorrect, une erreur est affichée.

2. **Création du pipe et fork des processus**
   - Un `pipe()` est créé pour permettre la communication entre les deux processus.
   - Un `fork()` est effectué pour exécuter la première commande (`cmd1`).
   - Le processus parent attend la fin du premier avant d'exécuter la seconde commande (`cmd2`).

3. **Redirection des entrées/sorties**
   - Le processus enfant redirige l'entrée du fichier `file1` et la sortie vers le pipe.
   - Le processus parent prend l'entrée du pipe et redirige la sortie vers `file2`.

4. **Exécution des commandes avec `execve()`**
   - Chaque commande est cherchée dans le `PATH` avant d'être exécutée.

---

## 📌 **2. Gestion des processus (`main.c`)**
Deux fonctions principales gèrent les processus :

### 🔹 **Processus Enfant (`child_process()`)**
- Ouvre `file1` en lecture.
- Redirige `file1` vers l'entrée standard (`stdin`).
- Redirige la sortie standard (`stdout`) vers le pipe.
- Ferme les descripteurs inutiles et exécute `cmd1` avec `execve()`.

### 🔹 **Processus Parent (`parent_process()`)**
- Ouvre `file2` en écriture (création si inexistant).
- Redirige l'entrée standard (`stdin`) vers le pipe.
- Redirige la sortie standard (`stdout`) vers `file2`.
- Exécute `cmd2` avec `execve()`.

---

## 📌 **3. Recherche et Exécution des Commandes (`utils.c`)**

### 🔹 **Recherche du Chemin de la Commande (`find_path()`)**
- Parcourt la variable d'environnement `PATH` pour trouver l'exécutable.
- Teste chaque chemin possible avec `access()`.
- Retourne le chemin correct ou affiche une erreur si introuvable.

### 🔹 **Exécution de la Commande (`execute()`)**
- Sépare la commande et ses arguments avec `ft_split()`.
- Récupère le chemin correct avec `find_path()`.
- Utilise `execve()` pour exécuter la commande.
- En cas d'erreur, une fonction `error()` affiche un message et quitte le programme.

---

## 📌 **4. Gestion des Erreurs (`utils.c`)**

Le programme gère plusieurs types d'erreurs :
- **Fichier introuvable ou permissions insuffisantes** : affiché via `perror()`.
- **Commande invalide** : si `execve()` échoue.
- **Erreur de processus (fork, pipe, dup2)** : fermeture propre et message d'erreur.

Exemple de message d'erreur :
```sh
Error: No such file or directory
```

---

## 📌 **5. Compilation et Utilisation**

### 🔹 **Compilation**
```sh
make
```
Cela génère un exécutable `pipex`.

### 🔹 **Exécution**
```sh
./pipex infile "cmd1 args" "cmd2 args" outfile
```
Exemple d'utilisation :
```sh
./pipex input.txt "grep hello" "wc -l" output.txt
```
Equivalent à :
```sh
grep hello < input.txt | wc -l > output.txt
```

---

## 📌 **6. Améliorations Possibles**
- Support des commandes avec chemins absolus et relatifs.
- Gestion de plusieurs pipes en chaîne (`<file1> cmd1 | cmd2 | cmd3 > file2`).
- Implémentation du mode `heredoc` pour simuler une entrée utilisateur interactive.

---

## 📌 **7. Ressources**
- `man 2 pipe`
- `man 2 fork`
- `man 2 execve`
- `man 2 open`
- `man 2 dup2`
- `man 3 perror`

---

🚀 **Projet Pipex - 42 School** | Par **mstasiak**

---

English

---

# **Pipex - Unix Command Execution in Pipeline**

This project reimplements the functionality of the pipe (`|`) redirection in Shell, allowing two commands to be executed in sequence with an input file and an output file.

---

## 📌 **1. Overall Program Workflow (`main.c`)**
The program follows these steps:

1. **Argument Verification**
   - The program expects exactly **four arguments** in the following format:
     ```sh
     ./pipex <file1> <cmd1> <cmd2> <file2>
     ```
   - If the number of arguments is incorrect, an error is displayed.

2. **Pipe Creation and Process Forking**
   - A `pipe()` is created to allow communication between the two processes.
   - A `fork()` is performed to execute the first command (`cmd1`).
   - The parent process waits for the first process to finish before executing the second command (`cmd2`).

3. **Input/Output Redirection**
   - The child process redirects the input from `file1` and the output to the pipe.
   - The parent process takes the input from the pipe and redirects the output to `file2`.

4. **Command Execution with `execve()`**
   - Each command is searched in the `PATH` before being executed.

---

## 📌 **2. Process Management (`main.c`)**
Two main functions manage the processes:

### 🔹 **Child Process (`child_process()`)**
- Opens `file1` for reading.
- Redirects `file1` to the standard input (`stdin`).
- Redirects the standard output (`stdout`) to the pipe.
- Closes unnecessary file descriptors and executes `cmd1` with `execve()`.

### 🔹 **Parent Process (`parent_process()`)**
- Opens `file2` for writing (creates it if it doesn't exist).
- Redirects the standard input (`stdin`) to the pipe.
- Redirects the standard output (`stdout`) to `file2`.
- Executes `cmd2` with `execve()`.

---

## 📌 **3. Command Search and Execution (`utils.c`)**

### 🔹 **Finding the Command Path (`find_path()`)**
- Scans the `PATH` environment variable to find the executable.
- Tests each possible path with `access()`.
- Returns the correct path or displays an error if not found.

### 🔹 **Command Execution (`execute()`)**
- Splits the command and its arguments with `ft_split()`.
- Retrieves the correct path using `find_path()`.
- Uses `execve()` to execute the command.
- In case of an error, an `error()` function displays a message and exits the program.

---

## 📌 **4. Error Handling (`utils.c`)**

The program handles several types of errors:
- **File not found or insufficient permissions**: displayed via `perror()`.
- **Invalid command**: if `execve()` fails.
- **Process errors (fork, pipe, dup2)**: clean closure and error message.

Example error message:
```sh
Error: No such file or directory
```

---

## 📌 **5. Compilation and Usage**

### 🔹 **Compilation**
```sh
make
```
This generates an executable `pipex`.

### 🔹 **Execution**
```sh
./pipex infile "cmd1 args" "cmd2 args" outfile
```
Example usage:
```sh
./pipex input.txt "grep hello" "wc -l" output.txt
```
Equivalent to:
```sh
grep hello < input.txt | wc -l > output.txt
```

---

## 📌 **6. Possible Improvements**
- Support for commands with absolute and relative paths.
- Handling multiple pipes in sequence (`<file1> cmd1 | cmd2 | cmd3 > file2`).
- Implementing `heredoc` mode to simulate interactive user input.

---

## 📌 **7. Resources**
- `man 2 pipe`
- `man 2 fork`
- `man 2 execve`
- `man 2 open`
- `man 2 dup2`
- `man 3 perror`

---

🚀 **Pipex Project - 42 School** | By **mstasiak**
