/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fpf_print_prefix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:37:55 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/05 11:16:22 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fpf_print_prefix(int fd, t_print *tab)
{
	char	*prefix;

	prefix = pf_addprefix(tab);
	ft_putstr_fd(prefix, fd);
	free(prefix);
}
