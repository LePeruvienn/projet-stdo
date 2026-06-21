#!/bin/bash

#            USE -h FOR HELP !
#            USE -h FOR HELP !
#            USE -h FOR HELP !
#            USE -h FOR HELP !
#            USE -h FOR HELP !
#            USE -h FOR HELP !

######################################
#
#         LANCEUR DE TESTS
# 
# $ run_test              |->  Lance tout les tests
# $ run_test test1 test2  |->  Lance tout les tests passer en paramêtre
# $ run_test [ args ] -X  |->  L'option `-X` permet d'activer l'afficahge du stdout des tests lancer
#
######################################

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)
BIN_DIR="$SCRIPT_DIR/../bin"

STDOUT_ON=0
TEST_FILES=()

file_amount=0
test_amount=0
ko_amount=0

run_test() {

	local test_file=$1
	local test_name=$(basename "$1")

	if [ -x "$test_file" ]; then

		if [ "$STDOUT_ON" -eq 1 ]; then
			echo 
			echo "[ $test_name ] : Running ... "
			"$test_file"
		else
			"$test_file" &> /dev/null
		fi

		local status=$?

		echo -n "[ $test_name ] : "

		test_amount=$((test_amount + 1))

		if [ "$status" -eq 0 ]; then
			echo  "OK ! with code $status"
		else
			echo  "FAILED ! with code $status"
			ko_amount=$((ko_amount + 1))
		fi

	else
		echo "[SKIP]: $test_name (not executable or not found)"
	fi
}

for arg in "$@"; do
	case "$arg" in
		-X)
			STDOUT_ON=1
			;;
		-h|--help)
			echo "Usage: $0 [-X] [tests...] :"
			echo "- run_test              :  Lance tout les tests"
			echo "- run_test test1 test2  :  Lance tout les tests passer en paramêtre"
			echo "- run_test [ ... ]  -X  :  L'option -X permet d'activer l'afficahge du stdout des tests lancer"
			exit 0
			;;
		-*)
			echo "Option inconnue : $arg"
			exit 1
			;;
		*)
			TEST_FILES+=("$BIN_DIR/$arg.tst")	
			file_amount=$((file_amount + 1))
			;;
	esac
done

echo
echo "Running tests ..."
echo

if [ "$file_amount" -eq 0 ]; then
	shopt -s nullglob
	for f in "$BIN_DIR"/*.tst; do
		run_test "$f"
	done

else
	for f in "${TEST_FILES[@]}"; do
		run_test "$f"
	done
fi


echo
echo "Run $test_amount tests, $ko_amount Failed."

if [ "$test_amount" -ge 1 ]; then

	if [ "$ko_amount" -eq 0 ]; then
		echo "- Juste le GOAT en fait B)"
	elif [ "$ko_amount" -eq "$test_amount" ]; then
		echo "- Bro ... tu troll la :("
	fi

fi

