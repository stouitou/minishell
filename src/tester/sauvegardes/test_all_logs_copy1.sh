#!/bin/bash

# The first line #!/bin/bash is called a shebang line, and it specifies
# the path to the shell interpreter to be used to execute the script.
# In this case, it indicates that the script should be interpreted using
# the Bash shell (/bin/bash).

# Chemin vers le fichier de logs contenant les commandes
LOG_FILE="./src/tester/tests.logs"

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

    echo -e "${BLUE}Command $((++command_count)):${NC} $command"
    if [ "$actual_output" = "$expected_output" ] && [ "$actual_status" = "$expected_status" ]; then
        echo -e "${GREEN}Test passed successfully!${NC}"
        echo "Expected output: <$expected_output>"
        echo "Actual output  : <$actual_output>"
        echo "Expected status: $expected_status"
        echo "Actual status  : $actual_status"
    else
        echo -e "${RED}Test failed!${NC}"
        echo "Expected output: <$expected_output>"
        echo "Actual output  : <$actual_output>"
        echo "Expected status: $expected_status"
        echo "Actual status  : $actual_status"
    fi
    echo
}

# Variable pour compter le nombre de commandes
command_count=0

# Boucle pour lire les commandes depuis le fichier de logs
while IFS= read -r command; do
    # Exécuter la commande dans le programme minishell et enregistrer l'output
    minishell_output=$(./minishell <<< "$command" | tail -n +2)
    minishell_output="${minishell_output#$PROMPT}"
    minishell_status=$?

    # Exécuter la même commande dans le terminal et enregistrer l'output et le statut de retour
    terminal_output=$(eval "$command" 2>&1)
    terminal_status=$?

    # Tronquer le prompt du terminal output
    terminal_output="${terminal_output#$PROMPT}"

    # Comparer l'output et le statut de retour
    compare_output_and_status "$terminal_output" "$terminal_status" "$minishell_output" "$minishell_status" "$command"

done < "$LOG_FILE"
