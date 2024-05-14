/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:30:54 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/14 17:14:55 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_new(int *ib)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = NULL;
	new->index = ib[0];
	new->quotes = 0;
	new->block = ib[1];
	new->type = 0;
	new->category = 0;
	new->is_expand = false;
	new->head = new;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
