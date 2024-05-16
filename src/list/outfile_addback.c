/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_addback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:43:21 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/16 15:32:04 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	outfile_addback(t_outfile **outfile, t_outfile *new)
{
	t_outfile	*cur;

	// ft_printf("in addback, new->content = %s\n", new->content);
	if (!outfile || !new)
		return ;
	if (!*outfile)
	{
		*outfile = new;
		return ;
	}
	cur = *outfile;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}
