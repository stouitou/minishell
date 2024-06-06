/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_contents.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:45:50 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/06 09:46:10 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_contents(t_entry *entry, t_token *cur, t_token *prev)
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
