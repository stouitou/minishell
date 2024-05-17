/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_before_return.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:14:02 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/29 11:07:18 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_before_return(t_entry *entry, char *err, char *str, int error)
{
	ft_fprintf(2, "%s", err);
	if (str)
		ft_fprintf(2, ": %s", str);
	ft_fprintf(2, "\n");
	entry->status = error;
	token_clear(&(entry->token));
}
