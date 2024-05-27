/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:20:00 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/27 16:31:57 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_exception(t_entry *entry)
{
	t_token	*cur;

	if (!entry)
		return (false);
	cur = entry->token;
	if (ft_strcmp(cur->content, ":") == 0)
	{
		token_clear(&(entry->token));
		return (true);
	}
	if ((ft_strcmp(cur->content, "!") == 0 || ft_strcmp(cur->content, "?") == 0)
		&& (cur->next && cur->next->index != cur->index))
	{
		remove_node(&(entry->token), cur);
		entry->status = 1;
		return (true);
	}
	return (false);
}

static void	analyze_operator(t_token *cur, t_entry *entry)
{
	if (ft_strncmp(cur->content, "|", 1) == 0)
	{
		if (!cur->prev
			|| (cur->next && ft_strncmp(cur->next->content, "|", 1) == 0))
		{
			free_token_before_return(entry, ERR_SYNTAX, cur->content, 2);
			token_clear(&(cur->next));
			cur->next = NULL;
			return ;
		}
	}
	else if (ft_strcmp(cur->content, "newline") != 0)
	{
		if (!cur->next || cur->next->type != WORD)
		{
			free_token_before_return(entry, ERR_SYNTAX, cur->next->content, 2);
			token_clear(&(cur->next));
			cur->next = NULL;
			return ;
		}
	}
}

void	analyze_syntax(t_entry *entry)
{
	t_token	*cur;

	if (!entry->token)
		return ;
	if (is_exception(entry))
		return ;
	cur = entry->token;
	while (cur)
	{
		if (cur->type == OPERATOR)
			analyze_operator(cur, entry);
		if (entry->status)
			return ;
		cur = cur->next;
	}
}
