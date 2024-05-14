#!/bin/bash

# Chemin vers le fichier all.logs
LOG_FILE="./all.logs"

# Créer un nouveau fichier temporaire pour stocker les lignes uniques
TEMP_FILE=$(mktemp)

# Vérifier si la création du fichier temporaire a réussi
if [ $? -ne 0 ]; then
    echo "Erreur lors de la création du fichier temporaire."
    exit 1
fi

# Parcourir chaque ligne du fichier all.logs
while IFS= read -r line; do
    # Vérifier si la ligne n'est pas déjà présente dans le fichier temporaire
    if ! grep -qxF "$line" "$TEMP_FILE"; then
        # Si la ligne n'est pas en double, l'ajouter au fichier temporaire
        echo "$line" >> "$TEMP_FILE"
    fi
done < "$LOG_FILE"

# Remplacer le fichier all.logs par le fichier temporaire contenant les lignes uniques
mv "$TEMP_FILE" "$LOG_FILE"

echo "Suppression des doublons terminée."
