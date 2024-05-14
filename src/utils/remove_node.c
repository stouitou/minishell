/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:31:15 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/07 17:34:46 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_node(t_token **token, t_token *cur)
{
	t_token	*prev;
	t_token	*next;

	if (!cur)
		return ;
	// ft_printf("cur->content in remove node = %s\n", cur->content);
	prev = cur->prev;
	next = cur->next;
	if (prev)
		prev->next = next;
	else
		*token = next;
	if (next)
		next->prev = prev;
	del_node(&cur);
	// ft_printf("cur in remove node = %p\n", cur);
}
