#!/bin/bash

# Chemin vers le fichier de logs contenant les commandes
LOG_FILE="./src/tester/tests.logs"
ALL_FILE="./src/tester/all.logs"
NO_HEREDOC_FILE="./src/tester/no_heredoc.logs"

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
    command="$5"

    # Supprimer le dernier caractère de nouvelle ligne des sorties réelles
    actual_output="${actual_output%$'\n'}"

    # Retirer les occurrences de "./test_last_log.sh: " des expected outputs
    expected_output="${expected_output//.\/test_all_logs.sh: /}"

    echo
    if [ "$actual_output" = "$expected_output" ] && [ "$actual_status" = "$expected_status" ]; then
        echo -e "${GREEN}OK${NC} ${BLUE}Test $((++command_count)):${NC} $command"
        echo "Expected : $expected_output"
        echo "Actual   : $actual_output"
        echo -e "Status   : ${GREEN}$actual_status${NC} (when expected : $expected_status)"
    else
        echo -e "${RED}KO${NC} ${BLUE}Test $((++command_count)):${NC} $command"
        echo "Expected : $expected_output"
        echo "Actual   : $actual_output"
        echo -e "Status   : ${RED}$actual_status${NC} (when expected : $expected_status)"
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
    compare_output_and_status "$terminal_output" "$terminal_status" "$minishell_output" "$minishell_status" "$command"

    # Remove the tested command from the tests.logs file
    sed -i '$d' "$ALL_FILE"

done < "$NO_HEREDOC_FILE"
