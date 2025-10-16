#!/bin/bash

# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Aide
if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    echo -e "${CYAN}═══════════════════════════════════════════════════${NC}"
    echo -e "${CYAN}    Testeur de maps pour Cub3D${NC}"
    echo -e "${CYAN}═══════════════════════════════════════════════════${NC}"
    echo ""
    echo -e "${YELLOW}Usage:${NC}"
    echo -e "  ./test_maps.sh [mode]"
    echo ""
    echo -e "${YELLOW}Modes disponibles:${NC}"
    echo -e "  ${GREEN}(aucun)${NC}       Teste le mandatory ET le bonus"
    echo -e "  ${GREEN}mandatory, m${NC}  Teste uniquement le mandatory (make + ./cub3D)"
    echo -e "  ${GREEN}bonus, b${NC}      Teste uniquement le bonus (make bonus + ./cub3D_Bonus)"
    echo ""
    echo -e "${YELLOW}Description:${NC}"
    echo -e "  - Vérifie la norminette"
    echo -e "  - Compile le projet (make ou make bonus)"
    echo -e "  - Teste toutes les maps avec valgrind"
    echo -e "  - Les maps invalides doivent être rejetées"
    echo -e "  - Les maps valides ne doivent pas avoir de fuites mémoire"
    echo ""
    echo -e "${YELLOW}Note:${NC}"
    echo -e "  - En mode mandatory: teste maps/Invalid et maps/Valid"
    echo -e "  - En mode bonus: teste aussi maps/Bonus et maps/Bonus/Invalid"
    echo ""
    exit 0
fi

# Vérifier le mode (mandatory ou bonus)
MODE="both"
if [ "$1" = "mandatory" ] || [ "$1" = "m" ]; then
    MODE="mandatory"
elif [ "$1" = "bonus" ] || [ "$1" = "b" ]; then
    MODE="bonus"
fi

echo -e "${CYAN}========================================${NC}"
echo -e "${CYAN}   Testeur de maps pour Cub3D${NC}"
if [ "$MODE" = "mandatory" ]; then
    echo -e "${CYAN}   Mode: MANDATORY${NC}"
elif [ "$MODE" = "bonus" ]; then
    echo -e "${CYAN}   Mode: BONUS${NC}"
else
    echo -e "${CYAN}   Mode: MANDATORY + BONUS${NC}"
fi
echo -e "${CYAN}========================================${NC}\n"

# Vérification de la norminette
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo -e "${YELLOW}📋 Vérification de la norminette...${NC}"
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"

if ! command -v norminette &> /dev/null; then
    echo -e "${RED}❌ norminette n'est pas installée !${NC}"
    echo -e "${YELLOW}Continuez quand même ? (y/n)${NC}"
    read -r response
    if [ "$response" != "y" ] && [ "$response" != "Y" ]; then
        exit 1
    fi
else
    norm_output=$(norminette | grep "Error" | grep -d "mlx_flush_event.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  14, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  15, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  16, col:   1):	Consecutive newlines
Error: TOO_FEW_TAB          (line:  19, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  19, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  21, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  21, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  22, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  22, col:   3):	Space on empty line
Error: TOO_FEW_TAB          (line:  23, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  23, col:   6):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  23, col:  30):	missing space after operator
Error: TOO_FEW_TAB          (line:  24, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  24, col:   3):	Space on empty line
mlx_mouse_hook.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  14, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  15, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  16, col:   1):	Consecutive newlines
Error: TOO_MANY_TABS_FUNC   (line:  17, col:   5):	extra tabs before function name
Error: SPC_AFTER_OPERATOR   (line:  17, col:  39):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  17, col:  54):	missing space after operator
Error: SPACE_REPLACE_TAB    (line:  19, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  20, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  21, col:   3):	Found space when expecting tab
mlx.h: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  15, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  29, col:   1):	Consecutive newlines
Error: PREPROC_BAD_INDENT   (line:  32, col:   1):	Bad preprocessor indentation
Error: TAB_INSTEAD_SPC      (line:  32, col:  32):	Found tab when expecting space
Error: CONSECUTIVE_NEWLINES (line:  34, col:   1):	Consecutive newlines
Error: NO_ARGS_VOID         (line:  35, col:  19):	Empty function argument requires void
Error: CONSECUTIVE_NEWLINES (line:  41, col:   1):	Consecutive newlines
Error: MISALIGNED_FUNC_DECL (line:  50, col:   5):	Misaligned function declaration
Error: MISALIGNED_FUNC_DECL (line:  51, col:   5):	Misaligned function declaration
Error: TOO_MANY_ARGS        (line:  51, col:  73):	Function has more than 4 arguments
Error: CONSECUTIVE_NEWLINES (line:  58, col:   1):	Consecutive newlines
Error: SPC_AFTER_OPERATOR   (line:  63, col:  37):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  63, col:  47):	missing space after operator
Error: MIXED_SPACE_TAB      (line:  70, col:   9):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line:  70, col:  13):	Two or more consecutives spaces
Error: MISALIGNED_FUNC_DECL (line:  75, col:   5):	Misaligned function declaration
Error: TOO_MANY_TAB         (line:  76, col:   1):	Extra tabs for indent level
Error: TOO_MANY_ARGS        (line:  76, col:  30):	Function has more than 4 arguments
Error: MISALIGNED_FUNC_DECL (line:  77, col:   5):	Misaligned function declaration
Error: CONSECUTIVE_NEWLINES (line:  79, col:   1):	Consecutive newlines
Error: MISALIGNED_FUNC_DECL (line:  84, col:   5):	Misaligned function declaration
Error: EXP_PARENTHESIS      (line:  84, col:  19):	Expected parenthesis
Error: MISALIGNED_FUNC_DECL (line:  85, col:   5):	Misaligned function declaration
Error: EXP_PARENTHESIS      (line:  85, col:  17):	Expected parenthesis
Error: MISALIGNED_FUNC_DECL (line:  86, col:   5):	Misaligned function declaration
Error: EXP_PARENTHESIS      (line:  86, col:  20):	Expected parenthesis
Error: MISALIGNED_FUNC_DECL (line:  88, col:   5):	Misaligned function declaration
Error: EXP_PARENTHESIS      (line:  88, col:  18):	Expected parenthesis
Error: MISALIGNED_FUNC_DECL (line:  89, col:   5):	Misaligned function declaration
Error: EXP_PARENTHESIS      (line:  89, col:  13):	Expected parenthesis
Error: SPACE_REPLACE_TAB    (line:  90, col:   4):	Found space when expecting tab
Error: EXP_PARENTHESIS      (line:  90, col:  17):	Expected parenthesis
Error: CONSECUTIVE_NEWLINES (line: 102, col:   1):	Consecutive newlines
Error: MISALIGNED_FUNC_DECL (line: 107, col:   5):	Misaligned function declaration
Error: TOO_FEW_TAB          (line: 108, col:   1):	Missing tabs for indent level
Error: MIXED_SPACE_TAB      (line: 108, col:   5):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line: 108, col:   9):	Two or more consecutives spaces
Error: TOO_MANY_ARGS        (line: 108, col:  29):	Function has more than 4 arguments
Error: MIXED_SPACE_TAB      (line: 111, col:   9):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line: 111, col:  13):	Two or more consecutives spaces
Error: MIXED_SPACE_TAB      (line: 113, col:   9):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line: 113, col:  13):	Two or more consecutives spaces
Error: MISALIGNED_FUNC_DECL (line: 114, col:   5):	Misaligned function declaration
Error: MISALIGNED_FUNC_DECL (line: 116, col:   5):	Misaligned function declaration
Error: MISALIGNED_FUNC_DECL (line: 118, col:   5):	Misaligned function declaration
Error: MISALIGNED_FUNC_DECL (line: 125, col:   5):	Misaligned function declaration
Error: TOO_FEW_TAB          (line: 126, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 126, col:  18):	Found space when expecting tab
Error: MISALIGNED_FUNC_DECL (line: 128, col:   5):	Misaligned function declaration
Error: MISALIGNED_FUNC_DECL (line: 129, col:   5):	Misaligned function declaration
Error: MISALIGNED_FUNC_DECL (line: 130, col:   5):	Misaligned function declaration
Error: MISALIGNED_FUNC_DECL (line: 132, col:   5):	Misaligned function declaration
Error: MISALIGNED_FUNC_DECL (line: 133, col:   5):	Misaligned function declaration
Error: MISALIGNED_FUNC_DECL (line: 134, col:   5):	Misaligned function declaration
Error: MISALIGNED_FUNC_DECL (line: 135, col:   5):	Misaligned function declaration
Error: MISALIGNED_FUNC_DECL (line: 137, col:   5):	Misaligned function declaration
mlx_key_hook.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  14, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  15, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  16, col:   1):	Consecutive newlines
Error: TOO_MANY_TABS_FUNC   (line:  17, col:   5):	extra tabs before function name
Error: SPC_AFTER_OPERATOR   (line:  17, col:  37):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  17, col:  52):	missing space after operator
Error: SPACE_REPLACE_TAB    (line:  19, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  20, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  21, col:   3):	Found space when expecting tab
mlx_rgb.c: Error!
Error: INVALID_HEADER       (line:   5, col:   1):	Missing or invalid 42 header
Error: SPACE_REPLACE_TAB    (line:   8, col:  18):	Found space when expecting tab
Error: GLOBAL_VAR_NAMING    (line:   8, col:  19):	Global variable must start with g_
Error: EOL_OPERATOR         (line:   8, col:  35):	Logic operator at the end of line
Error: TOO_FEW_TAB          (line:  10, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  10, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  10, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  10, col:  11):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  10, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  11, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  11, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  11, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  11, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  11, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  12, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  12, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  12, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  12, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  12, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  13, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  13, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  13, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  13, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  13, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  14, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  14, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  14, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  14, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  14, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  15, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  15, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  15, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  15, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  15, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  16, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  16, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  16, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  16, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  16, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  17, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  17, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  17, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  17, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  17, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  18, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  18, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  18, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  18, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  18, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  19, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  19, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  19, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  19, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  19, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  20, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  20, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  20, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  20, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  20, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  21, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  21, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  21, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  21, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  21, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  22, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  22, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  22, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  22, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  22, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  23, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  23, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  23, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  23, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  23, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  24, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  24, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  24, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  24, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  24, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  25, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  25, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  25, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  25, col:  22):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  25, col:  33):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  26, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  26, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  26, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  26, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  26, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  27, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  27, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  27, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  27, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  27, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  28, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  28, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  28, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  28, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  28, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  29, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  29, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  29, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  29, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  29, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  30, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  30, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  30, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  30, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  30, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  31, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  31, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  31, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  31, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  31, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  32, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  32, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  32, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  32, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  32, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  33, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  33, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  33, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  33, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  33, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  34, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  34, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  34, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  34, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  34, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  35, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  35, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  35, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  35, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  35, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  36, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  36, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  36, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  36, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  36, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  37, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  37, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  37, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  37, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  37, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  38, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  38, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  38, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  38, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  38, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  39, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  39, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  39, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  39, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  39, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  40, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  40, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  40, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  40, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  40, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  41, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  41, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  41, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  41, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  41, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  42, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  42, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  42, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  42, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  42, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  43, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  43, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  43, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  43, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  43, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  44, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  44, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  44, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  44, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  44, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  45, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  45, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  45, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  45, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  45, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  46, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  46, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  46, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  46, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  46, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  47, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  47, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  47, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  47, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  47, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  48, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  48, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  48, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  48, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  48, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  49, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  49, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  49, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  49, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  49, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  50, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  50, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  50, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  50, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  50, col:  18):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  51, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  51, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  51, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  51, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  51, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  52, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  52, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  52, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  52, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  52, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  53, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  53, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  53, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  53, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  53, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  54, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  54, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  54, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  54, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  54, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  55, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  55, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  55, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  55, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  55, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  56, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  56, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  56, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  56, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  56, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  57, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  57, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  57, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  57, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  57, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  58, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  58, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  58, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  58, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  58, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  59, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  59, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  59, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  59, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  59, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  60, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  60, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  60, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  60, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  60, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  61, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  61, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  61, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  61, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  61, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  62, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  62, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  62, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  62, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  62, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  63, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  63, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  63, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  63, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  63, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  64, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  64, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  64, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  64, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  64, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  65, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  65, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  65, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  65, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  65, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  66, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  66, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  66, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  66, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  66, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  67, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  67, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  67, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  67, col:  11):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  67, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  68, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  68, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  68, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  68, col:  11):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  68, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  69, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  69, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  69, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  69, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  69, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  70, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  70, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  70, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  70, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  70, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  71, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  71, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  71, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  71, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  71, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  72, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  72, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  72, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  72, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  72, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  73, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  73, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  73, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  73, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  73, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  74, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  74, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  74, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  74, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  74, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  75, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  75, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  75, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  75, col:  11):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  75, col:  18):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  76, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  76, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  76, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  76, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  76, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  77, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  77, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  77, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  77, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  77, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  78, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  78, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  78, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  78, col:  22):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  78, col:  33):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  79, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  79, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  79, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  79, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  79, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  80, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  80, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  80, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  80, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  80, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  81, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  81, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  81, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  81, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  81, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  82, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  82, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  82, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  82, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  82, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  83, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  83, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  83, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  83, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  83, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  84, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  84, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  84, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  84, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  84, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  85, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  85, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  85, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  85, col:  22):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  85, col:  33):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  86, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  86, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  86, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  86, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  86, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  87, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  87, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  87, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  87, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  87, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  88, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  88, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  88, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  88, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  88, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  89, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  89, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  89, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  89, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  89, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  90, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  90, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  90, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  90, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  90, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  91, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  91, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  91, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  91, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  91, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  92, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  92, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  92, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  92, col:  11):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  92, col:  18):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  93, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  93, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  93, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  93, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  93, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  94, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  94, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  94, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  94, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  94, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  95, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  95, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  95, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  95, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  95, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  96, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  96, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  96, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  96, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  96, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  97, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  97, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  97, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  97, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  97, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  98, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  98, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  98, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  98, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  98, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  99, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  99, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line:  99, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line:  99, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line:  99, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 100, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 100, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 100, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 100, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 100, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 101, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 101, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 101, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 101, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 101, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 102, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 102, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 102, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 102, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 102, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 103, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 103, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 103, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 103, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 103, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 104, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 104, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 104, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 104, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 104, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 105, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 105, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 105, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 105, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 105, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 106, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 106, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 106, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 106, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 106, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 107, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 107, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 107, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 107, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 107, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 108, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 108, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 108, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 108, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 108, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 109, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 109, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 109, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 109, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 109, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 110, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 110, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 110, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 110, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 110, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 111, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 111, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 111, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 111, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 111, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 112, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 112, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 112, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 112, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 112, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 113, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 113, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 113, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 113, col:  23):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 113, col:  34):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 114, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 114, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 114, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 114, col:  22):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 114, col:  33):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 115, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 115, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 115, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 115, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 115, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 116, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 116, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 116, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 116, col:  11):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 116, col:  20):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 117, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 117, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 117, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 117, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 117, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 118, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 118, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 118, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 118, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 118, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 119, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 119, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 119, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 119, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 119, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 120, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 120, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 120, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 120, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 120, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 121, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 121, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 121, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 121, col:  24):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 121, col:  35):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 122, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 122, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 122, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 122, col:  23):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 122, col:  34):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 123, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 123, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 123, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 123, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 123, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 124, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 124, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 124, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 124, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 124, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 125, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 125, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 125, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 125, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 125, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 126, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 126, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 126, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 126, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 126, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 127, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 127, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 127, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 127, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 127, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 128, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 128, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 128, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 128, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 128, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 129, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 129, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 129, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 129, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 129, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 130, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 130, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 130, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 130, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 130, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 131, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 131, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 131, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 131, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 131, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 132, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 132, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 132, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 132, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 132, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 133, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 133, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 133, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 133, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 133, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 134, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 134, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 134, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 134, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 134, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 135, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 135, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 135, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 135, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 135, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 136, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 136, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 136, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 136, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 136, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 137, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 137, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 137, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 137, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 137, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 138, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 138, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 138, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 138, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 138, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 139, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 139, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 139, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 139, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 139, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 140, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 140, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 140, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 140, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 140, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 141, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 141, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 141, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 141, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 141, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 142, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 142, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 142, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 142, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 142, col:  21):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 143, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 143, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 143, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 143, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 143, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 144, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 144, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 144, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 144, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 144, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 145, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 145, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 145, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 145, col:  24):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 145, col:  33):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 146, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 146, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 146, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 146, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 146, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 147, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 147, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 147, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 147, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 147, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 148, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 148, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 148, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 148, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 148, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 149, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 149, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 149, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 149, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 149, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 150, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 150, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 150, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 150, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 150, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 151, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 151, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 151, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 151, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 151, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 152, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 152, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 152, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 152, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 152, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 153, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 153, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 153, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 153, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 153, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 154, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 154, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 154, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 154, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 154, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 155, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 155, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 155, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 155, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 155, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 156, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 156, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 156, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 156, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 156, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 157, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 157, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 157, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 157, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 157, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 158, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 158, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 158, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 158, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 158, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 159, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 159, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 159, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 159, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 159, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 160, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 160, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 160, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 160, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 160, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 161, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 161, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 161, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 161, col:  22):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 161, col:  33):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 162, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 162, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 162, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 162, col:  27):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 162, col:  38):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 163, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 163, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 163, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 163, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 163, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 164, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 164, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 164, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 164, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 164, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 165, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 165, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 165, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 165, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 165, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 166, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 166, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 166, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 166, col:  11):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 166, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 167, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 167, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 167, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 167, col:  22):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 167, col:  33):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 168, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 168, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 168, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 168, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 168, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 169, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 169, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 169, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 169, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 169, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 170, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 170, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 170, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 170, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 170, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 171, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 171, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 171, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 171, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 171, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 172, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 172, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 172, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 172, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 172, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 173, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 173, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 173, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 173, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 173, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 174, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 174, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 174, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 174, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 174, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 175, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 175, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 175, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 175, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 175, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 176, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 176, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 176, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 176, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 176, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 177, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 177, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 177, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 177, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 177, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 178, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 178, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 178, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 178, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 178, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 179, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 179, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 179, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 179, col:  11):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 179, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 180, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 180, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 180, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 180, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 180, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 181, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 181, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 181, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 181, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 181, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 182, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 182, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 182, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 182, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 182, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 183, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 183, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 183, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 183, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 183, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 184, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 184, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 184, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 184, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 184, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 185, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 185, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 185, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 185, col:  10):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 185, col:  21):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 186, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 186, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 186, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 186, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 186, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 187, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 187, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 187, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 187, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 187, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 188, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 188, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 188, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 188, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 188, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 189, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 189, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 189, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 189, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 189, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 190, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 190, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 190, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 190, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 190, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 191, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 191, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 191, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 191, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 191, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 192, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 192, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 192, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 192, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 192, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 193, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 193, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 193, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 193, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 193, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 194, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 194, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 194, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 194, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 194, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 195, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 195, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 195, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 195, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 195, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 196, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 196, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 196, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 196, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 196, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 197, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 197, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 197, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 197, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 197, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 198, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 198, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 198, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 198, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 198, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 199, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 199, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 199, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 199, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 199, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 200, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 200, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 200, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 200, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 200, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 201, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 201, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 201, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 201, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 201, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 202, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 202, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 202, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 202, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 202, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 203, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 203, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 203, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 203, col:  10):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 203, col:  21):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 204, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 204, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 204, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 204, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 204, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 205, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 205, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 205, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 205, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 205, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 206, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 206, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 206, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 206, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 206, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 207, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 207, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 207, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 207, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 207, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 208, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 208, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 208, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 208, col:  11):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 208, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 209, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 209, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 209, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 209, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 209, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 210, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 210, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 210, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 210, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 210, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 211, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 211, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 211, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 211, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 211, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 212, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 212, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 212, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 212, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 212, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 213, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 213, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 213, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 213, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 213, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 214, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 214, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 214, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 214, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 214, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 215, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 215, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 215, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 215, col:  22):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 215, col:  33):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 216, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 216, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 216, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 216, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 216, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 217, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 217, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 217, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 217, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 217, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 218, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 218, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 218, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 218, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 218, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 219, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 219, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 219, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 219, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 219, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 220, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 220, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 220, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 220, col:  11):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 220, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 221, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 221, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 221, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 221, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 221, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 222, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 222, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 222, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 222, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 222, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 223, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 223, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 223, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 223, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 223, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 224, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 224, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 224, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 224, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 224, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 225, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 225, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 225, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 225, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 225, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 226, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 226, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 226, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 226, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 226, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 227, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 227, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 227, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 227, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 227, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 228, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 228, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 228, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 228, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 228, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 229, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 229, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 229, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 229, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 229, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 230, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 230, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 230, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 230, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 230, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 231, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 231, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 231, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 231, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 231, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 232, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 232, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 232, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 232, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 232, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 233, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 233, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 233, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 233, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 233, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 234, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 234, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 234, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 234, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 234, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 235, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 235, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 235, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 235, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 235, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 236, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 236, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 236, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 236, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 236, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 237, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 237, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 237, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 237, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 237, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 238, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 238, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 238, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 238, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 238, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 239, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 239, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 239, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 239, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 239, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 240, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 240, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 240, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 240, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 240, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 241, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 241, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 241, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 241, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 241, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 242, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 242, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 242, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 242, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 242, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 243, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 243, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 243, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 243, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 243, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 244, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 244, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 244, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 244, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 244, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 245, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 245, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 245, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 245, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 245, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 246, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 246, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 246, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 246, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 246, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 247, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 247, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 247, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 247, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 247, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 248, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 248, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 248, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 248, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 248, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 249, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 249, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 249, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 249, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 249, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 250, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 250, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 250, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 250, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 250, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 251, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 251, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 251, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 251, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 251, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 252, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 252, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 252, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 252, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 252, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 253, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 253, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 253, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 253, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 253, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 254, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 254, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 254, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 254, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 254, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 255, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 255, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 255, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 255, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 255, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 256, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 256, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 256, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 256, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 256, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 257, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 257, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 257, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 257, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 257, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 258, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 258, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 258, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 258, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 258, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 259, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 259, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 259, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 259, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 259, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 260, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 260, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 260, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 260, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 260, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 261, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 261, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 261, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 261, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 261, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 262, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 262, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 262, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 262, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 262, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 263, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 263, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 263, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 263, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 263, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 264, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 264, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 264, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 264, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 264, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 265, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 265, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 265, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 265, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 265, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 266, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 266, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 266, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 266, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 266, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 267, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 267, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 267, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 267, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 267, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 268, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 268, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 268, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 268, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 268, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 269, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 269, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 269, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 269, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 269, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 270, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 270, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 270, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 270, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 270, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 271, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 271, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 271, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 271, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 271, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 272, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 272, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 272, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 272, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 272, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 273, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 273, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 273, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 273, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 273, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 274, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 274, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 274, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 274, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 274, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 275, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 275, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 275, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 275, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 275, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 276, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 276, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 276, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 276, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 276, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 277, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 277, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 277, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 277, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 277, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 278, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 278, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 278, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 278, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 278, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 279, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 279, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 279, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 279, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 279, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 280, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 280, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 280, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 280, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 280, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 281, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 281, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 281, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 281, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 281, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 282, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 282, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 282, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 282, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 282, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 283, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 283, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 283, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 283, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 283, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 284, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 284, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 284, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 284, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 284, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 285, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 285, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 285, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 285, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 285, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 286, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 286, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 286, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 286, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 286, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 287, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 287, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 287, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 287, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 287, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 288, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 288, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 288, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 288, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 288, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 289, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 289, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 289, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 289, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 289, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 290, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 290, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 290, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 290, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 290, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 291, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 291, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 291, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 291, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 291, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 292, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 292, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 292, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 292, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 292, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 293, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 293, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 293, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 293, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 293, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 294, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 294, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 294, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 294, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 294, col:  19):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 295, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 295, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 295, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 295, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 295, col:  19):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 296, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 296, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 296, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 296, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 296, col:  19):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 297, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 297, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 297, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 297, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 297, col:  19):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 298, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 298, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 298, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 298, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 298, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 299, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 299, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 299, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 299, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 299, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 300, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 300, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 300, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 300, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 300, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 301, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 301, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 301, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 301, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 301, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 302, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 302, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 302, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 302, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 302, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 303, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 303, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 303, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 303, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 303, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 304, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 304, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 304, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 304, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 304, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 305, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 305, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 305, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 305, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 305, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 306, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 306, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 306, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 306, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 306, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 307, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 307, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 307, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 307, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 307, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 308, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 308, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 308, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 308, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 308, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 309, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 309, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 309, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 309, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 309, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 310, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 310, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 310, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 310, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 310, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 311, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 311, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 311, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 311, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 311, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 312, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 312, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 312, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 312, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 312, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 313, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 313, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 313, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 313, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 313, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 314, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 314, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 314, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 314, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 314, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 315, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 315, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 315, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 315, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 315, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 316, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 316, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 316, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 316, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 316, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 317, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 317, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 317, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 317, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 317, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 318, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 318, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 318, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 318, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 318, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 319, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 319, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 319, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 319, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 319, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 320, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 320, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 320, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 320, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 320, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 321, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 321, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 321, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 321, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 321, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 322, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 322, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 322, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 322, col:  22):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 322, col:  33):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 323, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 323, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 323, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 323, col:  22):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 323, col:  33):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 324, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 324, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 324, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 324, col:  22):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 324, col:  33):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 325, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 325, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 325, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 325, col:  22):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 325, col:  33):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 326, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 326, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 326, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 326, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 326, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 327, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 327, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 327, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 327, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 327, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 328, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 328, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 328, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 328, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 328, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 329, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 329, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 329, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 329, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 329, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 330, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 330, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 330, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 330, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 330, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 331, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 331, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 331, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 331, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 331, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 332, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 332, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 332, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 332, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 332, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 333, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 333, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 333, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 333, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 333, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 334, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 334, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 334, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 334, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 334, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 335, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 335, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 335, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 335, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 335, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 336, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 336, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 336, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 336, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 336, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 337, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 337, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 337, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 337, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 337, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 338, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 338, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 338, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 338, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 338, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 339, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 339, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 339, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 339, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 339, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 340, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 340, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 340, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 340, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 340, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 341, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 341, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 341, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 341, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 341, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 342, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 342, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 342, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 342, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 342, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 343, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 343, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 343, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 343, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 343, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 344, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 344, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 344, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 344, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 344, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 345, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 345, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 345, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 345, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 345, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 346, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 346, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 346, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 346, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 346, col:  21):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 347, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 347, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 347, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 347, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 347, col:  21):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 348, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 348, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 348, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 348, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 348, col:  21):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 349, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 349, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 349, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 349, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 349, col:  21):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 350, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 350, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 350, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 350, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 350, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 351, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 351, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 351, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 351, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 351, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 352, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 352, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 352, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 352, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 352, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 353, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 353, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 353, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 353, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 353, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 354, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 354, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 354, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 354, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 354, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 355, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 355, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 355, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 355, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 355, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 356, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 356, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 356, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 356, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 356, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 357, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 357, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 357, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 357, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 357, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 358, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 358, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 358, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 358, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 358, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 359, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 359, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 359, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 359, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 359, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 360, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 360, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 360, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 360, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 360, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 361, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 361, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 361, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 361, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 361, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 362, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 362, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 362, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 362, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 362, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 363, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 363, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 363, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 363, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 363, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 364, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 364, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 364, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 364, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 364, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 365, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 365, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 365, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 365, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 365, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 366, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 366, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 366, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 366, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 366, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 367, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 367, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 367, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 367, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 367, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 368, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 368, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 368, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 368, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 368, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 369, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 369, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 369, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 369, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 369, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 370, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 370, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 370, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 370, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 370, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 371, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 371, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 371, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 371, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 371, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 372, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 372, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 372, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 372, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 372, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 373, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 373, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 373, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 373, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 373, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 374, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 374, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 374, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 374, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 374, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 375, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 375, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 375, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 375, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 375, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 376, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 376, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 376, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 376, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 376, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 377, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 377, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 377, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 377, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 377, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 378, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 378, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 378, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 378, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 378, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 379, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 379, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 379, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 379, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 379, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 380, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 380, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 380, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 380, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 380, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 381, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 381, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 381, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 381, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 381, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 382, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 382, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 382, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 382, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 382, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 383, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 383, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 383, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 383, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 383, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 384, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 384, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 384, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 384, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 384, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 385, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 385, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 385, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 385, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 385, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 386, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 386, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 386, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 386, col:  22):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 386, col:  33):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 387, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 387, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 387, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 387, col:  22):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 387, col:  33):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 388, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 388, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 388, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 388, col:  22):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 388, col:  33):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 389, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 389, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 389, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 389, col:  22):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 389, col:  33):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 390, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 390, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 390, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 390, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 390, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 391, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 391, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 391, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 391, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 391, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 392, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 392, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 392, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 392, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 392, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 393, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 393, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 393, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 393, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 393, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 394, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 394, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 394, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 394, col:  22):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 394, col:  33):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 395, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 395, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 395, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 395, col:  22):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 395, col:  33):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 396, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 396, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 396, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 396, col:  22):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 396, col:  33):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 397, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 397, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 397, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 397, col:  22):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 397, col:  33):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 398, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 398, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 398, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 398, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 398, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 399, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 399, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 399, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 399, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 399, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 400, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 400, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 400, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 400, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 400, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 401, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 401, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 401, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 401, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 401, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 402, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 402, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 402, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 402, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 402, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 403, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 403, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 403, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 403, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 403, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 404, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 404, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 404, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 404, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 404, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 405, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 405, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 405, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 405, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 405, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 406, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 406, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 406, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 406, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 406, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 407, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 407, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 407, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 407, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 407, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 408, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 408, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 408, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 408, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 408, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 409, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 409, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 409, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 409, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 409, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 410, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 410, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 410, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 410, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 410, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 411, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 411, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 411, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 411, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 411, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 412, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 412, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 412, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 412, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 412, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 413, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 413, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 413, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 413, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 413, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 414, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 414, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 414, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 414, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 414, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 415, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 415, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 415, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 415, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 415, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 416, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 416, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 416, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 416, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 416, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 417, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 417, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 417, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 417, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 417, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 418, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 418, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 418, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 418, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 418, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 419, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 419, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 419, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 419, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 419, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 420, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 420, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 420, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 420, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 420, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 421, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 421, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 421, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 421, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 421, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 422, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 422, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 422, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 422, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 422, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 423, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 423, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 423, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 423, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 423, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 424, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 424, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 424, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 424, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 424, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 425, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 425, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 425, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 425, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 425, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 426, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 426, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 426, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 426, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 426, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 427, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 427, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 427, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 427, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 427, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 428, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 428, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 428, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 428, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 428, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 429, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 429, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 429, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 429, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 429, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 430, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 430, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 430, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 430, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 430, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 431, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 431, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 431, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 431, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 431, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 432, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 432, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 432, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 432, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 432, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 433, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 433, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 433, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 433, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 433, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 434, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 434, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 434, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 434, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 434, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 435, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 435, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 435, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 435, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 435, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 436, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 436, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 436, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 436, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 436, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 437, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 437, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 437, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 437, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 437, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 438, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 438, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 438, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 438, col:  11):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 438, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 439, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 439, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 439, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 439, col:  11):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 439, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 440, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 440, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 440, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 440, col:  11):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 440, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 441, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 441, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 441, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 441, col:  11):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 441, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 442, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 442, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 442, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 442, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 442, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 443, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 443, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 443, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 443, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 443, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 444, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 444, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 444, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 444, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 444, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 445, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 445, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 445, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 445, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 445, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 446, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 446, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 446, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 446, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 446, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 447, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 447, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 447, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 447, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 447, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 448, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 448, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 448, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 448, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 448, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 449, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 449, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 449, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 449, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 449, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 450, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 450, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 450, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 450, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 450, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 451, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 451, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 451, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 451, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 451, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 452, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 452, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 452, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 452, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 452, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 453, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 453, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 453, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 453, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 453, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 454, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 454, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 454, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 454, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 454, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 455, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 455, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 455, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 455, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 455, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 456, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 456, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 456, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 456, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 456, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 457, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 457, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 457, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 457, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 457, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 458, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 458, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 458, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 458, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 458, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 459, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 459, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 459, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 459, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 459, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 460, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 460, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 460, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 460, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 460, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 461, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 461, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 461, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 461, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 461, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 462, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 462, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 462, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 462, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 462, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 463, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 463, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 463, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 463, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 463, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 464, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 464, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 464, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 464, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 464, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 465, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 465, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 465, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 465, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 465, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 466, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 466, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 466, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 466, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 466, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 467, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 467, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 467, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 467, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 467, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 468, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 468, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 468, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 468, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 468, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 469, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 469, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 469, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 469, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 469, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 470, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 470, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 470, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 470, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 470, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 471, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 471, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 471, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 471, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 471, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 472, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 472, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 472, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 472, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 472, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 473, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 473, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 473, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 473, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 473, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 474, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 474, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 474, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 474, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 474, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 475, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 475, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 475, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 475, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 475, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 476, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 476, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 476, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 476, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 476, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 477, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 477, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 477, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 477, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 477, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 478, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 478, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 478, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 478, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 478, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 479, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 479, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 479, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 479, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 479, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 480, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 480, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 480, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 480, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 480, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 481, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 481, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 481, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 481, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 481, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 482, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 482, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 482, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 482, col:  11):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 482, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 483, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 483, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 483, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 483, col:  11):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 483, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 484, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 484, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 484, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 484, col:  11):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 484, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 485, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 485, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 485, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 485, col:  11):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 485, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 486, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 486, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 486, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 486, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 486, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 487, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 487, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 487, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 487, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 487, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 488, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 488, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 488, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 488, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 488, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 489, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 489, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 489, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 489, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 489, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 490, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 490, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 490, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 490, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 490, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 491, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 491, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 491, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 491, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 491, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 492, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 492, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 492, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 492, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 492, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 493, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 493, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 493, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 493, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 493, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 494, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 494, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 494, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 494, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 494, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 495, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 495, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 495, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 495, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 495, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 496, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 496, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 496, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 496, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 496, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 497, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 497, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 497, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 497, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 497, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 498, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 498, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 498, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 498, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 498, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 499, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 499, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 499, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 499, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 499, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 500, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 500, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 500, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 500, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 500, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 501, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 501, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 501, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 501, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 501, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 502, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 502, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 502, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 502, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 502, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 503, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 503, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 503, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 503, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 503, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 504, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 504, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 504, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 504, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 504, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 505, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 505, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 505, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 505, col:  21):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 505, col:  32):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 506, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 506, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 506, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 506, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 506, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 507, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 507, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 507, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 507, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 507, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 508, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 508, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 508, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 508, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 508, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 509, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 509, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 509, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 509, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 509, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 510, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 510, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 510, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 510, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 510, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 511, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 511, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 511, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 511, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 511, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 512, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 512, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 512, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 512, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 512, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 513, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 513, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 513, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 513, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 513, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 514, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 514, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 514, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 514, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 514, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 515, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 515, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 515, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 515, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 515, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 516, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 516, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 516, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 516, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 516, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 517, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 517, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 517, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 517, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 517, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 518, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 518, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 518, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 518, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 518, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 519, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 519, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 519, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 519, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 519, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 520, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 520, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 520, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 520, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 520, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 521, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 521, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 521, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 521, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 521, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 522, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 522, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 522, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 522, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 522, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 523, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 523, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 523, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 523, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 523, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 524, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 524, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 524, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 524, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 524, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 525, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 525, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 525, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 525, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 525, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 526, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 526, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 526, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 526, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 526, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 527, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 527, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 527, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 527, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 527, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 528, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 528, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 528, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 528, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 528, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 529, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 529, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 529, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 529, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 529, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 530, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 530, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 530, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 530, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 530, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 531, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 531, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 531, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 531, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 531, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 532, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 532, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 532, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 532, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 532, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 533, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 533, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 533, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 533, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 533, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 534, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 534, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 534, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 534, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 534, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 535, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 535, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 535, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 535, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 535, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 536, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 536, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 536, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 536, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 536, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 537, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 537, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 537, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 537, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 537, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 538, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 538, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 538, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 538, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 538, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 539, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 539, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 539, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 539, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 539, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 540, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 540, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 540, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 540, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 540, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 541, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 541, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 541, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 541, col:  20):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 541, col:  31):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 542, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 542, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 542, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 542, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 542, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 543, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 543, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 543, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 543, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 543, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 544, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 544, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 544, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 544, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 544, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 545, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 545, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 545, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 545, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 545, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 546, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 546, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 546, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 546, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 546, col:  18):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 547, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 547, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 547, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 547, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 547, col:  18):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 548, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 548, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 548, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 548, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 548, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 549, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 549, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 549, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 549, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 549, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 550, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 550, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 550, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 550, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 550, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 551, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 551, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 551, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 551, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 551, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 552, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 552, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 552, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 552, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 552, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 553, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 553, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 553, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 553, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 553, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 554, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 554, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 554, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 554, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 554, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 555, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 555, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 555, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 555, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 555, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 556, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 556, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 556, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 556, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 556, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 557, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 557, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 557, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 557, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 557, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 558, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 558, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 558, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 558, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 558, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 559, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 559, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 559, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 559, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 559, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 560, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 560, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 560, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 560, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 560, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 561, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 561, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 561, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 561, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 561, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 562, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 562, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 562, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 562, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 562, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 563, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 563, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 563, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 563, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 563, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 564, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 564, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 564, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 564, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 564, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 565, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 565, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 565, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 565, col:  12):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 565, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 566, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 566, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 566, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 566, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 566, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 567, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 567, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 567, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 567, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 567, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 568, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 568, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 568, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 568, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 568, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 569, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 569, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 569, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 569, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 569, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 570, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 570, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 570, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 570, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 570, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 571, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 571, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 571, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 571, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 571, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 572, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 572, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 572, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 572, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 572, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 573, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 573, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 573, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 573, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 573, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 574, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 574, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 574, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 574, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 574, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 575, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 575, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 575, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 575, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 575, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 576, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 576, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 576, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 576, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 576, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 577, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 577, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 577, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 577, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 577, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 578, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 578, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 578, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 578, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 578, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 579, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 579, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 579, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 579, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 579, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 580, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 580, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 580, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 580, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 580, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 581, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 581, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 581, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 581, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 581, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 582, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 582, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 582, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 582, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 582, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 583, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 583, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 583, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 583, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 583, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 584, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 584, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 584, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 584, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 584, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 585, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 585, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 585, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 585, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 585, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 586, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 586, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 586, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 586, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 586, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 587, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 587, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 587, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 587, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 587, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 588, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 588, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 588, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 588, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 588, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 589, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 589, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 589, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 589, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 589, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 590, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 590, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 590, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 590, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 590, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 591, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 591, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 591, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 591, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 591, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 592, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 592, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 592, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 592, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 592, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 593, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 593, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 593, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 593, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 593, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 594, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 594, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 594, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 594, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 594, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 595, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 595, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 595, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 595, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 595, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 596, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 596, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 596, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 596, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 596, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 597, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 597, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 597, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 597, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 597, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 598, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 598, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 598, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 598, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 598, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 599, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 599, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 599, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 599, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 599, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 600, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 600, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 600, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 600, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 600, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 601, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 601, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 601, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 601, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 601, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 602, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 602, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 602, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 602, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 602, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 603, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 603, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 603, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 603, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 603, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 604, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 604, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 604, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 604, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 604, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 605, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 605, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 605, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 605, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 605, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 606, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 606, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 606, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 606, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 606, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 607, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 607, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 607, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 607, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 607, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 608, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 608, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 608, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 608, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 608, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 609, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 609, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 609, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 609, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 609, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 610, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 610, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 610, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 610, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 610, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 611, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 611, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 611, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 611, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 611, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 612, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 612, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 612, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 612, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 612, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 613, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 613, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 613, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 613, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 613, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 614, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 614, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 614, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 614, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 614, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 615, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 615, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 615, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 615, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 615, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 616, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 616, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 616, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 616, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 616, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 617, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 617, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 617, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 617, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 617, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 618, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 618, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 618, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 618, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 618, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 619, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 619, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 619, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 619, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 619, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 620, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 620, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 620, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 620, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 620, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 621, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 621, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 621, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 621, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 621, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 622, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 622, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 622, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 622, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 622, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 623, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 623, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 623, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 623, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 623, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 624, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 624, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 624, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 624, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 624, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 625, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 625, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 625, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 625, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 625, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 626, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 626, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 626, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 626, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 626, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 627, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 627, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 627, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 627, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 627, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 628, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 628, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 628, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 628, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 628, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 629, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 629, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 629, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 629, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 629, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 630, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 630, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 630, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 630, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 630, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 631, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 631, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 631, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 631, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 631, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 632, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 632, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 632, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 632, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 632, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 633, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 633, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 633, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 633, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 633, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 634, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 634, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 634, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 634, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 634, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 635, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 635, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 635, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 635, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 635, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 636, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 636, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 636, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 636, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 636, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 637, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 637, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 637, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 637, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 637, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 638, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 638, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 638, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 638, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 638, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 639, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 639, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 639, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 639, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 639, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 640, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 640, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 640, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 640, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 640, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 641, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 641, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 641, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 641, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 641, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 642, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 642, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 642, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 642, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 642, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 643, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 643, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 643, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 643, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 643, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 644, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 644, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 644, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 644, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 644, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 645, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 645, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 645, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 645, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 645, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 646, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 646, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 646, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 646, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 646, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 647, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 647, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 647, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 647, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 647, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 648, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 648, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 648, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 648, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 648, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 649, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 649, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 649, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 649, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 649, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 650, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 650, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 650, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 650, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 650, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 651, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 651, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 651, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 651, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 651, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 652, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 652, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 652, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 652, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 652, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 653, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 653, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 653, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 653, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 653, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 654, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 654, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 654, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 654, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 654, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 655, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 655, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 655, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 655, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 655, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 656, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 656, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 656, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 656, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 656, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 657, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 657, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 657, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 657, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 657, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 658, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 658, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 658, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 658, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 658, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 659, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 659, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 659, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 659, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 659, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 660, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 660, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 660, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 660, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 660, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 661, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 661, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 661, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 661, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 661, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 662, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 662, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 662, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 662, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 662, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 663, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 663, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 663, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 663, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 663, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 664, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 664, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 664, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 664, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 664, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 665, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 665, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 665, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 665, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 665, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 666, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 666, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 666, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 666, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 666, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 667, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 667, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 667, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 667, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 667, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 668, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 668, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 668, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 668, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 668, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 669, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 669, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 669, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 669, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 669, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 670, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 670, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 670, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 670, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 670, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 671, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 671, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 671, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 671, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 671, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 672, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 672, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 672, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 672, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 672, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 673, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 673, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 673, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 673, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 673, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 674, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 674, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 674, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 674, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 674, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 675, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 675, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 675, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 675, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 675, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 676, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 676, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 676, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 676, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 676, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 677, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 677, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 677, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 677, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 677, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 678, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 678, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 678, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 678, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 678, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 679, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 679, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 679, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 679, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 679, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 680, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 680, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 680, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 680, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 680, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 681, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 681, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 681, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 681, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 681, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 682, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 682, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 682, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 682, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 682, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 683, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 683, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 683, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 683, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 683, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 684, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 684, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 684, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 684, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 684, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 685, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 685, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 685, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 685, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 685, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 686, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 686, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 686, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 686, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 686, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 687, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 687, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 687, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 687, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 687, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 688, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 688, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 688, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 688, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 688, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 689, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 689, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 689, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 689, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 689, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 690, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 690, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 690, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 690, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 690, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 691, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 691, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 691, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 691, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 691, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 692, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 692, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 692, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 692, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 692, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 693, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 693, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 693, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 693, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 693, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 694, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 694, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 694, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 694, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 694, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 695, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 695, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 695, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 695, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 695, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 696, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 696, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 696, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 696, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 696, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 697, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 697, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 697, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 697, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 697, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 698, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 698, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 698, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 698, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 698, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 699, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 699, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 699, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 699, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 699, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 700, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 700, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 700, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 700, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 700, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 701, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 701, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 701, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 701, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 701, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 702, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 702, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 702, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 702, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 702, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 703, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 703, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 703, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 703, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 703, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 704, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 704, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 704, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 704, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 704, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 705, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 705, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 705, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 705, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 705, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 706, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 706, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 706, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 706, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 706, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 707, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 707, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 707, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 707, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 707, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 708, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 708, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 708, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 708, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 708, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 709, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 709, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 709, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 709, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 709, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 710, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 710, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 710, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 710, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 710, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 711, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 711, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 711, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 711, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 711, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 712, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 712, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 712, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 712, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 712, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 713, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 713, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 713, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 713, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 713, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 714, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 714, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 714, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 714, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 714, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 715, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 715, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 715, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 715, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 715, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 716, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 716, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 716, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 716, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 716, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 717, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 717, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 717, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 717, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 717, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 718, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 718, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 718, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 718, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 718, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 719, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 719, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 719, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 719, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 719, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 720, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 720, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 720, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 720, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 720, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 721, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 721, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 721, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 721, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 721, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 722, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 722, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 722, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 722, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 722, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 723, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 723, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 723, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 723, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 723, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 724, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 724, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 724, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 724, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 724, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 725, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 725, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 725, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 725, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 725, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 726, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 726, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 726, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 726, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 726, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 727, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 727, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 727, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 727, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 727, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 728, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 728, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 728, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 728, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 728, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 729, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 729, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 729, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 729, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 729, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 730, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 730, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 730, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 730, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 730, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 731, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 731, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 731, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 731, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 731, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 732, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 732, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 732, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 732, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 732, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 733, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 733, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 733, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 733, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 733, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 734, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 734, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 734, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 734, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 734, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 735, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 735, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 735, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 735, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 735, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 736, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 736, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 736, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 736, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 736, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 737, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 737, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 737, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 737, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 737, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 738, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 738, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 738, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 738, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 738, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 739, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 739, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 739, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 739, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 739, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 740, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 740, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 740, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 740, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 740, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 741, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 741, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 741, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 741, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 741, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 742, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 742, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 742, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 742, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 742, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 743, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 743, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 743, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 743, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 743, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 744, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 744, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 744, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 744, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 744, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 745, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 745, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 745, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 745, col:  13):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 745, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 746, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 746, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 746, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 746, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 746, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 747, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 747, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 747, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 747, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 747, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 748, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 748, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 748, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 748, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 748, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 749, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 749, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 749, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 749, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 749, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 750, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 750, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 750, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 750, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 750, col:  27):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 751, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 751, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 751, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 751, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 751, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 752, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 752, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 752, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 752, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 752, col:  23):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 753, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 753, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 753, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 753, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 753, col:  22):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 754, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 754, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 754, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 754, col:  16):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 754, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 755, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 755, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 755, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 755, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 755, col:  24):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 756, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 756, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 756, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 756, col:  19):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 756, col:  30):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 757, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 757, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 757, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 757, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 757, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 758, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 758, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 758, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 758, col:  15):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 758, col:  26):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 759, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 759, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 759, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 759, col:  14):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 759, col:  25):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 760, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 760, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 760, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 760, col:  18):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 760, col:  29):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 761, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 761, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 761, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_OPR       (line: 761, col:  17):	extra space before operator
Error: NO_SPC_BFR_PAR       (line: 761, col:  28):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 762, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 762, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 762, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_PAR       (line: 762, col:  15):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 763, col:   1):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 763, col:   2):	Extra space after parenthesis (brace/bracket)
Error: SPACE_REPLACE_TAB    (line: 763, col:   2):	Found space when expecting tab
Error: NO_SPC_BFR_PAR       (line: 763, col:   9):	Extra space before parenthesis (brace/bracket)
mlx_init.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  14, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  15, col:   1):	Consecutive newlines
Error: NO_ARGS_VOID         (line:  16, col:  19):	Empty function argument requires void
Error: SPACE_EMPTY_LINE     (line:  19, col:   1):	Space on empty line
Error: ASSIGN_IN_CONTROL    (line:  20, col:  16):	Assignment in control structure
Error: SPACE_AFTER_KW       (line:  21, col:  18):	Missing space after keyword
Error: ASSIGN_IN_CONTROL    (line:  22, col:  24):	Assignment in control structure
Error: SPACE_AFTER_KW       (line:  25, col:  18):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line:  29, col:  47):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  30, col:  45):	missing space after operator
Error: SPC_AFTER_PAR        (line:  31, col:  32):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line:  31, col:  33):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  31, col:  33):	missing space before operator
Error: SPC_BFR_OPERATOR     (line:  31, col:  33):	missing space before operator
Error: LINE_TOO_LONG        (line:  40, col:  83):	line too long
Error: SPC_AFTER_OPERATOR   (line:  44, col:  51):	missing space after operator
Error: MIXED_SPACE_TAB      (line:  45, col:  13):	Mixed spaces and tabs
Error: SPC_AFTER_OPERATOR   (line:  45, col:  30):	missing space after operator
Error: TOO_MANY_LINES       (line:  49, col:   1):	Function has more than 25 lines
Error: CONSECUTIVE_NEWLINES (line:  51, col:   1):	Consecutive newlines
Error: TOO_MANY_TABS_FUNC   (line:  58, col:   5):	extra tabs before function name
Error: SPC_AFTER_OPERATOR   (line:  65, col:  52):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  65, col:  59):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  65, col:  66):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  70, col:  21):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  72, col:  35):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  72, col:  35):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  72, col:  55):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  72, col:  60):	missing space after operator
Error: EOL_OPERATOR         (line:  72, col:  75):	Logic operator at the end of line
Error: TOO_MANY_TAB         (line:  73, col:  13):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line:  73, col:  24):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  73, col:  34):	missing space after operator
Error: NO_SPC_AFR_PAR       (line:  73, col:  52):	Extra space after parenthesis (brace/bracket)
Error: NO_SPC_BFR_PAR       (line:  73, col:  54):	Extra space before parenthesis (brace/bracket)
Error: TOO_MANY_TABS_FUNC   (line:  84, col:   5):	extra tabs before function name
Error: SPC_AFTER_OPERATOR   (line:  86, col:  23):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  86, col:  35):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  86, col:  35):	missing space before operator
Error: SPACE_AFTER_KW       (line:  87, col:  28):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line:  87, col:  36):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  87, col:  36):	missing space before operator
Error: TOO_MANY_TAB         (line:  88, col:   1):	Extra tabs for indent level
Error: BRACE_SHOULD_EOL     (line:  88, col:  10):	Expected newline after brace
Error: TOO_MANY_INSTR       (line:  88, col:  11):	Too many instructions on a single line
Error: TOO_MANY_INSTR       (line:  88, col:  41):	Too many instructions on a single line
Error: NO_SPC_AFR_PAR       (line:  88, col:  55):	Extra space after parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  88, col:  61):	Missing tabs for indent level
Error: TOO_MANY_INSTR       (line:  88, col:  61):	Too many instructions on a single line
Error: SPACE_AFTER_KW       (line:  89, col:  26):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line:  89, col:  34):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  89, col:  34):	missing space before operator
Error: TOO_MANY_TAB         (line:  90, col:   1):	Extra tabs for indent level
Error: BRACE_SHOULD_EOL     (line:  90, col:  10):	Expected newline after brace
Error: TOO_MANY_INSTR       (line:  90, col:  11):	Too many instructions on a single line
Error: TOO_MANY_INSTR       (line:  90, col:  41):	Too many instructions on a single line
Error: NO_SPC_AFR_PAR       (line:  90, col:  55):	Extra space after parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  90, col:  61):	Missing tabs for indent level
Error: TOO_MANY_INSTR       (line:  90, col:  61):	Too many instructions on a single line
Error: SPACE_AFTER_KW       (line:  91, col:  28):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line:  91, col:  38):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  91, col:  38):	missing space before operator
Error: TOO_MANY_TAB         (line:  92, col:   1):	Extra tabs for indent level
Error: BRACE_SHOULD_EOL     (line:  92, col:  10):	Expected newline after brace
Error: TOO_MANY_INSTR       (line:  92, col:  11):	Too many instructions on a single line
Error: TOO_MANY_INSTR       (line:  92, col:  43):	Too many instructions on a single line
Error: NO_SPC_AFR_PAR       (line:  92, col:  57):	Extra space after parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  92, col:  63):	Missing tabs for indent level
Error: TOO_MANY_INSTR       (line:  92, col:  63):	Too many instructions on a single line
Error: SPACE_AFTER_KW       (line:  93, col:  26):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line:  93, col:  36):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  93, col:  36):	missing space before operator
Error: TOO_MANY_TAB         (line:  94, col:   1):	Extra tabs for indent level
Error: BRACE_SHOULD_EOL     (line:  94, col:  10):	Expected newline after brace
Error: TOO_MANY_INSTR       (line:  94, col:  11):	Too many instructions on a single line
Error: TOO_MANY_INSTR       (line:  94, col:  43):	Too many instructions on a single line
Error: NO_SPC_AFR_PAR       (line:  94, col:  57):	Extra space after parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  94, col:  63):	Missing tabs for indent level
Error: TOO_MANY_INSTR       (line:  94, col:  63):	Too many instructions on a single line
Error: SPACE_AFTER_KW       (line:  95, col:  28):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line:  95, col:  37):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  95, col:  37):	missing space before operator
Error: TOO_MANY_TAB         (line:  96, col:   1):	Extra tabs for indent level
Error: BRACE_SHOULD_EOL     (line:  96, col:  10):	Expected newline after brace
Error: TOO_MANY_INSTR       (line:  96, col:  11):	Too many instructions on a single line
Error: TOO_MANY_INSTR       (line:  96, col:  42):	Too many instructions on a single line
Error: NO_SPC_AFR_PAR       (line:  96, col:  56):	Extra space after parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  96, col:  62):	Missing tabs for indent level
Error: TOO_MANY_INSTR       (line:  96, col:  62):	Too many instructions on a single line
Error: SPACE_AFTER_KW       (line:  97, col:  26):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line:  97, col:  35):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  97, col:  35):	missing space before operator
Error: TOO_MANY_TAB         (line:  98, col:   1):	Extra tabs for indent level
Error: BRACE_SHOULD_EOL     (line:  98, col:  10):	Expected newline after brace
Error: TOO_MANY_INSTR       (line:  98, col:  11):	Too many instructions on a single line
Error: TOO_MANY_INSTR       (line:  98, col:  42):	Too many instructions on a single line
Error: NO_SPC_AFR_PAR       (line:  98, col:  56):	Extra space after parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  98, col:  62):	Missing tabs for indent level
Error: TOO_MANY_INSTR       (line:  98, col:  62):	Too many instructions on a single line
mlx_int_do_nothing.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  12, col:   1):	Consecutive newlines
Error: EMPTY_LINE_FUNCTION  (line:  15, col:   1):	Empty line in function
Error: SPACE_EMPTY_LINE     (line:  15, col:   1):	Space on empty line
mlx_expose_hook.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  14, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  15, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  16, col:   1):	Consecutive newlines
Error: TOO_MANY_TABS_FUNC   (line:  17, col:   5):	extra tabs before function name
Error: SPC_AFTER_OPERATOR   (line:  17, col:  40):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  17, col:  55):	missing space after operator
Error: SPACE_REPLACE_TAB    (line:  19, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  20, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  21, col:   3):	Found space when expecting tab
mlx_int_str_to_wordtab.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  14, col:   1):	Consecutive newlines
Error: SPC_AFTER_OPERATOR   (line:  15, col:  30):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  15, col:  41):	missing space after operator
Error: TOO_FEW_TAB          (line:  17, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  17, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  18, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  18, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  19, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  19, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  20, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  20, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  22, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  23, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  23, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  23, col:  12):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  23, col:  12):	missing space before operator
Error: TOO_FEW_TAB          (line:  24, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  24, col:   5):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  25, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  26, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  26, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  26, col:  15):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  26, col:  15):	missing space before operator
Error: SPC_BFR_OPERATOR     (line:  26, col:  21):	missing space before operator
Error: TOO_FEW_TAB          (line:  27, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  27, col:   5):	Space on empty line
Error: SPACE_REPLACE_TAB    (line:  28, col:   7):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  29, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  30, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  30, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  31, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  31, col:   9):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  32, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  32, col:  11):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  33, col:   7):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  34, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  35, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  35, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  36, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  36, col:   3):	Found space when expecting tab
Error: CONSECUTIVE_NEWLINES (line:  39, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  40, col:   1):	Consecutive newlines
Error: SPC_AFTER_OPERATOR   (line:  41, col:  35):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  41, col:  46):	missing space after operator
Error: TOO_FEW_TAB          (line:  43, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  43, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  44, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  44, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  45, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  45, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  46, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  46, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  47, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  47, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  49, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  50, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  50, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  50, col:  12):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  50, col:  12):	missing space before operator
Error: TOO_FEW_TAB          (line:  51, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  51, col:   5):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  52, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  53, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  54, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  54, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  54, col:  15):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  54, col:  15):	missing space before operator
Error: SPC_BFR_OPERATOR     (line:  54, col:  21):	missing space before operator
Error: TOO_FEW_TAB          (line:  55, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  55, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  56, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  56, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  56, col:  15):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  56, col:  15):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  57, col:  13):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  57, col:  13):	missing space before operator
Error: TOO_FEW_TAB          (line:  58, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  58, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  59, col:   1):	Missing tabs for indent level
Error: MIXED_SPACE_TAB      (line:  60, col:   1):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line:  60, col:   5):	Two or more consecutives spaces
Error: MIXED_SPACE_TAB      (line:  61, col:   1):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line:  61, col:   5):	Two or more consecutives spaces
Error: MIXED_SPACE_TAB      (line:  62, col:   1):	Mixed spaces and tabs
Error: TOO_FEW_TAB          (line:  62, col:   1):	Missing tabs for indent level
Error: CONSECUTIVE_SPC      (line:  62, col:   5):	Two or more consecutives spaces
Error: MIXED_SPACE_TAB      (line:  63, col:   1):	Mixed spaces and tabs
Error: TOO_FEW_TAB          (line:  63, col:   1):	Missing tabs for indent level
Error: CONSECUTIVE_SPC      (line:  63, col:   5):	Two or more consecutives spaces
Error: MIXED_SPACE_TAB      (line:  64, col:   1):	Mixed spaces and tabs
Error: TOO_FEW_TAB          (line:  64, col:   1):	Missing tabs for indent level
Error: CONSECUTIVE_SPC      (line:  64, col:   5):	Two or more consecutives spaces
Error: TOO_FEW_TAB          (line:  65, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  66, col:   7):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  67, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  68, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  68, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  69, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  69, col:   3):	Found space when expecting tab
Error: TOO_MANY_LINES       (line:  70, col:   1):	Function has more than 25 lines
Error: CONSECUTIVE_NEWLINES (line:  72, col:   1):	Consecutive newlines
Error: TOO_FEW_TAB          (line:  75, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  75, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  76, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  76, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  77, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  77, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  78, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  78, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  80, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  81, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  82, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  83, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  83, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  83, col:  13):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  83, col:  13):	missing space before operator
Error: TOO_FEW_TAB          (line:  84, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  84, col:   3):	Space on empty line
Error: TOO_FEW_TAB          (line:  85, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  85, col:   5):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  85, col:  17):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  85, col:  17):	missing space before operator
Error: SPC_AFTER_PAR        (line:  85, col:  21):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line:  85, col:  22):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  85, col:  22):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  85, col:  36):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  85, col:  36):	missing space before operator
Error: SPC_AFTER_PAR        (line:  85, col:  40):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line:  85, col:  41):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  85, col:  41):	missing space before operator
Error: SPACE_REPLACE_TAB    (line:  86, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  87, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  87, col:   5):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  87, col:  14):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  87, col:  14):	missing space before operator
Error: SPACE_REPLACE_TAB    (line:  88, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  89, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  89, col:   5):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  89, col:  17):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  89, col:  17):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  89, col:  31):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  89, col:  31):	missing space before operator
Error: SPC_AFTER_PAR        (line:  89, col:  35):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line:  89, col:  36):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  89, col:  36):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  89, col:  50):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  89, col:  50):	missing space before operator
Error: SPC_AFTER_PAR        (line:  89, col:  54):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line:  89, col:  55):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  89, col:  55):	missing space before operator
Error: SPACE_REPLACE_TAB    (line:  90, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  91, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  91, col:   3):	Space on empty line
Error: TOO_FEW_TAB          (line:  92, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  92, col:   3):	Found space when expecting tab
Error: ASSIGN_IN_CONTROL    (line:  92, col:  13):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line:  92, col:  24):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  92, col:  24):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  92, col:  33):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  92, col:  33):	missing space before operator
Error: TOO_FEW_TAB          (line:  93, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  93, col:   5):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  94, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  95, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  96, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  96, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  96, col:  13):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  96, col:  13):	missing space before operator
Error: TOO_FEW_TAB          (line:  97, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  97, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  98, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  98, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  98, col:  19):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  98, col:  19):	missing space before operator
Error: SPC_AFTER_PAR        (line:  98, col:  23):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line:  98, col:  24):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  98, col:  24):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  98, col:  38):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  98, col:  38):	missing space before operator
Error: SPC_AFTER_PAR        (line:  98, col:  42):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line:  98, col:  43):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  98, col:  43):	missing space before operator
Error: TOO_FEW_TAB          (line:  99, col:   1):	Missing tabs for indent level
Error: MIXED_SPACE_TAB      (line: 100, col:   1):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line: 100, col:   5):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line: 100, col:  12):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 100, col:  12):	missing space before operator
Error: MIXED_SPACE_TAB      (line: 101, col:   1):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line: 101, col:   5):	Two or more consecutives spaces
Error: TOO_FEW_TAB          (line: 102, col:   1):	Missing tabs for indent level
Error: TOO_FEW_TAB          (line: 103, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 103, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 103, col:  16):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 103, col:  16):	missing space before operator
Error: TOO_FEW_TAB          (line: 104, col:   1):	Missing tabs for indent level
Error: MIXED_SPACE_TAB      (line: 105, col:   1):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line: 105, col:   5):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line: 105, col:  25):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 105, col:  25):	missing space before operator
Error: MIXED_SPACE_TAB      (line: 106, col:   1):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line: 106, col:   5):	Two or more consecutives spaces
Error: TOO_FEW_TAB          (line: 107, col:   1):	Missing tabs for indent level
Error: TOO_FEW_TAB          (line: 108, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 108, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 108, col:  19):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 108, col:  19):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 108, col:  33):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 108, col:  33):	missing space before operator
Error: SPC_AFTER_PAR        (line: 108, col:  37):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 108, col:  38):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 108, col:  38):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 108, col:  52):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 108, col:  52):	missing space before operator
Error: SPC_AFTER_PAR        (line: 108, col:  56):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 108, col:  57):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 108, col:  57):	missing space before operator
Error: TOO_FEW_TAB          (line: 110, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 110, col:   5):	Space on empty line
Error: SPACE_REPLACE_TAB    (line: 111, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 112, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 112, col:   3):	Found space when expecting tab
Error: TOO_MANY_LINES       (line: 113, col:   1):	Function has more than 25 lines
mlx_int_set_win_event_mask.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  14, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  15, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  16, col:   1):	Consecutive newlines
Error: TOO_FEW_TAB          (line:  19, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  19, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  20, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  20, col:   3):	Found space when expecting tab
Error: MISALIGNED_VAR_DECL  (line:  20, col:  13):	Misaligned variable declaration
Error: TOO_FEW_TAB          (line:  21, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  21, col:   3):	Found space when expecting tab
Error: MISALIGNED_VAR_DECL  (line:  21, col:  13):	Misaligned variable declaration
Error: TOO_FEW_TAB          (line:  22, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  22, col:   3):	Found space when expecting tab
Error: MISALIGNED_VAR_DECL  (line:  22, col:  25):	Misaligned variable declaration
Error: SPACE_REPLACE_TAB    (line:  24, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  25, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  25, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  26, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  26, col:   5):	Space on empty line
Error: SPACE_REPLACE_TAB    (line:  27, col:   7):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  28, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  29, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  29, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  31, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  31, col:   7):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  32, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  33, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  33, col:   5):	Space on empty line
mlx_pixel_put.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  14, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  15, col:   1):	Consecutive newlines
Error: TOO_MANY_TABS_FUNC   (line:  16, col:   5):	extra tabs before function name
Error: SPC_AFTER_OPERATOR   (line:  16, col:  35):	missing space after operator
Error: MIXED_SPACE_TAB      (line:  17, col:   9):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line:  17, col:  13):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line:  17, col:  24):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  17, col:  30):	missing space after operator
Error: TOO_MANY_ARGS        (line:  17, col:  41):	Function has more than 4 arguments
Error: TOO_FEW_TAB          (line:  19, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  19, col:   4):	Found space when expecting tab
Error: SPACE_EMPTY_LINE     (line:  20, col:   1):	Space on empty line
Error: SPACE_REPLACE_TAB    (line:  21, col:   4):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  21, col:  49):	missing space after operator
Error: TOO_FEW_TAB          (line:  22, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  22, col:   4):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  22, col:  27):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  22, col:  35):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  22, col:  48):	missing space after operator
Error: TOO_FEW_TAB          (line:  23, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  23, col:   4):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  23, col:  28):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  23, col:  40):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  23, col:  48):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  23, col:  50):	missing space after operator
Error: TOO_FEW_TAB          (line:  24, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  24, col:   4):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  25, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  25, col:   6):	Found space when expecting tab
mlx_int_anti_resize_win.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  13, col:   1):	Consecutive newlines
Error: SPC_AFTER_OPERATOR   (line:  14, col:  41):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  14, col:  52):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  14, col:  58):	missing space after operator
Error: TOO_FEW_TAB          (line:  16, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  16, col:   3):	Found space when expecting tab
Error: CONSECUTIVE_SPC      (line:  16, col:  13):	Two or more consecutives spaces
Error: SPACE_REPLACE_TAB    (line:  16, col:  13):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  17, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  17, col:   3):	Found space when expecting tab
Error: MISALIGNED_VAR_DECL  (line:  17, col:  13):	Misaligned variable declaration
Error: SPACE_EMPTY_LINE     (line:  18, col:   1):	Space on empty line
Error: TOO_FEW_TAB          (line:  19, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  19, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  19, col:  34):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  19, col:  38):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  19, col:  45):	missing space after operator
Error: SPACE_REPLACE_TAB    (line:  20, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  21, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  22, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  23, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  24, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  25, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  26, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  27, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  27, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  27, col:  34):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  27, col:  38):	missing space after operator
mlx_loop.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: SPACE_REPLACE_TAB    (line:  14, col:   7):	Found space when expecting tab
Error: EXP_PARENTHESIS      (line:  14, col:  35):	Expected parenthesis
Error: NO_ARGS_VOID         (line:  14, col:  40):	Empty function argument requires void
Error: TOO_MANY_TABS_FUNC   (line:  31, col:   9):	extra tabs before function name
Error: TOO_MANY_TABS_FUNC   (line:  37, col:   9):	extra tabs before function name
Error: SPC_AFTER_OPERATOR   (line:  48, col:  37):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  50, col:  39):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  50, col:  39):	missing space before operator
Error: EMPTY_LINE_FUNCTION  (line:  52, col:   1):	Empty line in function
Error: LINE_TOO_LONG        (line:  53, col:  83):	line too long
mlx_screen_size.c: Error!
Error: INVALID_HEADER       (line:   1, col:   1):	Missing or invalid 42 header
Error: TOO_MANY_TABS_FUNC   (line:   3, col:   5):	extra tabs before function name
Error: FORBIDDEN_CHAR_NAME  (line:   5, col:  25):	user defined identifiers should contain only lowercase characters, digits or '_'
Error: SPACE_EMPTY_LINE     (line:   8, col:   1):	Space on empty line
mlx_new_window.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  21, col:   1):	Consecutive newlines
Error: SPC_AFTER_OPERATOR   (line:  22, col:  37):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  22, col:  48):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  22, col:  59):	missing space after operator
Error: WRONG_SCOPE_COMMENT  (line:  31, col:   5):	Comment is invalid in this scope
Error: WRONG_SCOPE_COMMENT  (line:  35, col:   5):	Comment is invalid in this scope
Error: TAB_INSTEAD_SPC      (line:  36, col:  32):	Found tab when expecting space
Error: WRONG_SCOPE_COMMENT  (line:  36, col:  33):	Comment is invalid in this scope
Error: WRONG_SCOPE_COMMENT  (line:  36, col:  33):	Comment is invalid in this scope
Error: ASSIGN_IN_CONTROL    (line:  37, col:  19):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line:  39, col:  50):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  39, col:  61):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  39, col:  63):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  39, col:  65):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  39, col:  72):	missing space after operator
Error: TOO_MANY_TAB         (line:  40, col:   1):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line:  40, col:  22):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  40, col:  37):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  40, col:  49):	missing space after operator
Error: TOO_MANY_TAB         (line:  41, col:   1):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line:  41, col:  32):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  41, col:  32):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  41, col:  44):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  41, col:  44):	missing space before operator
Error: SPC_BFR_OPERATOR     (line:  41, col:  58):	missing space before operator
Error: EOL_OPERATOR         (line:  41, col:  59):	Logic operator at the end of line
Error: TOO_MANY_TAB         (line:  42, col:   1):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line:  42, col:  31):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  43, col:  33):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  43, col:  49):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  43, col:  56):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  44, col:  29):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  44, col:  45):	missing space after operator
Error: LINE_TOO_LONG        (line:  45, col:  82):	line too long
Error: SPC_AFTER_OPERATOR   (line:  49, col:  42):	missing space after operator
Error: TOO_MANY_TAB         (line:  50, col:   1):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line:  50, col:  27):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  50, col:  27):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  50, col:  39):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  50, col:  39):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  50, col:  52):	missing space after operator
Error: WRONG_SCOPE_COMMENT  (line:  53, col:   5):	Comment is invalid in this scope
Error: SPC_AFTER_OPERATOR   (line:  59, col:  29):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  60, col:  35):	missing space after operator
Error: TOO_MANY_LINES       (line:  62, col:   1):	Function has more than 25 lines
mlx_ext_randr.c: Error!
Error: EMPTY_LINE_FILE_START (line:   1, col:   1):	Empty line at start of file
Error: INVALID_HEADER       (line:   1, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:   2, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:   3, col:   1):	Consecutive newlines
Error: GLOBAL_VAR_NAMING    (line:  11, col:   9):	Global variable must start with g_
Error: CONSECUTIVE_NEWLINES (line:  13, col:   1):	Consecutive newlines
Error: TOO_MANY_TABS_FUNC   (line:  14, col:   9):	extra tabs before function name
Error: TOO_FEW_TAB          (line:  16, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  16, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  17, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  17, col:   3):	Found space when expecting tab
Error: MISALIGNED_VAR_DECL  (line:  17, col:  17):	Misaligned variable declaration
Error: TOO_FEW_TAB          (line:  18, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  18, col:   3):	Found space when expecting tab
Error: MISALIGNED_VAR_DECL  (line:  18, col:  17):	Misaligned variable declaration
Error: TOO_FEW_TAB          (line:  19, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  19, col:   3):	Found space when expecting tab
Error: MISALIGNED_VAR_DECL  (line:  19, col:  25):	Misaligned variable declaration
Error: TOO_FEW_TAB          (line:  20, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  20, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  21, col:   1):	Missing tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line:  21, col:   1):	Too many variables declarations in a function
Error: SPACE_REPLACE_TAB    (line:  21, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  22, col:   1):	Missing tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line:  22, col:   1):	Too many variables declarations in a function
Error: SPACE_REPLACE_TAB    (line:  22, col:   3):	Found space when expecting tab
Error: MISALIGNED_VAR_DECL  (line:  22, col:  17):	Misaligned variable declaration
Error: TOO_FEW_TAB          (line:  23, col:   1):	Missing tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line:  23, col:   1):	Too many variables declarations in a function
Error: SPACE_REPLACE_TAB    (line:  23, col:   3):	Found space when expecting tab
Error: MISALIGNED_VAR_DECL  (line:  23, col:  17):	Misaligned variable declaration
Error: TOO_FEW_TAB          (line:  24, col:   1):	Missing tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line:  24, col:   1):	Too many variables declarations in a function
Error: SPACE_REPLACE_TAB    (line:  24, col:   3):	Found space when expecting tab
Error: MISALIGNED_VAR_DECL  (line:  24, col:  17):	Misaligned variable declaration
Error: TOO_FEW_TAB          (line:  26, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  26, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  27, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  27, col:   5):	Found space when expecting tab
Error: EMPTY_LINE_FUNCTION  (line:  28, col:   1):	Empty line in function
Error: SPACE_REPLACE_TAB    (line:  29, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  30, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  31, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  32, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  33, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  33, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  34, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  34, col:   5):	Space on empty line
Error: SPACE_REPLACE_TAB    (line:  35, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  36, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  36, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  37, col:   1):	Missing tabs for indent level
Error: MIXED_SPACE_TAB      (line:  38, col:   1):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line:  38, col:   5):	Two or more consecutives spaces
Error: MIXED_SPACE_TAB      (line:  39, col:   1):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line:  39, col:   5):	Two or more consecutives spaces
Error: TOO_FEW_TAB          (line:  40, col:   1):	Missing tabs for indent level
Error: TOO_FEW_TAB          (line:  41, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  41, col:   7):	Space on empty line
Error: TOO_FEW_TAB          (line:  42, col:   1):	Missing tabs for indent level
Error: TOO_FEW_TAB          (line:  43, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  43, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  44, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  44, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  45, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  45, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  46, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  46, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  47, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  47, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  48, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  48, col:   5):	Space on empty line
Error: EMPTY_LINE_FUNCTION  (line:  49, col:   1):	Empty line in function
Error: SPACE_EMPTY_LINE     (line:  49, col:   1):	Space on empty line
Error: SPACE_REPLACE_TAB    (line:  50, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  51, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  52, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  52, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  53, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  53, col:   5):	Space on empty line
Error: SPACE_REPLACE_TAB    (line:  54, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  55, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  55, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  56, col:   1):	Missing tabs for indent level
Error: MIXED_SPACE_TAB      (line:  57, col:   1):	Mixed spaces and tabs
Error: TOO_FEW_TAB          (line:  57, col:   1):	Missing tabs for indent level
Error: CONSECUTIVE_SPC      (line:  57, col:   5):	Two or more consecutives spaces
Error: LINE_TOO_LONG        (line:  57, col:  83):	line too long
Error: EOL_OPERATOR         (line:  57, col:  84):	Logic operator at the end of line
Error: TOO_FEW_TAB          (line:  58, col:   5):	Missing tabs for indent level
Error: LINE_TOO_LONG        (line:  58, col:  82):	line too long
Error: EOL_OPERATOR         (line:  58, col:  89):	Logic operator at the end of line
Error: TOO_FEW_TAB          (line:  59, col:   5):	Missing tabs for indent level
Error: NO_SPC_AFR_PAR       (line:  59, col:  67):	Extra space after parenthesis (brace/bracket)
Error: NO_SPC_BFR_PAR       (line:  59, col:  69):	Extra space before parenthesis (brace/bracket)
Error: MIXED_SPACE_TAB      (line:  60, col:   1):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line:  60, col:   5):	Two or more consecutives spaces
Error: TOO_FEW_TAB          (line:  61, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  61, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  62, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  62, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  63, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  63, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  64, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  64, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  65, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  65, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  66, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  66, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  67, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  67, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  68, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  68, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  69, col:   5):	Found space when expecting tab
Error: LINE_TOO_LONG        (line:  69, col:  24):	line too long
Error: WRONG_SCOPE_COMMENT  (line:  69, col:  24):	Comment is invalid in this scope
Error: WRONG_SCOPE_COMMENT  (line:  69, col:  24):	Comment is invalid in this scope
Error: LINE_TOO_LONG        (line:  69, col:  85):	line too long
Error: SPACE_REPLACE_TAB    (line:  70, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  71, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  71, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  72, col:   5):	Found space when expecting tab
Error: EMPTY_LINE_FUNCTION  (line:  73, col:   1):	Empty line in function
Error: SPACE_REPLACE_TAB    (line:  74, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  75, col:   3):	Found space when expecting tab
Error: EMPTY_LINE_FUNCTION  (line:  76, col:   1):	Empty line in function
Error: SPACE_REPLACE_TAB    (line:  77, col:   3):	Found space when expecting tab
Error: LINE_TOO_LONG        (line:  77, col:  91):	line too long
Error: TOO_FEW_TAB          (line:  78, col:   1):	Missing tabs for indent level
Error: MIXED_SPACE_TAB      (line:  78, col:   5):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line:  78, col:   9):	Two or more consecutives spaces
Error: TOO_FEW_TAB          (line:  79, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  79, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  80, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  80, col:   5):	Found space when expecting tab
Error: LINE_TOO_LONG        (line:  80, col:  84):	line too long
Error: TOO_FEW_TAB          (line:  81, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  81, col:   3):	Space on empty line
Error: TOO_FEW_TAB          (line:  82, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  82, col:   5):	Found space when expecting tab
Error: EMPTY_LINE_FUNCTION  (line:  83, col:   1):	Empty line in function
Error: SPACE_EMPTY_LINE     (line:  83, col:   1):	Space on empty line
Error: TOO_FEW_TAB          (line:  84, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  84, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  85, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  85, col:   3):	Found space when expecting tab
Error: EMPTY_LINE_FUNCTION  (line:  86, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line:  87, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  87, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  88, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  88, col:   5):	Space on empty line
Error: LINE_TOO_LONG        (line:  89, col:   1):	line too long
Error: SPACE_EMPTY_LINE     (line:  89, col:   7):	Space on empty line
Error: WRONG_SCOPE_COMMENT  (line:  89, col:   7):	Comment is invalid in this scope
Error: LINE_TOO_LONG        (line:  89, col: 125):	line too long
Error: TOO_FEW_TAB          (line:  90, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  90, col:   7):	Found space when expecting tab
Error: LINE_TOO_LONG        (line:  90, col:  84):	line too long
Error: TOO_FEW_TAB          (line:  91, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  91, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  92, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  92, col:   3):	Space on empty line
Error: TOO_FEW_TAB          (line:  93, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  93, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  94, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  94, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  95, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  95, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  96, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  96, col:   5):	Space on empty line
Error: EMPTY_LINE_FUNCTION  (line:  97, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line:  98, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  98, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  99, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  99, col:   3):	Found space when expecting tab
Error: EMPTY_LINE_FUNCTION  (line: 100, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line: 101, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 101, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 102, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 102, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 103, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 103, col:   3):	Found space when expecting tab
Error: TOO_MANY_LINES       (line: 104, col:   1):	Function has more than 25 lines
mlx_put_image_to_window.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  12, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  15, col:   1):	Consecutive newlines
Error: SPC_AFTER_OPERATOR   (line:  16, col:  41):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  16, col:  57):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  17, col:  22):	missing space after operator
Error: TOO_MANY_ARGS        (line:  17, col:  29):	Function has more than 4 arguments
Error: TOO_FEW_TAB          (line:  19, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  19, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  21, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  22, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  22, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  23, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  23, col:   5):	Space on empty line
Error: SPACE_REPLACE_TAB    (line:  24, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  25, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  25, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  26, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  26, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  27, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  27, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  27, col:  16):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  27, col:  16):	missing space before operator
Error: TOO_FEW_TAB          (line:  28, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  28, col:   5):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  28, col:  31):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  28, col:  61):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  28, col:  63):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  28, col:  65):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  28, col:  67):	missing space after operator
Error: TOO_FEW_TAB          (line:  29, col:   1):	Missing tabs for indent level
Error: MIXED_SPACE_TAB      (line:  29, col:   5):	Mixed spaces and tabs
Error: SPC_AFTER_OPERATOR   (line:  29, col:  20):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  29, col:  32):	missing space after operator
Error: TOO_FEW_TAB          (line:  30, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  30, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  30, col:  16):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  30, col:  16):	missing space before operator
Error: TOO_FEW_TAB          (line:  31, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  31, col:   5):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  31, col:  28):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  31, col:  58):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  31, col:  60):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  31, col:  62):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  31, col:  64):	missing space after operator
Error: MIXED_SPACE_TAB      (line:  32, col:   1):	Mixed spaces and tabs
Error: TOO_FEW_TAB          (line:  32, col:   1):	Missing tabs for indent level
Error: CONSECUTIVE_SPC      (line:  32, col:   5):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line:  32, col:  21):	missing space after operator
Error: TOO_FEW_TAB          (line:  33, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  33, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  33, col:  26):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  33, col:  35):	missing space after operator
Error: MIXED_SPACE_TAB      (line:  34, col:   1):	Mixed spaces and tabs
Error: TOO_FEW_TAB          (line:  34, col:   1):	Missing tabs for indent level
Error: CONSECUTIVE_SPC      (line:  34, col:   5):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line:  34, col:  10):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  34, col:  12):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  34, col:  23):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  34, col:  35):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  34, col:  37):	missing space after operator
Error: TOO_FEW_TAB          (line:  35, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  35, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  36, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  36, col:   5):	Found space when expecting tab
mlx_new_image.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  12, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  13, col:   1):	Consecutive newlines
Error: TAB_INSTEAD_SPC      (line:  20, col:  20):	Found tab when expecting space
Error: MACRO_NAME_CAPITAL   (line:  20, col:  21):	Macro name must be capitalized
Error: FORBIDDEN_CHAR_NAME  (line:  22, col:   5):	user defined identifiers should contain only lowercase characters, digits or '_'
Error: GLOBAL_VAR_NAMING    (line:  22, col:   5):	Global variable must start with g_
Error: SPC_AFTER_OPERATOR   (line:  24, col:  26):	missing space after operator
Error: TOO_FEW_TAB          (line:  26, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  26, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  26, col:  23):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  26, col:  23):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  26, col:  46):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  26, col:  46):	missing space before operator
Error: TOO_FEW_TAB          (line:  27, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  27, col:   5):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  27, col:  12):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  27, col:  28):	missing space after operator
Error: SPACE_REPLACE_TAB    (line:  28, col:   3):	Found space when expecting tab
Error: CONSECUTIVE_NEWLINES (line:  31, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  36, col:   1):	Consecutive newlines
Error: SPC_AFTER_OPERATOR   (line:  37, col:  45):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  37, col:  55):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  37, col:  66):	missing space after operator
Error: TOO_FEW_TAB          (line:  39, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  39, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  40, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  40, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  42, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  42, col:   3):	Found space when expecting tab
Error: ASSIGN_IN_CONTROL    (line:  42, col:  13):	Assignment in control structure
Error: TOO_FEW_TAB          (line:  43, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  43, col:   5):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  44, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  44, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  44, col:  12):	missing space after operator
Error: SPACE_REPLACE_TAB    (line:  45, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  46, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  46, col:  45):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  46, col:  58):	missing space after operator
Error: MIXED_SPACE_TAB      (line:  47, col:   9):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line:  47, col:  13):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line:  47, col:  26):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  47, col:  36):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  47, col:  48):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  47, col:  54):	missing space after operator
Error: TOO_FEW_TAB          (line:  48, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  48, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  49, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  49, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  50, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  50, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  51, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  51, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  52, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  52, col:   5):	Space on empty line
Error: SPACE_REPLACE_TAB    (line:  53, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  54, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  55, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  56, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  57, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  58, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  58, col:  38):	missing space after operator
Error: SPC_BFR_PAR          (line:  58, col:  39):	Missing space before parenthesis (brace/bracket)
Error: SPC_BFR_OPERATOR     (line:  58, col:  45):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  58, col:  49):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  58, col:  49):	missing space before operator
Error: SPACE_AFTER_KW       (line:  58, col:  50):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line:  58, col:  56):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  58, col:  56):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  58, col:  58):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  58, col:  68):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  58, col:  68):	missing space before operator
Error: TOO_FEW_TAB          (line:  59, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  59, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  59, col:  21):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  59, col:  21):	missing space before operator
Error: SPC_BFR_OPERATOR     (line:  59, col:  21):	missing space before operator
Error: TOO_FEW_TAB          (line:  60, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  60, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  61, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  61, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  62, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  62, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  63, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  63, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  64, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  64, col:   5):	Space on empty line
Error: SPACE_REPLACE_TAB    (line:  65, col:   3):	Found space when expecting tab
Error: MULT_ASSIGN_LINE     (line:  65, col:  32):	Multiple assignations on a single line
Error: MULT_ASSIGN_LINE     (line:  65, col:  51):	Multiple assignations on a single line
Error: SPC_AFTER_OPERATOR   (line:  65, col:  73):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  65, col:  75):	missing space after operator
Error: TOO_FEW_TAB          (line:  66, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  66, col:   3):	Found space when expecting tab
Error: SPC_BFR_OPERATOR     (line:  66, col:  16):	missing space before operator
Error: SPC_BFR_PAR          (line:  66, col:  18):	Missing space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  67, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  67, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  68, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  68, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  68, col:  28):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  68, col:  37):	missing space after operator
Error: TOO_FEW_TAB          (line:  69, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  69, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  70, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  70, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  71, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  71, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  72, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  72, col:   5):	Space on empty line
Error: SPACE_REPLACE_TAB    (line:  73, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  74, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  75, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  76, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  76, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  76, col:  32):	missing space after operator
Error: EOL_OPERATOR         (line:  76, col:  46):	Logic operator at the end of line
Error: TOO_FEW_TAB          (line:  77, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  77, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  77, col:   8):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  77, col:   8):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  77, col:  28):	missing space after operator
Error: TOO_FEW_TAB          (line:  78, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  78, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  79, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  79, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  80, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  80, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  81, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  81, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  81, col:  28):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  81, col:  37):	missing space after operator
Error: TOO_FEW_TAB          (line:  82, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  82, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  83, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  83, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  84, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  84, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  85, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  85, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  86, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  86, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  87, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  87, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  87, col:  24):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  87, col:  33):	missing space after operator
Error: TOO_FEW_TAB          (line:  88, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  88, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  88, col:  24):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  88, col:  24):	missing space before operator
Error: TOO_FEW_TAB          (line:  89, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  89, col:   5):	Space on empty line
Error: SPACE_REPLACE_TAB    (line:  90, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  90, col:  48):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  90, col:  59):	missing space after operator
Error: MIXED_SPACE_TAB      (line:  91, col:  13):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line:  91, col:  17):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line:  91, col:  30):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  91, col:  36):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  91, col:  43):	missing space after operator
Error: SPACE_REPLACE_TAB    (line:  92, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  93, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  93, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  94, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  94, col:   3):	Space on empty line
Error: TOO_FEW_TAB          (line:  95, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  95, col:   5):	Space on empty line
Error: SPACE_REPLACE_TAB    (line:  96, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  96, col:  45):	missing space after operator
Error: TOO_FEW_TAB          (line:  97, col:   1):	Missing tabs for indent level
Error: MIXED_SPACE_TAB      (line:  97, col:   9):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line:  97, col:  13):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line:  97, col:  25):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  97, col:  32):	missing space after operator
Error: SPACE_REPLACE_TAB    (line:  98, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  99, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  99, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line: 100, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 100, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 101, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 101, col:   5):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 102, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 102, col:   3):	Found space when expecting tab
Error: TOO_MANY_LINES       (line: 103, col:   1):	Function has more than 25 lines
Error: CONSECUTIVE_NEWLINES (line: 105, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line: 106, col:   1):	Consecutive newlines
Error: SPC_AFTER_OPERATOR   (line: 107, col:  40):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 107, col:  62):	missing space after operator
Error: TOO_FEW_TAB          (line: 109, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 109, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 111, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 111, col:   3):	Found space when expecting tab
Error: ASSIGN_IN_CONTROL    (line: 111, col:  13):	Assignment in control structure
Error: TOO_FEW_TAB          (line: 112, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 112, col:   5):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 113, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 113, col:   3):	Found space when expecting tab
Error: ASSIGN_IN_CONTROL    (line: 113, col:  19):	Assignment in control structure
Error: SPC_BFR_OPERATOR     (line: 113, col:  34):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 113, col:  38):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 113, col:  38):	missing space before operator
Error: SPACE_AFTER_KW       (line: 113, col:  39):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line: 113, col:  45):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 113, col:  45):	missing space before operator
Error: TOO_FEW_TAB          (line: 114, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 114, col:   3):	Space on empty line
Error: TOO_FEW_TAB          (line: 115, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 115, col:   5):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 116, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 116, col:   5):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 117, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 117, col:   3):	Space on empty line
Error: TOO_FEW_TAB          (line: 118, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 118, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 118, col:  18):	missing space after operator
Error: SPC_BFR_PAR          (line: 118, col:  19):	Missing space before parenthesis (brace/bracket)
Error: SPC_BFR_OPERATOR     (line: 118, col:  25):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 118, col:  29):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 118, col:  29):	missing space before operator
Error: SPACE_AFTER_KW       (line: 118, col:  30):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line: 118, col:  36):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 118, col:  36):	missing space before operator
Error: SPACE_REPLACE_TAB    (line: 119, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 119, col:  42):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 119, col:  55):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 119, col:  67):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 119, col:  74):	missing space after operator
Error: MIXED_SPACE_TAB      (line: 120, col:   9):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line: 120, col:  13):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line: 120, col:  26):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 120, col:  32):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 120, col:  39):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 120, col:  42):	missing space after operator
Error: TOO_FEW_TAB          (line: 121, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 121, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 122, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 122, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line: 123, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 123, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 124, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 124, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 125, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 125, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 126, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 126, col:   5):	Space on empty line
Error: SPACE_REPLACE_TAB    (line: 127, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line: 128, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line: 129, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line: 130, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line: 131, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line: 132, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 132, col:  41):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 132, col:  52):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 132, col:  58):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 132, col:  65):	missing space after operator
Error: SPACE_REPLACE_TAB    (line: 133, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line: 134, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 135, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 135, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 136, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 136, col:   5):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 137, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 137, col:   3):	Found space when expecting tab
Error: TOO_MANY_LINES       (line: 138, col:   1):	Function has more than 25 lines
Error: CONSECUTIVE_NEWLINES (line: 140, col:   1):	Consecutive newlines
Error: SPC_AFTER_OPERATOR   (line: 141, col:  36):	missing space after operator
Error: TOO_FEW_TAB          (line: 143, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 143, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 145, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 145, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 146, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 146, col:   5):	Found space when expecting tab
Error: ASSIGN_IN_CONTROL    (line: 146, col:  13):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line: 146, col:  42):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 146, col:  48):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 146, col:  55):	missing space after operator
Error: TOO_FEW_TAB          (line: 147, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 147, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 148, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 148, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 148, col:  33):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 148, col:  39):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 148, col:  46):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 151, col:  37):	missing space after operator
Error: TOO_FEW_TAB          (line: 153, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 153, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 155, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 155, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 156, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 156, col:   5):	Found space when expecting tab
Error: ASSIGN_IN_CONTROL    (line: 156, col:  13):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line: 156, col:  42):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 156, col:  48):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 156, col:  55):	missing space after operator
Error: TOO_FEW_TAB          (line: 157, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 157, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 158, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 158, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 158, col:  33):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 158, col:  39):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 158, col:  46):	missing space after operator
mlx_xpm.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: SPACE_REPLACE_TAB    (line:  14, col:  25):	Found space when expecting tab
Error: GLOBAL_VAR_NAMING    (line:  14, col:  26):	Global variable must start with g_
Error: CONSECUTIVE_NEWLINES (line:  16, col:   1):	Consecutive newlines
Error: TAB_INSTEAD_SPC      (line:  17, col:  17):	Found tab when expecting space
Error: PREPROC_CONSTANT     (line:  17, col:  29):	Preprocessor statement must only contain constant defines
Error: PREPROC_CONSTANT     (line:  17, col:  35):	Preprocessor statement must only contain constant defines
Error: TOO_MANY_VALS        (line:  17, col:  43):	Too many values on define
Error: PREPROC_CONSTANT     (line:  17, col:  47):	Preprocessor statement must only contain constant defines
Error: TOO_MANY_VALS        (line:  17, col:  48):	Too many values on define
Error: PREPROC_CONSTANT     (line:  17, col:  60):	Preprocessor statement must only contain constant defines
Error: TOO_MANY_VALS        (line:  17, col:  61):	Too many values on define
Error: TOO_MANY_VALS        (line:  17, col:  66):	Too many values on define
Error: PREPROC_CONSTANT     (line:  17, col:  70):	Preprocessor statement must only contain constant defines
Error: TOO_MANY_VALS        (line:  17, col:  71):	Too many values on define
Error: NEWLINE_DEFINE       (line:  17, col:  77):	Newline in define
Error: TOO_MANY_VALS        (line:  18, col:   9):	Too many values on define
Error: PREPROC_CONSTANT     (line:  18, col:  15):	Preprocessor statement must only contain constant defines
Error: TOO_MANY_VALS        (line:  18, col:  23):	Too many values on define
Error: PREPROC_CONSTANT     (line:  18, col:  29):	Preprocessor statement must only contain constant defines
Error: TOO_MANY_VALS        (line:  18, col:  30):	Too many values on define
Error: TOO_MANY_VALS        (line:  18, col:  45):	Too many values on define
Error: PREPROC_CONSTANT     (line:  18, col:  49):	Preprocessor statement must only contain constant defines
Error: TOO_MANY_VALS        (line:  18, col:  50):	Too many values on define
Error: NEWLINE_DEFINE       (line:  18, col:  66):	Newline in define
Error: PREPROC_CONSTANT     (line:  19, col:  12):	Preprocessor statement must only contain constant defines
Error: TOO_MANY_VALS        (line:  19, col:  13):	Too many values on define
Error: PREPROC_CONSTANT     (line:  19, col:  18):	Preprocessor statement must only contain constant defines
Error: TOO_MANY_VALS        (line:  19, col:  19):	Too many values on define
Error: PREPROC_CONSTANT     (line:  19, col:  32):	Preprocessor statement must only contain constant defines
Error: TOO_MANY_VALS        (line:  19, col:  33):	Too many values on define
Error: TOO_MANY_VALS        (line:  19, col:  38):	Too many values on define
Error: NEWLINE_DEFINE       (line:  19, col:  46):	Newline in define
Error: TOO_MANY_VALS        (line:  20, col:  17):	Too many values on define
Error: PREPROC_CONSTANT     (line:  20, col:  28):	Preprocessor statement must only contain constant defines
Error: TOO_MANY_VALS        (line:  20, col:  29):	Too many values on define
Error: TOO_MANY_VALS        (line:  20, col:  35):	Too many values on define
Error: TOO_MANY_VALS        (line:  20, col:  43):	Too many values on define
Error: TOO_MANY_VALS        (line:  20, col:  48):	Too many values on define
Error: TOO_MANY_VALS        (line:  20, col:  53):	Too many values on define
Error: PREPROC_CONSTANT     (line:  20, col:  57):	Preprocessor statement must only contain constant defines
Error: TOO_MANY_VALS        (line:  20, col:  58):	Too many values on define
Error: NEWLINE_DEFINE       (line:  20, col:  65):	Newline in define
Error: PREPROC_CONSTANT     (line:  21, col:  16):	Preprocessor statement must only contain constant defines
Error: PREPROC_CONSTANT     (line:  21, col:  17):	Preprocessor statement must only contain constant defines
Error: TOO_MANY_VALS        (line:  21, col:  25):	Too many values on define
Error: CONSECUTIVE_NEWLINES (line:  23, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  24, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  25, col:   1):	Consecutive newlines
Error: SPC_AFTER_OPERATOR   (line:  26, col:  36):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  26, col:  45):	missing space after operator
Error: ASSIGN_IN_CONTROL    (line:  32, col:  15):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line:  32, col:  36):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  32, col:  36):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  32, col:  41):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  32, col:  45):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  32, col:  50):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  32, col:  50):	missing space before operator
Error: SPC_AFTER_PAR        (line:  32, col:  56):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line:  32, col:  57):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  32, col:  57):	missing space before operator
Error: SPC_BFR_OPERATOR     (line:  32, col:  57):	missing space before operator
Error: ASSIGN_IN_CONTROL    (line:  34, col:  15):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line:  34, col:  36):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  34, col:  36):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  34, col:  41):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  34, col:  41):	missing space before operator
Error: SPC_BFR_OPERATOR     (line:  34, col:  46):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  34, col:  48):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  34, col:  52):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  34, col:  57):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  34, col:  57):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  34, col:  62):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  34, col:  62):	missing space before operator
Error: SPC_BFR_OPERATOR     (line:  34, col:  67):	missing space before operator
Error: SPC_AFTER_PAR        (line:  34, col:  70):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line:  34, col:  71):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  34, col:  71):	missing space before operator
Error: SPC_BFR_OPERATOR     (line:  34, col:  71):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  36, col:  10):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  36, col:  10):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  36, col:  15):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  36, col:  15):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  37, col:  10):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  37, col:  10):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  37, col:  15):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  37, col:  15):	missing space before operator
Error: SPC_BFR_OPERATOR     (line:  37, col:  20):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  37, col:  22):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  37, col:  22):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  38, col:  16):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  38, col:  16):	missing space before operator
Error: SPC_BFR_OPERATOR     (line:  38, col:  21):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  39, col:  17):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  39, col:  17):	missing space before operator
Error: SPC_BFR_OPERATOR     (line:  39, col:  22):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  40, col:  16):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  40, col:  16):	missing space before operator
Error: CONSECUTIVE_NEWLINES (line:  43, col:   1):	Consecutive newlines
Error: IMPLICIT_VAR_TYPE    (line:  46, col:   1):	Missing type in variable declaration
Error: IMPLICIT_VAR_TYPE    (line:  47, col:   1):	Missing type in variable declaration
Error: VAR_DECL_START_FUNC  (line:  47, col:   1):	Variable declaration not at start of function
Error: CONSECUTIVE_NEWLINES (line:  48, col:   1):	Consecutive newlines
Error: EMPTY_LINE_FUNCTION  (line:  48, col:   1):	Empty line in function
Error: SPC_AFTER_OPERATOR   (line:  62, col:  45):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  62, col:  54):	missing space after operator
Error: ASSIGN_IN_CONTROL    (line:  70, col:  15):	Assignment in control structure
Error: SPC_AFTER_PAR        (line:  70, col:  28):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line:  70, col:  29):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  70, col:  29):	missing space before operator
Error: TOO_MANY_TAB         (line:  72, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line:  73, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line:  74, col:   1):	Extra tabs for indent level
Error: ASSIGN_IN_CONTROL    (line:  74, col:  24):	Assignment in control structure
Error: SPC_BFR_OPERATOR     (line:  74, col:  37):	missing space before operator
Error: TOO_MANY_TAB         (line:  75, col:   1):	Extra tabs for indent level
Error: EMPTY_LINE_FUNCTION  (line:  79, col:   1):	Empty line in function
Error: SPACE_EMPTY_LINE     (line:  79, col:   1):	Space on empty line
Error: CONSECUTIVE_NEWLINES (line:  83, col:   1):	Consecutive newlines
Error: SPC_AFTER_OPERATOR   (line:  84, col:  35):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  90, col:  25):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  90, col:  25):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  90, col:  29):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  90, col:  29):	missing space before operator
Error: EMPTY_LINE_FUNCTION  (line:  91, col:   1):	Empty line in function
Error: SPACE_EMPTY_LINE     (line:  91, col:   1):	Space on empty line
Error: TOO_MANY_TAB         (line: 101, col:   1):	Extra tabs for indent level
Error: SPC_BFR_OPERATOR     (line: 101, col:  32):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 101, col:  34):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 101, col:  36):	missing space after operator
Error: TOO_MANY_TAB         (line: 104, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 110, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 111, col:   1):	Extra tabs for indent level
Error: CONSECUTIVE_NEWLINES (line: 117, col:   1):	Consecutive newlines
Error: TOO_MANY_FUNCS       (line: 118, col:   1):	Too many functions in file
Error: TOO_MANY_ARGS        (line: 118, col:  75):	Function has more than 4 arguments
Error: SPACE_EMPTY_LINE     (line: 121, col:   1):	Space on empty line
Error: TOO_FEW_TAB          (line: 123, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 123, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 124, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 124, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line: 125, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 125, col:   5):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 126, col:  19):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 126, col:  19):	missing space before operator
Error: SPACE_AFTER_KW       (line: 126, col:  20):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line: 126, col:  21):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 126, col:  21):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 126, col:  25):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 126, col:  25):	missing space before operator
Error: SPACE_AFTER_KW       (line: 126, col:  33):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line: 126, col:  36):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 126, col:  36):	missing space before operator
Error: TOO_FEW_TAB          (line: 127, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 127, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 128, col:  19):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 128, col:  19):	missing space before operator
Error: SPACE_AFTER_KW       (line: 128, col:  20):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line: 128, col:  21):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 128, col:  21):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 128, col:  25):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 128, col:  25):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 128, col:  29):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 128, col:  29):	missing space before operator
Error: SPC_BFR_OPERATOR     (line: 128, col:  33):	missing space before operator
Error: SPACE_AFTER_KW       (line: 128, col:  39):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line: 128, col:  42):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 128, col:  42):	missing space before operator
Error: SPACE_REPLACE_TAB    (line: 129, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 130, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 130, col:   5):	Space on empty line
Error: CONSECUTIVE_NEWLINES (line: 133, col:   1):	Consecutive newlines
Error: TOO_MANY_FUNCS       (line: 134, col:   1):	Too many functions in file
Error: SPC_AFTER_OPERATOR   (line: 134, col:  40):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 134, col:  51):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 134, col:  65):	missing space after operator
Error: TOO_MANY_TAB         (line: 136, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 137, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 138, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 139, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 140, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 141, col:   1):	Extra tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line: 141, col:   1):	Too many variables declarations in a function
Error: TOO_MANY_TAB         (line: 142, col:   1):	Extra tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line: 142, col:   1):	Too many variables declarations in a function
Error: TOO_MANY_TAB         (line: 143, col:   1):	Extra tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line: 143, col:   1):	Too many variables declarations in a function
Error: TOO_MANY_TAB         (line: 144, col:   1):	Extra tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line: 144, col:   1):	Too many variables declarations in a function
Error: TOO_MANY_TAB         (line: 145, col:   1):	Extra tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line: 145, col:   1):	Too many variables declarations in a function
Error: TOO_MANY_TAB         (line: 146, col:   1):	Extra tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line: 146, col:   1):	Too many variables declarations in a function
Error: TOO_MANY_TAB         (line: 147, col:   1):	Extra tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line: 147, col:   1):	Too many variables declarations in a function
Error: TOO_MANY_TAB         (line: 148, col:   1):	Extra tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line: 148, col:   1):	Too many variables declarations in a function
Error: TOO_MANY_TAB         (line: 149, col:   1):	Extra tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line: 149, col:   1):	Too many variables declarations in a function
Error: TOO_MANY_TAB         (line: 150, col:   1):	Extra tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line: 150, col:   1):	Too many variables declarations in a function
Error: TOO_MANY_TAB         (line: 151, col:   1):	Extra tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line: 151, col:   1):	Too many variables declarations in a function
Error: TOO_MANY_TAB         (line: 152, col:   1):	Extra tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line: 152, col:   1):	Too many variables declarations in a function
Error: MISALIGNED_VAR_DECL  (line: 152, col:  21):	Misaligned variable declaration
Error: TOO_MANY_TAB         (line: 153, col:   1):	Extra tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line: 153, col:   1):	Too many variables declarations in a function
Error: TOO_MANY_TAB         (line: 154, col:   1):	Extra tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line: 154, col:   1):	Too many variables declarations in a function
Error: TOO_MANY_TAB         (line: 155, col:   1):	Extra tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line: 155, col:   1):	Too many variables declarations in a function
Error: TOO_MANY_TAB         (line: 156, col:   1):	Extra tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line: 156, col:   1):	Too many variables declarations in a function
Error: TOO_MANY_TAB         (line: 157, col:   1):	Extra tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line: 157, col:   1):	Too many variables declarations in a function
Error: MISALIGNED_VAR_DECL  (line: 157, col:  21):	Misaligned variable declaration
Error: TOO_MANY_TAB         (line: 158, col:   1):	Extra tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line: 158, col:   1):	Too many variables declarations in a function
Error: TOO_MANY_TAB         (line: 165, col:   1):	Extra tabs for indent level
Error: ASSIGN_IN_CONTROL    (line: 165, col:  20):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line: 165, col:  28):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 165, col:  33):	missing space after operator
Error: EOL_OPERATOR         (line: 165, col:  46):	Logic operator at the end of line
Error: TOO_MANY_TAB         (line: 166, col:  25):	Extra tabs for indent level
Error: LINE_TOO_LONG        (line: 166, col:  84):	line too long
Error: EOL_OPERATOR         (line: 166, col:  90):	Logic operator at the end of line
Error: TOO_MANY_TAB         (line: 167, col:  25):	Extra tabs for indent level
Error: EOL_OPERATOR         (line: 167, col:  74):	Logic operator at the end of line
Error: TOO_MANY_TAB         (line: 168, col:  25):	Extra tabs for indent level
Error: NO_SPC_AFR_PAR       (line: 168, col:  45):	Extra space after parenthesis (brace/bracket)
Error: NO_SPC_BFR_PAR       (line: 168, col:  47):	Extra space before parenthesis (brace/bracket)
Error: IMPLICIT_VAR_TYPE    (line: 169, col:   1):	Missing type in variable declaration
Error: TOO_MANY_TAB         (line: 169, col:   1):	Extra tabs for indent level
Error: WRONG_SCOPE_VAR      (line: 169, col:   1):	Variable declared in incorrect scope
Error: TOO_MANY_TAB         (line: 170, col:   1):	Extra tabs for indent level
Error: EMPTY_LINE_FUNCTION  (line: 172, col:   1):	Empty line in function
Error: TOO_MANY_TAB         (line: 174, col:   1):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line: 174, col:  16):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 174, col:  16):	missing space before operator
Error: TOO_MANY_TAB         (line: 175, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 177, col:   1):	Extra tabs for indent level
Error: ASSIGN_IN_CONTROL    (line: 177, col:  37):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line: 177, col:  50):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 177, col:  50):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 177, col:  53):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 177, col:  53):	missing space before operator
Error: TERNARY_FBIDDEN      (line: 177, col:  53):	Ternaries are forbidden
Error: SPC_AFTER_OPERATOR   (line: 177, col:  64):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 177, col:  64):	missing space before operator
Error: IMPLICIT_VAR_TYPE    (line: 178, col:   1):	Missing type in variable declaration
Error: TOO_MANY_TAB         (line: 178, col:   1):	Extra tabs for indent level
Error: WRONG_SCOPE_VAR      (line: 178, col:   1):	Variable declared in incorrect scope
Error: TOO_MANY_TAB         (line: 179, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 180, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 181, col:   1):	Extra tabs for indent level
Error: ASSIGN_IN_CONTROL    (line: 181, col:  30):	Assignment in control structure
Error: SPACE_AFTER_KW       (line: 181, col:  39):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line: 181, col:  41):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 181, col:  41):	missing space before operator
Error: IMPLICIT_VAR_TYPE    (line: 182, col:   1):	Missing type in variable declaration
Error: TOO_MANY_TAB         (line: 182, col:   1):	Extra tabs for indent level
Error: WRONG_SCOPE_VAR      (line: 182, col:   1):	Variable declared in incorrect scope
Error: CONSECUTIVE_NEWLINES (line: 183, col:   1):	Consecutive newlines
Error: EMPTY_LINE_FUNCTION  (line: 183, col:   1):	Empty line in function
Error: EMPTY_LINE_FUNCTION  (line: 185, col:   1):	Empty line in function
Error: TOO_MANY_TAB         (line: 187, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 188, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 189, col:   1):	Extra tabs for indent level
Error: ASSIGN_IN_CONTROL    (line: 189, col:  28):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line: 189, col:  36):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 189, col:  41):	missing space after operator
Error: EOL_OPERATOR         (line: 189, col:  54):	Logic operator at the end of line
Error: TOO_MANY_TAB         (line: 190, col:  33):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line: 190, col:  68):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 190, col:  68):	missing space before operator
Error: NO_SPC_AFR_PAR       (line: 190, col:  73):	Extra space after parenthesis (brace/bracket)
Error: NO_SPC_BFR_PAR       (line: 190, col:  75):	Extra space before parenthesis (brace/bracket)
Error: IMPLICIT_VAR_TYPE    (line: 191, col:   1):	Missing type in variable declaration
Error: TOO_MANY_TAB         (line: 191, col:   1):	Extra tabs for indent level
Error: WRONG_SCOPE_VAR      (line: 191, col:   1):	Variable declared in incorrect scope
Error: TOO_MANY_TAB         (line: 193, col:   1):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line: 193, col:  49):	missing space after operator
Error: EXP_NEWLINE          (line: 193, col:  55):	Expected newline after control structure
Error: EMPTY_LINE_FUNCTION  (line: 194, col:   1):	Empty line in function
Error: TOO_MANY_TAB         (line: 195, col:   1):	Extra tabs for indent level
Error: IMPLICIT_VAR_TYPE    (line: 196, col:   1):	Missing type in variable declaration
Error: TOO_MANY_TAB         (line: 196, col:   1):	Extra tabs for indent level
Error: WRONG_SCOPE_VAR      (line: 196, col:   1):	Variable declared in incorrect scope
Error: SPC_BFR_OPERATOR     (line: 197, col:  61):	missing space before operator
Error: WRONG_SCOPE_COMMENT  (line: 198, col:  17):	Comment is invalid in this scope
Error: TOO_MANY_TAB         (line: 209, col:   1):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line: 210, col:  64):	missing space after operator
Error: WRONG_SCOPE_COMMENT  (line: 211, col:  33):	Comment is invalid in this scope
Error: LINE_TOO_LONG        (line: 211, col:  90):	line too long
Error: TOO_MANY_TAB         (line: 212, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 213, col:   1):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line: 214, col:  67):	missing space after operator
Error: LINE_TOO_LONG        (line: 215, col:  50):	line too long
Error: WRONG_SCOPE_COMMENT  (line: 215, col:  50):	Comment is invalid in this scope
Error: WRONG_SCOPE_COMMENT  (line: 215, col:  50):	Comment is invalid in this scope
Error: LINE_TOO_LONG        (line: 215, col: 105):	line too long
Error: TOO_MANY_TAB         (line: 216, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 217, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 219, col:   1):	Extra tabs for indent level
Error: EMPTY_LINE_FUNCTION  (line: 220, col:   1):	Empty line in function
Error: TOO_MANY_TAB         (line: 221, col:   1):	Extra tabs for indent level
Error: ASSIGN_IN_CONTROL    (line: 221, col:  19):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line: 221, col:  39):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 221, col:  45):	missing space after operator
Error: IMPLICIT_VAR_TYPE    (line: 222, col:   1):	Missing type in variable declaration
Error: TOO_MANY_TAB         (line: 222, col:   1):	Extra tabs for indent level
Error: WRONG_SCOPE_VAR      (line: 222, col:   1):	Variable declared in incorrect scope
Error: SPC_AFTER_OPERATOR   (line: 223, col:  23):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 223, col:  23):	missing space before operator
Error: EMPTY_LINE_FUNCTION  (line: 224, col:   1):	Empty line in function
Error: CONSECUTIVE_NEWLINES (line: 225, col:   1):	Consecutive newlines
Error: EMPTY_LINE_FUNCTION  (line: 225, col:   1):	Empty line in function
Error: TOO_MANY_TAB         (line: 228, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 229, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 230, col:   1):	Extra tabs for indent level
Error: ASSIGN_IN_CONTROL    (line: 230, col:  28):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line: 230, col:  36):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 230, col:  41):	missing space after operator
Error: IMPLICIT_VAR_TYPE    (line: 231, col:   1):	Missing type in variable declaration
Error: TOO_MANY_TAB         (line: 231, col:   1):	Extra tabs for indent level
Error: WRONG_SCOPE_VAR      (line: 231, col:   1):	Variable declared in incorrect scope
Error: TOO_MANY_TAB         (line: 233, col:   1):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line: 233, col:  25):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 233, col:  25):	missing space before operator
Error: TOO_MANY_TAB         (line: 234, col:   1):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line: 236, col:  61):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 236, col:  61):	missing space before operator
Error: SPACE_AFTER_KW       (line: 236, col:  62):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line: 236, col:  65):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 236, col:  65):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 236, col:  67):	missing space after operator
Error: TOO_MANY_TAB         (line: 237, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 239, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 240, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 242, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 243, col:   1):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line: 243, col:  59):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 243, col:  59):	missing space before operator
Error: MULT_IN_SINGLE_INSTR (line: 244, col:   1):	Multiple instructions in single line control structure
Error: TOO_MANY_TAB         (line: 244, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 247, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 248, col:   1):	Extra tabs for indent level
Error: WRONG_SCOPE_COMMENT  (line: 249, col:  25):	Comment is invalid in this scope
Error: TOO_MANY_TAB         (line: 256, col:   1):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line: 256, col:  32):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 256, col:  32):	missing space before operator
Error: SPC_BFR_OPERATOR     (line: 256, col:  32):	missing space before operator
Error: TOO_MANY_TAB         (line: 258, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 260, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 262, col:   1):	Extra tabs for indent level
Error: WRONG_SCOPE_COMMENT  (line: 263, col:   9):	Comment is invalid in this scope
Error: TOO_MANY_TAB         (line: 282, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 283, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 284, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 285, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 286, col:   1):	Extra tabs for indent level
Error: TOO_MANY_LINES       (line: 287, col:   1):	Function has more than 25 lines
Error: CONSECUTIVE_NEWLINES (line: 289, col:   1):	Consecutive newlines
Error: TOO_MANY_FUNCS       (line: 290, col:   1):	Too many functions in file
Error: TOO_MANY_TAB         (line: 292, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 293, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 295, col:   1):	Extra tabs for indent level
Error: ASSIGN_IN_CONTROL    (line: 295, col:  27):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line: 295, col:  53):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 295, col:  58):	missing space after operator
Error: SPC_AFTER_PAR        (line: 295, col:  64):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 295, col:  65):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 295, col:  65):	missing space before operator
Error: SPC_BFR_OPERATOR     (line: 295, col:  65):	missing space before operator
Error: TOO_MANY_TAB         (line: 296, col:   1):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line: 297, col:  46):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 297, col:  46):	missing space before operator
Error: SPC_BFR_OPERATOR     (line: 297, col:  56):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 297, col:  58):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 297, col:  63):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 297, col:  68):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 297, col:  68):	missing space before operator
Error: SPC_BFR_OPERATOR     (line: 297, col:  78):	missing space before operator
Error: LINE_TOO_LONG        (line: 297, col:  82):	line too long
Error: TOO_MANY_TAB         (line: 298, col:   1):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line: 298, col:  27):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 298, col:  27):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 298, col:  37):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 298, col:  41):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 298, col:  49):	missing space before operator
Error: TOO_MANY_TAB         (line: 299, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 300, col:   1):	Extra tabs for indent level
Error: ASSIGN_IN_CONTROL    (line: 300, col:  27):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line: 300, col:  53):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 300, col:  58):	missing space after operator
Error: SPC_AFTER_PAR        (line: 300, col:  64):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 300, col:  65):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 300, col:  65):	missing space before operator
Error: SPC_BFR_OPERATOR     (line: 300, col:  65):	missing space before operator
Error: TOO_MANY_TAB         (line: 301, col:   1):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line: 302, col:  46):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 302, col:  46):	missing space before operator
Error: SPC_BFR_OPERATOR     (line: 302, col:  56):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 302, col:  58):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 302, col:  62):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 302, col:  67):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 302, col:  67):	missing space before operator
Error: SPC_BFR_OPERATOR     (line: 302, col:  77):	missing space before operator
Error: TOO_MANY_TAB         (line: 303, col:   1):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line: 303, col:  27):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 303, col:  27):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 303, col:  37):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 303, col:  41):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 303, col:  49):	missing space before operator
Error: TOO_MANY_TAB         (line: 304, col:   1):	Extra tabs for indent level
Error: CONSECUTIVE_NEWLINES (line: 307, col:   1):	Consecutive newlines
Error: TOO_MANY_FUNCS       (line: 308, col:   1):	Too many functions in file
Error: SPC_AFTER_OPERATOR   (line: 308, col:  44):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 308, col:  55):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 308, col:  66):	missing space after operator
Error: TOO_MANY_TAB         (line: 310, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 311, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 312, col:   1):	Extra tabs for indent level
Error: MISALIGNED_VAR_DECL  (line: 312, col:  17):	Misaligned variable declaration
Error: TOO_MANY_TAB         (line: 313, col:   1):	Extra tabs for indent level
Error: MISALIGNED_VAR_DECL  (line: 313, col:  17):	Misaligned variable declaration
Error: TOO_MANY_TAB         (line: 316, col:   1):	Extra tabs for indent level
Error: ASSIGN_IN_CONTROL    (line: 316, col:  17):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line: 316, col:  28):	missing space after operator
Error: SPC_AFTER_PAR        (line: 316, col:  38):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 316, col:  39):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 316, col:  39):	missing space before operator
Error: SPC_BFR_OPERATOR     (line: 316, col:  39):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 316, col:  63):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 316, col:  65):	missing space after operator
Error: SPC_AFTER_PAR        (line: 316, col:  75):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 316, col:  76):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 316, col:  76):	missing space before operator
Error: SPC_BFR_OPERATOR     (line: 316, col:  76):	missing space before operator
Error: EOL_OPERATOR         (line: 316, col:  81):	Logic operator at the end of line
Error: LINE_TOO_LONG        (line: 316, col:  83):	line too long
Error: TOO_MANY_TAB         (line: 317, col:  25):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line: 317, col:  38):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 317, col:  43):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 317, col:  54):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 317, col:  54):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 317, col:  64):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 317, col:  76):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 317, col:  79):	missing space after operator
Error: LINE_TOO_LONG        (line: 317, col:  82):	line too long
Error: SPC_AFTER_PAR        (line: 317, col:  82):	Missing space after parenthesis (brace/bracket)
Error: EOL_OPERATOR         (line: 317, col:  83):	Logic operator at the end of line
Error: SPC_BFR_OPERATOR     (line: 317, col:  83):	missing space before operator
Error: TOO_MANY_TAB         (line: 318, col:  25):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 319, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 320, col:   1):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line: 320, col:  23):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 320, col:  23):	missing space before operator
Error: TOO_MANY_TAB         (line: 321, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 322, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 323, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 324, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 325, col:   1):	Extra tabs for indent level
Error: ASSIGN_IN_CONTROL    (line: 325, col:  17):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line: 325, col:  41):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 325, col:  45):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 325, col:  50):	missing space after operator
Error: TOO_MANY_TAB         (line: 326, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 329, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 330, col:   1):	Extra tabs for indent level
Error: SPC_AFTER_OPERATOR   (line: 330, col:  19):	missing space after operator
Error: TOO_MANY_TAB         (line: 331, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 332, col:   1):	Extra tabs for indent level
Error: TOO_MANY_FUNCS       (line: 335, col:   1):	Too many functions in file
Error: SPC_AFTER_OPERATOR   (line: 335, col:  39):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 335, col:  55):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 335, col:  66):	missing space after operator
Error: TOO_MANY_TAB         (line: 337, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 339, col:   1):	Extra tabs for indent level
Error: ASSIGN_IN_CONTROL    (line: 339, col:  17):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line: 339, col:  41):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 339, col:  50):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 339, col:  52):	missing space after operator
Error: TOO_MANY_TAB         (line: 340, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 343, col:   1):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line: 344, col:   1):	Extra tabs for indent level
mlx_loop_hook.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  14, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  15, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  16, col:   1):	Consecutive newlines
Error: SPC_AFTER_OPERATOR   (line:  17, col:  31):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  17, col:  46):	missing space after operator
Error: SPACE_REPLACE_TAB    (line:  19, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  20, col:   3):	Found space when expecting tab
mlx_hook.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  14, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  15, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  16, col:   1):	Consecutive newlines
Error: SPC_BEFORE_NL        (line:  17, col:  55):	Space before newline
Error: MIXED_SPACE_TAB      (line:  18, col:   5):	Mixed spaces and tabs
Error: SPC_AFTER_OPERATOR   (line:  18, col:  24):	missing space after operator
Error: SPACE_REPLACE_TAB    (line:  20, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  21, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  22, col:   3):	Found space when expecting tab
Error: CONSECUTIVE_NEWLINES (line:  25, col:   1):	Consecutive newlines
Error: TOO_FEW_TAB          (line:  28, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  28, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  33, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  33, col:   3):	Found space when expecting tab
Error: CONSECUTIVE_NEWLINES (line:  36, col:   1):	Consecutive newlines
Error: TOO_FEW_TAB          (line:  39, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  39, col:   3):	Found space when expecting tab
mlx_lib_xpm.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  14, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  15, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  16, col:   1):	Consecutive newlines
Error: TOO_MANY_TABS_FUNC   (line:  17, col:   9):	extra tabs before function name
Error: SPC_AFTER_OPERATOR   (line:  17, col:  46):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  17, col:  57):	missing space after operator
Error: MIXED_SPACE_TAB      (line:  18, col:  13):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line:  18, col:  17):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line:  18, col:  39):	missing space after operator
Error: TOO_FEW_TAB          (line:  20, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  20, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  21, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  21, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  22, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  22, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  23, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  23, col:   3):	Found space when expecting tab
Error: MISALIGNED_VAR_DECL  (line:  23, col:  17):	Misaligned variable declaration
Error: SPACE_REPLACE_TAB    (line:  25, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  26, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  27, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  28, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  29, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  29, col:  31):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  29, col:  31):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  29, col:  47):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  29, col:  47):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  29, col:  57):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  29, col:  57):	missing space before operator
Error: TOO_FEW_TAB          (line:  30, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  30, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  30, col:  29):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  30, col:  35):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  30, col:  41):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  30, col:  47):	missing space after operator
Error: TOO_FEW_TAB          (line:  31, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  31, col:   5):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  32, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  32, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  33, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  33, col:   5):	Found space when expecting tab
Error: EMPTY_LINE_FUNCTION  (line:  34, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line:  35, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  35, col:   3):	Found space when expecting tab
Error: ASSIGN_IN_CONTROL    (line:  35, col:  13):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line:  35, col:  41):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  35, col:  53):	missing space after operator
Error: TOO_FEW_TAB          (line:  36, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  36, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  37, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  37, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  38, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  38, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  39, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  39, col:   5):	Space on empty line
Error: SPACE_REPLACE_TAB    (line:  40, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  41, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  42, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  42, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  42, col:  34):	missing space after operator
Error: TOO_FEW_TAB          (line:  43, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  43, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  44, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  44, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  44, col:  23):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  44, col:  33):	missing space after operator
Error: SPACE_AFTER_KW       (line:  44, col:  40):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line:  44, col:  46):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  44, col:  46):	missing space before operator
Error: TOO_FEW_TAB          (line:  45, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  45, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  46, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  46, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  47, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  47, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  48, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  48, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  48, col:  16):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  48, col:  16):	missing space before operator
Error: TOO_FEW_TAB          (line:  49, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  49, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  50, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  50, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  50, col:  32):	missing space after operator
Error: SPACE_REPLACE_TAB    (line:  51, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  51, col:  45):	missing space after operator
Error: TOO_FEW_TAB          (line:  52, col:   1):	Missing tabs for indent level
Error: MIXED_SPACE_TAB      (line:  52, col:   9):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line:  52, col:  13):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line:  52, col:  34):	missing space after operator
Error: TOO_FEW_TAB          (line:  53, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  53, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  54, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  54, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  54, col:  16):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  54, col:  16):	missing space before operator
Error: TOO_FEW_TAB          (line:  55, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  55, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  56, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  56, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  56, col:  31):	missing space after operator
Error: TOO_FEW_TAB          (line:  57, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  57, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  58, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  58, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  59, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  59, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  60, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  61, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  62, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  63, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  64, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  65, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  65, col:   3):	Found space when expecting tab
Error: TOO_MANY_LINES       (line:  66, col:   1):	Function has more than 25 lines
Error: CONSECUTIVE_NEWLINES (line:  68, col:   1):	Consecutive newlines
Error: SPC_AFTER_OPERATOR   (line:  69, col:  34):	missing space after operator
Error: TOO_FEW_TAB          (line:  71, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  71, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  71, col:  18):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  71, col:  18):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  71, col:  47):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  71, col:  47):	missing space before operator
Error: EOL_OPERATOR         (line:  71, col:  62):	Logic operator at the end of line
Error: TOO_FEW_TAB          (line:  72, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  72, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  72, col:  20):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  72, col:  20):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  72, col:  51):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  72, col:  51):	missing space before operator
Error: EOL_OPERATOR         (line:  72, col:  66):	Logic operator at the end of line
Error: TOO_FEW_TAB          (line:  73, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  73, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  73, col:  23):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  73, col:  23):	missing space before operator
Error: EOL_OPERATOR         (line:  73, col:  42):	Logic operator at the end of line
Error: TOO_FEW_TAB          (line:  74, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  74, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  74, col:  24):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  74, col:  24):	missing space before operator
Error: EOL_OPERATOR         (line:  74, col:  44):	Logic operator at the end of line
Error: TOO_FEW_TAB          (line:  75, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  75, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  75, col:  29):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  75, col:  29):	missing space before operator
Error: EOL_OPERATOR         (line:  75, col:  54):	Logic operator at the end of line
Error: TOO_FEW_TAB          (line:  76, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  76, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  76, col:  23):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  76, col:  23):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  76, col:  56):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  76, col:  56):	missing space before operator
Error: EOL_OPERATOR         (line:  76, col:  70):	Logic operator at the end of line
Error: TOO_FEW_TAB          (line:  77, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  77, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  77, col:  27):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  77, col:  27):	missing space before operator
Error: EOL_OPERATOR         (line:  77, col:  50):	Logic operator at the end of line
Error: TOO_FEW_TAB          (line:  78, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  78, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  78, col:  27):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  78, col:  27):	missing space before operator
Error: EOL_OPERATOR         (line:  78, col:  50):	Logic operator at the end of line
Error: TOO_FEW_TAB          (line:  79, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  79, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  79, col:  21):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  79, col:  21):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  79, col:  57):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  79, col:  57):	missing space before operator
Error: EOL_OPERATOR         (line:  79, col:  76):	Logic operator at the end of line
Error: TOO_FEW_TAB          (line:  80, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  80, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  80, col:  22):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  80, col:  22):	missing space before operator
Error: NO_SPC_BFR_PAR       (line:  80, col:  40):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  81, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  81, col:   5):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  82, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  82, col:   3):	Found space when expecting tab
Error: CONSECUTIVE_NEWLINES (line:  85, col:   1):	Consecutive newlines
Error: SPC_AFTER_OPERATOR   (line:  86, col:  44):	missing space after operator
Error: MIXED_SPACE_TAB      (line:  87, col:   9):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line:  87, col:  13):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line:  87, col:  30):	missing space after operator
Error: TOO_FEW_TAB          (line:  89, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  89, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  89, col:  35):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  89, col:  41):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  89, col:  48):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  89, col:  67):	missing space after operator
Error: CONSECUTIVE_NEWLINES (line:  92, col:   1):	Consecutive newlines
Error: SPC_AFTER_OPERATOR   (line:  93, col:  39):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  93, col:  51):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  93, col:  62):	missing space after operator
Error: TOO_FEW_TAB          (line:  95, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  95, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  95, col:  35):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  95, col:  41):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  95, col:  48):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  95, col:  71):	missing space after operator
Error: SPC_BFR_PAR          (line:  95, col:  72):	Missing space before parenthesis (brace/bracket)
Error: LINE_TOO_LONG        (line:  95, col:  84):	line too long
mlx_int_wait_first_expose.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  12, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  15, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  16, col:   1):	Consecutive newlines
Error: SPC_AFTER_OPERATOR   (line:  17, col:  43):	missing space after operator
Error: TOO_FEW_TAB          (line:  19, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  19, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  21, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  21, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  21, col:  29):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  21, col:  33):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  21, col:  46):	missing space after operator
Error: TOO_FEW_TAB          (line:  22, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  22, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  22, col:  30):	missing space after operator
mlx_mouse.c: Error!
Error: INVALID_HEADER       (line:   1, col:   1):	Missing or invalid 42 header
Error: TOO_MANY_TABS_FUNC   (line:   3, col:   5):	extra tabs before function name
Error: TOO_MANY_TABS_FUNC   (line:   9, col:   5):	extra tabs before function name
Error: SPACE_REPLACE_TAB    (line:  11, col:  16):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  12, col:  11):	Found space when expecting tab
Error: MISALIGNED_VAR_DECL  (line:  12, col:  12):	Misaligned variable declaration
Error: SPACE_REPLACE_TAB    (line:  13, col:  11):	Found space when expecting tab
Error: MISALIGNED_VAR_DECL  (line:  13, col:  12):	Misaligned variable declaration
Error: SPACE_REPLACE_TAB    (line:  14, col:  11):	Found space when expecting tab
Error: MISALIGNED_VAR_DECL  (line:  14, col:  12):	Misaligned variable declaration
Error: LINE_TOO_LONG        (line:  17, col:  82):	line too long
Error: TOO_MANY_TABS_FUNC   (line:  23, col:   5):	extra tabs before function name
Error: TOO_MANY_TABS_FUNC   (line:  36, col:   5):	extra tabs before function name
Error: IMPLICIT_VAR_TYPE    (line:  43, col:   1):	Missing type in variable declaration
Error: CONSECUTIVE_NEWLINES (line:  44, col:   1):	Consecutive newlines
Error: EMPTY_LINE_FUNCTION  (line:  44, col:   1):	Empty line in function
mlx_destroy_window.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  14, col:   1):	Consecutive newlines
Error: SPC_AFTER_OPERATOR   (line:  15, col:  36):	missing space after operator
Error: TOO_FEW_TAB          (line:  17, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  17, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  18, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  18, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  19, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  19, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  21, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  22, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  23, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  24, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  24, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  25, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  25, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  26, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  26, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  26, col:  12):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  26, col:  12):	missing space before operator
Error: TOO_FEW_TAB          (line:  28, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  28, col:   7):	Space on empty line
Error: SPACE_REPLACE_TAB    (line:  30, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  31, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  31, col:   5):	Space on empty line
Error: SPACE_REPLACE_TAB    (line:  32, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  33, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  33, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  33, col:  31):	missing space after operator
Error: TOO_FEW_TAB          (line:  34, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  34, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  34, col:  24):	missing space after operator
Error: TOO_FEW_TAB          (line:  35, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  35, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  36, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  36, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  37, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  37, col:   5):	Found space when expecting tab
mlx_get_data_addr.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  12, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  15, col:   1):	Consecutive newlines
Error: SPC_AFTER_OPERATOR   (line:  16, col:  38):	missing space after operator
Error: MIXED_SPACE_TAB      (line:  17, col:   9):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line:  17, col:  13):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line:  17, col:  30):	missing space after operator
Error: SPACE_REPLACE_TAB    (line:  19, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  20, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  21, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  22, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  22, col:   3):	Found space when expecting tab
mlx_string_put.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  14, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  15, col:   1):	Consecutive newlines
Error: TOO_MANY_TABS_FUNC   (line:  16, col:   5):	extra tabs before function name
Error: SPC_AFTER_OPERATOR   (line:  16, col:  36):	missing space after operator
Error: MIXED_SPACE_TAB      (line:  17, col:   9):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line:  17, col:  13):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line:  17, col:  25):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  17, col:  31):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  17, col:  41):	missing space after operator
Error: TOO_MANY_ARGS        (line:  17, col:  55):	Function has more than 4 arguments
Error: TOO_FEW_TAB          (line:  19, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  19, col:   4):	Found space when expecting tab
Error: SPACE_EMPTY_LINE     (line:  20, col:   1):	Space on empty line
Error: SPACE_REPLACE_TAB    (line:  21, col:   4):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  21, col:  49):	missing space after operator
Error: TOO_FEW_TAB          (line:  22, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  22, col:   4):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  22, col:  27):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  22, col:  35):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  22, col:  48):	missing space after operator
Error: TOO_FEW_TAB          (line:  23, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  23, col:   4):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  23, col:  29):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  23, col:  41):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  23, col:  49):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  23, col:  51):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  23, col:  53):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  23, col:  60):	missing space after operator
Error: TOO_FEW_TAB          (line:  24, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  24, col:   4):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  25, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  25, col:   6):	Found space when expecting tab
mlx_get_color_value.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  14, col:   1):	Consecutive newlines
Error: CONSECUTIVE_SPC      (line:  15, col:   4):	Two or more consecutives spaces
Error: SPACE_BEFORE_FUNC    (line:  15, col:  16):	space before function name
Error: SPC_AFTER_OPERATOR   (line:  15, col:  49):	missing space after operator
Error: TOO_FEW_TAB          (line:  17, col:   1):	Missing tabs for indent level
Error: SPACE_AFTER_KW       (line:  17, col:   3):	Missing space after keyword
Error: SPACE_REPLACE_TAB    (line:  17, col:   3):	Found space when expecting tab
Error: SPC_BFR_PAR          (line:  17, col:   9):	Missing space before parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line:  17, col:  37):	missing space after operator
Error: TOO_MANY_TABS_FUNC   (line:  20, col:   5):	extra tabs before function name
Error: SPC_AFTER_OPERATOR   (line:  20, col:  44):	missing space after operator
Error: TOO_FEW_TAB          (line:  22, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  22, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  24, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  24, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  24, col:  18):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  24, col:  18):	missing space before operator
Error: TOO_FEW_TAB          (line:  25, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  25, col:   5):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  26, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  26, col:  18):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  26, col:  18):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  26, col:  22):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  26, col:  22):	missing space before operator
Error: SPACE_REPLACE_TAB    (line:  27, col:   3):	Found space when expecting tab
Error: SPACE_AFTER_KW       (line:  27, col:  14):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line:  27, col:  19):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  27, col:  19):	missing space before operator
Error: SPACE_REPLACE_TAB    (line:  28, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  28, col:  19):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  28, col:  19):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  28, col:  23):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  28, col:  23):	missing space before operator
Error: SPACE_REPLACE_TAB    (line:  29, col:   3):	Found space when expecting tab
Error: SPC_BFR_OPERATOR     (line:  29, col:  22):	missing space before operator
Error: SPC_BFR_PAR          (line:  29, col:  24):	Missing space before parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line:  29, col:  27):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  29, col:  27):	missing space before operator
Error: SPC_AFTER_PAR        (line:  29, col:  44):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line:  29, col:  45):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  29, col:  45):	missing space before operator
Error: SPC_BFR_OPERATOR     (line:  29, col:  63):	missing space before operator
Error: EOL_OPERATOR         (line:  29, col:  64):	Logic operator at the end of line
Error: TOO_FEW_TAB          (line:  30, col:   1):	Missing tabs for indent level
Error: TOO_FEW_TAB          (line:  30, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  30, col:   5):	Found space when expecting tab
Error: SPC_BFR_OPERATOR     (line:  30, col:  15):	missing space before operator
Error: SPC_BFR_PAR          (line:  30, col:  17):	Missing space before parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line:  30, col:  20):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  30, col:  20):	missing space before operator
Error: SPC_AFTER_PAR        (line:  30, col:  37):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line:  30, col:  38):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  30, col:  38):	missing space before operator
Error: SPC_BFR_OPERATOR     (line:  30, col:  56):	missing space before operator
Error: EOL_OPERATOR         (line:  30, col:  57):	Logic operator at the end of line
Error: TOO_FEW_TAB          (line:  31, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  31, col:   5):	Found space when expecting tab
Error: SPC_BFR_OPERATOR     (line:  31, col:  14):	missing space before operator
Error: SPC_BFR_PAR          (line:  31, col:  16):	Missing space before parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line:  31, col:  19):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  31, col:  19):	missing space before operator
Error: SPC_AFTER_PAR        (line:  31, col:  36):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line:  31, col:  37):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  31, col:  37):	missing space before operator
Error: TOO_FEW_TAB          (line:  32, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  32, col:   3):	Found space when expecting tab
mlx_destroy_image.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  14, col:   1):	Consecutive newlines
Error: TOO_FEW_TAB          (line:  17, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  17, col:   3):	Found space when expecting tab
Error: EOL_OPERATOR         (line:  17, col:  40):	Logic operator at the end of line
Error: TOO_FEW_TAB          (line:  18, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  18, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  19, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  19, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  20, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  20, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  21, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  21, col:   7):	Found space when expecting tab
Error: SPACE_EMPTY_LINE     (line:  22, col:   7):	Space on empty line
Error: WRONG_SCOPE_COMMENT  (line:  22, col:   7):	Comment is invalid in this scope
Error: TOO_FEW_TAB          (line:  23, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  23, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line:  24, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  24, col:   3):	Found space when expecting tab
Error: CONSECUTIVE_SPC      (line:  24, col:  29):	Two or more consecutives spaces
Error: WRONG_SCOPE_COMMENT  (line:  24, col:  31):	Comment is invalid in this scope
Error: WRONG_SCOPE_COMMENT  (line:  24, col:  31):	Comment is invalid in this scope
Error: TOO_FEW_TAB          (line:  25, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  25, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  26, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  26, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  27, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  27, col:   5):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  28, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  28, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  29, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  29, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  30, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  30, col:   5):	Found space when expecting tab
mlx_int.h: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  12, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  35, col:   1):	Consecutive newlines
Error: PREPROC_CONSTANT     (line:  40, col:  55):	Preprocessor statement must only contain constant defines
Error: CONSECUTIVE_NEWLINES (line:  42, col:   1):	Consecutive newlines
Error: LINE_TOO_LONG        (line:  46, col:  84):	line too long
Error: CONSECUTIVE_NEWLINES (line:  48, col:   1):	Consecutive newlines
Error: TAB_REPLACE_SPACE    (line:  49, col:   1):	Found tab when expecting space
Error: CONSECUTIVE_NEWLINES (line:  55, col:   1):	Consecutive newlines
Error: TAB_REPLACE_SPACE    (line:  62, col:   1):	Found tab when expecting space
Error: CONSECUTIVE_NEWLINES (line:  69, col:   1):	Consecutive newlines
Error: TAB_REPLACE_SPACE    (line:  70, col:   1):	Found tab when expecting space
Error: CONSECUTIVE_NEWLINES (line:  84, col:   1):	Consecutive newlines
Error: TAB_REPLACE_SPACE    (line:  85, col:   1):	Found tab when expecting space
Error: TAB_REPLACE_SPACE    (line: 100, col:   1):	Found tab when expecting space
Error: MIXED_SPACE_TAB      (line: 118, col:   8):	Mixed spaces and tabs
Error: SPACE_REPLACE_TAB    (line: 118, col:   8):	Found space when expecting tab
Error: CONSECUTIVE_NEWLINES (line: 121, col:   1):	Consecutive newlines
Error: NO_ARGS_VOID         (line: 122, col:  36):	Empty function argument requires void
Error: NO_ARGS_VOID         (line: 123, col:  37):	Empty function argument requires void
Error: NO_ARGS_VOID         (line: 124, col:  40):	Empty function argument requires void
Error: NO_ARGS_VOID         (line: 125, col:  37):	Empty function argument requires void
Error: NO_ARGS_VOID         (line: 126, col:  41):	Empty function argument requires void
Error: NO_ARGS_VOID         (line: 127, col:  43):	Empty function argument requires void
Error: NO_ARGS_VOID         (line: 128, col:  40):	Empty function argument requires void
Error: NO_ARGS_VOID         (line: 129, col:  34):	Empty function argument requires void
Error: NO_ARGS_VOID         (line: 130, col:  41):	Empty function argument requires void
Error: NO_ARGS_VOID         (line: 131, col:  42):	Empty function argument requires void
Error: NO_ARGS_VOID         (line: 132, col:  32):	Empty function argument requires void
Error: NO_ARGS_VOID         (line: 133, col:  28):	Empty function argument requires void
Error: SPC_AFTER_OPERATOR   (line: 136, col:  47):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 136, col:  58):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 137, col:  42):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 137, col:  53):	missing space after operator
Error: CONSECUTIVE_NEWLINES (line: 139, col:   1):	Consecutive newlines
mlx_clear_window.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  12, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  15, col:   1):	Consecutive newlines
Error: TOO_MANY_TABS_FUNC   (line:  16, col:   5):	extra tabs before function name
Error: SPC_AFTER_OPERATOR   (line:  16, col:  38):	missing space after operator
Error: TOO_FEW_TAB          (line:  18, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  18, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  18, col:  29):	missing space after operator
Error: TOO_FEW_TAB          (line:  19, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  19, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  20, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  20, col:   5):	Found space when expecting tab
mlx_int_param_event.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: NO_ARGS_VOID         (line:  13, col:  25):	Empty function argument requires void
Error: FORBIDDEN_CHAR_NAME  (line:  17, col:   5):	user defined identifiers should contain only lowercase characters, digits or '_'
Error: FORBIDDEN_CHAR_NAME  (line:  17, col:   5):	user defined identifiers should contain only lowercase characters, digits or '_'
Error: TOO_FEW_TAB          (line:  19, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  19, col:   3):	Found space when expecting tab
Error: MIXED_SPACE_TAB      (line:  20, col:  17):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line:  20, col:  21):	Two or more consecutives spaces
Error: TOO_MANY_TAB         (line:  20, col:  21):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line:  21, col:  13):	Extra tabs for indent level
Error: FORBIDDEN_CHAR_NAME  (line:  24, col:   5):	user defined identifiers should contain only lowercase characters, digits or '_'
Error: FORBIDDEN_CHAR_NAME  (line:  24, col:   5):	user defined identifiers should contain only lowercase characters, digits or '_'
Error: TOO_FEW_TAB          (line:  26, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  26, col:   3):	Found space when expecting tab
Error: MIXED_SPACE_TAB      (line:  27, col:  21):	Mixed spaces and tabs
Error: TOO_MANY_TAB         (line:  27, col:  25):	Extra tabs for indent level
Error: CONSECUTIVE_SPC      (line:  28, col:  13):	Two or more consecutives spaces
Error: TOO_MANY_TAB         (line:  28, col:  13):	Extra tabs for indent level
Error: FORBIDDEN_CHAR_NAME  (line:  31, col:   5):	user defined identifiers should contain only lowercase characters, digits or '_'
Error: FORBIDDEN_CHAR_NAME  (line:  31, col:   5):	user defined identifiers should contain only lowercase characters, digits or '_'
Error: TOO_FEW_TAB          (line:  33, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  33, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  33, col:  50):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  33, col:  64):	missing space after operator
Error: MIXED_SPACE_TAB      (line:  34, col:   9):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line:  34, col:  13):	Two or more consecutives spaces
Error: TOO_MANY_TAB         (line:  34, col:  13):	Extra tabs for indent level
Error: FORBIDDEN_CHAR_NAME  (line:  37, col:   5):	user defined identifiers should contain only lowercase characters, digits or '_'
Error: FORBIDDEN_CHAR_NAME  (line:  37, col:   5):	user defined identifiers should contain only lowercase characters, digits or '_'
Error: TOO_FEW_TAB          (line:  39, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  39, col:   3):	Found space when expecting tab
Error: MIXED_SPACE_TAB      (line:  40, col:  13):	Mixed spaces and tabs
Error: TOO_MANY_TAB         (line:  40, col:  17):	Extra tabs for indent level
Error: TOO_MANY_TAB         (line:  41, col:  17):	Extra tabs for indent level
Error: TOO_MANY_FUNCS       (line:  44, col:   1):	Too many functions in file
Error: FORBIDDEN_CHAR_NAME  (line:  44, col:   5):	user defined identifiers should contain only lowercase characters, digits or '_'
Error: FORBIDDEN_CHAR_NAME  (line:  44, col:   5):	user defined identifiers should contain only lowercase characters, digits or '_'
Error: TOO_FEW_TAB          (line:  46, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  46, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  46, col:  46):	missing space after operator
Error: TOO_MANY_TAB         (line:  47, col:  17):	Extra tabs for indent level
Error: TOO_MANY_FUNCS       (line:  50, col:   1):	Too many functions in file
Error: FORBIDDEN_CHAR_NAME  (line:  50, col:   5):	user defined identifiers should contain only lowercase characters, digits or '_'
Error: TOO_FEW_TAB          (line:  52, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  52, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  53, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  53, col:   5):	Found space when expecting tab
Error: CONSECUTIVE_NEWLINES (line:  56, col:   1):	Consecutive newlines
Error: TOO_MANY_FUNCS       (line:  57, col:   1):	Too many functions in file
Error: TOO_FEW_TAB          (line:  59, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  59, col:   3):	Found space when expecting tab
Error: GLOBAL_VAR_NAMING    (line:  62, col:   8):	Global variable must start with g_
Error: EOL_OPERATOR         (line:  62, col:  35):	Logic operator at the end of line
Error: TOO_FEW_TAB          (line:  64, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  64, col:   3):	Found space when expecting tab
Error: CONSECUTIVE_SPC      (line:  64, col:  23):	Two or more consecutives spaces
Error: TOO_FEW_TAB          (line:  65, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  65, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  66, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  66, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  67, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  67, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  68, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  68, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  69, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  69, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  70, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  70, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  71, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  71, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  72, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  72, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  73, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  73, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  74, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  74, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  75, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  75, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  76, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  76, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  77, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  77, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  78, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  78, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  79, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  79, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  80, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  80, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  81, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  81, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  82, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  82, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  83, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  83, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  84, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  84, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  85, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  85, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  86, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  86, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  87, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  87, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  88, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  88, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  89, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  89, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  90, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  90, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  91, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  91, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  92, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  92, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  93, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  93, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  94, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  94, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  95, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  95, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  96, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  96, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  97, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  97, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  98, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  98, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  99, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line:  99, col:   3):	Space on empty line
mlx_int_get_visual.c: Error!
Error: INVALID_HEADER       (line:  10, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  12, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  15, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  20, col:   1):	Consecutive newlines
Error: TOO_MANY_TABS_FUNC   (line:  21, col:   5):	extra tabs before function name
Error: TOO_FEW_TAB          (line:  23, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  23, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  24, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  24, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  25, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  25, col:   3):	Found space when expecting tab
Error: MISALIGNED_VAR_DECL  (line:  25, col:  13):	Misaligned variable declaration
Error: SPACE_REPLACE_TAB    (line:  27, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  28, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  28, col:  45):	missing space after operator
Error: TOO_FEW_TAB          (line:  29, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  29, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  30, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  30, col:   5):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  31, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  32, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  33, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  33, col:   3):	Found space when expecting tab
Error: ASSIGN_IN_CONTROL    (line:  33, col:  12):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line:  33, col:  42):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  33, col:  58):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  33, col:  58):	missing space before operator
Error: MIXED_SPACE_TAB      (line:  34, col:   9):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line:  34, col:  13):	Two or more consecutives spaces
Error: TOO_FEW_TAB          (line:  34, col:  13):	Missing tabs for indent level
Error: SPC_AFTER_OPERATOR   (line:  34, col:  26):	missing space after operator
Error: NO_SPC_AFR_PAR       (line:  34, col:  36):	Extra space after parenthesis (brace/bracket)
Error: NO_SPC_BFR_PAR       (line:  34, col:  38):	Extra space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line:  35, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  35, col:   5):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  36, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  37, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  38, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  38, col:   3):	Found space when expecting tab
test/main.c: Error!
Error: EMPTY_LINE_FILE_START (line:   1, col:   1):	Empty line at start of file
Error: INVALID_HEADER       (line:   1, col:   1):	Missing or invalid 42 header
Error: TAB_INSTEAD_SPC      (line:   5, col:   5):	Found tab when expecting space
Error: TAB_INSTEAD_SPC      (line:   6, col:   6):	Found tab when expecting space
Error: TAB_INSTEAD_SPC      (line:   7, col:   7):	Found tab when expecting space
Error: TAB_INSTEAD_SPC      (line:   8, col:   8):	Found tab when expecting space
Error: TAB_INSTEAD_SPC      (line:   9, col:   9):	Found tab when expecting space
Error: TAB_INSTEAD_SPC      (line:  10, col:  10):	Found tab when expecting space
Error: GLOBAL_VAR_NAMING    (line:  12, col:  10):	Global variable must start with g_
Error: GLOBAL_VAR_NAMING    (line:  13, col:  10):	Global variable must start with g_
Error: CONSECUTIVE_SPC      (line:  14, col:   5):	Two or more consecutives spaces
Error: SPACE_REPLACE_TAB    (line:  14, col:   5):	Found space when expecting tab
Error: GLOBAL_VAR_NAMING    (line:  14, col:  10):	Global variable must start with g_
Error: CONSECUTIVE_SPC      (line:  15, col:   5):	Two or more consecutives spaces
Error: SPACE_REPLACE_TAB    (line:  15, col:   5):	Found space when expecting tab
Error: GLOBAL_VAR_NAMING    (line:  15, col:  10):	Global variable must start with g_
Error: CONSECUTIVE_SPC      (line:  16, col:   5):	Two or more consecutives spaces
Error: SPACE_REPLACE_TAB    (line:  16, col:   5):	Found space when expecting tab
Error: GLOBAL_VAR_NAMING    (line:  16, col:  10):	Global variable must start with g_
Error: GLOBAL_VAR_NAMING    (line:  17, col:  10):	Global variable must start with g_
Error: GLOBAL_VAR_NAMING    (line:  18, col:  10):	Global variable must start with g_
Error: GLOBAL_VAR_NAMING    (line:  19, col:  10):	Global variable must start with g_
Error: GLOBAL_VAR_NAMING    (line:  20, col:   5):	Global variable must start with g_
Error: MISALIGNED_VAR_DECL  (line:  20, col:   5):	Misaligned variable declaration
Error: GLOBAL_VAR_NAMING    (line:  21, col:   5):	Global variable must start with g_
Error: MISALIGNED_VAR_DECL  (line:  21, col:   5):	Misaligned variable declaration
Error: GLOBAL_VAR_NAMING    (line:  22, col:   5):	Global variable must start with g_
Error: MISALIGNED_VAR_DECL  (line:  22, col:   5):	Misaligned variable declaration
Error: GLOBAL_VAR_NAMING    (line:  23, col:   5):	Global variable must start with g_
Error: MISALIGNED_VAR_DECL  (line:  23, col:   5):	Misaligned variable declaration
Error: GLOBAL_VAR_NAMING    (line:  24, col:   5):	Global variable must start with g_
Error: MISALIGNED_VAR_DECL  (line:  24, col:   5):	Misaligned variable declaration
Error: GLOBAL_VAR_NAMING    (line:  25, col:   5):	Global variable must start with g_
Error: MISALIGNED_VAR_DECL  (line:  25, col:   5):	Misaligned variable declaration
Error: GLOBAL_VAR_NAMING    (line:  26, col:   5):	Global variable must start with g_
Error: MISALIGNED_VAR_DECL  (line:  26, col:   5):	Misaligned variable declaration
Error: GLOBAL_VAR_NAMING    (line:  27, col:   5):	Global variable must start with g_
Error: MISALIGNED_VAR_DECL  (line:  27, col:   5):	Misaligned variable declaration
Error: GLOBAL_VAR_NAMING    (line:  28, col:   5):	Global variable must start with g_
Error: MISALIGNED_VAR_DECL  (line:  28, col:   5):	Misaligned variable declaration
Error: GLOBAL_VAR_NAMING    (line:  29, col:   5):	Global variable must start with g_
Error: MISALIGNED_VAR_DECL  (line:  29, col:   5):	Misaligned variable declaration
Error: GLOBAL_VAR_NAMING    (line:  30, col:   5):	Global variable must start with g_
Error: MISALIGNED_VAR_DECL  (line:  30, col:   5):	Misaligned variable declaration
Error: GLOBAL_VAR_NAMING    (line:  31, col:   5):	Global variable must start with g_
Error: MISALIGNED_VAR_DECL  (line:  31, col:   5):	Misaligned variable declaration
Error: GLOBAL_VAR_NAMING    (line:  32, col:  10):	Global variable must start with g_
Error: GLOBAL_VAR_NAMING    (line:  33, col:  10):	Global variable must start with g_
Error: GLOBAL_VAR_NAMING    (line:  34, col:  10):	Global variable must start with g_
Error: GLOBAL_VAR_NAMING    (line:  35, col:  10):	Global variable must start with g_
Error: GLOBAL_VAR_NAMING    (line:  36, col:   5):	Global variable must start with g_
Error: MISALIGNED_VAR_DECL  (line:  36, col:   5):	Misaligned variable declaration
Error: GLOBAL_VAR_NAMING    (line:  37, col:   5):	Global variable must start with g_
Error: MISALIGNED_VAR_DECL  (line:  37, col:   5):	Misaligned variable declaration
Error: GLOBAL_VAR_NAMING    (line:  39, col:   5):	Global variable must start with g_
Error: MISALIGNED_VAR_DECL  (line:  39, col:   5):	Misaligned variable declaration
Error: SPC_AFTER_OPERATOR   (line:  41, col:  26):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  41, col:  32):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  42, col:  36):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  42, col:  44):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  42, col:  51):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  42, col:  57):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  42, col:  63):	missing space after operator
Error: LINE_TOO_LONG        (line:  42, col:  84):	line too long
Error: TOO_MANY_ARGS        (line:  42, col:  85):	Function has more than 4 arguments
Error: TOO_FEW_TAB          (line:  46, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  46, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  46, col:  30):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  46, col:  35):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  46, col:  39):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  46, col:  41):	missing space after operator
Error: TOO_FEW_TAB          (line:  51, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  51, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  51, col:  30):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  51, col:  35):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  51, col:  39):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  51, col:  41):	missing space after operator
Error: TOO_FEW_TAB          (line:  52, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  52, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  52, col:  30):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  52, col:  35):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  52, col:  39):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  52, col:  41):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  55, col:  21):	missing space after operator
Error: TOO_FEW_TAB          (line:  57, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  57, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  57, col:  29):	missing space after operator
Error: TOO_FEW_TAB          (line:  58, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  58, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  58, col:  10):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  58, col:  10):	missing space before operator
Error: TOO_FEW_TAB          (line:  59, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  59, col:   5):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  62, col:  21):	missing space after operator
Error: TOO_FEW_TAB          (line:  64, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  64, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  64, col:  29):	missing space after operator
Error: TOO_FEW_TAB          (line:  65, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  65, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  65, col:  10):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  65, col:  10):	missing space before operator
Error: TOO_FEW_TAB          (line:  66, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  66, col:   5):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  69, col:  21):	missing space after operator
Error: TOO_FEW_TAB          (line:  71, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  71, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  71, col:  29):	missing space after operator
Error: TOO_FEW_TAB          (line:  72, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  72, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  72, col:  10):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  72, col:  10):	missing space before operator
Error: TOO_FEW_TAB          (line:  73, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  73, col:   5):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  73, col:  27):	missing space after operator
Error: TOO_MANY_FUNCS       (line:  76, col:   1):	Too many functions in file
Error: SPC_AFTER_OPERATOR   (line:  76, col:  26):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  76, col:  32):	missing space after operator
Error: TOO_FEW_TAB          (line:  78, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  78, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  78, col:  47):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  78, col:  54):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  78, col:  56):	missing space after operator
Error: TOO_MANY_FUNCS       (line:  81, col:   1):	Too many functions in file
Error: SPC_AFTER_OPERATOR   (line:  81, col:  26):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  81, col:  32):	missing space after operator
Error: TOO_FEW_TAB          (line:  83, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  83, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  83, col:  47):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  83, col:  54):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  83, col:  56):	missing space after operator
Error: TOO_MANY_FUNCS       (line:  86, col:   1):	Too many functions in file
Error: SPC_AFTER_OPERATOR   (line:  86, col:  21):	missing space after operator
Error: TOO_FEW_TAB          (line:  88, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  88, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  88, col:  44):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  88, col:  46):	missing space after operator
Error: CONSECUTIVE_NEWLINES (line:  91, col:   1):	Consecutive newlines
Error: TOO_MANY_FUNCS       (line:  92, col:   1):	Too many functions in file
Error: NO_ARGS_VOID         (line:  92, col:  10):	Empty function argument requires void
Error: TOO_FEW_TAB          (line:  94, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  94, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  96, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  96, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  97, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  98, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  98, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  99, col:   5):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 100, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 100, col:   3):	Space on empty line
Error: SPACE_REPLACE_TAB    (line: 101, col:   5):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 102, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 102, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 102, col:  34):	missing space after operator
Error: EMPTY_LINE_FUNCTION  (line: 103, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line: 104, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 104, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 105, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 105, col:   3):	Found space when expecting tab
Error: ASSIGN_IN_CONTROL    (line: 105, col:  13):	Assignment in control structure
Error: TOO_FEW_TAB          (line: 106, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 106, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line: 107, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 107, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 108, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 108, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 109, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 109, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line: 110, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 110, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 110, col:  44):	missing space after operator
Error: SPC_BFR_PAR          (line: 110, col:  45):	Missing space before parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 110, col:  70):	missing space after operator
Error: SPC_BFR_PAR          (line: 110, col:  71):	Missing space before parenthesis (brace/bracket)
Error: LINE_TOO_LONG        (line: 110, col:  82):	line too long
Error: EMPTY_LINE_FUNCTION  (line: 111, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line: 112, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 112, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 112, col:  43):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 112, col:  51):	missing space after operator
Error: TOO_FEW_TAB          (line: 113, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 113, col:   3):	Found space when expecting tab
Error: ASSIGN_IN_CONTROL    (line: 113, col:  14):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line: 113, col:  34):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 113, col:  42):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 113, col:  50):	missing space after operator
Error: TOO_FEW_TAB          (line: 114, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 114, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line: 115, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 115, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 116, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 116, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 117, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 117, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line: 118, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 118, col:   3):	Found space when expecting tab
Error: EMPTY_LINE_FUNCTION  (line: 119, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line: 120, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 120, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 121, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 121, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 121, col:  19):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 121, col:  27):	missing space after operator
Error: TOO_FEW_TAB          (line: 122, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 122, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 123, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 123, col:   3):	Found space when expecting tab
Error: EMPTY_LINE_FUNCTION  (line: 124, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line: 125, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 125, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 126, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 126, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 126, col:  23):	missing space after operator
Error: TOO_FEW_TAB          (line: 127, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 127, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 128, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 128, col:   3):	Found space when expecting tab
Error: EMPTY_LINE_FUNCTION  (line: 129, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line: 130, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 130, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 130, col:  40):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 130, col:  47):	missing space after operator
Error: TOO_FEW_TAB          (line: 131, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 131, col:   3):	Found space when expecting tab
Error: ASSIGN_IN_CONTROL    (line: 131, col:  13):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line: 131, col:  32):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 131, col:  39):	missing space after operator
Error: TOO_FEW_TAB          (line: 132, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 132, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line: 133, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 133, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 134, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 134, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 135, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 135, col:   5):	Space on empty line
Error: SPACE_REPLACE_TAB    (line: 136, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 136, col:  32):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 136, col:  38):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 136, col:  43):	missing space after operator
Error: TOO_FEW_TAB          (line: 137, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 137, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 137, col:  61):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 137, col:  66):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 137, col:  70):	missing space after operator
Error: MIXED_SPACE_TAB      (line: 138, col:   1):	Mixed spaces and tabs
Error: TOO_FEW_TAB          (line: 138, col:   1):	Missing tabs for indent level
Error: EMPTY_LINE_FUNCTION  (line: 139, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line: 140, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 140, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 141, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 141, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 141, col:  20):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 141, col:  25):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 141, col:  29):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 141, col:  36):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 141, col:  43):	missing space after operator
Error: TOO_FEW_TAB          (line: 142, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 142, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 142, col:  29):	missing space after operator
Error: SPC_BFR_PAR          (line: 142, col:  30):	Missing space before parenthesis (brace/bracket)
Error: EMPTY_LINE_FUNCTION  (line: 143, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line: 144, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 144, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 145, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 145, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 145, col:  30):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 145, col:  35):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 145, col:  39):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 145, col:  42):	missing space after operator
Error: TOO_FEW_TAB          (line: 146, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 146, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 147, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 147, col:   3):	Found space when expecting tab
Error: EMPTY_LINE_FUNCTION  (line: 148, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line: 149, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 149, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 150, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 150, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 151, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 151, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 152, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 152, col:   3):	Found space when expecting tab
Error: EMPTY_LINE_FUNCTION  (line: 153, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line: 154, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 154, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 154, col:  40):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 154, col:  47):	missing space after operator
Error: TOO_FEW_TAB          (line: 155, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 155, col:   3):	Found space when expecting tab
Error: ASSIGN_IN_CONTROL    (line: 155, col:  13):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line: 155, col:  32):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 155, col:  39):	missing space after operator
Error: TOO_FEW_TAB          (line: 156, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 156, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line: 157, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 157, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 158, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 158, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 159, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 159, col:   5):	Space on empty line
Error: SPACE_REPLACE_TAB    (line: 160, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 160, col:  32):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 160, col:  38):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 160, col:  43):	missing space after operator
Error: TOO_FEW_TAB          (line: 161, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 161, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 161, col:  58):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 161, col:  63):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 161, col:  67):	missing space after operator
Error: MIXED_SPACE_TAB      (line: 162, col:   1):	Mixed spaces and tabs
Error: TOO_FEW_TAB          (line: 162, col:   1):	Missing tabs for indent level
Error: EMPTY_LINE_FUNCTION  (line: 163, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line: 164, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 164, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 165, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 165, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 165, col:  20):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 165, col:  25):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 165, col:  29):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 165, col:  36):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 165, col:  43):	missing space after operator
Error: TOO_FEW_TAB          (line: 166, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 166, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 166, col:  29):	missing space after operator
Error: SPC_BFR_PAR          (line: 166, col:  30):	Missing space before parenthesis (brace/bracket)
Error: EMPTY_LINE_FUNCTION  (line: 167, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line: 168, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 168, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 169, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 169, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 169, col:  30):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 169, col:  35):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 169, col:  39):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 169, col:  42):	missing space after operator
Error: TOO_FEW_TAB          (line: 170, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 170, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 171, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 171, col:   3):	Found space when expecting tab
Error: EMPTY_LINE_FUNCTION  (line: 172, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line: 173, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 173, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 174, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 174, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 174, col:  21):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 174, col:  26):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 174, col:  28):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 174, col:  36):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 174, col:  36):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 174, col:  38):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 174, col:  47):	missing space after operator
Error: TOO_FEW_TAB          (line: 175, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 175, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 175, col:  21):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 175, col:  26):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 175, col:  29):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 175, col:  37):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 175, col:  37):	missing space before operator
Error: SPC_BFR_OPERATOR     (line: 175, col:  39):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 175, col:  42):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 175, col:  51):	missing space after operator
Error: TOO_FEW_TAB          (line: 176, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 176, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 177, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 177, col:   3):	Found space when expecting tab
Error: EMPTY_LINE_FUNCTION  (line: 178, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line: 179, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 179, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 180, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 180, col:   3):	Found space when expecting tab
Error: ASSIGN_IN_CONTROL    (line: 180, col:  13):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line: 180, col:  40):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 180, col:  51):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 180, col:  59):	missing space after operator
Error: TOO_FEW_TAB          (line: 181, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 181, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line: 182, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 182, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 183, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 183, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 184, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 184, col:   5):	Space on empty line
Error: SPACE_REPLACE_TAB    (line: 185, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 185, col:  32):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 185, col:  38):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 185, col:  43):	missing space after operator
Error: TOO_FEW_TAB          (line: 186, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 186, col:   3):	Found space when expecting tab
Error: MIXED_SPACE_TAB      (line: 187, col:   1):	Mixed spaces and tabs
Error: TOO_FEW_TAB          (line: 187, col:   1):	Missing tabs for indent level
Error: SPC_AFTER_OPERATOR   (line: 187, col:  12):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 187, col:  19):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 187, col:  24):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 187, col:  28):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 187, col:  36):	missing space after operator
Error: SPC_BFR_PAR          (line: 187, col:  37):	Missing space before parenthesis (brace/bracket)
Error: TOO_FEW_TAB          (line: 188, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 188, col:   3):	Found space when expecting tab
Error: EMPTY_LINE_FUNCTION  (line: 189, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line: 190, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 190, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 191, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 191, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 191, col:  30):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 191, col:  35):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 191, col:  39):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 191, col:  41):	missing space after operator
Error: TOO_FEW_TAB          (line: 192, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 192, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 192, col:  30):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 192, col:  35):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 192, col:  39):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 192, col:  43):	missing space after operator
Error: TOO_FEW_TAB          (line: 193, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 193, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 194, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 194, col:   3):	Found space when expecting tab
Error: EMPTY_LINE_FUNCTION  (line: 195, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line: 196, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 196, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line: 197, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 197, col:  28):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 197, col:  36):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 197, col:  44):	missing space after operator
Error: TOO_FEW_TAB          (line: 198, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 198, col:   3):	Found space when expecting tab
Error: ASSIGN_IN_CONTROL    (line: 198, col:  13):	Assignment in control structure
Error: SPC_AFTER_OPERATOR   (line: 198, col:  32):	missing space after operator
Error: TOO_FEW_TAB          (line: 199, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 199, col:   5):	Space on empty line
Error: TOO_FEW_TAB          (line: 200, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 200, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 201, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 201, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 202, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 202, col:   5):	Space on empty line
Error: SPACE_REPLACE_TAB    (line: 203, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 203, col:  32):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 203, col:  38):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 203, col:  43):	missing space after operator
Error: TOO_FEW_TAB          (line: 204, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 204, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 204, col:  20):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 204, col:  25):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 204, col:  29):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 204, col:  36):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 204, col:  43):	missing space after operator
Error: EMPTY_LINE_FUNCTION  (line: 205, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line: 206, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 206, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line: 207, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 207, col:  28):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 207, col:  36):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 207, col:  44):	missing space after operator
Error: TOO_FEW_TAB          (line: 208, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 208, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 208, col:  23):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 208, col:  35):	missing space after operator
Error: TOO_FEW_TAB          (line: 209, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 209, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 209, col:  22):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 209, col:  33):	missing space after operator
Error: TOO_FEW_TAB          (line: 210, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 210, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 210, col:  20):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 210, col:  29):	missing space after operator
Error: TOO_FEW_TAB          (line: 211, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 211, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 211, col:  23):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 211, col:  35):	missing space after operator
Error: TOO_FEW_TAB          (line: 212, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 212, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 212, col:  22):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 212, col:  33):	missing space after operator
Error: TOO_FEW_TAB          (line: 213, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 213, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 213, col:  20):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 213, col:  29):	missing space after operator
Error: TOO_FEW_TAB          (line: 214, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 214, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 214, col:  20):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 214, col:  29):	missing space after operator
Error: EMPTY_LINE_FUNCTION  (line: 215, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line: 216, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 216, col:   3):	Found space when expecting tab
Error: EMPTY_LINE_FUNCTION  (line: 217, col:   1):	Empty line in function
Error: TOO_FEW_TAB          (line: 218, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 218, col:   3):	Found space when expecting tab
Error: EMPTY_LINE_FUNCTION  (line: 219, col:   1):	Empty line in function
Error: SPACE_EMPTY_LINE     (line: 219, col:   1):	Space on empty line
Error: TOO_FEW_TAB          (line: 220, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 220, col:   3):	Found space when expecting tab
Error: TOO_MANY_LINES       (line: 221, col:   1):	Function has more than 25 lines
Error: CONSECUTIVE_NEWLINES (line: 223, col:   1):	Consecutive newlines
Error: TOO_MANY_FUNCS       (line: 224, col:   1):	Too many functions in file
Error: SPC_AFTER_OPERATOR   (line: 224, col:  26):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 224, col:  32):	missing space after operator
Error: TOO_FEW_TAB          (line: 226, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 226, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 227, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 227, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 228, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 228, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line: 230, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 231, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 231, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 232, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 232, col:   5):	Space on empty line
Error: SPACE_REPLACE_TAB    (line: 233, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 234, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 234, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 235, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 235, col:   9):	Space on empty line
Error: SPACE_REPLACE_TAB    (line: 236, col:  11):	Found space when expecting tab
Error: SPACE_AFTER_KW       (line: 236, col:  20):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line: 236, col:  21):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 236, col:  21):	missing space before operator
Error: SPC_AFTER_PAR        (line: 236, col:  25):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 236, col:  26):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 236, col:  26):	missing space before operator
Error: SPC_BFR_OPERATOR     (line: 236, col:  28):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 236, col:  34):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 236, col:  34):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 236, col:  37):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 236, col:  37):	missing space before operator
Error: SPC_AFTER_PAR        (line: 236, col:  41):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 236, col:  42):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 236, col:  42):	missing space before operator
Error: SPC_AFTER_PAR        (line: 236, col:  44):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 236, col:  45):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 236, col:  45):	missing space before operator
Error: SPC_BFR_OPERATOR     (line: 236, col:  50):	missing space before operator
Error: SPACE_AFTER_KW       (line: 236, col:  54):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line: 236, col:  55):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 236, col:  55):	missing space before operator
Error: SPC_AFTER_PAR        (line: 236, col:  59):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 236, col:  60):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 236, col:  60):	missing space before operator
Error: SPC_AFTER_PAR        (line: 236, col:  62):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 236, col:  63):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 236, col:  63):	missing space before operator
Error: MIXED_SPACE_TAB      (line: 237, col:   1):	Mixed spaces and tabs
Error: TOO_FEW_TAB          (line: 237, col:   1):	Missing tabs for indent level
Error: CONSECUTIVE_SPC      (line: 237, col:   5):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line: 237, col:  24):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 237, col:  28):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 237, col:  30):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 237, col:  32):	missing space after operator
Error: TOO_FEW_TAB          (line: 238, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 238, col:   9):	Space on empty line
Error: TOO_FEW_TAB          (line: 239, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 239, col:   5):	Space on empty line
Error: CONSECUTIVE_NEWLINES (line: 242, col:   1):	Consecutive newlines
Error: TOO_MANY_FUNCS       (line: 243, col:   1):	Too many functions in file
Error: SPC_AFTER_OPERATOR   (line: 243, col:  36):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 243, col:  44):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 243, col:  51):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 243, col:  57):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line: 243, col:  63):	missing space after operator
Error: LINE_TOO_LONG        (line: 243, col:  84):	line too long
Error: TOO_MANY_ARGS        (line: 243, col:  85):	Function has more than 4 arguments
Error: TOO_FEW_TAB          (line: 245, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 245, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 246, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 246, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 247, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 247, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 248, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 248, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 249, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 249, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 250, col:   1):	Missing tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line: 250, col:   1):	Too many variables declarations in a function
Error: SPACE_REPLACE_TAB    (line: 250, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 251, col:   1):	Missing tabs for indent level
Error: TOO_MANY_VARS_FUNC   (line: 251, col:   1):	Too many variables declarations in a function
Error: SPACE_REPLACE_TAB    (line: 251, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line: 251, col:  16):	Found space when expecting tab
Error: MISALIGNED_VAR_DECL  (line: 251, col:  17):	Misaligned variable declaration
Error: SPACE_REPLACE_TAB    (line: 253, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 253, col:  12):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 253, col:  12):	missing space before operator
Error: TOO_FEW_TAB          (line: 254, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 254, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 254, col:  23):	missing space after operator
Error: SPACE_REPLACE_TAB    (line: 255, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 256, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 256, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 257, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 257, col:   5):	Space on empty line
Error: SPACE_REPLACE_TAB    (line: 258, col:   7):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 258, col:  17):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 258, col:  17):	missing space before operator
Error: SPACE_AFTER_KW       (line: 258, col:  18):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line: 258, col:  19):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 258, col:  19):	missing space before operator
Error: SPACE_REPLACE_TAB    (line: 259, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 260, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line: 260, col:   7):	Found space when expecting tab
Error: TOO_FEW_TAB          (line: 261, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 261, col:   9):	Space on empty line
Error: MIXED_SPACE_TAB      (line: 262, col:   1):	Mixed spaces and tabs
Error: TOO_FEW_TAB          (line: 262, col:   1):	Missing tabs for indent level
Error: CONSECUTIVE_SPC      (line: 262, col:   5):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line: 262, col:  15):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 262, col:  15):	missing space before operator
Error: MIXED_SPACE_TAB      (line: 263, col:   1):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line: 263, col:   5):	Two or more consecutives spaces
Error: SPACE_AFTER_KW       (line: 263, col:  18):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line: 263, col:  19):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 263, col:  19):	missing space before operator
Error: SPC_AFTER_PAR        (line: 263, col:  23):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 263, col:  24):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 263, col:  24):	missing space before operator
Error: SPC_BFR_OPERATOR     (line: 263, col:  26):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 263, col:  32):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 263, col:  32):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 263, col:  35):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 263, col:  35):	missing space before operator
Error: SPC_AFTER_PAR        (line: 263, col:  39):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 263, col:  40):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 263, col:  40):	missing space before operator
Error: SPC_AFTER_PAR        (line: 263, col:  42):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 263, col:  43):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 263, col:  43):	missing space before operator
Error: TOO_FEW_TAB          (line: 264, col:   1):	Missing tabs for indent level
Error: SPC_AFTER_OPERATOR   (line: 264, col:  16):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 264, col:  16):	missing space before operator
Error: SPC_AFTER_PAR        (line: 264, col:  20):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 264, col:  21):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 264, col:  21):	missing space before operator
Error: SPC_AFTER_PAR        (line: 264, col:  23):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 264, col:  24):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 264, col:  24):	missing space before operator
Error: MIXED_SPACE_TAB      (line: 265, col:   1):	Mixed spaces and tabs
Error: TOO_FEW_TAB          (line: 265, col:   1):	Missing tabs for indent level
Error: CONSECUTIVE_SPC      (line: 265, col:   5):	Two or more consecutives spaces
Error: MIXED_SPACE_TAB      (line: 266, col:   1):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line: 266, col:   5):	Two or more consecutives spaces
Error: SPACE_AFTER_KW       (line: 266, col:  18):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line: 266, col:  19):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 266, col:  19):	missing space before operator
Error: SPC_AFTER_PAR        (line: 266, col:  23):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 266, col:  24):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 266, col:  24):	missing space before operator
Error: SPC_BFR_OPERATOR     (line: 266, col:  26):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 266, col:  32):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 266, col:  32):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 266, col:  35):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 266, col:  35):	missing space before operator
Error: SPC_AFTER_PAR        (line: 266, col:  39):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 266, col:  40):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 266, col:  40):	missing space before operator
Error: SPC_AFTER_PAR        (line: 266, col:  42):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 266, col:  43):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 266, col:  43):	missing space before operator
Error: SPC_BFR_OPERATOR     (line: 266, col:  48):	missing space before operator
Error: SPACE_AFTER_KW       (line: 266, col:  52):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line: 266, col:  53):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 266, col:  53):	missing space before operator
Error: SPC_AFTER_PAR        (line: 266, col:  57):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 266, col:  58):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 266, col:  58):	missing space before operator
Error: SPC_AFTER_PAR        (line: 266, col:  60):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line: 266, col:  61):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 266, col:  61):	missing space before operator
Error: SPACE_REPLACE_TAB    (line: 267, col:  11):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line: 267, col:  43):	missing space after operator
Error: MIXED_SPACE_TAB      (line: 268, col:   1):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line: 268, col:   5):	Two or more consecutives spaces
Error: MIXED_SPACE_TAB      (line: 269, col:   1):	Mixed spaces and tabs
Error: TOO_FEW_TAB          (line: 269, col:   1):	Missing tabs for indent level
Error: CONSECUTIVE_SPC      (line: 269, col:   5):	Two or more consecutives spaces
Error: MIXED_SPACE_TAB      (line: 270, col:   1):	Mixed spaces and tabs
Error: TOO_FEW_TAB          (line: 270, col:   1):	Missing tabs for indent level
Error: CONSECUTIVE_SPC      (line: 270, col:   5):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line: 270, col:  19):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 270, col:  19):	missing space before operator
Error: MIXED_SPACE_TAB      (line: 271, col:   1):	Mixed spaces and tabs
Error: MULT_IN_SINGLE_INSTR (line: 271, col:   1):	Multiple instructions in single line control structure
Error: TOO_FEW_TAB          (line: 271, col:   1):	Missing tabs for indent level
Error: CONSECUTIVE_SPC      (line: 271, col:   5):	Two or more consecutives spaces
Error: TOO_FEW_TAB          (line: 272, col:   1):	Missing tabs for indent level
Error: MIXED_SPACE_TAB      (line: 273, col:   5):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line: 273, col:   9):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line: 273, col:  16):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 273, col:  16):	missing space before operator
Error: SPACE_AFTER_KW       (line: 273, col:  17):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line: 273, col:  18):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 273, col:  18):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 273, col:  22):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 273, col:  22):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 273, col:  60):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 273, col:  60):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 273, col:  64):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 273, col:  64):	missing space before operator
Error: TOO_FEW_TAB          (line: 274, col:   1):	Missing tabs for indent level
Error: MIXED_SPACE_TAB      (line: 275, col:   5):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line: 275, col:   9):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line: 275, col:  16):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 275, col:  16):	missing space before operator
Error: SPACE_AFTER_KW       (line: 275, col:  17):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line: 275, col:  18):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 275, col:  18):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 275, col:  22):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 275, col:  22):	missing space before operator
Error: MIXED_SPACE_TAB      (line: 276, col:   1):	Mixed spaces and tabs
Error: TOO_FEW_TAB          (line: 276, col:   1):	Missing tabs for indent level
Error: CONSECUTIVE_SPC      (line: 276, col:   5):	Two or more consecutives spaces
Error: MIXED_SPACE_TAB      (line: 277, col:   1):	Mixed spaces and tabs
Error: TOO_FEW_TAB          (line: 277, col:   1):	Missing tabs for indent level
Error: CONSECUTIVE_SPC      (line: 277, col:   5):	Two or more consecutives spaces
Error: MIXED_SPACE_TAB      (line: 278, col:   1):	Mixed spaces and tabs
Error: TOO_FEW_TAB          (line: 278, col:   1):	Missing tabs for indent level
Error: CONSECUTIVE_SPC      (line: 278, col:   5):	Two or more consecutives spaces
Error: TOO_FEW_TAB          (line: 279, col:   1):	Missing tabs for indent level
Error: MIXED_SPACE_TAB      (line: 280, col:   5):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line: 280, col:   9):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line: 280, col:  16):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 280, col:  16):	missing space before operator
Error: SPACE_AFTER_KW       (line: 280, col:  17):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line: 280, col:  18):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 280, col:  18):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 280, col:  22):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 280, col:  22):	missing space before operator
Error: SPC_BFR_OPERATOR     (line: 280, col:  62):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 280, col:  64):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 280, col:  64):	missing space before operator
Error: TOO_FEW_TAB          (line: 281, col:   1):	Missing tabs for indent level
Error: MIXED_SPACE_TAB      (line: 282, col:   5):	Mixed spaces and tabs
Error: CONSECUTIVE_SPC      (line: 282, col:   9):	Two or more consecutives spaces
Error: SPC_AFTER_OPERATOR   (line: 282, col:  16):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 282, col:  16):	missing space before operator
Error: SPACE_AFTER_KW       (line: 282, col:  17):	Missing space after keyword
Error: SPC_AFTER_OPERATOR   (line: 282, col:  18):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 282, col:  18):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 282, col:  22):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 282, col:  22):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line: 282, col:  60):	missing space after operator
Error: SPC_BFR_OPERATOR     (line: 282, col:  60):	missing space before operator
Error: MIXED_SPACE_TAB      (line: 283, col:   1):	Mixed spaces and tabs
Error: TOO_FEW_TAB          (line: 283, col:   1):	Missing tabs for indent level
Error: CONSECUTIVE_SPC      (line: 283, col:   5):	Two or more consecutives spaces
Error: TOO_FEW_TAB          (line: 284, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 284, col:   9):	Space on empty line
Error: TOO_FEW_TAB          (line: 285, col:   1):	Missing tabs for indent level
Error: SPACE_EMPTY_LINE     (line: 285, col:   5):	Space on empty line
Error: EMPTY_LINE_FUNCTION  (line: 286, col:   1):	Empty line in function
Error: TOO_MANY_LINES       (line: 287, col:   1):	Function has more than 25 lines
test/new_win.c: Error!
Error: EMPTY_LINE_FILE_START (line:   1, col:   1):	Empty line at start of file
Error: INVALID_HEADER       (line:   1, col:   1):	Missing or invalid 42 header
Error: CONSECUTIVE_NEWLINES (line:   2, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:   3, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:   6, col:   1):	Consecutive newlines
Error: SPACE_REPLACE_TAB    (line:   7, col:   5):	Found space when expecting tab
Error: GLOBAL_VAR_NAMING    (line:   7, col:   7):	Global variable must start with g_
Error: SPACE_REPLACE_TAB    (line:   8, col:   5):	Found space when expecting tab
Error: GLOBAL_VAR_NAMING    (line:   8, col:   7):	Global variable must start with g_
Error: SPACE_REPLACE_TAB    (line:   9, col:   5):	Found space when expecting tab
Error: GLOBAL_VAR_NAMING    (line:   9, col:   7):	Global variable must start with g_
Error: CONSECUTIVE_NEWLINES (line:  11, col:   1):	Consecutive newlines
Error: CONSECUTIVE_NEWLINES (line:  12, col:   1):	Consecutive newlines
Error: SPACE_BEFORE_FUNC    (line:  13, col:   4):	space before function name
Error: SPC_AFTER_OPERATOR   (line:  13, col:  21):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  13, col:  27):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  13, col:  38):	missing space after operator
Error: TOO_FEW_TAB          (line:  15, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  15, col:   3):	Found space when expecting tab
Error: TOO_FEW_TAB          (line:  16, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  16, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  16, col:  25):	missing space after operator
Error: SPACE_REPLACE_TAB    (line:  17, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  17, col:  28):	missing space after operator
Error: SPC_AFTER_PAR        (line:  17, col:  36):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line:  17, col:  37):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  17, col:  37):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  17, col:  41):	missing space after operator
Error: SPC_AFTER_PAR        (line:  17, col:  49):	Missing space after parenthesis (brace/bracket)
Error: SPC_AFTER_OPERATOR   (line:  17, col:  50):	missing space after operator
Error: SPC_BFR_OPERATOR     (line:  17, col:  50):	missing space before operator
Error: SPC_AFTER_OPERATOR   (line:  17, col:  54):	missing space after operator
Error: TOO_FEW_TAB          (line:  18, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  18, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  18, col:  22):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  18, col:  33):	missing space after operator
Error: CONSECUTIVE_NEWLINES (line:  21, col:   1):	Consecutive newlines
Error: SPACE_BEFORE_FUNC    (line:  22, col:   4):	space before function name
Error: NO_ARGS_VOID         (line:  22, col:  10):	Empty function argument requires void
Error: TOO_FEW_TAB          (line:  24, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  24, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  25, col:   3):	Found space when expecting tab
Error: SPACE_REPLACE_TAB    (line:  26, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  26, col:  28):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  26, col:  32):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  26, col:  36):	missing space after operator
Error: SPACE_REPLACE_TAB    (line:  27, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  27, col:  28):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  27, col:  32):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  27, col:  36):	missing space after operator
Error: TOO_FEW_TAB          (line:  28, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  28, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  28, col:  22):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  28, col:  33):	missing space after operator
Error: TOO_FEW_TAB          (line:  29, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  29, col:   3):	Found space when expecting tab
Error: SPC_AFTER_OPERATOR   (line:  29, col:  22):	missing space after operator
Error: SPC_AFTER_OPERATOR   (line:  29, col:  33):	missing space after operator
Error: TOO_FEW_TAB          (line:  30, col:   1):	Missing tabs for indent level
Error: SPACE_REPLACE_TAB    (line:  30, col:   3):	Found space when expecting tab" 2>&1)
    norm_errors=$(echo "$norm_output" | grep "Error" | wc -l)
    
    if [ $norm_errors -gt 0 ]; then
        echo -e "${RED}❌ Erreurs de norminette détectées :${NC}"
        echo "$norm_output" | grep "Error"
        echo -e "${YELLOW}Continuez quand même ? (y/n)${NC}"
        read -r response
        if [ "$response" != "y" ] && [ "$response" != "Y" ]; then
            exit 1
        fi
    else
        echo -e "${GREEN}✅ Aucune erreur de norminette${NC}"
    fi
fi
echo ""

# Fonction de compilation
compile_project() {
    local compile_mode=$1
    
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    if [ "$compile_mode" = "bonus" ]; then
        echo -e "${YELLOW}🔨 Compilation avec 'make bonus'...${NC}"
        make bonus
    else
        echo -e "${YELLOW}🔨 Compilation avec 'make'...${NC}"
        make
    fi
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}❌ Erreur lors de la compilation !${NC}"
        return 1
    fi
    echo -e "${GREEN}✅ Compilation réussie !${NC}"
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}\n"
    return 0
}

# Vérifier que valgrind est installé
if ! command -v valgrind &> /dev/null; then
    echo -e "${RED}valgrind n'est pas installé !${NC}"
    echo -e "${YELLOW}Installation recommandée: sudo apt-get install valgrind${NC}"
    exit 1
fi

# Vérifier que xdotool est installé
if ! command -v xdotool &> /dev/null; then
    echo -e "${YELLOW}xdotool n'est pas installé (recommandé pour fermer automatiquement le jeu)${NC}"
    echo -e "${YELLOW}Installation: sudo apt-get install xdotool${NC}"
    USE_XDOTOOL=false
else
    USE_XDOTOOL=true
fi

# Compteurs globaux
total_tests=0
failed_tests=0
passed_tests=0

# Fonction pour tester une map
test_map() {
    local map_path=$1
    local map_name=$(basename "$map_path")
    local is_invalid=$2
    local executable=$3  # "./cub3D" ou "./cub3D_Bonus"
    
    total_tests=$((total_tests + 1))
    
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${YELLOW}Test #${total_tests}: ${map_name}${NC}"
    echo -e "${BLUE}Chemin: ${map_path}${NC}"
    
    # Créer un fichier temporaire pour la sortie de valgrind
    valgrind_output=$(mktemp)
    
    # Exécuter avec valgrind en arrière-plan
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
        --error-exitcode=42 "$executable" "$map_path" > "$valgrind_output" 2>&1 &
    
    local pid=$!
    
    # Si c'est une map valide, attendre 10 secondes puis envoyer ESC pour fermer proprement
    if [ "$is_invalid" = "false" ] && [ "$USE_XDOTOOL" = "true" ]; then
        sleep 3
        # Trouver la fenêtre du jeu et envoyer ESC
        local window_id=$(xdotool search --pid $pid 2>/dev/null | head -1)
        if [ -n "$window_id" ]; then
            xdotool key --window $window_id Escape 2>/dev/null
            echo -e "${BLUE}🎮 Envoi de la touche ESC pour fermer le jeu...${NC}"
        fi
    fi
    
    # Attendre jusqu'à 15 secondes maximum
    local elapsed=0
    local max_wait=15
    if [ "$is_invalid" = "true" ]; then
        max_wait=5  # Les maps invalides ne devraient pas prendre longtemps
    fi
    
    while [ $elapsed -lt $max_wait ]; do
        if ! kill -0 $pid 2>/dev/null; then
            break
        fi
        sleep 1
        elapsed=$((elapsed + 1))
    done
    
    # Si le processus tourne encore, le tuer
    if kill -0 $pid 2>/dev/null; then
        echo -e "${YELLOW}⏱️  TIMEOUT (${max_wait}s) - Arrêt forcé du programme${NC}"
        kill -9 $pid 2>/dev/null
        wait $pid 2>/dev/null
        failed_tests=$((failed_tests + 1))
        rm -f "$valgrind_output"
        echo ""
        return
    fi
    
    # Récupérer le code de sortie
    wait $pid 2>/dev/null
    exit_code=$?
    
    # Afficher toutes les erreurs de valgrind s'il y en a
    local has_errors=false
    local no_leaks=false
    
    # Vérifier si "All heap blocks were freed -- no leaks are possible" est présent
    if grep -q "All heap blocks were freed -- no leaks are possible" "$valgrind_output" && \
       grep -q "ERROR SUMMARY: 0 errors from 0 contexts" "$valgrind_output"; then
        no_leaks=true
    fi
    
    # Vérifier s'il y a des erreurs (sauf si no_leaks est true)
    if [ "$no_leaks" = "false" ]; then
        if grep -q "ERROR SUMMARY: [1-9]" "$valgrind_output" || \
           grep -q "Invalid" "$valgrind_output" || \
           grep -q "Mismatched" "$valgrind_output" || \
           grep -q "definitely lost" "$valgrind_output" || \
           grep -q "indirectly lost" "$valgrind_output" || \
           grep -q "possibly lost" "$valgrind_output"; then
            has_errors=true
        fi
    fi
    
    # Vérifier le code de sortie
    if [ $exit_code -eq 42 ] || [ "$has_errors" = "true" ]; then
        echo -e "${RED}❌ ERREUR VALGRIND - Fuites mémoire ou erreurs détectées${NC}"
        echo -e "${RED}═══════════════════════════════════════════════════════${NC}"
        cat "$valgrind_output"
        echo -e "${RED}═══════════════════════════════════════════════════════${NC}"
        failed_tests=$((failed_tests + 1))
    elif [ $exit_code -eq 139 ]; then
        echo -e "${RED}💥 SEGMENTATION FAULT${NC}"
        echo -e "${RED}═══════════════════════════════════════════════════════${NC}"
        cat "$valgrind_output"
        echo -e "${RED}═══════════════════════════════════════════════════════${NC}"
        failed_tests=$((failed_tests + 1))
    elif [ $exit_code -ne 0 ]; then
        if [ "$is_invalid" = "true" ]; then
            # Vérifier quand même s'il y a des erreurs valgrind
            if [ "$has_errors" = "true" ]; then
                echo -e "${YELLOW}⚠️  Map invalide rejetée MAIS avec erreurs valgrind (code: $exit_code)${NC}"
                echo -e "${YELLOW}═══════════════════════════════════════════════════════${NC}"
                cat "$valgrind_output"
                echo -e "${YELLOW}═══════════════════════════════════════════════════════${NC}"
                failed_tests=$((failed_tests + 1))
            else
                echo -e "${GREEN}✅ PASS - Map invalide correctement rejetée (code: $exit_code)${NC}"
                passed_tests=$((passed_tests + 1))
            fi
        else
            echo -e "${RED}❌ FAIL - Code de sortie: $exit_code${NC}"
            if [ "$has_errors" = "true" ]; then
                echo -e "${RED}═══════════════════════════════════════════════════════${NC}"
                cat "$valgrind_output"
                echo -e "${RED}═══════════════════════════════════════════════════════${NC}"
            fi
            failed_tests=$((failed_tests + 1))
        fi
    else
        if [ "$is_invalid" = "true" ]; then
            echo -e "${RED}❌ FAIL - Map invalide acceptée (devrait échouer)${NC}"
            if [ "$has_errors" = "true" ]; then
                echo -e "${RED}═══════════════════════════════════════════════════════${NC}"
                cat "$valgrind_output"
                echo -e "${RED}═══════════════════════════════════════════════════════${NC}"
            fi
            failed_tests=$((failed_tests + 1))
        else
            # Vérifier s'il y a des erreurs valgrind même avec exit code 0
            if [ "$has_errors" = "true" ]; then
                echo -e "${RED}❌ FAIL - Erreurs valgrind détectées${NC}"
                echo -e "${RED}═══════════════════════════════════════════════════════${NC}"
                cat "$valgrind_output"
                echo -e "${RED}═══════════════════════════════════════════════════════${NC}"
                failed_tests=$((failed_tests + 1))
            else
                echo -e "${GREEN}✅ PASS - Aucune erreur, aucune fuite${NC}"
                local error_summary=$(grep "ERROR SUMMARY" "$valgrind_output")
                local heap_summary=$(grep "in use at exit" "$valgrind_output")
                if [ -n "$error_summary" ]; then
                    echo -e "${GREEN}$error_summary${NC}"
                fi
                if [ -n "$heap_summary" ]; then
                    echo -e "${GREEN}$heap_summary${NC}"
                fi
                passed_tests=$((passed_tests + 1))
            fi
        fi
    fi
    
    # Nettoyer
    rm -f "$valgrind_output"
    echo ""
}

# Fonction pour exécuter les tests d'un mode (mandatory ou bonus)
run_tests() {
    local test_mode=$1  # "mandatory" ou "bonus"
    local executable=$2 # "./cub3D" ou "./cub3D_Bonus"
    
    echo -e "\n${CYAN}╔════════════════════════════════════════╗${NC}"
    if [ "$test_mode" = "mandatory" ]; then
        echo -e "${CYAN}║     TESTS MODE MANDATORY               ║${NC}"
    else
        echo -e "${CYAN}║     TESTS MODE BONUS                   ║${NC}"
    fi
    echo -e "${CYAN}╚════════════════════════════════════════╝${NC}\n"
    
    # Tester toutes les maps dans maps/Invalid
    echo -e "${BLUE}═══════════════════════════════════════${NC}"
    echo -e "${BLUE}   Testing Invalid Maps${NC}"
    echo -e "${BLUE}═══════════════════════════════════════${NC}\n"

    if [ -d "maps/Invalid" ]; then
        for map in maps/Invalid/*.cub; do
            if [ -f "$map" ]; then
                test_map "$map" "true" "$executable"
            fi
        done
    fi

    # Tester maps/Bonus/Invalid seulement en mode bonus
    if [ "$test_mode" = "bonus" ] && [ -d "maps/Bonus/Invalid" ]; then
        for map in maps/Bonus/Invalid/*.cub; do
            if [ -f "$map" ]; then
                test_map "$map" "true" "$executable"
            fi
        done
    fi

    # Tester toutes les maps dans maps/Valid
    echo -e "\n${BLUE}═══════════════════════════════════════${NC}"
    echo -e "${BLUE}   Testing Valid Maps${NC}"
    echo -e "${BLUE}═══════════════════════════════════════${NC}\n"

    if [ -d "maps/Valid" ]; then
        for map in maps/Valid/*.cub; do
            if [ -f "$map" ]; then
                test_map "$map" "false" "$executable"
            fi
        done
    fi

    # Tester maps/Bonus seulement en mode bonus
    if [ "$test_mode" = "bonus" ] && [ -d "maps/Bonus" ]; then
        for map in maps/Bonus/*.cub; do
            if [ -f "$map" ]; then
                test_map "$map" "false" "$executable"
            fi
        done
    fi
}

# Exécuter les tests selon le mode choisi
if [ "$MODE" = "mandatory" ] || [ "$MODE" = "both" ]; then
    compile_project "mandatory"
    if [ $? -eq 0 ]; then
        run_tests "mandatory" "./cub3D"
    else
        exit 1
    fi
fi

if [ "$MODE" = "bonus" ] || [ "$MODE" = "both" ]; then
    compile_project "bonus"
    if [ $? -eq 0 ]; then
        run_tests "bonus" "./cub3D_Bonus"
    else
        exit 1
    fi
fi

# Résumé final
echo -e "\n${CYAN}╔════════════════════════════════════════╗${NC}"
echo -e "${CYAN}║       RÉSUMÉ FINAL DES TESTS           ║${NC}"
echo -e "${CYAN}╚════════════════════════════════════════╝${NC}"
echo -e "Total de tests     : ${total_tests}"
echo -e "${GREEN}Tests réussis      : ${passed_tests}${NC}"
echo -e "${RED}Tests échoués      : ${failed_tests}${NC}"
echo -e "${CYAN}════════════════════════════════════════${NC}"

if [ $failed_tests -eq 0 ]; then
    echo -e "${GREEN}🎉 Tous les tests sont passés !${NC}"
    exit 0
else
    echo -e "${RED}⚠️  Certains tests ont échoué.${NC}"
    exit 1
fi
