#!/bin/bash

# Chemin vers le fichier all.logs
LOG_FILE="./all.logs"

# Chemin vers le nouveau fichier de logs filtré
FILTERED_LOG_FILE="./no_heredoc.logs"

# Parcourir chaque ligne du fichier all.logs
while IFS= read -r line; do
    # Vérifier si la ligne contient une redirection here_doc "<<"
    if ! grep -q '<<' <<< "$line"; then
        # Si la ligne ne contient pas de redirection here_doc, l'écrire dans le fichier filtré
        echo "$line" >> "$FILTERED_LOG_FILE"
    fi
done < "$LOG_FILE"

echo "Filtrage des redirections here_doc terminé. Les tests sans redirections here_doc ont été écrits dans $FILTERED_LOG_FILE."
