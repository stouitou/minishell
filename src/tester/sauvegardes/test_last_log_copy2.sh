#!/bin/bash

# Chemin vers le fichier de logs contenant toutes les commandes
ALL_LOGS_FILE="./src/tester/all.logs"

# Chemin vers le fichier contenant la dernière commande testée
LAST_TESTED_LOGS_FILE="./src/tester/last_tested.logs"

# Chemin vers le fichier contenant le status de la dernière commande testée
STATUS_LOGS_FILE="./src/tester/status.logs"

# Prompt de minishell
PROMPT="minishell > "

# Couleurs ANSI
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Exécuter make une seule fois
# make

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
    expected_output="${expected_output//.\/test_last_log.sh: /}"

    echo
    if [ "$actual_output" = "$expected_output" ] && [ "$actual_status" = "$expected_status" ]; then
        echo -e "${GREEN}OK${NC} ${BLUE}Test  :${NC} $command"
        echo "---------------------------------"
        echo -e "${CYAN}Expected${NC} : $expected_output"
        echo -e "${CYAN}Actual${NC}   : $actual_output"
        echo -e "${CYAN}Status${NC}   : ${GREEN}$actual_status${NC} (when expected : $expected_status)"
    else
        echo "---------------------------------"
        echo -e "${RED}KO${NC} ${BLUE}Test  :${NC} $command"
        echo -e "${CYAN}Expected${NC} : $expected_output"
        echo -e "${CYAN}Actual${NC}   : $actual_output"
        echo -e "${CYAN}Status${NC}   : ${RED}$actual_status${NC} (when expected : $expected_status)"
    fi
    echo
}

# Lire la dernière commande depuis le fichier de logs
last_command=$(tail -n 1 "$LAST_TESTED_LOGS_FILE")

# -----------------------------
# Exécuter la commande dans le programme minishell et enregistrer l'output
minishell_output=$(./minishell <<< "$last_command" 2>&1 | tail -n +2)
minishell_output="${minishell_output%"$PROMPT"*}"
minishell_status=$?
# -----------------------------

# # Run the minishell command and capture the output and exit status
# minishell_output_and_status=$(./minishell <<< "$last_command" 2>&1)
# minishell_status=${PIPESTATUS[0]} # Get the exit status of the minishell command

# # Remove the first line from the output
# minishell_output=$(echo "$minishell_output_and_status" | tail -n +2)

# # Remove the prompt from the output
# minishell_output="${minishell_output%"$PROMPT"*}"
# -----------------------------
# # Create a temporary file
# tempfile=$(mktemp)

# # Run the minishell command and redirect the output to the temporary file
# ./minishell <<< "$last_command" 2>&1 | tee $tempfile

# # Get the exit status of the minishell command
# minishell_status=$?

# # Read the output from the temporary file
# minishell_output=$(cat $tempfile)

# # Remove the first line from the output
# minishell_output=$(echo "$minishell_output" | tail -n +2)

# # Remove the prompt from the output
# minishell_output="${minishell_output%"$PROMPT"*}"

# # Delete the temporary file
# rm $tempfile
# -----------------------------

# Ajouter un délai pour permettre au terminal de traiter la commande
sleep 0.5

# Exécuter la même commande dans le terminal et enregistrer l'output et le statut de retour
terminal_output=$(eval "$last_command" 2>&1)
terminal_status=$?

# Tronquer le prompt du terminal output
terminal_output="${terminal_output#"$PROMPT"}"

# Comparer l'output et le statut de retour
compare_output_and_status "$terminal_output" "$terminal_status" "$minishell_output" "$minishell_status" "$last_command"

# Ajouter un délai pour permettre au terminal de traiter la commande
sleep 0.5

