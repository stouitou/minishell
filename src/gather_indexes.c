/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gather_indexes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:44:52 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 11:31:17 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	join_contents(t_entry *entry, t_token *cur, t_token *prev)
{
	char	*new;

	if (!cur || (!cur->content && !prev->content))
		return ;
	new = ft_strjoin(prev->content, cur->content);
	if (!new)
		free_token_and_exit(entry, ERR_MALLOC, cur->content, EXIT_FAILURE);
	free(prev->content);
	prev->content = NULL;
	cur->content = new;
	if (prev->quotes && !cur->quotes)
		cur->quotes = prev->quotes;
}

void	gather_indexes(t_entry *entry, t_token *cur)
{
	if (!cur)
		return ;
	while (cur)
	{
		if (cur->prev && cur->prev->index == cur->index)
			join_contents(entry, cur, cur->prev);
		cur = cur->next;
	}
}
