*This project has been created as part of the 42 Common Core by mstasiak.*

# Inception

## Description

Inception is a system administration project from the 42 Common Core. The goal is to set up a small but complete web infrastructure using Docker and Docker Compose, entirely inside a virtual machine.

The stack consists of three services running in dedicated containers:

- **NGINX** — the sole entry point, serving HTTPS on port 443 with TLSv1.2/TLSv1.3 and acting as a reverse proxy toward WordPress.
- **WordPress + PHP-FPM** — the CMS, running without any embedded web server, communicating with NGINX via FastCGI on port 9000.
- **MariaDB** — the relational database backend for WordPress.

All data is persisted through two Docker named volumes: one for the WordPress files, one for the database. The services communicate through a dedicated Docker bridge network called `inception`.

---

## Project description

### Why Docker instead of a VM?

| Aspect | Virtual Machine | Docker |
|---|---|---|
| Isolation | Full OS-level isolation | Process-level isolation via namespaces |
| Weight | Heavy (GB, full OS) | Lightweight (MB, shares host kernel) |
| Boot time | Minutes | Milliseconds |
| Portability | Depends on hypervisor | Runs anywhere Docker is installed |
| Use case | Full OS needed | Microservices, reproducible environments |

Docker is chosen here because each service is simple and stateless enough to benefit from containerisation without the overhead of a full VM.

### Secrets vs Environment Variables

| | Secrets | Environment Variables |
|---|---|---|
| Storage | Mounted as a file in `/run/secrets/` | Passed as plain text to the process |
| Security | Not visible in `docker inspect` or history | Visible in `docker inspect` |
| Use case | Passwords, API keys | Non-sensitive config (ports, hostnames) |
| Defined in | `secrets:` block in docker-compose.yml | `.env` file or `environment:` block |

In this project, credentials are stored in a `.env` file (not committed to Git) and injected as environment variables. Docker secrets would be the more secure approach for production.

### Docker Network vs Host Network

| | Docker Network (bridge) | Host Network |
|---|---|---|
| Isolation | Containers have their own IP space | Containers share the host's network stack |
| Communication | Via service name (DNS) | Via localhost |
| Security | Better isolation between services | No isolation — any port conflict is fatal |
| Forbidden by subject | No | **Yes** (`network: host` is prohibited) |

This project uses a custom bridge network named `inception`. Services can reach each other by container name (e.g., `mariadb:3306`).

### Docker Volumes vs Bind Mounts

| | Docker Named Volumes | Bind Mounts |
|---|---|---|
| Managed by | Docker engine | Host filesystem directly |
| Location | Docker's internal storage area | Any path on the host |
| Portability | High | Low (depends on host paths) |
| Performance | Optimised by Docker | Depends on the host FS |
| Subject rule | **Required** for DB and WordPress data | **Forbidden** for the two main volumes |

The two main volumes (`db_data` and `wordpress`) use `driver: local` with `driver_opts` to bind data to `/home/mstasiak/data/` on the host, satisfying both the named-volume requirement and the location requirement.

### Design choices

- Base image: `debian:bookworm` for all services (penultimate stable Debian as of project writing).
- No password in any Dockerfile — all credentials come from `.env`.
- NGINX generates a self-signed TLS certificate at build time using `openssl`.
- MariaDB initialises via a `setup.sh` script that runs `envsubst` on `init.sql` to substitute environment variables before executing SQL.
- WordPress is configured via WP-CLI in `auto_config.sh`.
- All containers use `restart: always` and have `depends_on` with healthchecks.

---

## Instructions

### Prerequisites

- A Linux virtual machine with Docker and Docker Compose installed.
- `sudo` access (needed for `/etc/hosts` modification and data directory creation).
- No service already running on port 443.

### Environment setup

Create the file `srcs/.env` at the root of the `srcs/` directory. It must contain (adapt values to your setup):

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
DB_ROOT_PASS=your_root_password
DB_ADMIN=wp_admin_db
DB_ADMIN_PASS=your_admin_db_password
DB_USER=wp_user
DB_PASS=your_user_password

# WordPress
WP_TITLE=My Inception Site
WP_ADMIN_USER=wp_superuser
WP_ADMIN_PASS=your_wp_admin_password
WP_ADMIN_EMAIL=admin@mstasiak.42.fr
WP_USER=wp_author
WP_USER_EMAIL=author@mstasiak.42.fr
WP_USER_PASS=your_wp_user_password
```

> **Important:** never commit `.env` to Git. Add it to `.gitignore`.

### Build and run

From the project root:

```bash
make        # builds images, creates volumes, adds hosts entry, starts containers
make down   # stops and removes containers
make clean  # stops containers and removes all Docker resources
make fclean # full clean + removes data directories and hosts entry
make re     # fclean + all
```

### Access

Once running, open your browser at: `https://mstasiak.42.fr`

The WordPress admin panel is at: `https://mstasiak.42.fr/wp-admin`

---

## Resources

### Documentation

- [Docker official documentation](https://docs.docker.com/)
- [Docker Compose file reference](https://docs.docker.com/compose/compose-file/)
- [NGINX documentation](https://nginx.org/en/docs/)
- [MariaDB documentation](https://mariadb.com/kb/en/)
- [PHP-FPM configuration](https://www.php.net/manual/en/install.fpm.configuration.php)
- [WP-CLI documentation](https://wp-cli.org/)
- [OpenSSL self-signed certificate](https://www.openssl.org/docs/man1.1.1/man1/req.html)
- [Best practices for Dockerfiles](https://docs.docker.com/develop/develop-images/dockerfile_best-practices/)
- [PID 1 and signal handling in containers](https://cloud.google.com/architecture/best-practices-for-building-containers#signal-handling)

### Articles

- [Understanding Docker volumes vs bind mounts](https://docs.docker.com/storage/volumes/)
- [TLS/SSL in NGINX](https://nginx.org/en/docs/http/configuring_https_servers.html)
- [FastCGI and PHP-FPM explained](https://www.digitalocean.com/community/tutorials/understanding-and-implementing-fastcgi-proxying-in-nginx)

### AI usage

AI was used during this project for the following tasks:

- **Debugging**: identifying configuration errors in `nginx.conf`, `setup.sh`, and `docker-compose.yml`.
- **Shell scripting**: reviewing the logic of `auto_config.sh` for idempotency.
- **Documentation**: generating drafts of README.md, USER_DOC.md, and DEV_DOC.md, which were then reviewed and corrected manually.

All AI-generated content was reviewed, tested, and understood before inclusion in the project.
