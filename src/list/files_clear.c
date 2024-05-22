/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:35:26 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/22 13:28:54 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	files_clear(t_files **file)
{
	t_files	*cur;
	t_files	*next;

	if (!*file)
		return ;
	// ft_printf("file in file clear = %p (%s)\n", *file, (*file)->content);
	cur = *file;
	while (cur)
	{
		next = cur->next;
		// ft_printf("In file clear, cur->content = %s\n", cur->content);
		free(cur->content);
		free(cur);
		cur = next;
	}
	*file = NULL;
}
