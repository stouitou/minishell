/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poriou <poriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:48:55 by poriou            #+#    #+#             */
/*   Updated: 2024/05/28 11:42:37 by poriou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	log_status(int status)
{
	FILE	*file;
	char	*log_path;

	log_path = "./src/tester/status.logs";
	file = fopen(log_path, "w+");
	if (file == NULL)
	{
		// printf("Problem: could not open status.logs file.\n");
		return ;
	}
	fprintf(file, "%d", status);
	fclose(file);
}
