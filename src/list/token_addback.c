/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_addback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:09:12 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/26 16:05:42 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_addback(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (!token || !new)
		return ;
	if (!*token)
	{
		*token = new;
		return ;
	}
	tmp = *token;
	new->prev = tmp->head;
	while (tmp->next)
	{
		tmp->head = new;
		tmp = tmp->next;
	}
	tmp->head = new;
	tmp->next = new;
}
