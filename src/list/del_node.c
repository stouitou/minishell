/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:26:04 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/07 12:35:08 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_node(t_token **node)
{
	if (!*node)
		return ;
	// ft_printf("(node)->content in del node = %s\n", (*node)->content);
	free((*node)->content);
	free(*node);
	// ft_printf("in del_node, node = %p\n", *node);
	*node = NULL;
}
