/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upd_token_heads_and_indexes.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:16:52 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/03 16:24:09 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	upd_token_heads_and_indexes(t_token *token)
{
	t_token	*head;
	int		i;

	if (!token)
		return ;
	i = 0;
	while (token->next)
	{
		token->index = i;
		token = token->next;
		i++;
	}
	token->index = i;
	head = token;
	while (token)
	{
		token->head = head;
		token = token->prev;
	}
}
