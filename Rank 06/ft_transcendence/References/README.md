# UNO - Transcendence 42

Implementation bootstrap for UNO (pre-2018 rules) with:

- NestJS backend (`backend`)
- React frontend (`frontend`)

## Quick start

### Makefile (recommended)

```bash
make install
make dev
```

Useful targets:

- `make dev-backend`
- `make dev-frontend`
- `make build`
- `make clean`
- `make docker-up`
- `make docker-logs`
- `make docker-down`

Docker quick start:

```bash
make docker-up
make docker-logs
make docker-down
```

### 1) Backend

```bash
cd backend
npm install
npm run start:dev
```

Backend runs on `http://localhost:3000` and Socket.IO namespace `/uno`.

### 2) Frontend

```bash
cd frontend
npm install
npm run dev
```

Frontend runs on `http://localhost:5173`.

### LAN / réseau 42

Le frontend est exposé en LAN (`0.0.0.0`).

- Depuis une autre machine du réseau 42, ouvre `http://IP_DE_LA_MACHINE:5173`.
- Le frontend utilise automatiquement `http://<hostname-client>:3000` pour le backend.
- Pour forcer une URL backend spécifique, crée `frontend/.env`:

```bash
VITE_BACKEND_URL=http://IP_DE_LA_MACHINE:3000
```

## Current scope

- Room creation and joining
- Minimal game start
- Basic turn progression and card play validation (value/color match)
- Real-time state sync through Socket.IO

## Next milestones

- Full action cards behavior (Skip/Reverse/Draw Two/Wild/Wild Draw Four)
- UNO call and penalties
- Challenge Wild Draw Four
- Stats/profile/leaderboard integration