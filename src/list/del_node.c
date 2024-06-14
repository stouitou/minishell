/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:26:04 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/14 18:16:17 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_node(t_token *node)
{
	if (!node)
		return ;
	// ft_printf("node->content = %s\n", (*node)->content);
	// ft_printf("node = %p\n", *node);
	free(node->content);
	node->content = NULL;
	free(node);
	node = NULL;
	// ft_printf("after, node = %p\n", *node);
}
