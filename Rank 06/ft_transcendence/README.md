# ft_transcendence

## Description
Ce dépôt documente l’état actuel du projet **ft_transcendence** tel qu’implémenté dans la base de référence :

- Jeu principal : **UNO** (règles **pré-2018**)
- Backend : **NestJS** + **Socket.IO**
- Frontend : **React + TypeScript + Vite**
- Orchestration : **npm workspaces**, **Makefile**, **Docker Compose**

L’objectif actuel est d’avoir une base fonctionnelle en temps réel pour la partie gameplay, avant l’extension vers les autres briques de Transcendence.

## État actuel (scope)
Les fonctionnalités déjà en place :

- Création de room
- Rejoindre une room
- Démarrage minimal d’une partie
- Progression des tours
- Validation basique des cartes (match couleur/valeur)
- Synchronisation temps réel de l’état via Socket.IO

## Stack technique

### Backend (`backend/`)
- NestJS
- WebSocket Gateway Socket.IO (namespace UNO)
- Scripts : `start:dev`, `build`, `start`
- Port : `3000`

### Frontend (`frontend/`)
- React 18 + TypeScript
- Vite (exposé en LAN)
- `socket.io-client`
- Scripts : `dev`, `build`, `preview`
- Port : `5173`

## Arborescence
```text
TODO tree à la fin du projet
```

## Prérequis
- Linux/macOS
- Docker + Docker Compose

## Installation
Depuis la racine du projet :

```bash
make install
```

Ou manuellement :

```bash
npm install
```

## Lancement en développement

### Méthode recommandée
```bash
make dev
```

### Cibles utiles
```bash
make dev-backend
make dev-frontend
make build
make clean
make fclean
```

## Lancement Docker

```bash
make docker-up
make docker-logs
make docker-down
```

Services exposés :
- Frontend : `http://localhost:5173`
- Backend : `http://localhost:3000`

## Lancement du projet

```bash
make
```


## Réseau / LAN (42)
Le frontend est lancé avec `--host 0.0.0.0`.

- Depuis une autre machine : `http://IP_DE_LA_MACHINE:5173`
- Pour forcer l’URL backend, créer `frontend/.env` :

```bash
VITE_BACKEND_URL=http://IP_DE_LA_MACHINE:3000
```

## Roadmap courte
Prochaines évolutions prévues :

- Cartes actions complètes (Skip, Reverse, Draw Two, Wild, Wild Draw Four)
- Appel UNO + pénalités
- Challenge Wild Draw Four
- Intégration stats/profil/leaderboard

## Commandes Makefile
- `make` / `make all` : install + lancement frontend
- `make install` : installe les dépendances workspace
- `make dev` : backend + frontend en parallèle
- `make build` : build backend + frontend
- `make clean` : supprime `backend/dist` et `frontend/dist`
- `make fclean` : `clean` + suppression `node_modules`
- `make re` : rebuild complet

## Notes
- Cette version décrit l’implémentation actuelle **UNO** de référence.
- Elle ne reflète pas encore l’intégralité des modules finaux de ft_transcendence.
