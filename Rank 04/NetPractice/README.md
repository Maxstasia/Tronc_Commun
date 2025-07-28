# NetPractice - README

---

## Description
NetPractice est un projet réalisé dans le cadre du cursus de l'école 42. Il vise à initier les étudiants aux concepts de réseau et à l'administration système à travers la configuration de petits réseaux fictifs en utilisant le protocole TCP/IP. Ce projet permet de comprendre le fonctionnement des adresses IP, des masques de sous-réseau, des routeurs et des périphériques réseau.

L'objectif est de maîtriser les concepts suivants :
- Compréhension des adressages TCP/IP (IPv4, sous-réseaux, masques, etc.).
- Configuration de réseaux fonctionnels à travers 10 exercices (niveaux).
- Utilisation d'une interface web pour configurer et tester les réseaux.
- Exportation des configurations réseau pour validation.
- Résolution de problèmes liés à la connectivité réseau.

## Structure du projet
Le projet repose sur une interface web accessible via un fichier `index.html`. Les éléments clés à rendre sont :
- **10 fichiers de configuration** : Un fichier par niveau, généré via le bouton "Get my config" dans l'interface d'entraînement.
- Ces fichiers doivent être placés à la racine du dépôt Git.

## Prérequis
- Un navigateur web moderne (Chrome, Firefox, etc.) pour exécuter l'interface `index.html`.
- Connaissances de base en réseau (adresses IP, masques de sous-réseau, routage).
- Accès à un terminal pour gérer les fichiers et le dépôt Git.
- Une calculatrice (comme `bc`) est autorisée, mais aucun autre outil externe n'est permis pendant l'évaluation.

## Installation
1. **Télécharger les fichiers du projet** :
   - Récupérez le fichier attaché au projet depuis l'intranet 42.
   - Extrayez les fichiers dans un dossier de votre choix.
2. **Lancer l'interface** :
   - Exécutez le fichier `index.html` dans un navigateur web.
   - L'interface d'entraînement s'ouvrira avec l'invite "Bienvenue sur NetPractice !".
3. **Configurer les niveaux** :
   - Entrez votre login dans le champ prévu pour l'entraînement.
   - Pour chaque niveau, configurez les champs non grisés pour rendre le réseau fonctionnel.
   - Utilisez le bouton "Check again" pour vérifier votre configuration.
   - Une fois le niveau validé, exportez la configuration avec "Get my config" et placez le fichier dans votre dépôt Git.
4. **Passer au niveau suivant** :
   - Cliquez sur le bouton "Next level" après avoir validé un niveau.
   - Répétez l'opération pour les 10 niveaux.

## Utilisation
### Commandes principales
1. **Lancer l'interface** :
   ```bash
   open index.html
   ```
   Ouvre l'interface d'entraînement dans votre navigateur par défaut.

2. **Exporter une configuration** :
   - Dans l'interface, après avoir validé un niveau, cliquez sur "Get my config" pour télécharger le fichier de configuration.
   - Placez ce fichier à la racine de votre dépôt Git.

3. **Vérifier les erreurs** :
   - Consultez le journal de log en bas à droite de l'interface pour comprendre pourquoi une configuration est incorrecte.

### Exemple de flux de travail
- Ouvrez `index.html` dans votre navigateur.
- Entrez votre login pour commencer l'entraînement.
- Pour le niveau 1, analysez le schéma réseau et modifiez les champs (adresses IP, masques, etc.) pour atteindre l'objectif indiqué.
- Cliquez sur "Check again" pour valider.
- Une fois réussi, exportez la configuration avec "Get my config" et passez au niveau suivant avec "Next level".
- Répétez pour les 10 niveaux.

## Fonctionnement détaillé
### Interface d'entraînement
- L'interface propose 10 niveaux, chacun représentant un réseau non fonctionnel.
- Chaque niveau affiche un objectif (ex. : connecter deux appareils via un routeur).
- Les champs non grisés (adresses IP, masques, passerelles) doivent être modifiés pour atteindre l'objectif.
- Le bouton "Check again" valide la configuration.
- Le bouton "Get my config" génère un fichier de configuration à inclure dans le dépôt Git.
- Un journal de log aide à diagnostiquer les erreurs.

### Rendu
- Vous devez soumettre 10 fichiers de configuration (un par niveau) à la racine de votre dépôt Git.
- Les fichiers doivent être générés en utilisant votre login dans l'interface.
- Pendant la soutenance, vous devrez résoudre 3 niveaux aléatoires dans un temps limité.

## Gestion des erreurs
- Vérifiez que les fichiers de configuration correspondent aux niveaux validés dans l'interface.
- Assurez-vous que les noms des fichiers respectent les consignes du sujet.
- Testez vos configurations avant la soutenance pour éviter les erreurs.
- Pendant l'évaluation, l'utilisation d'outils externes (sauf une calculatrice comme `bc`) est interdite.

## Limitations
- Les configurations doivent être réalisées dans l'interface web fournie, sans outils externes.
- Les niveaux doivent être validés avec votre login pour garantir la traçabilité.
- Les erreurs dans les noms de fichiers ou l'absence de fichiers entraîneront une note de 0.

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** : Juillet 2025 - Juillet 2025

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis de découvrir les bases du réseau et de l'adressage TCP/IP à travers une approche pratique.

---

# NetPractice - README

## Description
NetPractice is a project developed as part of the 42 school curriculum. It aims to introduce students to networking concepts and system administration by configuring small, fictional networks using the TCP/IP protocol. The project helps understand IP addressing, subnet masks, routers, and network devices.

The goal is to master the following concepts:
- Understanding TCP/IP addressing (IPv4, subnets, masks, etc.).
- Configuring functional networks through 10 exercises (levels).
- Using a web interface to configure and test networks.
- Exporting network configurations for validation.
- Solving connectivity-related issues.

## Project Structure
The project is based on a web interface accessible via an `index.html` file. The key deliverables are:
- **10 configuration files**: One file per level, generated using the "Get my config" button in the training interface.
- These files must be placed at the root of the Git repository.

## Prerequisites
- A modern web browser (Chrome, Firefox, etc.) to run the `index.html` interface.
- Basic knowledge of networking (IP addresses, subnet masks, routing).
- Access to a terminal for managing files and the Git repository.
- A calculator (like `bc`) is allowed, but no other external tools are permitted during evaluation.

## Installation
1. **Download the project files**:
   - Retrieve the attached file from the 42 intranet.
   - Extract the files to a directory of your choice.
2. **Launch the interface**:
   - Open the `index.html` file in a web browser.
   - The training interface will display "Welcome to NetPractice!".
3. **Configure the levels**:
   - Enter your login in the provided field for training.
   - For each level, configure the non-grayed fields to make the network functional.
   - Use the "Check again" button to verify your configuration.
   - Once validated, export the configuration using "Get my config" and place it in your Git repository.
4. **Move to the next level**:
   - Click the "Next level" button after validating a level.
   - Repeat for all 10 levels.

## Usage
### Key Commands
1. **Launch the interface**:
   ```bash
   open index.html
   ```
   Opens the training interface in your default browser.

2. **Export a configuration**:
   - In the interface, after validating a level, click "Get my config" to download the configuration file.
   - Place this file at the root of your Git repository.

3. **Check errors**:
   - Review the log at the bottom right of the interface to understand why a configuration is incorrect.

### Example Workflow
- Open `index.html` in your browser.
- Enter your login to start training.
- For level 1, analyze the network diagram and modify fields (IP addresses, masks, etc.) to meet the specified goal.
- Click "Check again" to validate.
- Once successful, export the configuration with "Get my config" and proceed to the next level with "Next level".
- Repeat for all 10 levels.

## Detailed Functionality
### Training Interface
- The interface provides 10 levels, each representing a non-functional network.
- Each level displays a goal (e.g., connecting two devices via a router).
- Non-grayed fields (IP addresses, masks, gateways) must be modified to achieve the goal.
- The "Check again" button validates the configuration.
- The "Get my config" button generates a configuration file for the Git repository.
- A log helps diagnose configuration errors.

### Submission
- Submit 10 configuration files (one per level) at the root of your Git repository.
- Files must be generated using your login in the interface.
- During the evaluation, you will solve 3 random levels within a limited time.

## Error Handling
- Ensure configuration files match the validated levels in the interface.
- Verify that file names comply with the project requirements.
- Test configurations before the evaluation to avoid errors.
- During evaluation, external tools (except a calculator like `bc`) are prohibited.

## Limitations
- Configurations must be done in the provided web interface, without external tools.
- Levels must be validated with your login for traceability.
- Errors in file names or missing files will result in a grade of 0.

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**: July 2025 - July 2025

## Acknowledgments
Thanks to 42 school for this project, which helped me explore networking basics and TCP/IP addressing through a hands-on approach.