#!/bin/bash

# Couleurs pour la lisibilité
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # Pas de couleur

# Chemins vers tes exécutables
PIPEX="./pipex"
PIPEX_BONUS="./pipex_bonus"
VALGRIND="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --leak-resolution=high --trace-children=yes"

# Fichiers temporaires pour comparer les sorties
TEST_DIR="outs"
mkdir -p "$TEST_DIR"
INPUT_FILE="$TEST_DIR/input.txt"
OUTPUT_PIPEX="$TEST_DIR/pipex_out.txt"
OUTPUT_BASH="$TEST_DIR/bash_out.txt"
OUTPUT_BONUS="$TEST_DIR/bonus_out.txt"

make
make bonus

# Vérifie si les exécutables existent
if [ ! -f "$PIPEX" ] || [ ! -f "$PIPEX_BONUS" ]; then
    echo -e "${RED}Erreur : $PIPEX ou $PIPEX_BONUS n'existe pas. Compile-les d'abord !${NC}"
    exit 1
fi

# Crée un fichier d'entrée pour les tests
echo -e "Ceci est un test\nLigne avec Now\nAnother line\n" > "$INPUT_FILE"

# Fonction pour comparer les sorties
compare_output() {
    local test_name="$1"
    local file1="$2"
    local file2="$3"
    if diff "$file1" "$file2" > /dev/null; then
        echo -e "${GREEN}[OK] $test_name : Sorties identiques${NC}"
    else
        echo -e "${RED}[KO] $test_name : Différences détectées${NC}"
        echo "Différence :"
        diff "$file1" "$file2"
    fi
}

# Fonction pour vérifier la norme
check_norm() {
    echo "Vérification de la norme 42..."
    norminette > norm_output.txt 2>&1
    if grep -q "Error" norm_output.txt; then
        echo -e "${RED}Norminette : Échec${NC}"
        cat norm_output.txt
    else
        echo -e "${GREEN}Norminette : OK${NC}"
    fi
    rm norm_output.txt
}

# Fonction pour lancer un test avec Valgrind
run_valgrind_test() {
    local test_name="$1"
    local cmd="$2"
    echo -e "\n--- Test : $test_name ---"
    $VALGRIND $cmd > valgrind_output.txt 2>&1
    if grep -q "ERROR SUMMARY: 0 errors from 0 contexts" valgrind_output.txt && \
       grep -q "All heap blocks were freed" valgrind_output.txt; then
        echo -e "${GREEN}Valgrind : Pas d'erreurs ni de fuites${NC}"
    else
        echo -e "${RED}Valgrind : Problèmes détectés${NC}"
        cat valgrind_output.txt
    fi
    rm valgrind_output.txt
	echo
}

# --- Tests pour pipex classique ---

echo -e "\n=== Tests pour pipex classique ===\n"

# Test 1 : Cas de base
echo "Test 1 : grep Now | wc -l"
$PIPEX "$INPUT_FILE" "grep Now" "wc -l" "$OUTPUT_PIPEX"
bash -c "< $INPUT_FILE grep Now | wc -l" > "$OUTPUT_BASH"
compare_output "Test 1" "$OUTPUT_PIPEX" "$OUTPUT_BASH"
run_valgrind_test "Test 1 avec Valgrind" "$PIPEX $INPUT_FILE \"grep Now\" \"wc -l\" $OUTPUT_PIPEX"

# Test 2 : Fichier d'entrée inexistant
echo "Test 2 : Fichier inexistant"
$PIPEX "non_existent.txt" "cat" "wc -w" "$OUTPUT_PIPEX"
run_valgrind_test "Test 2 avec Valgrind" "$PIPEX non_existent.txt \"cat\" \"wc -w\" $OUTPUT_PIPEX"

# Test 3 : Commande inexistante
echo "Test 3 : Commande inexistante"
$PIPEX "$INPUT_FILE" "cmd_not_found" "wc -l" "$OUTPUT_PIPEX"
run_valgrind_test "Test 3 avec Valgrind" "$PIPEX $INPUT_FILE \"cmd_not_found\" \"wc -l\" $OUTPUT_PIPEX"

# Test 4 : Environnement vide avec env -i
echo "Test 4 : env -i"
env -i $PIPEX "$INPUT_FILE" "grep Now" "wc -l" "$OUTPUT_PIPEX"
bash -c "env -i bash -c '< $INPUT_FILE grep Now | wc -l'" > "$OUTPUT_BASH"
compare_output "Test 4" "$OUTPUT_PIPEX" "$OUTPUT_BASH"
run_valgrind_test "Test 4 avec Valgrind" "env -i $PIPEX $INPUT_FILE \"grep Now\" \"wc -l\" $OUTPUT_PIPEX"

# --- Tests pour pipex_bonus ---

echo -e "\n=== Tests pour pipex_bonus ===\n"

# Test 5 : Cas de base avec plusieurs commandes
echo "Test 5 : grep Now | tr 'N' 'M' | wc -l"
$PIPEX_BONUS "$INPUT_FILE" "grep Now" "tr 'N' 'M'" "wc -l" "$OUTPUT_BONUS"
bash -c "< $INPUT_FILE grep Now | tr 'N' 'M' | wc -l" > "$OUTPUT_BASH"
compare_output "Test 5" "$OUTPUT_BONUS" "$OUTPUT_BASH"
run_valgrind_test "Test 5 avec Valgrind" "$PIPEX_BONUS $INPUT_FILE \"grep Now\" \"tr 'N' 'M'\" \"wc -l\" $OUTPUT_BONUS"

# Test 6 : Commande cheloue avec espaces et quotes
echo "Test 6 : Commande complexe"
$PIPEX_BONUS "$INPUT_FILE" "grep 'Now'" "awk '{print \$2}'" "$OUTPUT_BONUS"
bash -c "< $INPUT_FILE grep 'Now' | awk '{print \$2}'" > "$OUTPUT_BASH"
compare_output "Test 6" "$OUTPUT_BONUS" "$OUTPUT_BASH"
run_valgrind_test "Test 6 avec Valgrind" "$PIPEX_BONUS $INPUT_FILE \"grep 'Now'\" \"awk '{print \$2}'\" $OUTPUT_BONUS"

# Vérification de la norme
check_norm

# Nettoyage
rm -rf "$TEST_DIR"
make fclean

echo -e "\n=== Tests terminés ===\n"