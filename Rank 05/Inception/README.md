# Inception - README

---

## Description
Inception est un projet d’administration système réalisé dans le cadre du cursus de l’école 42. Il vise à approfondir les compétences en virtualisation et en gestion de conteneurs en utilisant **Docker**. L’objectif est de mettre en place une infrastructure multi-conteneurs avec **docker-compose**, comprenant plusieurs services interconnectés (NGINX, WordPress, MariaDB) fonctionnant dans une machine virtuelle. Ce projet met l’accent sur la configuration des conteneurs, la gestion des volumes, des réseaux Docker, et la sécurité (TLS, gestion des variables d’environnement).

L’objectif est de maîtriser les concepts suivants :
- Utilisation de Docker et docker-compose pour la virtualisation de services.
- Création et configuration de Dockerfiles personnalisés.
- Mise en place d’une infrastructure avec NGINX, WordPress, et MariaDB.
- Gestion des volumes et réseaux Docker.
- Configuration sécurisée avec TLSv1.2 ou TLSv1.3 et variables d’environnement.
- Implémentation de services bonus (Redis, FTP, Adminer, etc.).

## Structure du projet
Le projet est organisé comme suit :
- **Dossier principal** : Contient le dossier `srcs` avec les fichiers de configuration (Dockerfiles, docker-compose.yml, scripts).
- **Dossier srcs** : Contient les Dockerfiles pour chaque service (NGINX, WordPress, MariaDB) et le fichier `docker-compose.yml`.
- **Dossier bonus (optionnel)** : Contient les Dockerfiles et configurations pour les services bonus (Redis, FTP, Adminer, etc.).
- **Dossier /home/login/data** : Contient les volumes pour la base de données WordPress et les fichiers du site.
- **Makefile** : Pour automatiser la construction et la gestion des conteneurs.

Les fichiers clés incluent :
- **Dockerfiles** : Un par service (NGINX, WordPress, MariaDB, et bonus).
- **docker-compose.yml** : Définit les services, volumes, et réseaux.
- **.env** : Stocke les variables d’environnement (ex. : identifiants, mots de passe).
- **Makefile** : Automatise la compilation et le déploiement des conteneurs.

## Prérequis
- Une machine virtuelle Linux (Debian ou Alpine recommandé).
- Docker et docker-compose installés.
- Connaissances de base en administration système (gestion des conteneurs, réseaux, TLS).
- Connaissance des services web (NGINX, WordPress, MariaDB).
- Accès à un terminal pour configurer le nom de domaine local (ex. : mstasiak.42.fr).

## Installation
1. **Cloner le dépôt Git** :
   ```bash
   git clone <votre-dépôt-git>
   cd inception
   ```
2. **Configurer le fichier .env** :
   - Créez un fichier `.env` dans le dossier `srcs` pour définir les variables d’environnement (ex. : `DB_USER`, `DB_PASSWORD`).
   - Assurez-vous que les mots de passe ne sont pas inclus dans les Dockerfiles.
3. **Compiler et lancer les conteneurs** :
   ```bash
   make
   ```
   - Construit les images Docker et lance les conteneurs via `docker-compose.yml`.
4. **Compiler les bonus (si implémentés)** :
   ```bash
   make bonus
   ```
   - Construit et lance les services bonus.
5. **Nettoyer les conteneurs et images** :
   ```bash
   make clean
   ```
6. **Supprimer tous les volumes et données** :
   ```bash
   make fclean
   ```
7. **Recompiler tout** :
   ```bash
   make re
   ```

## Utilisation
### Commandes principales
1. **Lancer l’infrastructure** :
   ```bash
   make
   ```
   - Lance les conteneurs NGINX, WordPress, et MariaDB.
   - Le site WordPress est accessible via `https://mstasiak.42.fr` (remplacez `mstasiak` par votre login).
2. **Accéder au site** :
   - Ouvrez un navigateur et accédez à `https://mstasiak.42.fr`.
   - NGINX sert de point d’entrée unique sur le port 443 avec TLSv1.2 ou TLSv1.3.
3. **Gérer les conteneurs** :
   - Arrêter les conteneurs : `make stop`.
   - Redémarrer les conteneurs : `make restart`.

### Structure des services
- **NGINX** :
  - Point d’entrée unique de l’infrastructure.
  - Configuré avec TLSv1.2 ou TLSv1.3 sur le port 443.
  - Redirige les requêtes vers le conteneur WordPress.
- **WordPress + php-fpm** :
  - Contient WordPress avec php-fpm (sans NGINX).
  - Connecté à la base de données MariaDB.
  - Utilise un volume pour stocker les fichiers du site dans `/home/mstasiak/data/wp`.
- **MariaDB** :
  - Base de données pour WordPress.
  - Utilise un volume pour stocker les données dans `/home/mstasiak/data/db`.
  - Contient deux utilisateurs : un administrateur (sans `admin` dans le nom) et un utilisateur standard.
- **Docker Network** :
  - Connecte les conteneurs pour permettre la communication interne.
  - L’utilisation de `network: host`, `--link`, ou `links:` est interdite.
- **Volumes** :
  - Volume pour la base de données : `/home/mstasiak/data/db`.
  - Volume pour les fichiers WordPress : `/home/mstasiak/data/wp`.

### Configuration du domaine
- Configurez le fichier `/etc/hosts` sur la machine hôte pour pointer `mstasiak.42.fr` vers l’adresse IP locale (ex. : `127.0.0.1`).
  ```bash
  echo "127.0.0.1 mstasiak.42.fr" >> /etc/hosts
  ```
- Assurez-vous que le certificat TLS est correctement configuré pour sécuriser la connexion.

## Fonctionnement détaillé
### Partie obligatoire
- **NGINX** :
  - Construit à partir de l’avant-dernière version stable d’Alpine ou Debian.
  - Configure un serveur web sécurisé avec TLSv1.2 ou TLSv1.3.
  - Sert de reverse proxy pour rediriger les requêtes vers WordPress.
- **WordPress + php-fpm** :
  - Installe et configure WordPress avec php-fpm.
  - Connecté à MariaDB via des variables d’environnement (ex. : `DB_HOST`, `DB_USER`).
  - Les fichiers du site sont persistants via un volume.
- **MariaDB** :
  - Base de données relationnelle pour WordPress.
  - Configure deux utilisateurs : un administrateur et un utilisateur standard.
  - Les données sont persistantes via un volume.
- **Docker Compose** :
  - Le fichier `docker-compose.yml` définit les services, réseaux, et volumes.
  - Les conteneurs redémarrent automatiquement en cas de crash (`restart: always`).
  - Les variables d’environnement sont gérées via un fichier `.env` ou Docker secrets.
- **Bonnes pratiques** :
  - Les Dockerfiles suivent les bonnes pratiques (PID 1, éviter les boucles infinies comme `tail -f` ou `sleep infinity`).
  - Aucun mot de passe n’est codé en dur dans les Dockerfiles.
  - Les images sont construites localement (pas d’utilisation de DockerHub, sauf pour Alpine/Debian).

### Partie bonus
- **Redis Cache** : Mise en cache des données WordPress pour améliorer les performances.
- **Serveur FTP** : Accès au volume WordPress pour le transfert de fichiers.
- **Site statique** : Un site web dans un langage autre que PHP (ex. : HTML/CSS, Python Flask).
- **Adminer** : Interface web pour gérer la base de données MariaDB.
- **Service personnalisé** : Un service supplémentaire justifié (ex. : monitoring, backup).

### Makefile
Le Makefile inclut les règles suivantes :
- `all` : Construit et lance les conteneurs via `docker-compose.yml`.
- `clean` : Arrête et supprime les conteneurs et images.
- `fclean` : Supprime également les volumes et données persistantes.
- `re` : Recompile et relance tout.
- `bonus` : Construit et lance les services bonus.

## Gestion des erreurs
- Vérifiez que les conteneurs gèrent correctement les erreurs : fichiers de configuration absents, ports occupés, certificats TLS invalides.
- Assurez-vous que les Dockerfiles respectent les bonnes pratiques (ex. : gestion du PID 1).
- Testez avec des cas limites : crash de conteneurs, variables d’environnement manquantes.
- Les volumes doivent être correctement montés dans `/home/mstasiak/data`.
- Les conteneurs doivent redémarrer automatiquement en cas de crash.

## Limitations
- Le projet doit être réalisé dans une machine virtuelle.
- Les images doivent être construites à partir de l’avant-dernière version stable d’Alpine ou Debian.
- L’utilisation de `network: host`, `--link`, ou `links:` est interdite.
- Les boucles infinies (`tail -f`, `sleep infinity`, etc.) sont interdites.
- Les mots de passe ne doivent pas être codés en dur dans les Dockerfiles.
- Le tag `latest` est interdit pour les images.
- Les bonus ne sont évalués que si la partie obligatoire est parfaite.

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** : Avril 2025 - Avril 2025

## Remerciements
Merci à l’école 42 pour ce projet qui m’a permis d’explorer Docker, docker-compose, et la gestion d’une infrastructure multi-conteneurs, tout en approfondissant mes compétences en administration système et en sécurité.

---

# Inception - README

## Description
Inception is a system administration project developed as part of the 42 school curriculum. It aims to deepen containerization skills using **Docker**. The goal is to set up a multi-container infrastructure with **docker-compose**, including interconnected services (NGINX, WordPress, MariaDB) running in a virtual machine. The project emphasizes container configuration, volume and network management, and security (TLS, environment variables).

The goal is to master the following concepts:
- Using Docker and docker-compose for service virtualization.
- Creating and configuring custom Dockerfiles.
- Setting up an infrastructure with NGINX, WordPress, and MariaDB.
- Managing Docker volumes and networks.
- Implementing secure configurations with TLSv1.2 or TLSv1.3 and environment variables.
- Adding bonus services (Redis, FTP, Adminer, etc.).

## Project Structure
The project is organized as follows:
- **Main Directory**: Contains the `srcs` folder with configuration files (Dockerfiles, docker-compose.yml, scripts).
- **srcs Folder**: Contains Dockerfiles for each service (NGINX, WordPress, MariaDB) and the `docker-compose.yml` file.
- **Bonus Folder (optional)**: Contains Dockerfiles and configurations for bonus services (Redis, FTP, Adminer, etc.).
- **/home/login/data Folder**: Hosts volumes for the WordPress database and site files.
- **Makefile**: Automates container building and management.

Key files include:
- **Dockerfiles**: One per service (NGINX, WordPress, MariaDB, and bonuses).
- **docker-compose.yml**: Defines services, volumes, and networks.
- **.env**: Stores environment variables (e.g., `DB_USER`, `DB_PASSWORD`).
- **Makefile**: Automates building and deployment of containers.

## Prerequisites
- A Linux virtual machine (Debian or Alpine recommended).
- Docker and docker-compose installed.
- Basic knowledge of system administration (container management, networks, TLS).
- Familiarity with web services (NGINX, WordPress, MariaDB).
- Access to a terminal to configure the local domain name (e.g., mstasiak.42.fr).

## Installation
1. **Clone the Git repository**:
   ```bash
   git clone <your-git-repository>
   cd inception
   ```
2. **Configure the .env file**:
   - Create a `.env` file in the `srcs` folder to define environment variables (e.g., `DB_USER`, `DB_PASSWORD`).
   - Ensure passwords are not hardcoded in Dockerfiles.
3. **Build and run containers**:
   ```bash
   make
   ```
   - Builds Docker images and starts containers via `docker-compose.yml`.
4. **Build bonus services (if implemented)**:
   ```bash
   make bonus
   ```
   - Builds and starts bonus services.
5. **Clean containers and images**:
   ```bash
   make clean
   ```
6. **Remove all volumes and data**:
   ```bash
   make fclean
   ```
7. **Rebuild everything**:
   ```bash
   make re
   ```

## Usage
### Key Commands
1. **Start the infrastructure**:
   ```bash
   make
   ```
   - Starts NGINX, WordPress, and MariaDB containers.
   - The WordPress site is accessible at `https://mstasiak.42.fr` (replace `mstasiak` with your login).
2. **Access the site**:
   - Open a browser and navigate to `https://mstasiak.42.fr`.
   - NGINX serves as the single entry point on port 443 with TLSv1.2 or TLSv1.3.
3. **Manage containers**:
   - Stop containers: `make stop`.
   - Restart containers: `make restart`.

### Service Structure
- **NGINX**:
  - Single entry point for the infrastructure.
  - Configured with TLSv1.2 or TLSv1.3 on port 443.
  - Proxies requests to the WordPress container.
- **WordPress + php-fpm**:
  - Runs WordPress with php-fpm (no NGINX).
  - Connected to MariaDB.
  - Uses a volume for site files in `/home/mstasiak/data/wp`.
- **MariaDB**:
  - Database for WordPress.
  - Uses a volume for data in `/home/mstasiak/data/db`.
  - Includes two users: an admin (no `admin` in the name) and a standard user.
- **Docker Network**:
  - Connects containers for internal communication.
  - Use of `network: host`, `--link`, or `links:` is forbidden.
- **Volumes**:
  - Database volume: `/home/mstasiak/data/db`.
  - WordPress files volume: `/home/mstasiak/data/wp`.

### Domain Configuration
- Configure `/etc/hosts` on the host machine to point `mstasiak.42.fr` to the local IP (e.g., `127.0.0.1`).
  ```bash
  echo "127.0.0.1 mstasiak.42.fr" >> /etc/hosts
  ```
- Ensure the TLS certificate is properly configured for secure connections.

## Detailed Functionality
### Mandatory Part
- **NGINX**:
  - Built from the second-to-last stable version of Alpine or Debian.
  - Configures a secure web server with TLSv1.2 or TLSv1.3.
  - Acts as a reverse proxy to forward requests to WordPress.
- **WordPress + php-fpm**:
  - Installs and configures WordPress with php-fpm.
  - Connected to MariaDB via environment variables (e.g., `DB_HOST`, `DB_USER`).
  - Site files are persistent via a volume.
- **MariaDB**:
  - Relational database for WordPress.
  - Configures two users: an admin and a standard user.
  - Data is persistent via a volume.
- **Docker Compose**:
  - The `docker-compose.yml` file defines services, networks, and volumes.
  - Containers restart automatically on crash (`restart: always`).
  - Environment variables are managed via a `.env` file or Docker secrets.
- **Best Practices**:
  - Dockerfiles follow best practices (PID 1, no infinite loops like `tail -f` or `sleep infinity`).
  - Passwords are not hardcoded in Dockerfiles.
  - Images are built locally (no DockerHub usage, except for Alpine/Debian).

### Bonus Part
- **Redis Cache**: Caches WordPress data to improve performance.
- **FTP Server**: Provides access to the WordPress volume for file transfers.
- **Static Site**: A non-PHP website (e.g., HTML/CSS, Python Flask).
- **Adminer**: Web interface for managing the MariaDB database.
- **Custom Service**: A justified additional service (e.g., monitoring, backup).

### Makefile
The Makefile includes:
- `all`: Builds and starts containers via `docker-compose.yml`.
- `clean`: Stops and removes containers and images.
- `fclean`: Also removes volumes and persistent data.
- `re`: Rebuilds and restarts everything.
- `bonus`: Builds and starts bonus services.

## Error Handling
- Ensure containers handle errors correctly: missing configuration files, occupied ports, invalid TLS certificates.
- Verify Dockerfiles follow best practices (e.g., PID 1 management).
- Test edge cases: container crashes, missing environment variables.
- Volumes must be correctly mounted in `/home/mstasiak/data`.
- Containers must restart automatically on crash.

## Limitations
- The project must be executed in a virtual machine.
- Images must be built from the second-to-last stable version of Alpine or Debian.
- Use of `network: host`, `--link`, or `links:` is forbidden.
- Infinite loops (`tail -f`, `sleep infinity`, etc.) are prohibited.
- Passwords must not be hardcoded in Dockerfiles.
- The `latest` tag is forbidden for images.
- Bonuses are only evaluated if the mandatory part is perfect.

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**: April 2025 - April 2025

## Acknowledgments
Thanks to 42 school for this project, which allowed me to explore Docker, docker-compose, and multi-container infrastructure management while deepening my system administration and security skills.