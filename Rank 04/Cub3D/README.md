# Cub3D - README

---

## Description
Cub3D est un projet réalisé dans le cadre du cursus de l'école 42, inspiré du jeu emblématique *Wolfenstein 3D*, considéré comme le premier FPS (First Person Shooter). Ce projet vise à initier les étudiants à la technique du **ray-casting** pour créer une représentation graphique 3D d'un labyrinthe avec une vue subjective. Le programme `cub3D` utilise la bibliothèque **MiniLibX** pour afficher une vue dynamique dans laquelle le joueur peut se déplacer et interagir avec l'environnement. Ce projet combine des compétences en programmation C, design graphique, et mathématiques appliquées.

L'objectif est de maîtriser les concepts suivants :
- Programmation en C avec gestion des fenêtres et événements via MiniLibX.
- Implémentation du ray-casting pour simuler un environnement 3D.
- Parsing et validation d'un fichier de configuration (carte et textures).
- Gestion des textures, couleurs, et interactions clavier.
- Implémentation de fonctionnalités bonus comme les collisions, minimap, portes, animations, et contrôle à la souris.

## Structure du projet
Le projet est organisé comme suit :
- **Dossier principal** : Contient les fichiers sources (*.c, *.h) et le Makefile pour le programme `cub3D`.
- **Dossier bonus (optionnel)** : Contient les fichiers pour les fonctionnalités bonus (minimap, collisions, etc.).
- **Dossier libft** : Contient la bibliothèque libft pour les fonctions utilitaires (ex. : `ft_printf`).
- **Dossier MiniLibX** : Contient les sources de la bibliothèque MiniLibX (si utilisée depuis les sources).

Les fichiers clés incluent :
- **Sources C** : Fichiers pour le ray-casting, le parsing de la carte, la gestion des événements, et le rendu graphique.
- **Makefile** : Pour compiler les programmes avec les flags `-Wall`, `-Wextra`, `-Werror`.
- **Libft** : Bibliothèque personnalisée pour les fonctions utilitaires.
- **Fichiers .cub** : Fichiers de configuration décrivant la carte et les textures.

## Prérequis
- Un environnement Linux/Unix pour compiler et exécuter le programme.
- Connaissances de base en programmation C (gestion de la mémoire, structures de données).
- Compilateur compatible avec C99 (gcc, clang).
- Bibliothèque **MiniLibX** installée (version système ou compilée depuis les sources).
- Connaissance des concepts de ray-casting et de rendu graphique.
- Connaissance des mathématiques de base (trigonométrie) pour le ray-casting.

## Installation
1. **Cloner le dépôt Git** :
   ```bash
   git clone <votre-dépôt-git>
   cd cub3d
   ```
2. **Compiler la partie obligatoire** :
   ```bash
   make
   ```
   Produit l'exécutable `cub3D`.
3. **Compiler la partie bonus (si implémentée)** :
   ```bash
   make bonus
   ```
   Produit l'exécutable `cub3D` avec les fonctionnalités bonus.
4. **Nettoyer les fichiers objets** :
   ```bash
   make clean
   ```
5. **Recompiler tout** :
   ```bash
   make re
   ```

## Utilisation
### Commandes principales
1. **Lancer le programme cub3D** :
   ```bash
   ./cub3D <fichier.cub>
   ```
   Exemple :
   ```bash
   ./cub3D maps/map.cub
   ```
   - `<fichier.cub>` : Fichier de configuration décrivant la carte, les textures, et les couleurs.
   - Ouvre une fenêtre affichant une vue 3D du labyrinthe avec navigation clavier.

### Contrôles
- **Flèches gauche/droite** : Rotation de la caméra (regarder à gauche/droite).
- **W, A, S, D** : Déplacement du joueur (avant, gauche, arrière, droite).
- **ESC** : Ferme la fenêtre et quitte le programme.
- **Croix rouge** : Ferme la fenêtre et quitte le programme.
- **Souris (bonus, si implémenté)** : Rotation de la caméra.

### Exemple de fichier .cub
```plaintext
NO ./textures/north_wall.xpm
SO ./textures/south_wall.xpm
WE ./textures/west_wall.xpm
EA ./textures/east_wall.xpm
F 220,100,0
C 225,30,0

111111
100N01
101001
111111
```
- **NO, SO, WE, EA** : Chemins vers les textures pour les murs nord, sud, ouest, est.
- **F, C** : Couleurs RGB pour le sol et le plafond (valeurs entre 0 et 255).
- **Carte** : Grille composée de `0` (espace vide), `1` (mur), et `N`, `S`, `E`, `W` (position/orientation du joueur).

## Fonctionnement détaillé
### Partie obligatoire
- **Ray-casting** :
  - Utilise l’algorithme de ray-casting pour projeter une vue 3D à partir d’une carte 2D.
  - Pour chaque colonne de l’écran, un rayon est tracé depuis la position du joueur jusqu’à ce qu’il rencontre un mur.
  - La distance au mur détermine la hauteur de la bande verticale à dessiner, avec application des textures correspondantes (nord, sud, est, ouest).
- **Parsing du fichier .cub** :
  - Lit et valide les éléments : textures (NO, SO, WE, EA), couleurs (F, C), et la carte.
  - Vérifie que la carte est entourée de murs et contient une position de départ valide (N, S, E, W).
  - Gère les erreurs (fichier invalide, textures manquantes, carte ouverte) avec un message d’erreur.
- **Gestion des événements** :
  - Gère les touches W, A, S, D pour le déplacement et les flèches pour la rotation.
  - Ferme proprement la fenêtre avec ESC ou la croix rouge.
- **Rendu graphique** :
  - Affiche les murs avec des textures différentes selon leur orientation.
  - Dessine le sol et le plafond avec des couleurs distinctes.
  - Utilise MiniLibX pour la gestion des fenêtres, images, et événements.

### Partie bonus
- **Collisions contre les murs** : Empêche le joueur de traverser les murs.
- **Minimap** : Affiche une vue 2D de la carte avec la position du joueur.
- **Portes** : Permet d’ouvrir/fermer des portes (nouveau symbole dans la carte, ex. : `D`).
- **Animations** : Ajoute des sprites animés (ex. : objets ou ennemis en mouvement).
- **Rotation avec la souris** : Contrôle la caméra avec les mouvements de la souris.

### Makefile
Le Makefile inclut les règles suivantes :
- `all` : Compile le programme `cub3D`.
- `clean` : Supprime les fichiers objets.
- `fclean` : Supprime les fichiers objets et l’exécutable.
- `re` : Recompile tout.
- `bonus` : Compile le programme avec les fonctionnalités bonus.

## Gestion des erreurs
- Vérifiez que le programme gère correctement les erreurs : fichier .cub invalide, textures inaccessibles, carte non entourée de murs.
- Assurez-vous que le code respecte la Norme 42 (vérifié par `norminette`).
- Testez avec des cas limites : cartes vides, textures manquantes, résolutions élevées.
- Les fuites de mémoire doivent être éliminées (vérifié avec `valgrind` ou équivalent).
- Les descripteurs de fichiers et les ressources MiniLibX doivent être libérés correctement.

## Limitations
- Les variables globales sont interdites.
- Les erreurs non gérées (segmentation fault, double free, etc.) entraînent une note de 0.
- Le programme doit respecter la Norme 42, sinon la note est 0.
- Les fonctions autorisées incluent : `open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit`, les fonctions de la bibliothèque mathématique (`-lm`), et toutes les fonctions de MiniLibX.
- La carte doit être valide (entourée de murs, un seul joueur, caractères valides : `0`, `1`, `N`, `S`, `E`, `W`).

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** : Janvier 2025 - Janvier 2025

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis d'explorer le ray-casting, la programmation graphique avec MiniLibX, et l'application pratique des mathématiques dans un contexte de développement de jeux.

---

# Cub3D - README

## Description
Cub3D is a project developed as part of the 42 school curriculum, inspired by the iconic *Wolfenstein 3D*, considered the first First Person Shooter (FPS). This project introduces students to the **ray-casting** technique to create a 3D graphical representation of a maze with a first-person perspective. The `cub3D` program uses the **MiniLibX** library to display a dynamic view in which the player can navigate and interact with the environment. The project combines skills in C programming, graphical design, and applied mathematics.

The goal is to master the following concepts:
- Programming in C with window and event management using MiniLibX.
- Implementing ray-casting to simulate a 3D environment.
- Parsing and validating a configuration file (map and textures).
- Managing textures, colors, and keyboard interactions.
- Implementing bonus features like collisions, minimap, doors, animations, and mouse control.

## Project Structure
The project is organized as follows:
- **Main Directory**: Contains source files (*.c, *.h) and the Makefile for the `cub3D` program.
- **Bonus Directory (optional)**: Contains files for bonus features (minimap, collisions, etc.).
- **Libft Directory**: Contains the libft library for utility functions (e.g., `ft_printf`).
- **MiniLibX Directory**: Contains the MiniLibX library sources (if used from sources).

Key files include:
- **C Source Files**: Files for ray-casting, map parsing, event handling, and graphical rendering.
- **Makefile**: To compile programs with `-Wall`, `-Wextra`, `-Werror` flags.
- **Libft**: Custom library for utility functions.
- **.cub Files**: Configuration files describing the map and textures.

## Prerequisites
- A Linux/Unix environment to compile and run the program.
- Basic knowledge of C programming (memory management, data structures).
- A C99-compatible compiler (gcc, clang).
- **MiniLibX** library installed (system version or compiled from sources).
- Understanding of ray-casting and graphical rendering concepts.
- Basic knowledge of mathematics (trigonometry) for ray-casting.

## Installation
1. **Clone the Git repository**:
   ```bash
   git clone <your-git-repository>
   cd cub3d
   ```
2. **Compile the mandatory part**:
   ```bash
   make
   ```
   Produces the `cub3D` executable.
3. **Compile the bonus part (if implemented)**:
   ```bash
   make bonus
   ```
   Produces the `cub3D` executable with bonus features.
4. **Clean object files**:
   ```bash
   make clean
   ```
5. **Recompile everything**:
   ```bash
   make re
   ```

## Usage
### Key Commands
1. **Run the cub3D program**:
   ```bash
   ./cub3D <file.cub>
   ```
   Example:
   ```bash
   ./cub3D maps/map.cub
   ```
   - `<file.cub>`: Configuration file describing the map, textures, and colors.
   - Opens a window displaying a 3D view of the maze with keyboard navigation.

### Controls
- **Left/Right Arrows**: Rotate the camera (look left/right).
- **W, A, S, D**: Move the player (forward, left, backward, right).
- **ESC**: Closes the window and exits the program.
- **Red Cross**: Closes the window and exits the program.
- **Mouse (bonus, if implemented)**: Rotates the camera.

### Example .cub File
```plaintext
NO ./textures/north_wall.xpm
SO ./textures/south_wall.xpm
WE ./textures/west_wall.xpm
EA ./textures/east_wall.xpm
F 220,100,0
C 225,30,0

111111
100N01
101001
111111
```
- **NO, SO, WE, EA**: Paths to textures for north, south, west, east walls.
- **F, C**: RGB colors for floor and ceiling (values between 0 and 255).
- **Map**: Grid composed of `0` (empty space), `1` (wall), and `N`, `S`, `E`, `W` (player position/orientation).

## Detailed Functionality
### Mandatory Part
- **Ray-casting**:
  - Uses the ray-casting algorithm to project a 3D view from a 2D map.
  - For each screen column, a ray is cast from the player’s position until it hits a wall.
  - The distance to the wall determines the height of the vertical strip to draw, with corresponding textures (north, south, east, west).
- **.cub File Parsing**:
  - Reads and validates elements: textures (NO, SO, WE, EA), colors (F, C), and the map.
  - Ensures the map is enclosed by walls and contains a valid starting position (N, S, E, W).
  - Handles errors (invalid file, missing textures, open map) with an error message.
- **Event Handling**:
  - Manages W, A, S, D keys for movement and arrow keys for rotation.
  - Properly closes the window with ESC or the red cross.
- **Graphical Rendering**:
  - Displays walls with different textures based on their orientation.
  - Draws the floor and ceiling with distinct colors.
  - Uses MiniLibX for window, image, and event management.

### Bonus Part
- **Wall Collisions**: Prevents the player from passing through walls.
- **Minimap**: Displays a 2D view of the map with the player’s position.
- **Doors**: Allows opening/closing doors (new map symbol, e.g., `D`).
- **Animations**: Adds animated sprites (e.g., moving objects or enemies).
- **Mouse Rotation**: Controls the camera with mouse movements.

### Makefile
The Makefile includes:
- `all`: Compiles the `cub3D` program.
- `clean`: Removes object files.
- `fclean`: Removes object files and the executable.
- `re`: Recompiles everything.
- `bonus`: Compiles the program with bonus features.

## Error Handling
- Ensure the program handles errors correctly: invalid .cub file, inaccessible textures, non-enclosed map.
- Verify code compliance with the 42 Norm (checked by `norminette`).
- Test with edge cases: empty maps, missing textures, high resolutions.
- Eliminate memory leaks (checked with `valgrind` or equivalent).
- Properly free file descriptors and MiniLibX resources.

## Limitations
- Global variables are forbidden.
- Unhandled errors (segmentation fault, double free, etc.) result in a grade of 0.
- The program must comply with the 42 Norm, or the grade is 0.
- Authorized functions include: `open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit`, math library functions (`-lm`), and all MiniLibX functions.
- The map must be valid (enclosed by walls, single player, valid characters: `0`, `1`, `N`, `S`, `E`, `W`).

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**: January 2025 - January 2025

## Acknowledgments
Thanks to 42 school for this project, which allowed me to explore ray-casting, graphical programming with MiniLibX, and the practical application of mathematics in game development.