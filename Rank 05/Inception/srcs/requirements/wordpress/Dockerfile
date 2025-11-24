# inception/srcs/requirements/wordpress/Dockerfile
FROM debian:bookworm

# 1. Install WordPress et dépendances
RUN apt update && \
	apt upgrade -y && \
	apt-get -y install wget php7.3 php-fpm php-mysql mariadb-client && \
	rm -rf /var/lib/apt/lists/*

# 2. Télécharge et décompresse WordPress
RUN wget https://fr.wordpress.org/wordpress-6.0-fr_FR.tar.gz -P /var/www
RUN cd /var/www && tar -xzf wordpress-6.0-fr_FR.tar.gz && rm wordpress-6.0-fr_FR.tar.gz
RUN chown -R root:root /var/www/wordpress

# 3. Copie les fichiers de configuration
COPY ./conf/www.conf /etc/php/7.3/fpm/pool.d/www.conf

# 4. Installe WP-CLI
RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
RUN chmod +x wp-cli.phar
RUN mv wp-cli.phar /usr/local/bin/wp
COPY conf/auto_config.sh /usr/local/bin/auto_config.sh
RUN chmod +x /usr/local/bin/auto_config.sh
ENTRYPOINT ["/usr/local/bin/auto_config.sh"]

# 5. Crée les dossiers nécessaires
RUN mkdir -p /var/run/php

# 6. Expose le port
EXPOSE 9000

# 7. Démarre PHP-FPM
CMD ["usr/sbin/php-fpm7.3", "-F"]
