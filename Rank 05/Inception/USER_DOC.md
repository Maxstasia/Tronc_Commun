# User Documentation — Inception

This document explains how to use and manage the Inception WordPress stack as an end user or administrator.

---

## What services does this stack provide?

The Inception stack runs three services:

| Service | Role | Access |
|---|---|---|
| **NGINX** | HTTPS reverse proxy | Port 443 — entry point for all web traffic |
| **WordPress** | CMS / website | Via NGINX at `https://mstasiak.42.fr` |
| **MariaDB** | Database | Internal only — not accessible from outside |

All three services run in isolated Docker containers on the same internal network. Only NGINX is reachable from the outside world, through port 443 (HTTPS).

---

## Starting and stopping the project

### Start the project

From the project root directory:

```bash
make
```

This command will:
1. Add `mstasiak.42.fr` to your `/etc/hosts` if not already present.
2. Create the data directories on the host (`/home/mstasiak/data/db` and `/home/mstasiak/data/wordpress`).
3. Build the Docker images and start all containers in the background.

### Stop the project (keep data)

```bash
make down
```

Stops and removes the containers. Your data (database and WordPress files) is preserved on the host.

### Full cleanup (removes all data)

```bash
make fclean
```

Stops everything, removes all Docker resources, deletes the data directories, and removes the hosts entry. Use with caution — this deletes your WordPress site and database.

---

## Accessing the website and administration panel

### Website

Open your browser and go to:

```
https://mstasiak.42.fr
```

> The site uses a self-signed certificate. Your browser will show a security warning — this is expected. Click "Advanced" and proceed to the site.

### WordPress admin panel

```
https://mstasiak.42.fr/wp-admin
```

Log in with the administrator credentials (see section below).

---

## Locating and managing credentials

All credentials are stored in the file `srcs/.env` in the project directory. This file is never committed to Git.

### WordPress accounts

| Account | Variable in `.env` | Role |
|---|---|---|
| Administrator | `WP_ADMIN_USER` / `WP_ADMIN_PASS` | Full access to WordPress admin |
| Author | `WP_USER` / `WP_USER_PASS` | Can write and manage posts |

> The administrator username must **not** contain the word "admin" or "administrator" (42 project rule).

### Database accounts

| Account | Variable in `.env` | Role |
|---|---|---|
| DB admin | `DB_ADMIN` / `DB_ADMIN_PASS` | Full access to the WordPress database |
| DB user | `DB_USER` / `DB_PASS` | Read/write access to the WordPress database |
| DB root | `root` / `DB_ROOT_PASS` | MariaDB root (not used by WordPress) |

To change a password, update the `.env` file, then run `make fclean && make` to rebuild from scratch.

---

## Checking that services are running correctly

### Check container status

```bash
docker compose -f srcs/docker-compose.yml ps
```

All three containers (`mariadb`, `nginx`, `wordpress`) should show status `running` (or `healthy`).

### Check container logs

```bash
# Logs for all services
docker compose -f srcs/docker-compose.yml logs

# Logs for a specific service
docker compose -f srcs/docker-compose.yml logs mariadb
docker compose -f srcs/docker-compose.yml logs nginx
docker compose -f srcs/docker-compose.yml logs wordpress
```

### Check MariaDB health

```bash
docker exec mariadb mysqladmin ping -h localhost
```

Expected output: `mysqld is alive`

### Check that the website responds

```bash
curl -k https://mstasiak.42.fr
```

Expected: HTML output from WordPress (or a redirect to the site).

### Check that PHP-FPM is running inside the WordPress container

```bash
docker exec wordpress ps aux | grep php-fpm
```

You should see one master process and at least one worker.
