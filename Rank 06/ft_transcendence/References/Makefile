SHELL := /bin/sh
NPM := npm
COMPOSE_FILE := docker-compose.yml

.PHONY: help install dev dev-backend dev-frontend build clean require-compose docker-up docker-down docker-logs

help:
	@echo "Available targets:"
	@echo "  make install       - Install all workspace dependencies"
	@echo "  make dev           - Run backend and frontend in parallel"
	@echo "  make dev-backend   - Run NestJS backend in watch mode"
	@echo "  make dev-frontend  - Run React frontend (Vite)"
	@echo "  make build         - Build backend and frontend"
	@echo "  make clean         - Remove build artifacts"
	@echo "  make docker-up     - Start Docker stack"
	@echo "  make docker-down   - Stop Docker stack"
	@echo "  make docker-logs   - Follow Docker logs"

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

clean:
	rm -rf backend/dist frontend/dist

require-compose:
	@test -f $(COMPOSE_FILE) || { echo "docker-compose.yml not found at project root."; exit 1; }

docker-up: require-compose
	docker compose up --build -d

docker-down: require-compose
	docker compose down

docker-logs: require-compose
	docker compose logs -f
