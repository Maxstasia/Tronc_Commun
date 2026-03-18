# Developer Documentation — Inception

This document explains how to set up, build, run, and maintain the Inception project from a developer's perspective.

---

## Project structure

```
.
├── Makefile
├── README.md
├── USER_DOC.md
├── DEV_DOC.md
└── srcs/
    ├── .env                          ← environment variables (never commit this)
    ├── docker-compose.yml
    └── requirements/
        ├── mariadb/
        │   ├── Dockerfile
        │   ├── conf/
        │   │   └── 50-server.cnf     ← MariaDB server config
        │   └── tools/
        │       ├── init.sql          ← DB/user initialisation script (template)
        │       └── setup.sh          ← entrypoint: init DB then start mysqld
        ├── nginx/
        │   ├── Dockerfile
        │   └── conf/
        │       └── nginx.conf        ← NGINX config (TLSv1.2/1.3, FastCGI proxy)
        └── wordpress/
            ├── Dockerfile
            └── conf/
                ├── www.conf          ← PHP-FPM pool config
                └── auto_config.sh   ← entrypoint: wp config + core install + php-fpm
```

---

## Prerequisites

- A Linux virtual machine (the subject requires this).
- Docker Engine ≥ 20.x
- Docker Compose plugin (`docker compose`, not `docker-compose`)
- `sudo` access for `/etc/hosts` and data directory creation.
- `make`
- Ports 443 free on the host.

---

## Setting up the environment from scratch

### 1. Clone the repository

```bash
git clone <your-repo-url>
cd <repo>/Rank\ 05/Inception
```

### 2. Create the `.env` file

Create `srcs/.env` with the following content (replace placeholder values):

```env
# Domain
NGINX_HOST=mstasiak.42.fr
NGINX_PORT=443
DOMAIN_NAME=mstasiak.42.fr

# System
UID=1000
USER=mstasiak

# MariaDB
DB_NAME=wordpress
DB_ROOT_PASS=change_me_root
DB_ADMIN=wp_admin_db
DB_ADMIN_PASS=change_me_admin
DB_USER=wp_user
DB_PASS=change_me_user

# WordPress
WP_TITLE=My Site
WP_ADMIN_USER=wp_superuser
WP_ADMIN_PASS=change_me_wp_admin
WP_ADMIN_EMAIL=admin@mstasiak.42.fr
WP_USER=wp_author
WP_USER_EMAIL=author@mstasiak.42.fr
WP_USER_PASS=change_me_wp_user
```

> Add `srcs/.env` to `.gitignore` immediately.

> The WordPress admin username must **not** contain "admin" or "administrator" — this is enforced by the 42 subject.

---

## Building and launching the project

### Full build and start

```bash
make
```

This runs:
1. `make hosts` — adds `127.0.0.1 mstasiak.42.fr` to `/etc/hosts` (requires sudo).
2. `make volumes` — creates `/home/mstasiak/data/db` and `/home/mstasiak/data/wordpress` on the host.
3. `docker compose -f ./srcs/docker-compose.yml up -d --build` — builds images and starts containers.

### Build only (no start)

```bash
docker compose -f srcs/docker-compose.yml build
```

### Start without rebuilding

```bash
docker compose -f srcs/docker-compose.yml up -d
```

---

## How each service is built

### MariaDB

**Dockerfile** (`requirements/mariadb/Dockerfile`):
- Base: `debian:bookworm`
- Installs: `mariadb-server`, `mariadb-client`, `gettext-base` (for `envsubst`)
- Copies: `50-server.cnf` (bind-address, socket, port config), `init.sql`, `setup.sh`
- Runs as user `mysql`

**Entrypoint** (`setup.sh`):
1. Runs `mysql_install_db` if the data directory is empty.
2. Starts a temporary `mysqld` with `--skip-grant-tables --skip-networking`.
3. Runs `envsubst` on `init.sql` to substitute `${DB_NAME}`, `${DB_ADMIN}`, etc.
4. Executes the processed SQL.
5. Shuts down the temporary server.
6. Re-starts `mysqld` properly with `exec mysqld --bind-address=0.0.0.0` (PID 1).

**`init.sql`** creates:
- The `${DB_NAME}` database.
- Two users: `${DB_ADMIN}` (full privileges) and `${DB_USER}` (SELECT/INSERT/UPDATE/DELETE).

### NGINX

**Dockerfile** (`requirements/nginx/Dockerfile`):
- Base: `debian:bookworm`
- Installs: `nginx`, `openssl`
- Generates a self-signed TLS certificate at build time using `openssl req -x509`.
- Copies: `nginx.conf`
- Starts with: `nginx -g 'daemon off;'` (PID 1)

**`nginx.conf`** key settings:
- Listens on port 443 with `ssl_protocols TLSv1.2 TLSv1.3`.
- Serves `/var/www/wordpress` as root.
- Proxies `.php` requests to `wordpress:9000` via FastCGI.

### WordPress

**Dockerfile** (`requirements/wordpress/Dockerfile`):
- Base: `debian:bookworm`
- Installs: `php`, `php-fpm`, `php-mysql`, `mariadb-client`, `wget`
- Downloads WordPress 6.0 and extracts it to `/var/www/wordpress`.
- Downloads WP-CLI and installs it as `/usr/local/bin/wp`.
- Copies: `www.conf` (PHP-FPM pool), `auto_config.sh`
- Entrypoint: `auto_config.sh`

**`auto_config.sh`**:
1. Waits for MariaDB to be ready (10-second sleep, then relies on `depends_on: mariadb: condition: service_healthy`).
2. If `wp-config.php` does not exist: runs `wp config create`, `wp core install`, `wp user create`.
3. Creates `/run/php` if needed.
4. Starts `php-fpm8.2 -F` in foreground (PID 1).

**`www.conf`** key settings:
- `listen = 0.0.0.0:9000` — PHP-FPM listens on TCP port 9000 (not a Unix socket).
- `clear_env = no` — allows PHP-FPM workers to access environment variables.

---

## Managing containers and volumes

### Useful commands

```bash
# View running containers and their health status
docker compose -f srcs/docker-compose.yml ps

# Follow logs for all services
docker compose -f srcs/docker-compose.yml logs -f

# Enter a running container
docker exec -it mariadb bash
docker exec -it nginx bash
docker exec -it wordpress bash

# Run a MySQL query
docker exec -it mariadb mysql -u root -p

# Run WP-CLI inside the WordPress container
docker exec -it wordpress wp user list --allow-root --path=/var/www/wordpress

# Restart a single service
docker compose -f srcs/docker-compose.yml restart wordpress

# Rebuild a single service image
docker compose -f srcs/docker-compose.yml build --no-cache wordpress
docker compose -f srcs/docker-compose.yml up -d wordpress
```

### Stopping services

```bash
# Stop containers (data preserved)
make down

# Stop + remove images, networks, volumes
make clean

# Full reset (data directories deleted)
make fclean
```

---

## Where data is stored and how it persists

### Volume locations on the host

| Volume name | Host path | Contains |
|---|---|---|
| `db_data` | `/home/mstasiak/data/db` | MariaDB data files (`/var/lib/mysql` inside the container) |
| `wordpress` | `/home/mstasiak/data/wordpress` | WordPress PHP files (`/var/www/wordpress` inside the container) |

These directories are created by `make volumes` before the containers start. They are mounted into the containers as Docker volumes configured with `driver: local` and `driver_opts` (`type: none`, `o: bind`).

### Persistence model

- **MariaDB** writes to `/var/lib/mysql` inside the container, which is backed by `db_data` on the host. The data survives `make down` and container restarts.
- **WordPress** files (including `wp-config.php`, themes, plugins, uploads) are written to `/var/www/wordpress` inside the container, backed by the `wordpress` volume.
- Running `make fclean` **deletes** both host directories and all data permanently.

### Checking volume contents from the host

```bash
ls /home/mstasiak/data/db/          # MariaDB files
ls /home/mstasiak/data/wordpress/   # WordPress files
```

---

## Known issues and limitations

- **`sleep 10` in `auto_config.sh`**: this is a temporary workaround to wait for MariaDB. The `depends_on: condition: service_healthy` in docker-compose.yml mitigates this, but a proper retry loop on `mysqladmin ping` would be more robust.
- **Self-signed certificate**: browsers will warn about the certificate. This is expected in a local development environment.
- **`debian:bookworm`**: as of writing, this is the current oldstable Debian release. The subject requires the *penultimate* stable release. If Debian 14 (Forky) is released before your evaluation, switch to `debian:trixie` in all three Dockerfiles.
- **WordPress healthcheck**: the container healthcheck uses `curl http://localhost/` which does not work against a PHP-FPM process (no HTTP server). This healthcheck will always fail; it should be replaced with something like `php-fpm8.2 -t` to test the PHP-FPM configuration.
