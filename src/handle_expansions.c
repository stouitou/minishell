/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:16:07 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/13 12:34:49 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_expansions(t_entry *entry, char **env)
{
	t_token	*cur;
	t_token	*next;
	t_token	*prev;

	if (!entry->token)
		return ;
	cur = entry->token;
	while (cur)
	{
		prev = cur->prev;
		next = cur->next;
		if (cur->type == WORD && cur->quotes != SIMPLE
			&& (!prev || ft_strcmp(prev->content, "<<") != 0))
			expand_token(entry, cur, env);
		if (!cur->quotes
			&& cur->content && !cur->content[0]
			&& (!prev || (prev && prev->index != cur->index))
			&& (!next || (next && next->index != cur->index)))
			cur->content = NULL;
		cur = next;
	}
}
