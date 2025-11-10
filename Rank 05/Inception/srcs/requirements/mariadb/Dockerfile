# inception/srcs/requirements/mariadb/Dockerfile
FROM debian:bookworm

# 1. Install MariaDB
RUN apt update && \
    apt upgrade -y && \
    apt install -y mariadb-server mariadb-client && \
    rm -rf /var/lib/apt/lists/*

# 2. Crée le user mysql (mais on reste root pour la config)
RUN useradd -r -s /bin/false mysql

# 3. Prépare les dossiers AVANT de changer d'user
RUN mkdir -p /var/run/mysqld /var/lib/mysql && \
    chown mysql:mysql /var/run/mysqld /var/lib/mysql && \
    chmod 750 /var/run/mysqld

# 4. Copie les fichiers
COPY ./conf/my.cnf /etc/mysql/my.cnf
COPY ./tools/init.sql /docker-entrypoint-initdb.d/init.sql

# 5. Expose le port
EXPOSE 3306

# 6. Change d'user JUSTE avant CMD
USER mysql

# 7. Démarre MariaDB (PID 1 = mysqld)
CMD ["mysqld", "--bind-address=0.0.0.0"]
