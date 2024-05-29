/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:25:47 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/29 10:08:33 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_error(t_exe *exe, char *msg, char *data, int status)
{
	t_error	error;

	error.msg = msg;
	error.data = data;
	error.status = status;
	exe->error = error;
}
