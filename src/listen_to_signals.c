/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen_to_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:53:30 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/06 15:09:29 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	listen_signals(void)
{
	if (sig_stat == 130)
	{
		ft_printf("hello there\n");
		sig_stat = 0;
		return (1);
	}
	return (0);
}
