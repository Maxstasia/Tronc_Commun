# inception/srcs/requirements/mariadb/Dockerfile
FROM debian:bookworm

# 1. Install MariaDB + envsubst
RUN apt update && \
    apt upgrade -y && \
    apt install -y mariadb-server mariadb-client gettext-base && \
	apt install -y vim curl && \
    rm -rf /var/lib/apt/lists/*

# 2. Prépare les dossiers
RUN mkdir -p /var/run/mysqld /var/lib/mysql /etc/mysql /docker-entrypoint-initdb /home/${USER}/data/db && \
    chown mysql:mysql /var/run/mysqld /var/lib/mysql /etc/mysql /docker-entrypoint-initdb && \
    chmod 755 /var/run/mysqld

# 3. Copie les fichiers
COPY ./conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
COPY ./tools/init.sql /docker-entrypoint-initdb/init.sql
COPY ./tools/setup.sh /usr/local/bin/setup.sh

# 4. Rend le script exécutable
RUN chmod +x /usr/local/bin/setup.sh

# 5. Expose le port
EXPOSE 3306

# 6. Change d'user JUSTE avant CMD
USER mysql

# 7. Démarre MariaDB avec le script de setup
CMD ["setup.sh"]
