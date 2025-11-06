FROM debian:bookworm

# Crée un user mysql dédié (PID 1 safe)
RUN useradd -r -s /bin/false mysql

# Install MariaDB
RUN apt update && \
    apt install -y mariadb-server mariadb-client && \
    rm -rf /var/lib/apt/lists/*


# Copie les fichiers
COPY ./conf/my.cnf /etc/mysql/my.cnf
COPY ./tools/init.sql /docker-entrypoint-initdb.d/init.sql

# Prépare les dossiers
RUN mkdir -p /var/run/mysqld /var/lib/mysql && \
    chown mysql:mysql /var/run/mysqld /var/lib/mysql

# Expose
EXPOSE 3306

# Démarre en user mysql
USER mysql
CMD ["mysqld", "--bind-address=0.0.0.0"]
