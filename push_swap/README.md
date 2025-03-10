Français

---

# **Algorithme de Tri Push_swap**

Ce code est conçu pour trier une pile de nombres en utilisant l'algorithme **Radix Sort** pour les grandes listes et des méthodes plus simples pour les petites listes, dans le cadre du projet **push_swap** de l'école 42.

---

## 📌 **1. Fonctionnement global du programme (`main.c`)**
Le programme suit ces étapes :
1. **Vérification et initialisation des arguments**
   - Si un seul argument est donné (ex. `"3 2 5 1"`), il est splitté en plusieurs valeurs avec `ft_split()`.
   - Chaque nombre est converti en entier et ajouté à une liste chaînée (`t_stack`).
   - On indexe les valeurs pour préparer le tri (`index_stack()`).
 
2. **Vérification si la liste est déjà triée**
   - Si elle est triée, le programme s'arrête immédiatement (`is_sorted(stack_a)`).

3. **Choix du tri en fonction de la taille de la pile**
   - Si elle contient **5 éléments ou moins**, il applique un tri spécifique (`simple_sort()`).
   - Sinon, il applique **Radix Sort** (`radix_sort()`).

4. **Libération de la mémoire**
   - À la fin, toutes les piles sont libérées (`free_stack()`).

---

## 📌 **2. Implémentation des listes chaînées (`t_stack.c`)**
Le code utilise une **liste chaînée simple** pour stocker les nombres :

- **`ft_lstnew(int value)`** : Crée un nouvel élément de liste.
- **`ft_lstlast(t_stack *head)`** : Retourne le dernier élément de la liste.
- **`ft_lstadd_back(t_stack **stack, t_stack *new_stack)`** : Ajoute un élément à la fin de la liste.
- **`ft_lstsize(t_stack *head)`** : Compte le nombre d'éléments dans la liste.

Ces fonctions permettent de gérer dynamiquement la liste de nombres.

---

## 📌 **3. Implémentation du tri Radix (`radix.c`)**
L'algorithme **Radix Sort** est un tri basé sur les bits des nombres.

### 🔹 **Étapes du tri Radix**
1. **Déterminer le nombre de bits nécessaires (`get_max_bits()`)**
   - Cherche l'index le plus grand et compte combien de bits sont nécessaires pour le représenter.

2. **Trier les éléments bit par bit (`radix_sort()`)**
   - On parcourt chaque bit de **droite à gauche** (du LSB au MSB).
   - Pour chaque bit :
     - Si le bit est **1**, on effectue une **rotation (`ra()`)**.
     - Sinon, on envoie l'élément dans la pile B (`pb()`).
   - Une fois tous les éléments triés pour un bit donné, on remet tout dans `stack_a` (`pa()`).
   - On répète l'opération pour chaque bit.

### 🔹 **Explication du décalage binaire (`>>`)**
```c
if (((head_a->index >> i) & 1) == 1)
```
- `head_a->index >> i` : Décale l'index `i` bits vers la droite.
- `& 1` : Vérifie si le bit le plus à droite est `1`.
- Si c'est `1`, on fait `ra()` (rotation).
- Sinon, on fait `pb()` (push vers `stack_b`).

Ce processus trie progressivement les nombres en fonction de leurs bits.

---

## 📌 **4. Implémentation du tri simple (`simple.c`)**
Ce module gère les **petites listes** avec un tri spécifique :

- **`sort_3()`** : Trie une pile de 3 nombres avec `sa()` (swap) et `ra()` (rotate).
- **`sort_4()`** : Trouve le plus petit élément, le pousse sur `stack_b`, trie le reste, puis le remet dans `stack_a`.
- **`sort_5()`** : Même logique que `sort_4()`, mais en trouvant les deux plus petits éléments.
- **`simple_sort()`** : Choisit la bonne fonction en fonction de la taille de la liste.

---

English

---

# **Push_swap Sorting Algorithm**

This code is designed to sort a stack of numbers using the **Radix Sort** algorithm for large lists and simpler methods for smaller lists, as part of the **push_swap** project at 42 school.

---

## 📌 **1. Global Program Workflow (`main.c`)**
The program follows these steps:

1. **Argument verification and initialization**
   - If a single argument is provided (e.g., `"3 2 5 1"`), it is split into multiple values using `ft_split()`.
   - Each number is converted to an integer and added to a linked list (`t_stack`).
   - Values are indexed to prepare for sorting (`index_stack()`).

2. **Checking if the list is already sorted**
   - If it is sorted, the program stops immediately (`is_sorted(stack_a)`).

3. **Choosing the sorting method based on stack size**
   - If the stack contains **5 or fewer elements**, a specific sorting method is applied (`simple_sort()`).
   - Otherwise, **Radix Sort** is used (`radix_sort()`).

4. **Memory cleanup**
   - At the end, all stacks are freed (`free_stack()`).

---

## 📌 **2. Linked List Implementation (`t_stack.c`)**
The code uses a **singly linked list** to store numbers:

- **`ft_lstnew(int value)`** : Creates a new list element.
- **`ft_lstlast(t_stack *head)`** : Returns the last element of the list.
- **`ft_lstadd_back(t_stack **stack, t_stack *new_stack)`** : Adds an element to the end of the list.
- **`ft_lstsize(t_stack *head)`** : Counts the number of elements in the list.

These functions dynamically manage the number list.

---

## 📌 **3. Radix Sort Implementation (`radix.c`)**
The **Radix Sort** algorithm sorts numbers based on their binary representation.

### 🔹 **Radix Sort Steps**

1. **Determine the number of bits needed (`get_max_bits()`)**
   - Finds the largest index and counts how many bits are needed to represent it.

2. **Sorting elements bit by bit (`radix_sort()`)**
   - Iterates through each bit **from right to left** (from LSB to MSB).
   - For each bit:
     - If the bit is **1**, a **rotation (`ra()`)** is performed.
     - Otherwise, the element is pushed to stack B (`pb()`).
   - Once all elements are sorted for a given bit, they are moved back to `stack_a` (`pa()`).
   - This process repeats for each bit.

### 🔹 **Binary Shift Explanation (`>>`)**
```c
if (((head_a->index >> i) & 1) == 1)
```
- `head_a->index >> i` : Shifts the index `i` bits to the right.
- `& 1` : Checks if the rightmost bit is `1`.
- If it's `1`, `ra()` (rotation) is executed.
- Otherwise, `pb()` (push to `stack_b`) is executed.

This process gradually sorts the numbers based on their bits.

---

## 📌 **4. Simple Sort Implementation (`simple.c`)**
This module handles **small lists** using specific sorting methods:

- **`sort_3()`** : Sorts a stack of 3 numbers using `sa()` (swap) and `ra()` (rotate).
- **`sort_4()`** : Finds the smallest element, pushes it to `stack_b`, sorts the remaining elements, then moves it back to `stack_a`.
- **`sort_5()`** : Uses the same logic as `sort_4()`, but finds the two smallest elements.
- **`simple_sort()`** : Selects the appropriate function based on the list size.