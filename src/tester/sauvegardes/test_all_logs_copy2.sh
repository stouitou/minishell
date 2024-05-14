#!/bin/bash

# Chemin vers le fichier de logs contenant les commandes
LOG_FILE="./src/tester/tests.logs"
ALL_FILE="./src/tester/all.logs"

# Prompt de minishell
PROMPT="minishell > "

# Couleurs ANSI
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Exécuter make une seule fois
make

# Fonction pour comparer l'output et le statut de retour
compare_output_and_status() {
    expected_output="$1"
    expected_status="$2"
    actual_output="$3"
    actual_status="$4"
    expected_error="$5"
    actual_error="$6"
    command="$7"

    # Supprimer le dernier caractère de nouvelle ligne des sorties réelles
    actual_output="${actual_output%$'\n'}"
    actual_error="${actual_error%$'\n'}"

    echo -e "${BLUE}Command $((++command_count)):${NC} $command"
    if [ "$actual_output" = "$expected_output" ] && [ "$actual_status" = "$expected_status" ] && [ "$actual_error" = "$expected_error" ]; then
        echo -e "${GREEN}Test passed successfully!${NC}"
        echo "Expected output: <$expected_output>"
        echo "Actual output  : <$actual_output>"
        echo "Expected status: $expected_status"
        echo "Actual status  : $actual_status"
        echo "Expected error : <$expected_error>"
        echo "Actual error   : <$actual_error>"
    else
        echo -e "${RED}Test failed!${NC}"
        echo "Expected output: <$expected_output>"
        echo "Actual output  : <$actual_output>"
        echo "Expected status: $expected_status"
        echo "Actual status  : $actual_status"
        echo "Expected error : <$expected_error>"
        echo "Actual error   : <$actual_error>"
    fi
    echo
}

# Variable pour compter le nombre de commandes
command_count=0

# Boucle pour lire les commandes depuis le fichier de logs
while IFS= read -r command; do
    # Exécuter la commande dans le programme minishell et enregistrer l'output
    minishell_output=$(./minishell <<< "$command" 2>&1 | tail -n +2)
    minishell_output="${minishell_output%"$PROMPT"*}"
    minishell_status=$?

    # Ajouter un délai pour permettre au terminal de traiter la commande
    sleep 0.5

    # Exécuter la même commande dans le terminal et enregistrer l'output et le statut de retour
    terminal_output=$(eval "$command" 2>&1)
    terminal_status=$?

    # Tronquer le prompt du terminal output
    terminal_output="${terminal_output#"$PROMPT"}"

    # Comparer l'output et le statut de retour
    compare_output_and_status "$terminal_output" "$terminal_status" "$minishell_output" "$minishell_status" "$terminal_output" "$minishell_output" "$command"

    # Remove the tested command from the tests.logs file
    sed -i '$d' "$ALL_FILE"

done < "$LOG_FILE"
