/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upd_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:44:52 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/06 09:46:06 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	upd_token(t_entry *entry, t_token *token)
{
	t_token	*cur;
	bool	split;

	if (!token)
		return ;
	cur = token;
	split = false;
	while (cur)
	{
		if (!cur->quotes && cur->content && ft_strchr(cur->content, ' '))
		{
			separate_content(entry, cur, cur->next);
			split = true;
		}
		else if (!split && cur->prev && cur->prev->index == cur->index)
		{
			join_contents(entry, cur, cur->prev);
			split = false;
		}
		cur = cur->next;
	}
}
