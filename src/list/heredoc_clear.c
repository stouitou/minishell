/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:40:23 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/16 17:43:24 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_clear(t_heredoc **heredoc)
{
	t_heredoc	*cur;
	t_heredoc	*next;
	
	if (!*heredoc)
		return ;
	cur = *heredoc;
	while (cur)
	{
		next = cur->next;
		free(cur->content);
		free(cur);
		cur = next;
	}
	*heredoc = NULL;
}
