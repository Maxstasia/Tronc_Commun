#!/bin/bash

# Wait for MariaDB to be ready
while ! mariadb -h mariadb -u ${MYSQL_USER} -p${MYSQL_PASSWORD} -e "SELECT 1" >/dev/null 2>&1; do
    echo "Waiting for MariaDB to be ready..."
    sleep 3
done

echo "MariaDB is ready!"

# Change to WordPress directory
cd /var/www/html

# Download WordPress if not already present
if [ ! -f "wp-config.php" ]; then
    echo "Downloading WordPress..."
    wp core download --allow-root
    
    echo "Creating wp-config.php..."
    wp config create \
        --dbname=${MYSQL_DATABASE} \
        --dbuser=${MYSQL_USER} \
        --dbpass=${MYSQL_PASSWORD} \
        --dbhost=mariadb \
        --allow-root
    
    echo "Installing WordPress..."
    wp core install \
        --url=${DOMAIN_NAME} \
        --title="${WP_TITLE}" \
        --admin_user=${WP_ADMIN_USER} \
        --admin_password=${WP_ADMIN_PASSWORD} \
        --admin_email=${WP_ADMIN_EMAIL} \
        --allow-root
    
    echo "Creating WordPress user..."
    wp user create \
        ${WP_USER} \
        ${WP_USER_EMAIL} \
        --role=author \
        --user_pass=${WP_USER_PASSWORD} \
        --allow-root
    
    echo "WordPress installation completed!"
else
    echo "WordPress already installed, skipping setup."
fi

# Set proper permissions
chown -R www-data:www-data /var/www/html
chmod -R 755 /var/www/html

# Start PHP-FPM in foreground
exec php-fpm7.4 -F
