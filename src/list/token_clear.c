/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:45:28 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 11:34:36 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_clear(t_token **token)
{
	t_token	*tmp;
	t_token	*next;
	int		i;

	if (!token)
		return ;
	tmp = *token;
	i = 0;
	while (tmp)
	{
		next = tmp->next;
		del_node(&tmp);
		i++;
		tmp = next;
	}
	*token = NULL;
}
