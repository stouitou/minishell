/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:48:55 by poriou            #+#    #+#             */
/*   Updated: 2024/06/06 09:49:39 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_all_logs(const char *command)
{
	FILE	*file_all;
	char	*log_path_all = "./src/tester/all.logs";

	// Open "all.logs" file in append mode
	if (!command)
		return ;
	file_all = fopen(log_path_all, "a+");
	if (file_all == NULL)
	{
		// printf("Problem: could not open all logs file.\n");
		return ;
	}
	// Write the command to "all.logs"
	fprintf(file_all, "%s\n", command);
	// Close the "all.logs" file
	fclose(file_all);
}

/*
*	Creer un fichier de journalisation des tests.
*
*	Le mode "a" de fopen est l'equivalent de :
*	O_RDWR | O_CREAT | O_APPEND
*
*	O_RDWR : Indique que le fichier est ouvert en lecture et en écriture.
*	O_CREAT : Indique que le fichier sera créé s'il n'existe pas.
*	O_APPEND : Indique que les données seront ajoutées à la fin du fichier lors
*	de l'écriture, plutôt que de les écraser.
*/
void	log_tests(const char *command)
{
	FILE	*file;
	char	*log_path;
	char	buffer[256];
	int		found;

	add_to_all_logs(command);
	found = 0;
	log_path = "./src/tester/tests.logs";
	file = fopen(log_path, "a+");
	if (file == NULL)
	{
		// printf("Problem: could not open tester log file.\n");
		return ;
	}
	// Positionner le curseur au début du fichier
	fseek(file, 0, SEEK_SET);
	/*
		Rechercher la commande dans le fichier avec
		FGETS
		char *fgets(char *str, int num, FILE *stream);

		La fonction fgets lit ligne par ligne à partir du flux de fichiers spécifié.
		Elle lit les caractères jusqu'à ce qu'elle atteigne la fin de ligne '\n',
		le nombre maximum de caractères spécifié par num ou la fin de fichier.
		Une fois qu'elle a lu une ligne complète, elle stocke les caractères
		dans le tableau str, y compris le caractère de fin de ligne '\n',
		et ajoute également un caractère nul '\0' à la fin pour terminer la chaîne correctement.
	*/
	while (fgets(buffer, sizeof(buffer), file) != NULL)
	{
		/*
			Supprimer le saut de ligne à la fin de la commande lue depuis le fichier
			STRCSPN
			size_t strcspn(const char *str, const char *reject);

			La fonction est utilisée pour trouver la longueur du préfixe d'une chaîne de caractères
			qui ne contient aucun des caractères spécifiés.
		*/
		buffer[strcspn(buffer, "\n")] = '\0';
		// Comparer la commande actuelle avec la nouvelle commande
		if (strcmp(buffer, command) == 0)
		{
			found = 1;
			break ;
		}
	}
	if (!found)
		fprintf(file, "%s\n", command);
	fclose(file);
}
