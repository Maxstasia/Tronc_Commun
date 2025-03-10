# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester(pipex).sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 11:32:55 by mstasiak          #+#    #+#              #
#    Updated: 2025/03/10 14:12:31 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

# Couleurs pour une meilleure lisibilité
GREEN="\033[32m"
RED="\033[31m"
PINK="\033[35m"
RESET="\033[0m"

# Vérification si on teste les bonus
if [ "$1" = "bonus" ]; then
    BONUS=1
    echo "\n${GREEN}Running BONUS tests...${RESET}"
    else
    BONUS=0
fi

# Compilation du programme
if [ "$BONUS" -eq 1 ]; then
    make re_bonus
    else
    make re
fi

echo

# Fichiers de test
echo "Hello, world!" > infile

echo "\n${GREEN}Running basic test...${RESET}"
if [ "$BONUS" -eq 1 ]; then
    ./pipex_bonus infile "cat" "wc -w" outfile
    < infile cat | wc -w > expected
    diff -q outfile expected && echo "${GREEN}✅ Test 1 Passed${RESET}" || echo "${RED}❌ Test 1 Failed${RESET}"
    else
    ./pipex infile "cat" "wc -w" outfile
    < infile cat | wc -w > expected
    diff -q outfile expected && echo "${GREEN}✅ Test 1 Passed${RESET}" || echo "${RED}❌ Test 1 Failed${RESET}"
fi

if [ "$BONUS" -eq 1 ]; then
    echo "\n${GREEN}Running test with non-existent infile...${RESET}"
    ./pipex_bonus nonexistent "cat" "wc -w" outfile 2> error.log
    if grep -q "Error" error.log; then echo "${GREEN}✅ Test 2 Passed${RESET}"; else echo "${RED}❌ Test 2 Failed${RESET}"; fi
    else
    echo "\n${GREEN}Running test with non-existent infile...${RESET}"
    ./pipex nonexistent "cat" "wc -w" outfile 2> error.log
    if grep -q "Error" error.log; then echo "${GREEN}✅ Test 2 Passed${RESET}"; else echo "${RED}❌ Test 2 Failed${RESET}"; fi
fi

echo "\n${GREEN}Running test with invalid command...${RESET}"
if [ "$BONUS" -eq 1 ]; then
    ./pipex_bonus infile "invalidcmd" "wc -w" outfile 2> error.log
    if grep -q "Error" error.log; then echo "${GREEN}✅ Test 3 Passed${RESET}"; else echo "${RED}❌ Test 3 Failed${RESET}"; fi
    else
    ./pipex infile "invalidcmd" "wc -w" outfile 2> error.log
    if grep -q "Error" error.log; then echo "${GREEN}✅ Test 3 Passed${RESET}"; else echo "${RED}❌ Test 3 Failed${RESET}"; fi
fi

echo "\n${GREEN}Running test with permission denied...${RESET}"
touch noaccess
chmod 000 noaccess
if [ "$BONUS" -eq 1 ]; then
    ./pipex_bonus noaccess "cat" "wc -w" outfile 2> error.log
    if grep -q "Error" error.log; then echo "${GREEN}✅ Test 4 Passed${RESET}"; else echo "${RED}❌ Test 4 Failed${RESET}"; fi
    else
    ./pipex noaccess "cat" "wc -w" outfile 2> error.log
    if grep -q "Error" error.log; then echo "${GREEN}✅ Test 4 Passed${RESET}"; else echo "${RED}❌ Test 4 Failed${RESET}"; fi
fi
chmod 644 noaccess # On remet les permissions normales pour éviter les soucis

echo "\n${GREEN}Running test with empty infile...${RESET}"
touch emptyfile
if [ "$BONUS" -eq 1 ]; then
    ./pipex_bonus emptyfile "cat" "wc -w" outfile
    < emptyfile cat | wc -w > expected
    diff -q outfile expected && echo "${GREEN}✅ Test 5 Passed${RESET}" || echo "${RED}❌ Test 5 Failed${RESET}"
    else
    ./pipex emptyfile "cat" "wc -w" outfile
    < emptyfile cat | wc -w > expected
    diff -q outfile expected && echo "${GREEN}✅ Test 5 Passed${RESET}" || echo "${RED}❌ Test 5 Failed${RESET}"
fi

echo "\n${GREEN}Running test with one word in infile...${RESET}"
echo "42" > oneword
if [ "$BONUS" -eq 1 ]; then
    ./pipex_bonus oneword "cat" "wc -w" outfile
    < oneword cat | wc -w > expected
    diff -q outfile expected && echo "${GREEN}✅ Test 6 Passed${RESET}" || echo "${RED}❌ Test 6 Failed${RESET}"
    else
    ./pipex oneword "cat" "wc -w" outfile
    < oneword cat | wc -w > expected
    diff -q outfile expected && echo "${GREEN}✅ Test 6 Passed${RESET}" || echo "${RED}❌ Test 6 Failed${RESET}"
fi

echo "\n${GREEN}Running test with a large file...${RESET}"
base64 /dev/urandom | head -c 65000 > largefile
if [ "$BONUS" -eq 1 ]; then
    ./pipex_bonus largefile "cat" "wc -c" outfile
    < largefile cat | wc -c > expected
    diff -q outfile expected && echo "${GREEN}✅ Test 7 Passed${RESET}" || echo "${RED}❌ Test 7 Failed${RESET}"
    else
    ./pipex largefile "cat" "wc -c" outfile
    < largefile cat | wc -c > expected
    diff -q outfile expected && echo "${GREEN}✅ Test 7 Passed${RESET}" || echo "${RED}❌ Test 7 Failed${RESET}"
fi

echo "\n${GREEN}Running test with reversed commands...${RESET}"
if [ "$BONUS" -eq 1 ]; then
    ./pipex_bonus infile "wc -w" "cat" outfile
    < infile wc -w | cat > expected
    diff -q outfile expected && echo "${GREEN}✅ Test 8 Passed${RESET}" || echo "${RED}❌ Test 8 Failed${RESET}"
    else
    ./pipex infile "wc -w" "cat" outfile
    < infile wc -w | cat > expected
    diff -q outfile expected && echo "${GREEN}✅ Test 8 Passed${RESET}" || echo "${RED}❌ Test 8 Failed${RESET}"
fi

echo "\n${GREEN}Running test with incorrect arguments...${RESET}"
if [ "$BONUS" -eq 1 ]; then
    ./pipex_bonus infile "cat" "wc -w" 2> error.log
    if grep -q "Error" error.log; then echo "${GREEN}✅ Test 9 Passed${RESET}"; else echo "${RED}❌ Test 9 Failed${RESET}"; fi
    else
	./pipex infile "cat" "wc -w" 2> error.log
    if grep -q "Error" error.log; then echo "${GREEN}✅ Test 9 Passed${RESET}"; else echo "${RED}❌ Test 9 Failed${RESET}"; fi
fi

echo "\n${GREEN}Running test with special characters...${RESET}"
echo "Hello | grep Hello" > specialchars
if [ "$BONUS" -eq 1 ]; then
    ./pipex_bonus specialchars "grep Hello" "wc -l" outfile
    < specialchars grep Hello | wc -l > expected
    diff -q outfile expected && echo "${GREEN}✅ Test 10 Passed${RESET}" || echo "${RED}❌ Test 10 Failed${RESET}"
    else
    ./pipex specialchars "grep Hello" "wc -l" outfile
    < specialchars grep Hello | wc -l > expected
    diff -q outfile expected && echo "${GREEN}✅ Test 10 Passed${RESET}" || echo "${RED}❌ Test 10 Failed${RESET}"
fi

# Tests BONUS (si activé)
if [ "$BONUS" -eq 1 ]; then
    echo "\n${PINK}Running multiple pipes test...${RESET}"
    ./pipex_bonus infile "cat" "grep Hello" "wc -l" outfile
    < infile cat | grep Hello | wc -l > expected
    diff -q outfile expected && echo "${GREEN}✅ Test 1 Bonus Passed${RESET}" || echo "${RED}❌ Test 1 Bonus Passed${RESET}"
fi

if [ $BONUS -eq 1 ]; then
    echo "\n${PINK}Running multiple pipes test...${RESET}"
    echo "42 is amazing" > infile
    ./pipex_bonus infile "cat" "tr a-z A-Z" "rev" "wc -c" outfile
    < infile cat | tr a-z A-Z | rev | wc -c > expected
    diff -q outfile expected && echo "${GREEN}✅ Test 2 Bonus Passed${RESET}" || echo "${RED}❌ Test 2 Bonus Failed${RESET}"
fi

if [ $BONUS -eq 1 ]; then
    echo "\n${PINK}Running here_doc test...${RESET}"
    echo "hello\nworld\nSTOP" > heredoc_input
    ./pipex_bonus here_doc STOP "grep hello" "wc -l" heredoc_output <<EOF
hello
world
STOP
EOF
    echo "hello\nworld\nSTOP" | grep hello | wc -l > expected
    diff -q heredoc_output expected && echo "${GREEN}✅ Test 3 Bonus Passed${RESET}" || echo "${RED}❌ Test 3 Bonus Failed${RESET}"
fi

echo
echo

# Nettoyage
rm -f infile outfile expected error.log noaccess emptyfile oneword largefile specialchars heredoc_input heredoc_output STOP
make fclean

echo "\n${GREEN}All tests completed!${RESET}"
