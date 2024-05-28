/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:31:17 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 09:31:38 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_operator(t_token **token)
{
	t_token	*cur;
	t_token	*next;

	if (!token || !*token)
		return ;
	cur = *token;
	while (cur)
	{
		next = cur->next;
		if (cur->type == OPERATOR)
			remove_node(token, cur);
		cur = next;
	}
}
