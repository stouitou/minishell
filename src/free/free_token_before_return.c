/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_before_return.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:27:10 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/29 10:27:49 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_before_return(t_entry *entry, char *err, char *s, int error)
{
	ft_fprintf(2, "%s", err);
	if (s)
		ft_fprintf(2, ": %s", s);
	ft_fprintf(2, "\n");
	entry->status = error;
}
