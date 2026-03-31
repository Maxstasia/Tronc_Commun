SHELL := /bin/sh
NPM := npm
COMPOSE_FILE := docker-compose.yml

all: install build up dev-frontend

help:
	@echo "Available targets:"
	@echo "  make help          - Show this help"
	@echo "  make or make all   - Install dependencies and start frontend"
	@echo "  make install       - Install all workspace dependencies"
	@echo "  make dev           - Run backend and frontend in parallel"
	@echo "  make dev-backend   - Run NestJS backend in watch mode"
	@echo "  make dev-frontend  - Run React frontend (Vite)"
	@echo "  make build         - Build backend and frontend"
	@echo "  make clean         - Remove build artifacts"
	@echo "  make fclean        - Deep clean: build artifacts, deps, lockfiles, npm user cache"
	@echo "  make up            - Start Docker stack"
	@echo "  make down          - Stop Docker stack"
	@echo "  make logs          - Follow Docker logs"
	@echo "  make re            - Fclean and rebuild everything"

install:
	$(NPM) install

dev-backend:
	$(NPM) run dev:backend

dev-frontend:
	$(NPM) run dev:frontend

dev:
	@set -e; \
	trap 'kill 0' INT TERM EXIT; \
	$(NPM) run dev:backend & \
	$(NPM) run dev:frontend & \
	wait

build:
	$(NPM) run build

clean: down
	rm -rf backend/dist frontend/dist

fclean: clean
	rm -rf node_modules backend/node_modules frontend/node_modules
	rm -f package-lock.json backend/package-lock.json frontend/package-lock.json
	$(NPM) cache clean --force
	rm -rf ~/.npm/_cacache ~/.npm/_logs ~/.npm/_npx
	

require-compose:
	@test -f $(COMPOSE_FILE) || { echo "docker-compose.yml not found at project root."; exit 1; }

up: require-compose
	docker compose up --build -d

down: require-compose
	docker compose down

logs: require-compose
	docker compose logs -f

re: fclean all

.PHONY: all help install dev dev-backend dev-frontend build clean fclean require-compose up down logs re
