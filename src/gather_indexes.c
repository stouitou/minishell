/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gather_indexes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:44:52 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/14 15:10:58 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	join_contents(t_entry *entry, t_token *cur, t_token *prev)
{
	char	*new;

	if (!cur->content && !prev->content)
		return ;
	if (!cur)
		return ;
	new = ft_strjoin(prev->content, cur->content);
	if (!new)
	{
		ft_printf("oops\n");
		free_token_and_exit(&(entry->token), ERR_MALLOC, cur->content, EXIT_FAILURE);
	}
	free(prev->content);
	prev->content = NULL;
	cur->content = new;
}
/*
	KEEP QUOTED TYPE OF NEXT NODE IF NECESSARY FOR HERE_DOC DELIMIMTER
	Forgot everything?
	Try : cat << EOF | cat << 'EOF' | cat << ho"la" | cat << "'EOF'"
	with extensions as inputs
*/

void	gather_indexes(t_entry *entry, t_token *cur)
 {
	if (!cur)
		return ;
	while (cur)
	{
		if (cur->prev && cur->prev->index == cur->index)
			join_contents(entry, cur, cur->prev);
		cur = cur->next;
	}
 }

// void	gather_indexes(t_entry *entry, t_token *cur)
//  {
// 	t_token *next;
// 	t_token *prev;

	// print_block(*cur);
// 	if (!cur)
// 		return ;
// 	if (cur->next && ft_strcmp(cur->content, "$") == 0 && cur->next->quotes)
// 	{
		// remove_node(&(entry->token), cur);
// 		prev = cur->prev;
// 		next = cur->next;
// 		if (!prev)
// 			entry->token = next;
// 		else
// 			prev->next = next;
// 		next->prev = prev;
		// ft_printf("in gather indexes cur->content = %s\n", cur->content);
// 		del_node(&cur);
// 		return ;
// 	}
// 	while (cur && cur->next && cur->next->index == cur->index)
// 	{
		// ft_printf("in gather indexes cur->content = %s\n", cur->content);
// 		prev = cur->prev;
// 		next = cur->next;
// 		join_contents(entry, cur, next);
// 		if (!prev)
// 			entry->token = next;
// 		else
// 			prev->next = next;
// 		next->prev = prev;
		// next->next->prev = *cur;
		// ft_printf("next->next = %p\n", next->next);
		// ft_printf("next->next = %s\n", next->next->content);
		// cur->next = next->next;
		// ft_printf("2 in gather indexes cur->content = %s\n", cur->content);
// 		del_node(&cur);
// 	}
	// ft_printf("in gather, cur = %p\n", *cur);
//  }
