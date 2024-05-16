/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:26:08 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/16 14:11:38 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_outfile	*outfile_new(t_entry *entry, t_exe *exe, t_token *token)
{
	t_outfile	*new;

	new = (t_outfile *)malloc(sizeof(t_outfile));
	if (!new)
	{
		token_clear(&(entry->token));
		free_exe(exe);
		exit (EXIT_FAILURE);
	}
	new->content = ft_strdup(token->content);
	if (!new->content)
	{
		free(new);
		token_clear(&(entry->token));
		free_exe(exe);
		exit (EXIT_FAILURE);
	}
	if (token->category == APP_OUTFILE)
		new->append = true;
	else
		new->append = false;
	new->next = NULL;
	return (new);
}
