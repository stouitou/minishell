/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_addback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:43:21 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/22 13:08:48 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	files_addback(t_files **file, t_files *new)
{
	t_files	*cur;

	// ft_printf("in addback, new->content = %s\n", new->content);
	if (!file || !new)
		return ;
	if (!*file)
	{
		*file = new;
		return ;
	}
	cur = *file;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}
