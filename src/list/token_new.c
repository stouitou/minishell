/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poriou <poriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:30:54 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/26 08:24:18 by poriou           ###   ########.fr       */
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
	new->head = new;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
