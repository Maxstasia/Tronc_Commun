# Webserv - README

---

## Description
Webserv est un projet réalisé dans le cadre du cursus de l’école 42, visant à créer un serveur HTTP en **C++ 98**. Ce projet permet de comprendre les rouages du protocole HTTP, qui est à la base de la communication sur le Web. Le serveur `webserv` doit être capable de gérer des requêtes HTTP (GET, POST, DELETE), de servir des sites statiques, de gérer des CGI, et de répondre aux exigences d’un navigateur web moderne. Le programme est configuré via un fichier de configuration inspiré de NGINX, et il utilise une approche non-bloquante pour gérer les entrées/sorties.

L’objectif est de maîtriser les concepts suivants :
- Programmation en C++ 98 avec gestion non-bloquante des sockets.
- Implémentation du protocole HTTP (version 1.1).
- Parsing et validation d’un fichier de configuration.
- Gestion des requêtes HTTP (GET, POST, DELETE) et des CGI.
- Support des fonctionnalités bonus comme les cookies et la gestion de sessions.

## Structure du projet
Le projet est organisé comme suit :
- **Dossier principal** : Contient les fichiers sources (*.cpp, *.hpp), le Makefile, et les fichiers de configuration.
- **Dossier config** : Contient les fichiers de configuration (*.conf) pour tester le serveur.
- **Dossier www** : Contient les fichiers statiques pour le site web (HTML, CSS, images, etc.).
- **Dossier cgi-bin** : Contient les scripts CGI (ex. : PHP, Python).
- **Dossier tests** : Contient des scripts de test (ex. : en Python ou Go) pour valider le fonctionnement du serveur.

Les fichiers clés incluent :
- **Sources C++** : Fichiers pour la gestion des sockets, le parsing des requêtes, et l’exécution des CGI.
- **Makefile** : Pour compiler le programme avec les flags `-Wall`, `-Wextra`, `-Werror`, et `-std=c++98`.
- **Fichiers de configuration** : Fichiers *.conf définissant les ports, hôtes, routes, et autres paramètres.

## Prérequis
- Un environnement Linux/Unix (ou macOS avec ajustements pour `fcntl`).
- Compilateur C++ compatible avec le standard C++ 98 (ex. : g++).
- Connaissances de base en réseau (sockets, protocole HTTP).
- Familiarité avec les concepts de programmation non-bloquante (poll, select, epoll, ou kqueue).
- Connaissance du protocole HTTP/1.1 (RFC 2616 recommandé).

## Installation
1. **Cloner le dépôt Git** :
   ```bash
   git clone <votre-dépôt-git>
   cd webserv
   ```
2. **Compiler le programme** :
   ```bash
   make
   ```
   Produit l’exécutable `webserv`.
3. **Nettoyer les fichiers objets** :
   ```bash
   make clean
   ```
4. **Supprimer l’exécutable** :
   ```bash
   make fclean
   ```
5. **Recompiler tout** :
   ```bash
   make re
   ```

## Utilisation
### Commandes principales
1. **Lancer le serveur** :
   ```bash
   ./webserv [fichier_de_configuration]
   ```
   Exemple :
   ```bash
   ./webserv config/default.conf
   ```
   - `[fichier_de_configuration]` : Fichier *.conf définissant les paramètres du serveur (ports, routes, etc.).
   - Si aucun fichier n’est spécifié, un chemin par défaut peut être utilisé.
2. **Accéder au serveur** :
   - Ouvrez un navigateur et accédez à `http://localhost:<port>` (remplacez `<port>` par celui défini dans le fichier de configuration).
   - Exemple : `http://localhost:8080`.
3. **Tester avec telnet** :
   ```bash
   telnet localhost 8080
   ```
   Puis envoyez une requête HTTP manuelle, par exemple :
   ```http
   GET /index.html HTTP/1.1
   Host: localhost
   ```

### Exemple de fichier de configuration
```plaintext
server {
    listen 8080;
    server_name localhost;
    root ./www;
    index index.html;
    client_max_body_size 1000000;
    error_page 404 ./errors/404.html;

    location / {
        methods GET POST DELETE;
        autoindex on;
    }

    location /upload {
        methods POST;
        upload_dir ./uploads;
    }

    location /cgi-bin {
        cgi_path /usr/bin/php-cgi;
    }
}
```
- **listen** : Port d’écoute (ex. : 8080).
- **server_name** : Nom du serveur (ex. : localhost).
- **root** : Répertoire racine pour les fichiers statiques.
- **index** : Fichier par défaut pour les répertoires.
- **client_max_body_size** : Taille maximale des requêtes client.
- **error_page** : Page d’erreur par défaut.
- **location** : Définit les routes avec méthodes HTTP, autoindex, répertoire d’upload, ou CGI.

## Fonctionnement détaillé
### Partie obligatoire
- **Serveur HTTP** :
  - Implémenté en C++ 98, compatible avec HTTP/1.1.
  - Utilise une approche non-bloquante avec `poll()` (ou équivalent : `select`, `epoll`, `kqueue`) pour gérer les entrées/sorties.
  - Gère les sockets pour écouter les connexions (`socket`, `bind`, `listen`, `accept`).
  - Supporte les méthodes HTTP GET, POST, et DELETE.
- **Gestion des requêtes** :
  - Parse les requêtes HTTP pour extraire la méthode, l’URL, les en-têtes, et le corps.
  - Gère les requêtes chunked (déchunkage pour CGI).
  - Fournit des réponses avec des codes d’état HTTP précis (ex. : 200, 404, 500).
- **Fichier de configuration** :
  - Parse un fichier *.conf pour configurer les ports, hôtes, routes, et autres paramètres.
  - Supporte plusieurs serveurs (écoute sur plusieurs ports) avec un serveur par défaut par hôte:port.
  - Gère les pages d’erreur par défaut et la taille maximale des requêtes client.
- **CGI** :
  - Supporte l’exécution de scripts CGI (ex. : php-cgi, Python) avec `PATH_INFO` pour les chemins relatifs.
  - Appelle le CGI avec le fichier demandé comme premier argument.
  - Gère les requêtes POST et GET pour les CGI.
- **Fichiers statiques** :
  - Sert des sites web statiques (HTML, CSS, images) à partir du répertoire racine.
  - Supporte le listage de répertoires (`autoindex`).
- **Upload de fichiers** :
  - Gère les requêtes POST pour l’upload de fichiers vers un répertoire configuré.
- **Gestion des erreurs** :
  - Fournit des pages d’erreur par défaut si aucune n’est spécifiée.
  - Gère les déconnexions client sans bloquer.
  - Évite les crashs (ex. : segmentation fault, out-of-memory).

### Partie bonus
- **Cookies et gestion de sessions** :
  - Implémente le support des cookies pour maintenir des sessions utilisateur.
  - Fournit des exemples simples de gestion de sessions.
- **Support de multiples CGI** :
  - Gère plusieurs types de CGI (ex. : PHP, Python, Perl) avec différentes extensions.

### Makefile
Le Makefile inclut les règles suivantes :
- `all` : Compile le programme `webserv`.
- `clean` : Supprime les fichiers objets.
- `fclean` : Supprime les fichiers objets et l’exécutable.
- `re` : Recompile tout.

## Gestion des erreurs
- Vérifiez que le serveur gère correctement les erreurs : requêtes malformées, fichiers introuvables, déconnexions client.
- Assurez-vous que le code respecte le standard C++ 98 (vérifié avec `-std=c++98`).
- Testez avec des cas limites : requêtes volumineuses, connexions multiples, CGI invalides.
- Les opérations de lecture/écriture doivent toujours passer par `poll()` (ou équivalent).
- Les ressources (sockets, fichiers) doivent être correctement fermées.
- Testez la compatibilité avec un navigateur web (ex. : Firefox, Chrome) et comparez avec NGINX.

## Limitations
- Le programme doit être écrit en C++ 98.
- Les bibliothèques externes et Boost sont interdites.
- Les fonctions autorisées incluent : `execve`, `pipe`, `strerror`, `gai_strerror`, `errno`, `dup`, `dup2`, `fork`, `socketpair`, `htons`, `htonl`, `ntohs`, `ntohl`, `select`, `poll`, `epoll`, `kqueue`, `socket`, `accept`, `listen`, `send`, `recv`, `chdir`, `bind`, `connect`, `getaddrinfo`, `freeaddrinfo`, `setsockopt`, `getsockname`, `getprotobyname`, `fcntl` (sur macOS avec `F_SETFL`, `O_NONBLOCK`, `FD_CLOEXEC`), `close`, `read`, `write`, `waitpid`, `kill`, `signal`, `access`, `stat`, `open`, `opendir`, `readdir`, `closedir`.
- `fork` est interdit sauf pour les CGI.
- Les opérations de lecture/écriture sans `poll()` (ou équivalent) entraînent une note de 0.
- Le serveur doit rester disponible sous stress (testez avec des outils comme `siege` ou scripts personnalisés).

---

## Auteur
- **Nom** : mstasiak
- **Email** : mstasiak@student.42.fr
- **Date** : Mai 2025 - Mai 2025

## Remerciements
Merci à l’école 42 pour ce projet qui m’a permis d’explorer le protocole HTTP, la programmation réseau en C++ 98, et la gestion non-bloquante des sockets, tout en développant un serveur web robuste et fonctionnel.

---

# Webserv - README

## Description
Webserv is a project developed as part of the 42 school curriculum, aimed at creating an HTTP server in **C++ 98**. This project helps understand the intricacies of the HTTP protocol, the foundation of web communication. The `webserv` server must handle HTTP requests (GET, POST, DELETE), serve static websites, manage CGIs, and meet the requirements of modern web browsers. The program is configured via a configuration file inspired by NGINX and uses a non-blocking approach for I/O operations.

The goal is to master the following concepts:
- Programming in C++ 98 with non-blocking socket management.
- Implementing the HTTP/1.1 protocol.
- Parsing and validating a configuration file.
- Handling HTTP requests (GET, POST, DELETE) and CGIs.
- Supporting bonus features like cookies and session management.

## Project Structure
The project is organized as follows:
- **Main Directory**: Contains source files (*.cpp, *.hpp), the Makefile, and configuration files.
- **config Folder**: Contains configuration files (*.conf) for testing the server.
- **www Folder**: Contains static website files (HTML, CSS, images, etc.).
- **cgi-bin Folder**: Contains CGI scripts (e.g., PHP, Python).
- **tests Folder**: Contains test scripts (e.g., in Python or Go) to validate server functionality.

Key files include:
- **C++ Source Files**: Files for socket management, request parsing, and CGI execution.
- **Makefile**: Compiles the program with `-Wall`, `-Wextra`, `-Werror`, and `-std=c++98` flags.
- **Configuration Files**: *.conf files defining ports, hosts, routes, and other settings.

## Prerequisites
- A Linux/Unix environment (or macOS with adjustments for `fcntl`).
- C++ compiler compatible with C++ 98 (e.g., g++).
- Basic knowledge of networking (sockets, HTTP protocol).
- Familiarity with non-blocking programming (poll, select, epoll, or kqueue).
- Understanding of the HTTP/1.1 protocol (RFC 2616 recommended).

## Installation
1. **Clone the Git repository**:
   ```bash
   git clone <your-git-repository>
   cd webserv
   ```
2. **Compile the program**:
   ```bash
   make
   ```
   Produces the `webserv` executable.
3. **Clean object files**:
   ```bash
   make clean
   ```
4. **Remove the executable**:
   ```bash
   make fclean
   ```
5. **Recompile everything**:
   ```bash
   make re
   ```

## Usage
### Key Commands
1. **Start the server**:
   ```bash
   ./webserv [configuration_file]
   ```
   Example:
   ```bash
   ./webserv config/default.conf
   ```
   - `[configuration_file]`: *.conf file defining server parameters (ports, routes, etc.).
   - If no file is specified, a default path can be used.
2. **Access the server**:
   - Open a browser and navigate to `http://localhost:<port>` (replace `<port>` with the one defined in the configuration file).
   - Example: `http://localhost:8080`.
3. **Test with telnet**:
   ```bash
   telnet localhost 8080
   ```
   Then send a manual HTTP request, for example:
   ```http
   GET /index.html HTTP/1.1
   Host: localhost
   ```

### Example Configuration File
```plaintext
server {
    listen 8080;
    server_name localhost;
    root ./www;
    index index.html;
    client_max_body_size 1000000;
    error_page 404 ./errors/404.html;

    location / {
        methods GET POST DELETE;
        autoindex on;
    }

    location /upload {
        methods POST;
        upload_dir ./uploads;
    }

    location /cgi-bin {
        cgi_path /usr/bin/php-cgi;
    }
}
```
- **listen**: Listening port (e.g., 8080).
- **server_name**: Server name (e.g., localhost).
- **root**: Root directory for static files.
- **index**: Default file for directories.
- **client_max_body_size**: Maximum client request size.
- **error_page**: Default error page.
- **location**: Defines routes with HTTP methods, autoindex, upload directory, or CGI.

## Detailed Functionality
### Mandatory Part
- **HTTP Server**:
  - Implemented in C++ 98, compatible with HTTP/1.1.
  - Uses a non-blocking approach with `poll()` (or equivalent: `select`, `epoll`, `kqueue`) for I/O operations.
  - Manages sockets for listening to connections (`socket`, `bind`, `listen`, `accept`).
  - Supports HTTP methods GET, POST, and DELETE.
- **Request Handling**:
  - Parses HTTP requests to extract method, URL, headers, and body.
  - Handles chunked requests (unchunking for CGI).
  - Provides responses with accurate HTTP status codes (e.g., 200, 404, 500).
- **Configuration File**:
  - Parses a *.conf file to configure ports, hosts, routes, and other settings.
  - Supports multiple servers (listening on multiple ports) with a default server per host:port.
  - Manages default error pages and client request size limits.
- **CGI**:
  - Supports execution of CGI scripts (e.g., php-cgi, Python) with `PATH_INFO` for relative paths.
  - Calls the CGI with the requested file as the first argument.
  - Handles POST and GET methods for CGIs.
- **Static Files**:
  - Serves static websites (HTML, CSS, images) from the root directory.
  - Supports directory listing (`autoindex`).
- **File Upload**:
  - Handles POST requests for file uploads to a configured directory.
- **Error Handling**:
  - Provides default error pages if none are specified.
  - Manages client disconnections without blocking.
  - Avoids crashes (e.g., segmentation fault, out-of-memory).

### Bonus Part
- **Cookies and Session Management**:
  - Implements cookie support for maintaining user sessions.
  - Provides simple session management examples.
- **Multiple CGI Support**:
  - Handles multiple CGI types (e.g., PHP, Python, Perl) with different extensions.

### Makefile
The Makefile includes:
- `all`: Compiles the `webserv` program.
- `clean`: Removes object files.
- `fclean`: Removes object files and the executable.
- `re`: Recompiles everything.

## Error Handling
- Ensure the server handles errors correctly: malformed requests, missing files, client disconnections.
- Verify code compliance with C++ 98 (checked with `-std=c++98`).
- Test edge cases: large requests, multiple connections, invalid CGIs.
- All read/write operations must go through `poll()` (or equivalent).
- Resources (sockets, files) must be properly closed.
- Test compatibility with a web browser (e.g., Firefox, Chrome) and compare with NGINX.

## Limitations
- The program must be written in C++ 98.
- External libraries and Boost are forbidden.
- Authorized functions include: `execve`, `pipe`, `strerror`, `gai_strerror`, `errno`, `dup`, `dup2`, `fork`, `socketpair`, `htons`, `htonl`, `ntohs`, `ntohl`, `select`, `poll`, `epoll`, `kqueue`, `socket`, `accept`, `listen`, `send`, `recv`, `chdir`, `bind`, `connect`, `getaddrinfo`, `freeaddrinfo`, `setsockopt`, `getsockname`, `getprotobyname`, `fcntl` (on macOS with `F_SETFL`, `O_NONBLOCK`, `FD_CLOEXEC`), `close`, `read`, `write`, `waitpid`, `kill`, `signal`, `access`, `stat`, `open`, `opendir`, `readdir`, `closedir`.
- `fork` is forbidden except for CGIs.
- Read/write operations without `poll()` (or equivalent) result in a grade of 0.
- The server must remain available under stress (test with tools like `siege` or custom scripts).

---

## Author
- **Name**: mstasiak
- **Email**: mstasiak@student.42.fr
- **Date**: May 2025 - May 2025

## Acknowledgments
Thanks to 42 school for this project, which allowed me to explore the HTTP protocol, C++ 98 network programming, and non-blocking socket management while building a robust and functional web server.