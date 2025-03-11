#!/bin/bash
count=0
rm -rf output
mkdir output
ls -la > infile
valgrind >/dev/null 2>&1
val=$?

echo '================================================================'
echo '                     Norminette check'
echo '================================================================'
norminette ../ | grep "Error"
ret=$?
if [[ $ret -eq 1 ]]; then
	echo "$(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "$(tput setaf 1)[KO]$(tput sgr 0)"
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '          Test '$count' >> Forbidden function check'
echo '================================================================'
if [ ! -f fn_allowed ]; then
    echo "Erreur : fichier fn_allowed manquant."
    exit 1
fi
if [[ $(uname) = "Linux" ]]; then
	echo "Linux"
	nm -un pipex_bonus | grep -v w | grep -v __ | rev | cut -d "@" -f3- | rev | cut -c20- > fn_used
else
	echo "MacOS"
	nm -un pipex_bonus | grep -v __ | cut -c2- > fn_used  # macOS
fi
touch check
cat fn_used | while read fn
do
    grep $fn fn_allowed >> check
done
diff check fn_used > diff
ret=$?
unlink check
if [[ $ret -eq 0 ]]; then
	echo "$(tput setaf 2)[OK]$(tput sgr 0)"
	unlink diff
else
	cat diff | grep '>' | cut -c3- | while read fn
	do
		echo $fn
	done
	unlink diff
	echo "$(tput setaf 1)[KO]$(tput sgr 0)"
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '             Test' $count ">> Check the executable"
echo '                Executable name is pipex_bonus'
echo '================================================================'
if [ ! -f "pipex_bonus" ]; then
	echo "$(tput setaf 1)[KO]$(tput sgr 0)"
	echo
	exit 0
else
	echo "$(tput setaf 2)[OK]$(tput sgr 0)"
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '        Test' $count ">> Invalid number of arguments"
echo '                    ./pipex_bonus infile'
echo '================================================================'
echo "<"; ./pipex_bonus infile
if [[ $val != 127 ]]; then
	echo
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus infile >/dev/null 2>&1
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '        Test' $count ">> Invalid number of arguments"
echo ' ./pipex_bonus infile "cat -e" "grep $" "wc -l" output/outfile'${count}''
echo '================================================================'
echo "<"; ./pipex_bonus infile "cat -e" "grep $" "wc -l" "output/outfile${count}"
echo
if [ ! -f "output/outfile${count}" ]; then
    echo "$(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "$(tput setaf 1)[KO]$(tput sgr 0) - Compile bonus separately!"
fi
if [[ $val != 127 ]]; then
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus infile "cat -e" "grep $" "wc -l" output/valgrind >/dev/null 2>&1
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '                Test' $count ">> Invalid infile"
echo '     ./pipex_bonus file1 "cat" "grep x" output/outfile'${count}''
echo '================================================================'
echo "<"; ./pipex_bonus file1 "cat" "grep x" "output/outfile${count}"
exit=$?
echo
echo ">"; < file1 cat | grep x > "output/outfile${count}-orig"
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "<" $exit
	echo ">" $exit_orig
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi
if [[ $val != 127 ]]; then
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus file1 "cat" "grep x" output/valgrind >/dev/null 2>&1
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '              Test' $count ">> Infile bad permission"
echo '       ./pipex_bonus infile "cat" "cat -e" output/outfile'${count}''
echo '================================================================'
chmod 000 infile
echo "<"; ./pipex_bonus infile "cat" "cat -e" "output/outfile${count}"
exit=$?
echo
echo ">"; < infile cat | cat -e > "output/outfile${count}-orig"
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "<" $exit
	echo ">" $exit_orig
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi
if [[ $val != 127 ]]; then
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus infile "cat" "cat -e" output/valgrind >/dev/null 2>&1
	chmod 777 infile
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
chmod 777 infile
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '              Test' $count ">> Outfile bad permission"
echo '    ./pipex_bonus infile "grep pipex_bonus" "wc -lw" output/outfile'${count}''
echo '================================================================'
touch "output/outfile${count}"
chmod 000 "output/outfile${count}"
echo "<"; ./pipex_bonus infile "grep pipex_bonus" "wc -lw" "output/outfile${count}"
exit=$?
echo
touch "output/outfile${count}-orig"
chmod 000 "output/outfile${count}-orig"
echo ">"; < infile grep pipex_bonus | wc -lw > "output/outfile${count}-orig"
exit_orig=$?
chmod 777 "output/outfile${count}"
chmod 777 "output/outfile${count}-orig"
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "<" $exit
	echo ">" $exit_orig
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi
if [ -f "output/valgrind" ]; then
	chmod 000 "output/valgrind"
fi
if [[ $val != 127 ]]; then
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus infile "grep pipex_bonus" "wc -lw" output/valgrind >/dev/null 2>&1
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
if [ -f "output/valgrind" ]; then
	chmod 777 "output/valgrind"
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '                Test' $count ">> Invalid command 1"
echo '      ./pipex_bonus infile "catzado" "wc -w" output/outfile'${count}''
echo '================================================================'
echo "<"; ./pipex_bonus infile "catzado" "wc -w" "output/outfile${count}"
exit=$?
echo
echo ">"; < infile catzado | wc -w > "output/outfile${count}-orig"
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "<" $exit
	echo ">" $exit_orig
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi
if [[ $val != 127 ]]; then
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus infile "catzado" "wc -w" output/valgrind >/dev/null 2>&1
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '                Test' $count ">> Invalid command 2"
echo '   ./pipex_bonus infile "cat" "trzero a b" output/outfile'${count}''
echo '================================================================'
echo "<"; ./pipex_bonus infile "cat" "trzero a b" "output/outfile${count}"
exit=$?
echo
echo ">"; < infile cat | trzero a b > "output/outfile${count}-orig"
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "<" $exit
	echo ">" $exit_orig
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi
if [[ $val != 127 ]]; then
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus infile "cat" "trzero a b" output/valgrind >/dev/null 2>&1
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '               Test' $count ">> Both invalid commands"
echo '       ./pipex_bonus infile "ls-l" "grepzao x" output/outfile'${count}' '
echo '================================================================'
echo "<"; ./pipex_bonus infile "ls-l" "grepzao x" "output/outfile${count}"
exit=$?
echo
echo ">"; < infile ls-l | grepzao x > "output/outfile${count}-orig"
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "<" $exit
	echo ">" $exit_orig
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi
if [[ $val != 127 ]]; then
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus infile "ls-l" "grepzao x" output/valgrind >/dev/null 2>&1
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '                Test' $count ">> Valid commands"
echo '     ./pipex_bonus infile "grep d" "cat -e" output/outfile'${count}''
echo '================================================================'
echo "<"; ./pipex_bonus infile "grep d" "cat -e" "output/outfile${count}"
exit=$?
echo
echo ">"; < infile grep d | cat -e > "output/outfile${count}-orig"
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi
if [[ $val != 127 ]]; then
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus infile "grep d" "cat -e" output/valgrind >/dev/null 2>&1
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '                Test' $count ">> Valid commands"
echo './pipex_bonus /dev/urandom "head -n 10" "wc -l" output/outfile'${count}''
echo '================================================================'
echo "<"; ./pipex_bonus /dev/urandom "head -n 10" "wc -l" "output/outfile${count}"
exit=$?
echo
echo ">"; <  /dev/urandom head -n 10 | wc -l  > "output/outfile${count}-orig"
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "<" $exit
	echo ">" $exit_orig
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi
if [[ $val != 127 ]]; then
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus /dev/urandom "head -n 10" "wc -l" output/valgrind >/dev/null 2>&1
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '                Test' $count ">> Valid commands"
echo '  ./pipex_bonus infile "cat" "tr [a-z] [A-Z]" output/outfile'${count}''
echo '================================================================'
echo "<"; ./pipex_bonus infile "cat" "tr [a-z] [A-Z]" "output/outfile${count}"
exit=$?
echo
echo ">"; < infile cat | tr [a-z] [A-Z] > "output/outfile${count}-orig"
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "<" $exit
	echo ">" $exit_orig
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi
if [[ $val != 127 ]]; then
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus infile "cat" "tr [a-z] [A-Z]" output/valgrind >/dev/null 2>&1
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
sleep 1

echo
echo '~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'
echo '                   >>>>>> Extra Tests <<<<<<'
echo '             Kudos if you handled these situations'
echo '~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'

echo
count=$((count+1))
echo '================================================================'
echo '                Test' $count ">> Valid commands"
echo ' ./pipex_bonus infile "grep pipex_bonus" "tr x '\' \''" output/outfile'${count}''
echo '================================================================'
echo "<"; ./pipex_bonus infile "grep pipex_bonus" "tr x ' '" "output/outfile${count}"
exit=$?
echo
echo ">"; <  infile grep pipex_bonus | tr x ' ' > "output/outfile${count}-orig"
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "<" $exit
	echo ">" $exit_orig
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi
if [[ $val != 127 ]]; then
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus infile "grep pipex_bonus" "tr x ' '" output/valgrind >/dev/null 2>&1
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '                Test' $count ">> Valid commands"
echo " ./pipex_bonus infile \"echo 'Hi 42'\" \"tr 42 FT\" output/outfile${count}"
echo '================================================================'
echo "<"; ./pipex_bonus infile "echo 'Hi 42'" "tr 42 FT" "output/outfile${count}"
exit=$?
echo
echo ">"; <  infile echo 'Hi 42' | tr 42 FT > "output/outfile${count}-orig"
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "<" $exit
	echo ">" $exit_orig
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi
if [[ $val != 127 ]]; then
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus infile "echo 'Hi 42'" "tr 42 FT" output/valgrind >/dev/null 2>&1
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '                Test' $count ">> Valid commands"
echo " ./pipex_bonus infile \"tr ex ' X'\" \"tr pi 'P '\" output/outfile${count}"
echo '================================================================'
echo "<"; ./pipex_bonus infile "tr ex ' X'" "tr pi 'P '" "output/outfile${count}"
exit=$?
echo
echo ">"; <  infile tr ex ' X' | tr pi 'P ' > "output/outfile${count}-orig"
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "<" $exit
	echo ">" $exit_orig
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi
if [[ $val != 127 ]]; then
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus infile "tr ex ' X'" "tr pi 'P '" output/valgrind >/dev/null 2>&1
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
echo

trap 'chmod 777 infile; chmod 777 output/outfile*' EXIT
$(rm -f output/valgrind)
make fclean
