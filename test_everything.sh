#!/bin/bash

LOG_FILE="./src/tester/tests.logs"
ALL_FILE="./src/tester/all.logs"
STATUS_LOGS_FILE="./src/tester/status.logs"

PROMPT="minishell > "

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m'

make

calculate_similarity() {
    expected="$1"
    actual="$2"

    # Tokenize the strings into words
    expected_words=$(echo "$expected" | tr -s '[:space:]' '\n' | sort -u)
    actual_words=$(echo "$actual" | tr -s '[:space:]' '\n' | sort -u)

    # Count the number of common words
    common_words=$(comm -12 <(echo "$expected_words") <(echo "$actual_words") | wc -l)

    # Calculate the similarity as the ratio of common words to the total number of words
    total_expected_words=$(echo "$expected_words" | wc -l)
    similarity=$((common_words * 100 / total_expected_words))
    echo "$similarity"
}

compare_output_and_status() {
    expected_output="$1"
    expected_status="$2"
    actual_output="$3"
    actual_status="$4"
    command="$5"
    command_count="$6"

    # Compter le nombre de lignes dans l'output attendu et réel
    expected_lines=$(echo "$expected_output" | wc -l)
    actual_lines=$(echo -n "$actual_output" | wc -l)

    # Supprimer le dernier caractère de nouvelle ligne des sorties réelles
    actual_output="${actual_output%$'\n'}"

    # Retirer les occurrences de "./test_last_log.sh: " des expected outputs
    expected_output="${expected_output//.\/test_all_logs.sh: /}"

    # Calculer le score de similarité entre l'output réel et l'output attendu
    similarity=$(calculate_similarity "$actual_output" "$expected_output")

    # Définir le seuil de similarité requis pour réussir le test (80% dans cet exemple)
    threshold=40

    error_found=0

    if [ "$actual_output" = "$expected_output" ] && [ "$actual_lines" = "$expected_lines" ] && [ "$actual_status" = "$expected_status" ]; then
        echo -n -e "${BLUE}${command_count}:${GREEN}OMG ($similarity%)${NC}"
    elif [ "$similarity" -ge "$threshold" ] && [ "$actual_status" = "$expected_status" ]; then
        echo -n -e "${BLUE}${command_count}:${GREEN}OK ($similarity%)${NC}"
    elif [ "$similarity" -ge "$threshold" ]; then
        error_found=1
        echo -n -e "${BLUE}${command_count}:${YELLOW}STATUS ($similarity%)${NC} (returns ${actual_status} when ${expected_status} expected): ${command}"
    elif [ "$similarity" = 0 ]; then
        error_found=1
        echo -n -e "${BLUE}${command_count}:${RED}WHAT?! ($similarity%)${NC}: ${command}"
    else
        error_found=1
        echo -n -e "${BLUE}${command_count}:${RED}KO ($similarity%)${NC}: ${command}"
    fi
    if [ "$error_found" -gt 0 ]; then
        echo
    elif [ $((command_count % 5)) -eq 0 ] && [ "$error_found" -eq 0 ]; then
        echo
    else
        echo -n "   "
    fi
}

# Variable pour compter le nombre de commandes
command_count=0

# Boucle pour lire les commandes depuis le fichier de logs
while IFS= read -r command; do
    minishell_output=$(./minishell <<< "$command" 2>&1 | tail -n +2)
    minishell_output="${minishell_output%"$PROMPT"*}"
    minishell_status=$(<"$STATUS_LOGS_FILE")

    # Ajouter un délai pour permettre au terminal de traiter la commande
    sleep 0.2

    # Exécuter la même commande dans le terminal et enregistrer l'output et le statut de retour
    terminal_output=$(eval "$command" 2>&1)
    terminal_status=$?

    # Tronquer le prompt du terminal output
    terminal_output="${terminal_output#"$PROMPT"}"

    ((command_count++))

    # Comparer l'output et le statut de retour
    compare_output_and_status "$terminal_output" "$terminal_status" "$minishell_output" "$minishell_status" "$command" "$command_count"

    # Remove the tested command from the tests.logs file
    sed -i '$d' "$ALL_FILE"

done < "$ALL_FILE"
