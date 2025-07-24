# Born2beRoot - README

---

## Description
Born2beRoot est un projet réalisé dans le cadre du cursus de l'école 42. Il vise à initier les étudiants à l'administration système en créant une machine virtuelle avec un système d'exploitation (Debian ou Rocky Linux) configuré selon des règles strictes. Ce projet permet de découvrir la virtualisation, la gestion des partitions, la configuration de services comme SSH, la mise en place de politiques de sécurité (pare-feu, mots de passe, sudo), et la création d'un script de monitoring.

L'objectif est de maîtriser les concepts suivants :
- Configuration d'une machine virtuelle avec VirtualBox ou UTM.
- Gestion des partitions chiffrées avec LVM.
- Configuration d'un service SSH sécurisé sur le port 424burgo- Installation et configuration de sudo avec des règles strictes.
- Mise en place d'un pare-feu (UFW ou firewalld).
- Création d'un script bash pour surveiller l'état du système.
- Compréhension des différences entre Debian et Rocky Linux (AppArmor, SELinux, etc.).

## Structure du projet
Le projet ne repose pas sur une structure de fichiers de code spécifique, mais sur la configuration d'une machine virtuelle. Les éléments clés à rendre sont :
- **`signature.txt`** : Contient la signature SHA1 du disque virtuel (`.vdi` ou `.qcow2`).
- **`monitoring.sh`** : Script bash qui affiche des informations système toutes les 10 minutes via la commande `wall`.

## Prérequis
- Un système compatible avec VirtualBox (Windows, Linux, macOS) ou UTM (Mac M1).
- Une image ISO de Debian (version stable) ou Rocky Linux (version stable).
- Connaissances de base en administration système Linux (SSH, UFW/firewalld, LVM, etc.).
- Accès à un terminal pour exécuter les commandes de configuration et le script `monitoring.sh`.

## Installation
1. **Télécharger l'ISO** :
   - Téléchargez l'image ISO de Debian (recommandé pour les débutants) ou Rocky Linux (version stable).
2. **Créer une machine virtuelle** :
   - Utilisez VirtualBox ou UTM pour créer une machine virtuelle.
   - Allouez au moins 8 Go de disque, 1 Go de RAM, et 1 CPU.
3. **Installer le système** :
   - Suivez les instructions d'installation de Debian ou Rocky Linux.
   - Configurez au moins 2 partitions chiffrées avec LVM (ex. `/`, `/home`, `/swap`).
   - Assurez-vous que AppArmor (Debian) ou SELinux (Rocky) reste actif.
4. **Configurer le système** :
   - Configurez le hostname (ex. `votrelogin42`).
   - Installez et configurez SSH sur le port 4242 (interdiction de connexion root).
   - Configurez le pare-feu (UFW pour Debian, firewalld pour Rocky) pour n'ouvrir que le port 4242.
   - Mettez en place une politique de mot de passe fort (expiration, complexité, etc.).
   - Configurez sudo avec des règles strictes (3 essais, journalisation, etc.).
   - Créez un utilisateur avec votre login, appartenant aux groupes `user42` et `sudo`.
5. **Créer le script de monitoring** :
   - Développez `monitoring.sh` pour afficher les informations système demandées.
   - Planifiez son exécution toutes les 10 minutes avec `cron`.

## Utilisation
### Commandes principales
1. **Vérifier les partitions** :
   ```bash
   lsblk
   ```
   Affiche la structure des partitions (ex. `/boot`, `/`, `/home`, `/swap`).

2. **Configurer SSH** :
   ```bash
   sudo nano /etc/ssh/sshd_config
   ```
   Modifiez `Port 4242` et désactivez `PermitRootLogin`.

3. **Configurer le pare-feu** :
   - Pour Debian :
     ```bash
     sudo ufw allow 4242
     sudo ufw enable
     ```
   - Pour Rocky :
     ```bash
     sudo firewall-cmd --permanent --add-port=4242/tcp
     sudo firewall-cmd --reload
     ```

4. **Configurer la politique de mot de passe** :
   ```bash
   sudo nano /etc/login.defs
   ```
   Définissez `PASS_MAX_DAYS 30`, `PASS_MIN_DAYS 2`, `PASS_WARN_AGE 7`.

5. **Exécuter le script de monitoring** :
   ```bash
   bash monitoring.sh
   ```
   Affiche les informations système (architecture, CPU, mémoire, etc.) sur tous les terminaux.

### Exemple de script `monitoring.sh`
Voici un exemple simplifié du script demandé :
```bash
#!/bin/bash
wall << EOF
Architecture: $(uname -a)
#CPU physical: $(nproc --all)
#vCPU: $(grep -c ^processor /proc/cpuinfo)
#Memory Usage: $(free -m | awk '/Mem:/ {printf "%.2f%%", $3/$2*100}')
#Disk Usage: $(df -h / | awk 'NR==2 {print $5}')
#CPU load: $(top -bn1 | head -n3 | grep "Cpu(s)" | awk '{print $2 + $4}%')
#Last boot: $(who -b | awk '{print $3, $4}')
#LVM use: $(lsblk | grep -q lvm && echo yes || echo no)
#Connections TCP: $(ss -t | grep ESTAB | wc -l) ESTABLISHED
#User log: $(who | wc -l)
#Network: IP $(ip addr show | grep inet | awk 'NR==2 {print $2}') ($(ip link show | awk 'NR==3 {print $2}' | tr -d ':'))
#Sudo: $(grep sudo /var/log/auth.log | wc -l) cmd
EOF
```
Planifiez-le avec `crontab -e` :
```bash
*/10 * * * * /path/to/monitoring.sh
```

### Exemple de rendu
Générez la signature SHA1 du disque virtuel :
```bash
sha1sum /path/to/your/virtual_disk.vdi > signature.txt
```
Placez `signature.txt` à la racine de votre dépôt Git.

## Fonctionnement détaillé
### Configuration du système
- **Hostname** : Définissez un hostname unique (ex. `votrelogin42`) avec `hostnamectl`.
- **SSH** : Le service SSH doit être configuré pour écouter sur le port 4242 et interdire les connexions root.
- **Pare-feu** : Seule la connexion au port 4242 est autorisée.
- **Politique de mot de passe** :
  - Expiration tous les 30 jours.
  - Minimum 10 caractères (majuscule, minuscule, chiffre).
  - Interdiction de plus de 3 caractères consécutifs identiques.
  - Interdiction du nom d'utilisateur dans le mot de passe.
  - Minimum 7 caractères différents par rapport à l'ancien mot de passe (sauf pour root).
- **Sudo** :
  - Limite de 3 essais pour un mot de passe incorrect.
  - Message d'erreur personnalisé.
  - Journalisation des actions dans `/var/log/sudo/`.
  - Mode TTY activé.
  - Chemins restreints (ex. `/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin`).

### Script `monitoring.sh`
Le script affiche les informations suivantes toutes les 10 minutes :
- Architecture et version du kernel.
- Nombre de processeurs physiques et virtuels.
- Utilisation de la mémoire vive (en pourcentage).
- Utilisation du disque (en pourcentage).
- Charge CPU (en pourcentage).
- Date et heure du dernier redémarrage.
- Statut de LVM (actif/inactif).
- Nombre de connexions TCP actives.
- Nombre d'utilisateurs connectés.
- Adresse IPv4 et MAC.
- Nombre de commandes sudo exécutées.

### Bonus
- Configurer des partitions supplémentaires (ex. `/var`, `/srv`, `/tmp`, `/var/log`).
- Mettre en place un site WordPress avec lighttpd, MariaDB, et PHP.
- Configurer un service supplémentaire utile (sauf NGINX/Apache2), avec justification.

## Gestion des erreurs
- Vérifiez que le fichier `signature.txt` correspond à la signature SHA1 du disque virtuel, sinon la note sera 0.
- Assurez-vous que le script `monitoring.sh` n'affiche aucune erreur.
- Testez toutes les configurations (SSH, pare-feu, sudo, etc.) avant la soutenance.
- La partie bonus ne sera évaluée que si la partie obligatoire est parfaite.

## Limitations
- Pas d'interface graphique (X.org ou équivalent interdit, sinon note = 0).
- Rocky Linux est plus complexe (pas d'obligation de KDump, mais SELinux requis).
- Les signatures SHA1 peuvent changer après une première évaluation ; utilisez des sauvegardes ou des "save states".

---

## Auteur
- **Nom** : votre_nom
- **Email** : votre_nom@student.42.fr
- **Date** : Juillet 2025

## Remerciements
Merci à l'école 42 pour ce projet qui m'a permis de découvrir la virtualisation et l'administration système sous Linux.

---

# Born2beRoot - README

## Description
Born2beRoot is a project developed as part of the 42 school curriculum. It introduces students to system administration by creating a virtual machine with a configured operating system (Debian or Rocky Linux) following strict guidelines. The project covers virtualization, partition management, SSH service configuration, security policies (firewall, passwords, sudo), and a system monitoring script.

The goal is to master the following concepts:
- Setting up a virtual machine with VirtualBox or UTM.
- Managing encrypted partitions with LVM.
- Configuring a secure SSH service on port 4242.
- Setting up strict sudo configurations.
- Creating a bash script to monitor system status.
- Understanding differences between Debian and Rocky Linux (AppArmor, SELinux, etc.).

## Project Structure
The project does not involve a specific code file structure but focuses on configuring a virtual machine. The key deliverables are:
- **`signature.txt`**: Contains the SHA1 signature of the virtual disk (`.vdi` or `.qcow2`).
- **`monitoring.sh`**: Bash script that displays system information every 10 minutes using `wall`.

## Prerequisites
- A system compatible with VirtualBox (Windows, Linux, macOS) or UTM (Mac M1).
- A Debian (stable) or Rocky Linux (stable) ISO image.
- Basic knowledge of Linux system administration (SSH, UFW/firewalld, LVM, etc.).
- Access to a terminal for configuration commands and running `monitoring.sh`.

## Installation
1. **Download the ISO**:
   - Obtain the ISO image for Debian (recommended for beginners) or Rocky Linux (stable).
2. **Create a Virtual Machine**:
   - Use VirtualBox or UTM to create a virtual machine.
   - Allocate at least 8 GB of disk space, 1 GB of RAM, and 1 CPU.
3. **Install the System**:
   - Follow the installation instructions for Debian or Rocky Linux.
   - Configure at least 2 encrypted LVM partitions (e.g., `/`, `/home`, `/swap`).
   - Ensure AppArmor (Debian) or SELinux (Rocky) remains active.
4. **Configure the System**:
   - Set the hostname (e.g., `yourlogin42`).
   - Configure SSH to listen on port 4242 (disable root login).
   - Set up the firewall (UFW for Debian, firewalld for Rocky) to allow only port 4242.
   - Implement a strong password policy (expiration, complexity, etc.).
   - Configure sudo with strict rules (3 attempts, logging, etc.).
   - Create a user with your login, belonging to `user42` and `sudo` groups.
5. **Create the Monitoring Script**:
   - Develop `monitoring.sh` to display the required system information.
   - Schedule it to run every 10 minutes using `cron`.

## Usage
### Key Commands
1. **Check Partitions**:
   ```bash
   lsblk
   ```
   Displays the partition structure (e.g., `/boot`, `/`, `/home`, `/swap`).

2. **Configure SSH**:
   ```bash
   sudo nano /etc/ssh/sshd_config
   ```
   Set `Port 4242` and disable `PermitRootLogin`.

3. **Configure Firewall**:
   - For Debian:
     ```bash
     sudo ufw allow 4242
     sudo ufw enable
     ```
   - For Rocky:
     ```bash
     sudo firewall-cmd --permanent --add-port=4242/tcp
     sudo firewall-cmd --reload
     ```

4. **Configure Password Policy**:
   ```bash
   sudo nano /etc/login.defs
   ```
   Set `PASS_MAX_DAYS 30`, `PASS_MIN_DAYS 2`, `PASS_WARN_AGE 7`.

5. **Run Monitoring Script**:
   ```bash
   bash monitoring.sh
   ```
   Displays system information (architecture, CPU, memory, etc.) on all terminals.

### Example `monitoring.sh` Script
Here’s a simplified example of the required script:
```bash
#!/bin/bash
wall << EOF
Architecture: $(uname -a)
#CPU physical: $(nproc --all)
#vCPU: $(grep -c ^processor /proc/cpuinfo)
#Memory Usage: $(free -m | awk '/Mem:/ {printf "%.2f%%", $3/$2*100}')
#Disk Usage: $(df -h / | awk 'NR==2 {print $5}')
#CPU load: $(top -bn1 | head -n3 | grep "Cpu(s)" | awk '{print $2 + $4}%')
#Last boot: $(who -b | awk '{print $3, $4}')
#LVM use: $(lsblk | grep -q lvm && echo yes || echo no)
#Connections TCP: $(ss -t | grep ESTAB | wc -l) ESTABLISHED
#User log: $(who | wc -l)
#Network: IP $(ip addr show | grep inet | awk 'NR==2 {print $2}') ($(ip link show | awk 'NR==3 {print $2}' | tr -d ':'))
#Sudo: $(grep sudo /var/log/auth.log | wc -l) cmd
EOF
```
Schedule it with `crontab -e`:
```bash
*/10 * * * * /path/to/monitoring.sh
```

### Example Deliverable
Generate the SHA1 signature of the virtual disk:
```bash
sha1sum /path/to/your/virtual_disk.vdi > signature.txt
```
Place `signature.txt` in the root of your Git repository.

## Detailed Functionality
### System Configuration
- **Hostname**: Set a unique hostname (e.g., `yourlogin42`) using `hostnamectl`.
- **SSH**: Configure SSH to listen on port 4242 and disable root login.
- **Firewall**: Allow only port 4242 connections.
- **Password Policy**:
  - Passwords expire every 30 days.
  - Minimum 10 characters (uppercase, lowercase, digit).
  - No more than 3 consecutive identical characters.
  - No username in the password.
  - At least 7 characters different from the previous password (except for root).
- **Sudo**:
  - Limit to 3 incorrect password attempts.
  - Custom error message.
  - Log all actions in `/var/log/sudo/`.
  - Enable TTY mode.
  - Restrict paths (e.g., `/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin`).

### `monitoring.sh` Script
The script displays the following information every 10 minutes:
- OS architecture and kernel version.
- Number of physical and virtual CPUs.
- Memory usage (percentage).
- Disk usage (percentage).
- CPU load (percentage).
- Last boot time.
- LVM status (active/inactive).
- Number of active TCP connections.
- Number of logged-in users.
- IPv4 and MAC address.
- Number of sudo commands executed.

### Bonus
- Configure additional partitions (e.g., `/var`, `/srv`, `/tmp`, `/var/log`).
- Set up a functional WordPress site with lighttpd, MariaDB, and PHP.
- Implement an additional useful service (except NGINX/Apache2) with justification.

## Error Handling
- Ensure `signature.txt` matches the virtual disk’s SHA1 signature, or the grade will be 0.
- Verify that `monitoring.sh` produces no errors.
- Test all configurations (SSH, firewall, sudo, etc.) before the evaluation.
- Bonus features are only evaluated if the mandatory part is perfect.

## Limitations
- No graphical interface (X.org or equivalent is forbidden, or the grade will be 0).
- Rocky Linux is more complex (KDump not required, but SELinux is mandatory).
- Virtual disk signatures may change after the first evaluation; use backups or save states.

---

## Author
- **Name**: your_name
- **Email**: your_name@student.42.fr
- **Date**: July 2025

## Acknowledgments
Thanks to 42 school for this project, which helped me explore virtualization and Linux system administration.
