#!/bin/bash

# Couleurs pour les logs
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}[MariaDB] Starting setup...${NC}"

# Fichier pour marquer que l'init a été faite
INIT_FLAG="/var/lib/mysql/.init_done"

# 1. Initialiser la base de données si elle n'existe pas
if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo -e "${GREEN}[MariaDB] Initializing database...${NC}"
    mysql_install_db --user=mysql --datadir=/var/lib/mysql
fi

# 2. Vérifier si la configuration initiale a déjà été faite
if [ -f "$INIT_FLAG" ]; then
    echo -e "${YELLOW}[MariaDB] Database already configured, skipping init...${NC}"
else
    # 3. Démarrer MariaDB temporairement en arrière-plan (skip-grant-tables pour init)
    echo -e "${GREEN}[MariaDB] Starting temporary server...${NC}"
    mysqld --user=mysql --datadir=/var/lib/mysql --skip-networking --skip-grant-tables &
    MYSQL_PID=$!

    # 4. Attendre que le serveur soit prêt
    echo -e "${GREEN}[MariaDB] Waiting for server to be ready...${NC}"
    for i in {30..0}; do
        if mysqladmin ping --silent 2>/dev/null; then
            break
        fi
        echo -n "."
        sleep 1
    done

    if [ "$i" = 0 ]; then
        echo -e "${RED}[MariaDB] Failed to start!${NC}"
        exit 1
    fi

    echo -e "${GREEN}[MariaDB] Server is ready!${NC}"

    # 5. Préparer et exécuter le script SQL avec substitution des variables
    echo -e "${GREEN}[MariaDB] Executing init script...${NC}"
    SQL_TEMP="/tmp/init_processed.sql"
    envsubst < /docker-entrypoint-initdb/init.sql > "$SQL_TEMP"
    
    # Debug: afficher le SQL généré
    echo -e "${YELLOW}[MariaDB] Generated SQL:${NC}"
    cat "$SQL_TEMP"
    
    # Exécuter le SQL (sans -u root car on utilise skip-grant-tables)
    mysql < "$SQL_TEMP"
    
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}[MariaDB] Init script executed successfully!${NC}"
        touch "$INIT_FLAG"
    else
        echo -e "${RED}[MariaDB] Failed to execute init script!${NC}"
        exit 1
    fi

    # 6. Arrêter le serveur temporaire
    echo -e "${GREEN}[MariaDB] Stopping temporary server...${NC}"
    mysqladmin shutdown
    wait $MYSQL_PID
fi

echo -e "${GREEN}[MariaDB] Setup complete! Starting production server...${NC}"

# 6. Démarrer le serveur en mode production (PID 1)
exec mysqld --user=mysql --bind-address=0.0.0.0
