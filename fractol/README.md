# fractol - README

---

## Description
**Fract'ol** est un projet graphique de l'école 42 visant à créer un programme en C pour générer et afficher des fractales, notamment les ensembles de Mandelbrot et de Julia, en utilisant la bibliothèque graphique **MiniLibX**. Le projet permet d'explorer les notions de nombres complexes, d'optimisation graphique, et de gestion des événements clavier et souris. L'objectif est de produire des visualisations fluides et interactives des fractales, avec un zoom quasi-infini, des variations de l'ensemble de Julia via des paramètres, et un jeu de couleurs pour accentuer la profondeur des fractales.

Les objectifs principaux incluent :
- Maîtrise de la bibliothèque **MiniLibX** pour ouvrir une fenêtre, afficher des images, et gérer les événements.
- Compréhension des fractales et des calculs impliquant les nombres complexes.
- Optimisation des performances pour un rendu graphique fluide.
- Gestion des interactions utilisateur (zoom, déplacement, changement de paramètres).

## Structure du projet
- **Dossier principal** : `fractol/`
- **Fichiers obligatoires** :
  - `Makefile`
  - Fichiers sources en C (ex. `main.c`, fichiers pour la gestion des fractales et de MiniLibX).
  - Fichiers d'en-tête (ex. `fractol.h`).
- **Sortie** : Un exécutable nommé `fractol`.

## Prérequis
- Un système Unix-like (Linux, macOS).
- Un compilateur C compatible (ex. `gcc` ou `clang`).
- La bibliothèque **MiniLibX** fournie par l'école 42.
- Les bibliothèques standard C (`math.h` pour les calculs, etc.).
- Aucune bibliothèque externe autre que MiniLibX n'est autorisée.

## Compilation
Accédez au dossier du projet et exécutez :
```bash
make
```
Cela génère l'exécutable `fractol`. Le `Makefile` doit inclure les règles `$(NAME)`, `all`, `clean`, `fclean`, et `re`, et compiler avec les flags `-Wall -Wextra -Werror`. Si une bibliothèque comme `libft` est utilisée, elle doit être incluse dans un dossier `libft/` à la racine et compilée via le `Makefile`.

## Utilisation
Lancer le programme avec un paramètre spécifiant le type de fractale :
```bash
./fractol mandelbrot
./fractol julia <param1> <param2>
```
- `mandelbrot` : Affiche l'ensemble de Mandelbrot.
- `julia <param1> <param2>` : Affiche un ensemble de Julia avec des paramètres complexes (ex. `-0.4 0.6`).
- Sans paramètre ou avec un paramètre invalide, le programme affiche la liste des paramètres disponibles et quitte.

Exemple de sortie (liste des paramètres si invalide) :
```
Available fractals:
  - mandelbrot
  - julia <real> <imag>
Example: ./fractol julia -0.4 0.6
```

### Interactions
- **Zoom** : Utiliser la molette de la souris pour zoomer/dézoomer (centré sur la position de la souris pour les bonus).
- **Fermeture** : Appuyer sur **ESC** ou cliquer sur la croix de la fenêtre pour quitter proprement.
- **Bonus (si implémentés)** :
  - Déplacement de la vue avec les touches fléchées.
  - Changement dynamique des couleurs (color shift).
  - Affichage d'une fractale supplémentaire (ex. Burning Ship).

## Fonctionnement détaillé
### Partie obligatoire
- **Fractales supportées** :
  - **Mandelbrot** : Générée en itérant la formule \( z_{n+1} = z_n^2 + c \), où \( c \) est le point du plan complexe correspondant au pixel.
  - **Julia** : Générée avec la même formule, mais \( c \) est une constante complexe définie par les paramètres fournis en ligne de commande.
- **Rendu graphique** :
  - Utilise **MiniLibX** pour ouvrir une fenêtre et afficher une image.
  - Chaque pixel est calculé en fonction de son appartenance à l'ensemble fractal (nombre d'itérations avant divergence).
  - Un jeu de couleurs est appliqué pour refléter la profondeur (nombre d'itérations).
- **Gestion des événements** :
  - Zoom avec la molette de la souris (quasi-infini dans les limites de la précision machine).
  - Fermeture propre avec **ESC** ou la croix de la fenêtre.
- **Paramètres** :
  - Au moins un paramètre en ligne de commande pour choisir la fractale.
  - Pour Julia, deux paramètres optionnels (parties réelle et imaginaire de \( c \)) permettent de générer différents ensembles.
- **Erreurs** :
  - Si aucun paramètre n'est fourni ou si les paramètres sont invalides, affiche la liste des options et quitte.

### Partie bonus
- Implémentation d'une fractale supplémentaire (ex. **Burning Ship**).
- Zoom suivant la position de la souris.
- Déplacement de la vue avec les touches fléchées.
- Changement dynamique des couleurs (color shift) pour des effets visuels.

## Gestion des erreurs
- **Paramètres invalides** : Affiche la liste des fractales disponibles et quitte.
- **Erreurs graphiques** : Pas de segmentation fault, bus error, ou double free. Le programme doit être robuste.
- **Mémoire** : Toute mémoire allouée sur le tas (heap) doit être libérée pour éviter les fuites.

## Codes de sortie
- `0` : Succès (fermeture propre).
- Non spécifié pour les erreurs, mais le programme doit quitter proprement après avoir affiché un message d'erreur si nécessaire.

## Limitations
- Écrit en **C** uniquement, conforme à **la Norme** de l'école 42.
- Utilisation exclusive de **MiniLibX** pour la gestion graphique.
- Pas de fonctions interdites spécifiées, mais pas de bibliothèques externes autres que MiniLibX.
- Le programme doit être robuste (pas de crashes inattendus).
- Le `Makefile` ne doit pas relinker inutilement.

## Règles spécifiques
- Le programme doit être nommé `fractol`.
- Les fractales Mandelbrot et Julia sont obligatoires.
- La gestion de la fenêtre doit être fluide (changement de fenêtre, réduction, etc.).
- Les images MiniLibX doivent être utilisées pour le rendu.
- Un `Makefile` est requis avec les règles standard.
- Les bonus, s'ils sont implémentés, doivent être compilés via une règle `bonus` dans le `Makefile`.

## Bonus
- Une fractale supplémentaire (ex. Burning Ship).
- Zoom centré sur la position de la souris.
- Déplacement de la vue avec les touches fléchées.
- Effets de changement de couleurs dynamiques.

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** :

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis de découvrir la programmation graphique avec MiniLibX, les fractales, et la gestion des événements utilisateur.

---

# fractol - README

## Description
**Fract'ol** is a graphical project from 42 school aimed at creating a C program to generate and display fractals, specifically the Mandelbrot and Julia sets, using the **MiniLibX** graphical library. The project explores complex numbers, graphical optimization, and handling keyboard/mouse events. The goal is to produce smooth, interactive fractal visualizations with near-infinite zoom, varying Julia sets via parameters, and color schemes to highlight fractal depth.

Key objectives include:
- Mastering **MiniLibX** for window creation, image rendering, and event handling.
- Understanding fractals and complex number computations.
- Optimizing performance for smooth graphical rendering.
- Managing user interactions (zoom, movement, parameter changes).

## Project Structure
- **Main directory**: `fractol/`
- **Mandatory files**:
  - `Makefile`
  - C source files (e.g., `main.c`, files for fractal calculations and MiniLibX handling).
  - Header files (e.g., `fractol.h`).
- **Output**: An executable named `fractol`.

## Prerequisites
- A Unix-like system (Linux, macOS).
- A compatible C compiler (e.g., `gcc` or `clang`).
- The **MiniLibX** library provided by 42 school.
- Standard C libraries (`math.h` for calculations, etc.).
- No external libraries other than MiniLibX are allowed.

## Compilation
Navigate to the project directory and run:
```bash
make
```
This generates the `fractol` executable. The `Makefile` must include the rules `$(NAME)`, `all`, `clean`, `fclean`, and `re`, and compile with the flags `-Wall -Wextra -Werror`. If a library like `libft` is used, it must be included in a `libft/` directory at the root and compiled via the `Makefile`.

## Usage
Run the program with a parameter specifying the fractal type:
```bash
./fractol mandelbrot
./fractol julia <param1> <param2>
```
- `mandelbrot`: Displays the Mandelbrot set.
- `julia <param1> <param2>`: Displays a Julia set with complex parameters (e.g., `-0.4 0.6`).
- If no parameter or an invalid parameter is provided, the program displays available parameters and exits.

Example output (for invalid parameters):
```
Available fractals:
  - mandelbrot
  - julia <real> <imag>
Example: ./fractol julia -0.4 0.6
```

### Interactions
- **Zoom**: Use the mouse scroll wheel to zoom in/out (centered on the mouse position for bonuses).
- **Closing**: Press **ESC** or click the window’s close button to exit cleanly.
- **Bonuses (if implemented)**:
  - View movement with arrow keys.
  - Dynamic color changes (color shift).
  - Additional fractal (e.g., Burning Ship).

## Detailed Functionality
### Mandatory Part
- **Supported Fractals**:
  - **Mandelbrot**: Generated by iterating \( z_{n+1} = z_n^2 + c \), where \( c \) is the complex plane point corresponding to the pixel.
  - **Julia**: Uses the same formula, but \( c \) is a constant complex number set by command-line parameters.
- **Graphical Rendering**:
  - Uses **MiniLibX** to open a window and display an image.
  - Each pixel is computed based on its membership in the fractal set (number of iterations before divergence).
  - A color scheme reflects the depth (iteration count).
- **Event Handling**:
  - Zoom with the mouse scroll wheel (near-infinite within machine precision limits).
  - Clean exit with **ESC** or the window’s close button.
- **Parameters**:
  - At least one command-line parameter to select the fractal.
  - For Julia, two optional parameters (real and imaginary parts of \( c \)) generate different sets.
- **Errors**:
  - Invalid or missing parameters trigger a display of available options and a clean exit.

### Bonus Part
- Additional fractal (e.g., **Burning Ship**).
- Zoom centered on the mouse position.
- View movement with arrow keys.
- Dynamic color changes (color shift) for visual effects.

## Error Handling
- **Invalid Parameters**: Displays available fractals and exits.
- **Graphical Errors**: No segmentation faults, bus errors, or double frees. The program must be robust.
- **Memory**: All heap-allocated memory must be freed to prevent leaks.

## Exit Codes
- `0`: Success (clean exit).
- No specific error codes defined, but the program must exit cleanly after displaying an error message if needed.

## Limitations
- Written in **C** only, adhering to 42’s **Norme**.
- Uses **MiniLibX** exclusively for graphical operations.
- No forbidden functions specified, but no external libraries other than MiniLibX are allowed.
- The program must be robust (no unexpected crashes).
- The `Makefile` must not relink unnecessarily.

## Specific Rules
- The program must be named `fractol`.
- Mandelbrot and Julia fractals are mandatory.
- Window management must be smooth (switching, minimizing, etc.).
- MiniLibX images are required for rendering.
- A `Makefile` is required with standard rules.
- Bonuses, if implemented, must be compiled via a `bonus` rule in the `Makefile`.

## Bonuses
- An additional fractal (e.g., Burning Ship).
- Mouse-position-centered zoom.
- View movement with arrow keys.
- Dynamic color shift effects.

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**:

## Acknowledgments
Thanks to 42 school for this project, which allowed me to explore graphical programming with MiniLibX, fractals, and user event handling.
