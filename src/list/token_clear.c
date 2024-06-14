/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:45:28 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/14 18:19:00 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_clear(t_entry *entry, t_token **token)
{
	t_token	*tmp;
	t_token	*next;

	if (!token || !*token)
		return ;
	tmp = *token;
		tmp = (*token)->head;
	while (tmp)
	{
		next = tmp->prev;
		del_node(tmp);
		// free(tmp->content);
		// tmp->content = NULL;
		// ft_printf("in token clear tmp content = %s\n", tmp->content);
		// free(tmp);
		// tmp = NULL;
		// ft_printf("in token clear tmp = %p\n", tmp);
		tmp = next;
	}
	//entry->token = NULL;
	(void)entry;
}
