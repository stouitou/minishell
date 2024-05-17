/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_addback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:31:15 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/17 12:02:33 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	infile_addback(t_infile **infile, t_infile *new)
{
	t_infile	*cur;
	
	if (!infile || !new)
		return ;
	if (!*infile)
	{
		*infile = new;
		return ;
	}
	cur = *infile;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}
