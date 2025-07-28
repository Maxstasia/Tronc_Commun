# ft_transcendence - README

---

## Description
`ft_transcendence` est un projet réalisé dans le cadre du cursus de l’école 42, visant à créer un site web pour un concours de Pong en ligne avec des fonctionnalités multijoueurs en temps réel. Ce projet constitue une épreuve finale du tronc commun, mettant l’accent sur l’adaptation à des technologies potentiellement nouvelles, la résolution de problèmes complexes, et la gestion de projet en équipe. Le site doit être une application monopage (SPA) développée avec **TypeScript** pour le frontend et, si un backend est inclus, en **PHP pur** sans frameworks (sauf si le module Framework est choisi). L’infrastructure repose sur **Docker** pour un déploiement simplifié, et le projet inclut des modules optionnels pour enrichir les fonctionnalités.

L’objectif est de maîtriser les concepts suivants :
- Développement d’une application web monopage compatible avec Mozilla Firefox.
- Gestion d’un jeu Pong multijoueur en temps réel avec un système de tournoi.
- Utilisation de Docker pour déployer l’ensemble de l’application.
- Implémentation de mesures de sécurité (HTTPS, hachage des mots de passe, protection contre XSS/SQL injections).
- Exploration de modules avancés comme la blockchain, l’IA, ou les microservices.

## Structure du projet
Le projet est organisé comme suit :
- **Dossier principal** : Contient les dossiers pour le frontend, le backend (si applicable), les fichiers Docker, et la documentation.
- **Dossier frontend** : Contient le code TypeScript pour l’interface utilisateur et le jeu Pong (éventuellement avec Tailwind CSS ou Babylon.js si les modules correspondants sont choisis).
- **Dossier backend** : Contient le code PHP pur ou Fastify/Node.js (si le module Framework est choisi) pour gérer les fonctionnalités serveur.
- **Dossier config** : Contient les fichiers de configuration Docker (`Dockerfile`, `docker-compose.yml`) et les variables d’environnement (`.env`).
- **Dossier www** : Contient les fichiers statiques (HTML, CSS, images) pour le site.
- **Dossier tests** : Contient des scripts de test pour valider les fonctionnalités (ex. : tests en Python ou Go).
- **Dossier data** : Contient les données persistantes (base de données SQLite, fichiers uploadés, etc.).

Les fichiers clés incluent :
- **Dockerfile** : Définit les images pour les conteneurs (frontend, backend, base de données, etc.).
- **docker-compose.yml** : Configure les services, réseaux, et volumes Docker.
- **.env** : Stocke les variables d’environnement (ex. : clés API, mots de passe) ignorées par Git.
- **Makefile** : Automatise la compilation et le déploiement des conteneurs.

## Prérequis
- Un environnement Linux/Unix (ou macOS avec ajustements).
- **Docker** et **docker-compose** installés.
- Connaissances de base en développement web (TypeScript, PHP, HTML/CSS).
- Familiarité avec les concepts de réseau (WebSocket pour le multijoueur, HTTPS).
- Connaissance des principes de sécurité web (hachage, XSS, SQL injection).
- Accès à un terminal pour configurer et lancer les conteneurs.

## Installation
1. **Cloner le dépôt Git** :
   ```bash
   git clone <votre-dépôt-git>
   cd ft_transcendence
   ```
2. **Configurer le fichier .env** :
   - Créez un fichier `.env` dans le dossier principal pour définir les variables d’environnement (ex. : `DB_HOST`, `API_KEY`).
   - Assurez-vous que les identifiants sensibles ne sont pas inclus dans le dépôt Git.
3. **Compiler et lancer les conteneurs** :
   ```bash
   make
   ```
   - Construit les images Docker et lance les conteneurs via `docker-compose.yml`.
   - Une seule commande doit suffire pour lancer l’application.
4. **Nettoyer les conteneurs et images** :
   ```bash
   make clean
   ```
5. **Supprimer tous les volumes et données** :
   ```bash
   make fclean
   ```
6. **Recompiler tout** :
   ```bash
   make re
   ```

## Utilisation
### Commandes principales
1. **Lancer l’application** :
   ```bash
   make
   ```
   - Lance les conteneurs pour le frontend, le backend (si applicable), et les services associés.
   - Le site est accessible via `https://localhost:<port>` (port défini dans `docker-compose.yml`).
2. **Accéder au site** :
   - Ouvrez un navigateur (Mozilla Firefox recommandé) et accédez à `https://localhost:<port>`.
   - Naviguez avec les boutons Précédent/Suivant du navigateur pour tester la SPA.
3. **Gérer les conteneurs** :
   - Arrêter les conteneurs : `make stop`.
   - Redémarrer les conteneurs : `make restart`.

### Structure des services
- **Frontend** :
  - Application monopage en **TypeScript** (ou avec Tailwind CSS/Babylon.js si modules choisis).
  - Compatible avec Mozilla Firefox (et autres navigateurs si module Compatibilité Étendue).
  - Gère l’interface du jeu Pong et les interactions utilisateur (inscription, tournoi, chat, etc.).
- **Backend (optionnel)** :
  - Écrit en **PHP pur** sans frameworks (ou Fastify/Node.js si module Framework).
  - Gère la logique serveur, l’authentification, les tournois, et les interactions avec la base de données (SQLite si module Database).
- **Base de données (si applicable)** :
  - Utilise **SQLite** pour la persistance des données (scores, profils utilisateurs, historique).
  - Les mots de passe sont hachés avec un algorithme sécurisé (ex. : bcrypt).
- **Docker** :
  - Tous les services sont conteneurisés (frontend, backend, base de données, etc.).
  - Les conteneurs s’exécutent dans `/goinfre` (ou équivalent) sans volumes bind-mount pour les UID non-root.
- **Jeu Pong** :
  - Multijoueur en temps réel via WebSocket (ou équivalent).
  - Supporte les matchs 1v1 sur le même clavier (ou à distance si module Remote Players).
  - Système de tournoi avec matchmaking automatique.

### Configuration du domaine
- Configurez `/etc/hosts` sur la machine hôte pour pointer vers `localhost` (ex. : `127.0.0.1 ft_transcendence.local`).
  ```bash
  echo "127.0.0.1 ft_transcendence.local" >> /etc/hosts
  ```
- Assurez-vous que la connexion HTTPS est activée avec un certificat TLS valide.

## Fonctionnement détaillé
### Partie obligatoire
- **Site web monopage (SPA)** :
  - Développé en **TypeScript** pour le frontend.
  - Compatible avec Mozilla Firefox (dernière version stable).
  - Supporte les boutons Précédent/Suivant du navigateur.
  - Aucune erreur ou avertissement non géré lors de la navigation.
- **Jeu Pong** :
  - Multijoueur en temps réel (1v1 sur le même clavier par défaut).
  - Système de tournoi avec inscription par alias (réinitialisé à chaque tournoi).
  - Matchmaking automatique pour organiser les matchs.
  - Règles uniformes (ex. : vitesse des raquettes identique pour tous les joueurs).
  - Respecte l’esthétique du Pong original (1972), avec liberté sur le style visuel.
- **Docker** :
  - Tous les services sont lancés via une seule commande (`docker-compose up`).
  - Conteneurs autonomes sans volumes bind-mount pour les UID non-root.
  - Exécution dans `/goinfre` (ou équivalent) pour respecter les contraintes du cluster.
- **Sécurité** :
  - Connexion HTTPS obligatoire (wss pour WebSocket).
  - Hachage des mots de passe (si base de données utilisée).
  - Protection contre les injections SQL et XSS.
  - Validation des entrées utilisateur (côté client ou serveur).
  - Variables sensibles stockées dans `.env` et ignorées par Git.

### Modules (7 modules majeurs minimum requis)
- **Web** :
  - **Framework (majeur)** : Utilise **Fastify** avec **Node.js** pour le backend.
  - **Frontend Framework (mineur)** : Utilise **Tailwind CSS** avec TypeScript.
  - **Database (mineur)** : Utilise **SQLite** pour la persistance des données.
  - **Blockchain (majeur)** : Stocke les scores des tournois sur **Avalanche** avec **Solidity** (environnement de test).
- **User Management** :
  - **Standard User Management (majeur)** : Inscription, connexion, profils, avatars, amis, historique des matchs.
  - **Remote Authentication (majeur)** : Authentification via **OAuth 2.0**.
- **Gameplay and User Experience** :
  - **Remote Players (majeur)** : Supporte le jeu à distance entre deux ordinateurs.
  - **Multiple Players (majeur)** : Jeu avec plus de 2 joueurs (ex. : 4 joueurs sur un plateau carré).
  - **New Game (majeur)** : Ajoute un nouveau jeu avec historique et matchmaking.
  - **Game Customization (mineur)** : Options de personnalisation (power-ups, cartes).
  - **Live Chat (majeur)** : Messagerie directe, blocage, invitations, profils.
- **AI-Algo** :
  - **AI Opponent (majeur)** : IA simulant un joueur humain (rafraîchissement 1 Hz, sans algorithme A*).
  - **Stats Dashboards (mineur)** : Tableaux de bord pour les statistiques des joueurs et des matchs.
- **Cybersecurity** :
  - **WAF/ModSecurity & Vault (majeur)** : Protection avec **WAF/ModSecurity** et gestion des secrets avec **HashiCorp Vault**.
  - **GDPR Compliance (mineur)** : Anonymisation, gestion des données, suppression de compte.
  - **2FA & JWT (majeur)** : Authentification à deux facteurs et gestion des sessions avec **JWT**.
- **DevOps** :
  - **ELK Stack (majeur)** : Gestion des logs avec **Elasticsearch**, **Logstash**, **Kibana**.
  - **Monitoring (mineur)** : Surveillance avec **Prometheus** et **Grafana**.
  - **Microservices (majeur)** : Architecture backend en microservices.
- **Graphics** :
  - **3D Graphics (majeur)** : Jeu Pong en 3D avec **Babylon.js**.
- **Accessibility** :
  - **All Devices (mineur)** : Compatibilité responsive sur tous les appareils.
  - **Browser Compatibility (mineur)** : Support d’un navigateur supplémentaire.
  - **Multiple Languages (mineur)** : Support d’au moins 3 langues.
  - **Visually Impaired (mineur)** : Accessibilité pour les malvoyants (lecteurs d’écran, contraste élevé).
  - **SSR (mineur)** : Rendu côté serveur pour améliorer les performances.
- **Server-Side Pong** :
  - **Server-Side Pong (majeur)** : Pong côté serveur avec API.
  - **CLI Gameplay (majeur)** : Jeu via CLI connecté aux joueurs web via API.

### Makefile
Le Makefile inclut les règles suivantes :
- `all` : Construit et lance les conteneurs via `docker-compose.yml`.
- `clean` : Arrête et supprime les conteneurs et images.
- `fclean` : Supprime également les volumes et données persistantes.
- `re` : Recompile et relance tout.

## Gestion des erreurs
- Vérifiez que le site gère les erreurs : déconnexions réseau, entrées invalides, pannes de conteneurs.
- Testez la compatibilité avec Mozilla Firefox (et autres navigateurs si module choisi).
- Assurez-vous que les conteneurs redémarrent automatiquement en cas de crash.
- Validez la sécurité : aucune donnée sensible dans le dépôt Git, HTTPS activé, protections XSS/SQL activées.
- Testez avec des cas limites : multiples connexions, tournois volumineux, déconnexions soudaines.

## Limitations
- Le projet doit être conteneurisé avec Docker (pas de `containerd`, `podman`, etc.).
- Exécution dans `/goinfre` sans volumes bind-mount pour les UID non-root.
- Frontend en **TypeScript** (ou Tailwind CSS/Babylon.js si modules choisis).
- Backend en **PHP pur** (ou Fastify/Node.js si module Framework).
- Base de données en **SQLite** (si module Database).
- Interdiction des bibliothèques/tools offrant une solution complète pour une fonctionnalité/module.
- Les modules bonus ne sont évalués que si la partie obligatoire est parfaite.

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** : Juin 2025 - Juin 2025

## Remerciements
Merci à l’école 42 pour ce projet ambitieux qui m’a permis d’explorer des technologies modernes, de relever des défis complexes en équipe, et de développer une application web robuste et sécurisée centrée sur le jeu Pong.

---

# ft_transcendence - README

## Description
`ft_transcendence` is a project developed as part of the 42 school curriculum, aimed at creating a website for an online Pong contest with real-time multiplayer features. This project serves as a final challenge of the Common Core, emphasizing adaptation to potentially new technologies, complex problem-solving, and team project management. The site must be a single-page application (SPA) developed with **TypeScript** for the frontend and, if a backend is included, in **pure PHP** without frameworks (unless the Framework module is chosen). The infrastructure relies on **Docker** for simplified deployment, and the project includes optional modules to enhance functionality.

The goal is to master the following concepts:
- Developing a single-page web application compatible with Mozilla Firefox.
- Managing a real-time multiplayer Pong game with a tournament system.
- Using Docker to deploy the entire application.
- Implementing security measures (HTTPS, password hashing, XSS/SQL injection protection).
- Exploring advanced modules like blockchain, AI, or microservices.

## Project Structure
The project is organized as follows:
- **Main Directory**: Contains folders for the frontend, backend (if applicable), Docker files, and documentation.
- **frontend Folder**: Contains TypeScript code for the user interface and Pong game (potentially with Tailwind CSS or Babylon.js if corresponding modules are chosen).
- **backend Folder**: Contains pure PHP or Fastify/Node.js code (if Framework module is chosen) for server-side functionality.
- **config Folder**: Contains Docker configuration files (`Dockerfile`, `docker-compose.yml`) and environment variables (`.env`).
- **www Folder**: Contains static files (HTML, CSS, images) for the website.
- **tests Folder**: Contains test scripts to validate functionality (e.g., tests in Python or Go).
- **data Folder**: Contains persistent data (SQLite database, uploaded files, etc.).

Key files include:
- **Dockerfile**: Defines images for containers (frontend, backend, database, etc.).
- **docker-compose.yml**: Configures Docker services, networks, and volumes.
- **.env**: Stores environment variables (e.g., API keys, passwords) ignored by Git.
- **Makefile**: Automates container building and deployment.

## Prerequisites
- A Linux/Unix environment (or macOS with adjustments).
- **Docker** and **docker-compose** installed.
- Basic knowledge of web development (TypeScript, PHP, HTML/CSS).
- Familiarity with networking concepts (WebSocket for multiplayer, HTTPS).
- Understanding of web security principles (hashing, XSS, SQL injection).
- Access to a terminal to configure and run containers.

## Installation
1. **Clone the Git repository**:
   ```bash
   git clone <your-git-repository>
   cd ft_transcendence
   ```
2. **Configure the .env file**:
   - Create a `.env` file in the main directory to define environment variables (e.g., `DB_HOST`, `API_KEY`).
   - Ensure sensitive credentials are not included in the Git repository.
3. **Build and run containers**:
   ```bash
   make
   ```
   - Builds Docker images and starts containers via `docker-compose.yml`.
   - A single command must suffice to launch the application.
4. **Clean containers and images**:
   ```bash
   make clean
   ```
5. **Remove all volumes and data**:
   ```bash
   make fclean
   ```
6. **Rebuild everything**:
   ```bash
   make re
   ```

## Usage
### Key Commands
1. **Start the application**:
   ```bash
   make
   ```
   - Starts containers for the frontend, backend (if applicable), and associated services.
   - The site is accessible via `https://localhost:<port>` (port defined in `docker-compose.yml`).
2. **Access the site**:
   - Open a browser (Mozilla Firefox recommended) and navigate to `https://localhost:<port>`.
   - Use the browser’s Back/Forward buttons to test the SPA.
3. **Manage containers**:
   - Stop containers: `make stop`.
   - Restart containers: `make restart`.

### Service Structure
- **Frontend**:
  - Single-page application in **TypeScript** (or with Tailwind CSS/Babylon.js if modules chosen).
  - Compatible with Mozilla Firefox (and other browsers if Extended Compatibility module is chosen).
  - Handles the Pong game interface and user interactions (registration, tournament, chat, etc.).
- **Backend (optional)**:
  - Written in **pure PHP** without frameworks (or Fastify/Node.js if Framework module is chosen).
  - Manages server-side logic, authentication, tournaments, and database interactions (SQLite if Database module).
- **Database (if applicable)**:
  - Uses **SQLite** for data persistence (scores, user profiles, match history).
  - Passwords are hashed with a secure algorithm (e.g., bcrypt).
- **Docker**:
  - All services are containerized (frontend, backend, database, etc.).
  - Containers run in `/goinfre` (or equivalent) without bind-mount volumes for non-root UIDs.
- **Pong Game**:
  - Real-time multiplayer via WebSocket (or equivalent).
  - Supports 1v1 matches on the same keyboard (or remotely if Remote Players module).
  - Tournament system with automatic matchmaking.

### Domain Configuration
- Configure `/etc/hosts` on the host machine to point to `localhost` (e.g., `127.0.0.1 ft_transcendence.local`).
  ```bash
  echo "127.0.0.1 ft_transcendence.local" >> /etc/hosts
  ```
- Ensure HTTPS is enabled with a valid TLS certificate.

## Detailed Functionality
### Mandatory Part
- **Single-Page Application (SPA)**:
  - Developed in **TypeScript** for the frontend.
  - Compatible with the latest stable Mozilla Firefox.
  - Supports browser Back/Forward buttons.
  - No unhandled errors or warnings during navigation.
- **Pong Game**:
  - Real-time multiplayer (1v1 on the same keyboard by default).
  - Tournament system with alias-based registration (reset per tournament).
  - Automatic matchmaking for organizing matches.
  - Uniform rules (e.g., identical paddle speed for all players).
  - Captures the essence of the original Pong (1972), with flexibility in visual style.
- **Docker**:
  - All services launched via a single command (`docker-compose up`).
  - Autonomous containers without bind-mount volumes for non-root UIDs.
  - Runs in `/goinfre` (or equivalent) to meet cluster constraints.
- **Security**:
  - Mandatory HTTPS connection (wss for WebSocket).
  - Password hashing (if database used).
  - Protection against SQL injections and XSS attacks.
  - Input validation (client-side or server-side).
  - Sensitive variables stored in `.env` and ignored by Git.

### Modules (Minimum of 7 Major Modules Required)
- **Web**:
  - **Framework (Major)**: Uses **Fastify** with **Node.js** for the backend.
  - **Frontend Framework (Minor)**: Uses **Tailwind CSS** with TypeScript.
  - **Database (Minor)**: Uses **SQLite** for data persistence.
  - **Blockchain (Major)**: Stores tournament scores on **Avalanche** with **Solidity** (test environment).
- **User Management**:
  - **Standard User Management (Major)**: Registration, login, profiles, avatars, friends, match history.
  - **Remote Authentication (Major)**: Authentication via **OAuth 2.0**.
- **Gameplay and User Experience**:
  - **Remote Players (Major)**: Supports remote gameplay between two computers.
  - **Multiple Players (Major)**: Gameplay with more than 2 players (e.g., 4 players on a square board).
  - **New Game (Major)**: Adds a new game with history and matchmaking.
  - **Game Customization (Minor)**: Customization options (power-ups, maps).
  - **Live Chat (Major)**: Direct messaging, blocking, game invitations, profile access.
- **AI-Algo**:
  - **AI Opponent (Major)**: AI simulating human player (1 Hz refresh, no A* algorithm).
  - **Stats Dashboards (Minor)**: Dashboards for player and match statistics.
- **Cybersecurity**:
  - **WAF/ModSecurity & Vault (Major)**: Protection with **WAF/ModSecurity** and secrets management with **HashiCorp Vault**.
  - **GDPR Compliance (Minor)**: Data anonymization, management, account deletion.
  - **2FA & JWT (Major)**: Two-factor authentication and session management with **JWT**.
- **DevOps**:
  - **ELK Stack (Major)**: Log management with **Elasticsearch**, **Logstash**, **Kibana**.
  - **Monitoring (Minor)**: Monitoring with **Prometheus** and **Grafana**.
  - **Microservices (Major)**: Backend architecture as microservices.
- **Graphics**:
  - **3D Graphics (Major)**: 3D Pong game with **Babylon.js**.
- **Accessibility**:
  - **All Devices (Minor)**: Responsive compatibility across all devices.
  - **Browser Compatibility (Minor)**: Support for an additional browser.
  - **Multiple Languages (Minor)**: Support for at least 3 languages.
  - **Visually Impaired (Minor)**: Accessibility for visually impaired users (screen readers, high contrast).
  - **SSR (Minor)**: Server-side rendering for performance.
- **Server-Side Pong**:
  - **Server-Side Pong (Major)**: Server-side Pong with API.
  - **CLI Gameplay (Major)**: CLI gameplay connected to web players via API.

### Makefile
The Makefile includes:
- `all`: Builds and starts containers via `docker-compose.yml`.
- `clean`: Stops and removes containers and images.
- `fclean`: Also removes volumes and persistent data.
- `re`: Rebuilds and restarts everything.

## Error Handling
- Ensure the site handles errors: network disconnections, invalid inputs, container failures.
- Test compatibility with Mozilla Firefox (and other browsers if module chosen).
- Ensure containers restart automatically on crash.
- Validate security: no sensitive data in Git repository, HTTPS enabled, XSS/SQL protections active.
- Test edge cases: multiple connections, large tournaments, sudden disconnections.

## Limitations
- Project must be containerized with Docker (no `containerd`, `podman`, etc.).
- Runs in `/goinfre` without bind-mount volumes for non-root UIDs.
- Frontend in **TypeScript** (or Tailwind CSS/Babylon.js if modules chosen).
- Backend in **pure PHP** (or Fastify/Node.js if Framework module).
- Database in **SQLite** (if Database module).
- Libraries/tools providing complete solutions for a feature/module are prohibited.
- Bonus modules are evaluated only if the mandatory part is perfect.

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**: June 2025 - June 2025

## Acknowledgments
Thanks to 42 school for this ambitious project, which allowed me to explore modern technologies, tackle complex challenges in a team, and develop a robust and secure web application centered around the Pong game.