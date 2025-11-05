FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    php7.4-fpm \
    php7.4-mysql \
    php7.4-mysqli \
    php7.4-curl \
    php7.4-gd \
    php7.4-intl \
    php7.4-mbstring \
    php7.4-soap \
    php7.4-xml \
    php7.4-xmlrpc \
    php7.4-zip \
    curl \
    mariadb-client \
    && rm -rf /var/lib/apt/lists/*

# Download WP-CLI
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x wp-cli.phar \
    && mv wp-cli.phar /usr/local/bin/wp

# Create directory for PHP-FPM
RUN mkdir -p /run/php

# Copy PHP-FPM configuration
COPY conf/www.conf /etc/php/7.4/fpm/pool.d/www.conf

# Copy setup script
COPY tools/setup.sh /tmp/setup.sh
RUN chmod +x /tmp/setup.sh

WORKDIR /var/www/html

EXPOSE 9000

CMD ["/tmp/setup.sh"]
