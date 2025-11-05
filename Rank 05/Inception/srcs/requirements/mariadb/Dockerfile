FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    mariadb-server \
    mariadb-client \
    && rm -rf /var/lib/apt/lists/*

# Copy configuration script
COPY tools/setup.sh /tmp/setup.sh

RUN chmod +x /tmp/setup.sh

# Expose MariaDB port
EXPOSE 3306

CMD ["/tmp/setup.sh"]

