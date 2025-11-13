# inception/srcs/requirements/mariadb/Dockerfile
FROM debian:bookworm

# 1. Install MariaDB
RUN apt update && \
    apt upgrade -y && \
    apt install -y mariadb-server mariadb-client && \
    rm -rf /var/lib/apt/lists/*

# 2. Prépare les dossiers
RUN mkdir -p /var/run/mysqld /var/lib/mysql /etc/mysql /docker-entrypoint-initdb && \
    chown mysql:mysql /var/run/mysqld /var/lib/mysql /etc/mysql /docker-entrypoint-initdb && \
    chmod 755 /var/run/mysqld

# 3. Copie les fichiers
COPY ./conf/my.cnf /etc/mysql/my.cnf
COPY ./tools/init.sql /docker-entrypoint-initdb/init.sql

# 4. Expose le port
EXPOSE 3306

# 5. Change d'user JUSTE avant CMD
USER mysql

# 6. Démarre MariaDB (PID 1 = mysqld)
CMD ["mysqld", "--bind-address=0.0.0.0"]
