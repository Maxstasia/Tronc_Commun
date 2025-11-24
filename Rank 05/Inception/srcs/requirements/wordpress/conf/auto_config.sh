#!/bin/bash

# Attendre que MariaDB soit prête
sleep 10

# Configuration de WordPress si wp-config.php n'existe pas
if [ ! -f /var/www/wordpress/wp-config.php ]; then
	wp config create	--allow-root \
						--dbname=$DB_NAME \
						--dbuser=$DB_USER \
						--dbpass=$DB_PASS \
						--dbhost=mariadb:3306 \
						--path='/var/www/wordpress'
fi

# Installation de WordPress si elle n'est pas déjà faite
if ! wp core is-installed --allow-root --path='/var/www/wordpress'; then
	wp core install		--allow-root \
						--url=$DOMAIN_NAME \
						--title="$WP_TITLE" \
						--admin_user=$WP_ADMIN_USER \
						--admin_password=$WP_ADMIN_PASS \
						--admin_email=$WP_ADMIN_EMAIL \
						--path='/var/www/wordpress'
fi

# Création du deuxième utilisateur s'il n'existe pas déjà
if ! wp user get $WP_USER --allow-root --path='/var/www/wordpress' > /dev/null 2>&1; then
	wp user create		--allow-root \
						$WP_USER \
						$WP_USER_EMAIL \
						--user_pass=$WP_USER_PASS \
						--role=author \
						--path='/var/www/wordpress'
fi

# Créer le dossier /run/php s'il n'existe pas
if [ ! -d /run/php ]; then
	mkdir -p /run/php
fi

# Lancer PHP-FPM en mode foreground
/usr/sbin/php-fpm7.3 -F
