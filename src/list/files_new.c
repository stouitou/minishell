/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:26:08 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/14 15:51:21 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_files	*files_new(t_entry *entry, t_exe *exe, t_token *token)
{
	t_files	*new;

	new = (t_files *)malloc(sizeof(t_files));
	if (!new)
	{
		token_clear(entry, &(entry->token));
		free_exe(exe);
		exit (EXIT_FAILURE);
	}
	new->content = ft_strdup(token->content);
	if (!new->content)
	{
		free(new);
		token_clear(entry, &(entry->token));
		free_exe(exe);
		exit (EXIT_FAILURE);
	}
	new->category = token->category;
	new->next = NULL;
	return (new);
}
