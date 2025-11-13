-- Réactiver le système de permissions
FLUSH PRIVILEGES;

-- Configuration du root user
ALTER USER 'root'@'localhost' IDENTIFIED BY '${DB_ROOT_PASS}';

-- Création de la base de données
CREATE DATABASE IF NOT EXISTS ${DB_NAME};

-- Création des utilisateurs
CREATE USER IF NOT EXISTS '${DB_ADMIN}'@'%' IDENTIFIED BY '${DB_ADMIN_PASS}';
CREATE USER IF NOT EXISTS '${DB_USER}'@'%' IDENTIFIED BY '${DB_PASS}';

-- Attribution des privilèges
GRANT ALL PRIVILEGES ON ${DB_NAME}.* TO '${DB_ADMIN}'@'%';
GRANT SELECT, INSERT, UPDATE, DELETE ON ${DB_NAME}.* TO '${DB_USER}'@'%';

-- Application des changements
FLUSH PRIVILEGES;
