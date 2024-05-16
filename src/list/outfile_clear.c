/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:35:26 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/16 16:49:38 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	outfile_clear(t_outfile **outfile)
{
	t_outfile	*cur;
	t_outfile	*next;

	if (!*outfile)
		return ;
	// ft_printf("outfile in outfile clear = %p (%s)\n", *outfile, (*outfile)->content);
	cur = *outfile;
	while (cur)
	{
		next = cur->next;
		// ft_printf("In outfile clear, cur->content = %s\n", cur->content);
		free(cur->content);
		free(cur);
		cur = next;
	}
	*outfile = NULL;
}
