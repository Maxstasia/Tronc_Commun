#!/bin/bash

# Start MariaDB service in background
service mariadb start

# Wait for MariaDB to be ready
sleep 5

# Check if database already exists
if [ ! -d "/var/lib/mysql/${MYSQL_DATABASE}" ]; then
    echo "Creating database and users..."
    
    # Create database and users
    mariadb -u root << EOF
CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
FLUSH PRIVILEGES;
EOF

    echo "Database created successfully!"
else
    echo "Database already exists, skipping creation."
fi

# Stop MariaDB to restart it in foreground
service mariadb stop

# Start MariaDB in foreground
exec mysqld --bind-address=0.0.0.0
