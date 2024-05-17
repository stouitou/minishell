/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:26:48 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/17 09:28:36 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_infile	*infile_new(t_entry *entry, t_exe *exe, char *content)
{
	t_infile	*new;

	new = (t_infile *)malloc(sizeof(t_infile));
	if (!new)
	{
		token_clear(&(entry->token));
		free_exe(exe);
		exit (EXIT_FAILURE);
	}
	new->content = ft_strdup(content);
	if (!new->content)
	{
		free(new);
		token_clear(&(entry->token));
		free_exe(exe);
		exit (EXIT_FAILURE);
	}
	new->next = NULL;
	return (new);
}
