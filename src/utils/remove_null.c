/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_null.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:29:23 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 09:29:44 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_null(t_token **token)
{
	t_token	*cur;
	t_token	*next;

	if (!token || !*token)
		return ;
	cur = *token;
	while (cur)
	{
		next = cur->next;
		if (cur->category != CMD && cur->content == NULL)
			remove_node(token, cur);
		cur = next;
	}
}
