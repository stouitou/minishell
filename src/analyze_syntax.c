/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:20:00 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/14 11:06:38 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	// if (start[i + 1] == '{')
	// {
	// 	if (!handle_curly_brackets(entry, content + i))
	// 		return (NULL);
	// }

static void handle_curly_brackets(t_entry *entry, char *str)
{
	bool	bracket_1;
	bool	bracket_2;
	int		i;
	int		start;

	bracket_1 = false;
	bracket_2 = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '{')
		{
			bracket_1 = true;
			bracket_2 = false;
			start = i;
		}
		if (bracket_1 && str[i] == '}')
		{
			bracket_2 = true;
			bracket_1 = false;
		}
		i++;
	}
	if (bracket_1 && !bracket_2)
	{
		free_token_before_return(entry, ERR_SYNTAX, str + start, 2);
		return ;
	}
}

static bool	is_exception(t_entry *entry)
{
	t_token *cur;

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
				return ;
			}
	}
	else if (ft_strcmp(cur->content, "newline") != 0)
	{
		if (!cur->next || cur->next->type != WORD)
		{
			free_token_before_return(entry, ERR_SYNTAX, cur->next->content, 2);
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
		if (cur->type == WORD)
			handle_curly_brackets(entry, cur->content);
		if (entry->status)
			return ;
		cur = cur->next;
	}
}
