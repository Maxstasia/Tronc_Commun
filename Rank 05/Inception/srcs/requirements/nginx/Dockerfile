# inception/srcs/requirements/nginx/Dockerfile
FROM debian:bookworm

ARG NGINX_HOST
ARG UID

# 1. Install nginx et openssl
RUN apt update && \
    apt upgrade -y && \
    apt install -y nginx OpenSSL && \
	apt install -y vim curl && \
	rm -rf /var/lib/apt/lists/* \
	openssl req -x509 -nodes -out /etc/nginx/ssl/inception.crt -keyout /etc/nginx/ssl/inception.key -subj "/C=FR/ST=IDF/L=Paris/O=42/OU=42/CN=${NGINX_HOST}/UID=${UID}"

# 2. Prépare les dossiers
RUN mkdir -p /etc/nginx/ssl /var/run/nginx && \
	chown -R www-data:www-data /var/run/nginx /var/www/html && \
	chmod 755 /var/run/nginx /var/www/html

# 3. Copie les fichiers
COPY ./conf/nginx.conf /etc/nginx/nginx.conf

# 4. Expose le port
EXPOSE 3306

# 5. Change d'user JUSTE avant CMD
USER mysql

# 6. Démarre MariaDB avec le script de setup
CMD ["nginx", "-g", "daemon off;"]
