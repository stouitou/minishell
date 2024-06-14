/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_and_exit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:14:02 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/14 15:51:37 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_and_exit(t_entry *entry, char *err, char *str, int status)
{
	ft_fprintf(2, "%s", err);
	if (str)
		ft_fprintf(2, ": %s", str);
	ft_fprintf(2, "\n");
	token_clear(entry, &(entry->token));
	ft_free_str_array(entry->env);
	exit(status);
}

// void	free_token_and_exit(t_token **token, char *err, char *str, int status)
// {
// 	ft_fprintf(2, "%s", err);
// 	if (str)
// 		ft_fprintf(2, ": %s", str);
// 	ft_fprintf(2, "\n");
// 	token_clear(token);
// 	exit(status);
// }
