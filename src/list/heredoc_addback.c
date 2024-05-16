/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_addback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:31:15 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/16 17:34:02 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_addback(t_heredoc **heredoc, t_heredoc *new)
{
	t_heredoc	*cur;
	
	if (!heredoc || !new)
		return ;
	if (!*heredoc)
	{
		*heredoc = new;
		return ;
	}
	cur = *heredoc;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}
